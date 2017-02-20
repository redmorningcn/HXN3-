#include <includes.h>
/*
#define		COM_START_CODE		0x55
#define		PC_ADDR				0xaa
#define		HOST_ADDR			0x80
#define		SLAVE_ADDR			0xA1

#define		BROAD_ADDR			0xAF

#define		GET_DIP_PRS			0xc0
#define		SET_DIP_MOD			0xD7
#define		SET_PRS_LIN			0xD6

#define		TEST_COM			0xD4
#define		BROAD_INFO			0x66

#define		INF_HEAD_LEN		5
#define		INF_START_POS		4

typedef	struct	_stcCalDist_
{
	uint32	ModDPR;					//计算余量
	uint32	Dist;					//里程
}stcCalDist;

typedef struct _stcDist_						//油尺
{
	stcCalDist	A_sDist;						//总里程
	stcCalDist	C_sDist;						//分段里程
	stcCalDist	E_sDist;						//自定义里程
	uint32		Rec32;							//预留4字节
	uint16		Speed;							//速度
	uint16		Crc16;							//CRC检验
}stcDist;


uint8		l_DenDataErrFlg = NO_ERROR;
//----------------------------------------------------------------------------
// 功    能：   接收广播的里程数据结构
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
uint8  GetBoardDenData(uint8	*Buf,uint32	RecBufLen,stcDist * sDist)
{
    uint16			CrcCheck;
    uint16			i;
    uint8			StartCode,TargetAddr,SourceAddr,DataLen,DataTyp;
    static			uint32	ErrTimes = 0;
    uint32			FramLen;		   //帧长
	        
	StartCode 	= COM_START_CODE;
	TargetAddr 	= BROAD_ADDR;
	SourceAddr 	= HOST_ADDR;
	DataLen		= sizeof(stcDist)+sizeof(DataTyp);
	DataTyp		= BROAD_INFO;
	
	FramLen 	= DataLen + INF_START_POS + 2;
	
	if(RecBufLen >= FramLen)
    {
	    for(i = 0; i <= RecBufLen - FramLen;i++)
	    {
//	    	SysFastHoldTast();
	    	
			if(	(Buf[i] == StartCode )		&&		
				(Buf[i + 1] == TargetAddr) 	&& 
				(Buf[i + 2] == SourceAddr) 	&& 
				(Buf[i + 3] == DataLen)  	&&
				(Buf[i + 4] == DataTyp)  )
			{					
				
				memcpy((uint8 *)&CrcCheck,&Buf[FramLen - 2],sizeof(CrcCheck));
				
				if(CrcCheck == GetCrc16Check(&Buf[i],FramLen - 2))
				{
					memcpy((uint8 *)sDist,&Buf[i+INF_HEAD_LEN],sizeof(stcDist));

					l_DenDataErrFlg = NO_ERROR;
					
					ErrTimes = 0;	
									
					return 1;
				}
			}
	    }
    }    
	
	ErrTimes++;
	
	if(ErrTimes > 3)
	{
		l_DenDataErrFlg = ERROR;
	}
	
    return	0;											//接收失败
}
stcDist	 	g_sDist;
uint8 		l_ComErrFlg = NO_ERROR;



void	ComResetSysDeal(char *buf,uint32 len)	
{
	char	string[] = "pragram system";	
	char	*p;
	static	uint32	times = 0;

	//buf[sizeof(buf) - 1] = '\0';
	p = strstr(buf,string);

	if(p != 0)
	{
		times++;
		if(times > 2)
		{
			printfcom0("\r\n 系统重启");
			while(1);	
		}

		printfcom0("\r\n 系统重启 %d",times);
	}
	else
	{
		times = 0;
	}
}

//----------------------------------------------------------------------------
// 功    能：   取串口1的数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
uint8  GetCOM1Data_S(void)
{
	uint8					Buf[128];									
	static	uint32			Time = 0;
	static	uint32			Times = 0;
	uint32					RecBufLen;		
	static	uint32			ErrTimes = 0;			
	
	if(GetSysTime() - Time > 100 )						//0.25秒
	{
		if(Times++)
		{
			RecBufLen = ReadCOM3(Buf,128);	    

			if( RecBufLen )
			{
				ErrTimes = 0;
				//时间设置
				ComSetTime((char *)Buf,RecBufLen);
				//下载命令,如满足要求，系统重启		
				ComResetSysDeal((char *)Buf,RecBufLen);
				//取数
				if(GetBoardDenData(Buf,RecBufLen,(stcDist *)&g_sDist))
				{
					char	strtmp[12] = "\r\n OK ";
				   	//简单应答
					SendCOM3(strtmp,strlen(strtmp));

					l_ComErrFlg = NO_ERROR;
					return	1;
				}
		    }
		    
		    ErrTimes++;
		    
		    if(ErrTimes > 6)							//通信故障
		    {
		    	g_sDist.Speed = 0;
		    	if(ErrTimes % 4 == 0)
		    	{}
				
		    	l_ComErrFlg = ERROR;
		    }
	    }
	    
	    Time = GetSysTime();
    }
    
    return	0;
}

uint16 	GetTrainSpeed(void)
{
	return	g_sDist.Speed;
}

uint32 	GetTrainKm(void)
{
	return	g_sDist.A_sDist.Dist;
}

uint32	GetSpeedComErrFlg(void)
{
	return	l_ComErrFlg;	
}

void	COM3Task(void)
{
	GetCOM1Data_S();
}
*/
