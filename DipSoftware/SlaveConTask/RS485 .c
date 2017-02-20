#include <includes.h>
#include	"Card.h"
#include	"OperateCard.h"

//思维公司和南车公司通讯协议
#define         FRAM_HERD0     		0x7c         	//报文头			
#define     	HOST_ID      		0x11			//上位机地址	  		   
#define   		DEVICE_ID0      	0x51			//本机地址0	
#define         FRAM_END0     		0x7e         	//报文尾
#define			HOST_CODE_FLG		0x0c	
#define			DEVICE_CODE_FLG		0x8c
#define			ID_NUM				0x01
//#define			ID_NUM				0x02	
#define			CODE_TYPE			0x01	
#define			READ_REC_CODE		0x02
#define			DATA_TYPE			0x01

#define			HDLC_CODE0			0x7d
#define			HDLC_CODE1			0x5c
#define			HDLC_CODE2			0x5e
#define			HDLC_CODE3			0x5d


//extern	uint8	g_MastSlaveFlg;
			
//----------------------------------------------------------------------------
// 名    称：   
// 功    能：   接
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
uint8  RecData(uint8	*RecBuf,uint8 RecLen,uint8	*DataBuf,uint8	DataLen)
{
    uint16		i,j,k;
    uint8		Tmp;
    uint16		RecCRC16,Check16;
    uint8		HostCode,CodeType;
	
//	uint8		DeviceID;
//	uint8   	HostID;
	uint16		RecDataLen;
	uint16		ReCopyTime;
	uint8		IDNum;
	
//	HostID = HOST_ID;

//	DeviceID = DEVICE_ID0;
  
  	ReCopyTime = 0;
	for(j = 0;j < RecLen -1 - ReCopyTime ;j++ )											//去7d5c
	{
		if(	RecBuf[j] 	== HDLC_CODE0   					
			&& 	((RecBuf[j+1]) == HDLC_CODE1)
		   )
		{
			RecBuf[j] = FRAM_HERD0;														//7c
			for(k = j+1;k < RecLen-1; k++)
			{
				Tmp	 = RecBuf[k+1];
				
				RecBuf[k] = Tmp;
			}
			ReCopyTime++;
		}
		
		if(	RecBuf[j] 	== HDLC_CODE0   												//去7d5e
			&& 	((RecBuf[j+1]) == HDLC_CODE2)
			)
		{
			RecBuf[j] = FRAM_END0;														//7e
			for(k = j+1;k < RecLen-1; k++)
			{
				Tmp	 = RecBuf[k+1];
				
				RecBuf[k] = Tmp;
			}
			ReCopyTime++;			
		}
		
		if(	RecBuf[j] 	== HDLC_CODE0   												//去7d5d
			&& 	((RecBuf[j+1]) == HDLC_CODE3)
			)
		{
			RecBuf[j] = HDLC_CODE0;														//7d
			for(k = j+1;k < RecLen; k++)
			{
				Tmp	 = RecBuf[k+1];
				
				RecBuf[k] = Tmp;
			}
			ReCopyTime++;
		}					
	}
	
    for(i = 0; i < RecLen - 10;i++)												       //循环遍历
    {
		if(		((RecBuf[i+0]) == FRAM_HERD0)  				//报头
			&&	((RecBuf[i+1]) == HOST_ID) 
			&&	((RecBuf[i+2]) == DEVICE_ID0)  	 
		  )											
		{		
				
			RecDataLen  = RecBuf[i+3];
			RecDataLen  += RecBuf[i+4]*256;
			
			DataLen    =  RecDataLen;
			HostCode   =  RecBuf[i+5];
			IDNum	   =  RecBuf[i+6];
			CodeType   =  RecBuf[i+8];
						
			if(		(	HostCode 	!= HOST_CODE_FLG) 
				||	(   IDNum       != ID_NUM   )
				||  (   CodeType    != CODE_TYPE   )
				)
			 {	
			 	i = i + 8;															//地址不对或帧尾错误，跳过此帧
			 	continue;
			 }
									
			RecCRC16 = ((uint16)RecBuf[i+5+RecDataLen]) *256 + RecBuf[i+6+RecDataLen];	//校验	
	
			Check16 = GetCrc16Check(&RecBuf[i+5],DataLen);	
						
			if(		
					RecCRC16  ==  Check16 		
			  )
			{
				 memcpy(DataBuf,&RecBuf[i+5],DataLen);				//数据拷贝
				 
				 return	1;
			}
		}
	}
   	
   	DataLen = 0;
    return	0;
}


#define		OIL_DATA_LEN	16
#define		ATHER_DATA_LEN	4
void	Sendrs485(uint8	*DataBuf,uint32	DataLen,uint8	CheckNum)
{
	uint8	SndBuf[256] = {0};
	uint8	SndBufTmp[256] = {0};
//	uint8	SumCheck8;
	uint16	Crc16;
	uint16	AddHeadNum;
	uint16	i;
//	uint8	Tmp;
	uint8	ByteStation;
//	static	uint8 	FramNum =0;			//序号
	uint8	DeviceID;
//	static	uint8	Test = 0;
	
	DeviceID = DEVICE_ID0;
		
	ByteStation = 0;
	SndBuf[ByteStation++] = FRAM_HERD0;
	SndBuf[ByteStation++] = HOST_ID;
	SndBuf[ByteStation++] = DeviceID;	 
	SndBuf[ByteStation++] = DataLen+ATHER_DATA_LEN;	
	SndBuf[ByteStation++] = 0;	
	SndBuf[ByteStation++] = DEVICE_CODE_FLG;	
	SndBuf[ByteStation++] = ID_NUM;
	
	memcpy(&SndBuf[ByteStation],DataBuf,DataLen);
	
	SndBuf[ByteStation+DataLen+0] = DATA_TYPE;
	//SndBuf[ByteStation+DataLen+0] = Test++;			//数据备用起始位置
	SndBuf[ByteStation+DataLen+1] = CheckNum;
		
	Crc16 = GetCrc16Check(&SndBuf[1+4],2+DataLen+2);//枕头（1）+帧长度前包字节（4）
	
//	SndBuf[ByteStation+DataLen+2] = Crc16;
//	SndBuf[ByteStation+DataLen+3] = Crc16>>8;
	SndBuf[ByteStation+DataLen+3] = Crc16;
	SndBuf[ByteStation+DataLen+2] = Crc16>>8;
	
//////////////////////////////////////////////////////////
	SndBufTmp[0] = SndBuf[0];						//准备数据发送
//	SndBufTmp[1] = SndBuf[1];
//	SndBufTmp[2] = SndBuf[2];						//准备数据发送
//	SndBufTmp[3] = SndBuf[3];
//	SndBufTmp[4] = SndBuf[4];
		
	
	AddHeadNum = 0;
	for(i = 1; i< ByteStation+DataLen+4;i++ )				//数据，补移位 FRAM_HERD0
	{
		if(SndBuf[i] == FRAM_HERD0)					//7c
		{
			SndBufTmp[i+AddHeadNum] = HDLC_CODE0;
			AddHeadNum++;
			SndBufTmp[i+AddHeadNum] = HDLC_CODE1;
		}
		else if(SndBuf[i] == FRAM_END0)				//7e
		{
			SndBufTmp[i+AddHeadNum] = HDLC_CODE0;
			AddHeadNum++;
			SndBufTmp[i+AddHeadNum] = HDLC_CODE2;
		}
		else if(SndBuf[i] == HDLC_CODE0)			//7d		
		{
			SndBufTmp[i+AddHeadNum] = HDLC_CODE0;
			AddHeadNum++;
			SndBufTmp[i+AddHeadNum] = HDLC_CODE3;
		}	
		else
		{
			SndBufTmp[i+AddHeadNum] = SndBuf[i];
		}
	}

	SndBufTmp[ByteStation + DataLen+4 + AddHeadNum] = FRAM_END0;
			
	SendCOM3(SndBufTmp,ByteStation+DataLen+4 +AddHeadNum + 1);  // 数据标号+1=数据长度		
}


//模拟数据发送
void	MoldeSendrs485(void)
{
	uint8	SndBuf[100] = {0};
	uint8	SndBufTmp[100] = {0};
//	uint8	SumCheck8;
	uint16	Crc16;
	uint16	AddHeadNum;
	uint16	i;
//	uint8	Tmp;
	uint8	ByteStation;
	static	uint8 	FramNum =0;			//序号
//	uint8	DeviceID;
//	static	uint8	Test = 0;
	
//	DeviceID = DEVICE_ID0;
	
	ByteStation = 0;
	SndBuf[ByteStation++] = FRAM_HERD0;
	SndBuf[ByteStation++] = 0x11;
	SndBuf[ByteStation++] = 0x51;	 
	SndBuf[ByteStation++] = 0x06;	
	SndBuf[ByteStation++] = 0;	
	SndBuf[ByteStation++] = 0x0c;	
	SndBuf[ByteStation++] = 0x01;
	
	SndBuf[ByteStation++] = FramNum++;
	SndBuf[ByteStation++] = 0x01;
	SndBuf[ByteStation++] = 0;
	SndBuf[ByteStation++] = 0;
	//memcpy(&SndBuf[ByteStation],DataBuf,DataLen);
	
	//SndBuf[ByteStation+DataLen+0] = DATA_TYPE;
	//SndBuf[ByteStation+DataLen+0] = Test++;			//数据备用起始位置
	//SndBuf[ByteStation+DataLen+1] = CheckNum;
		
	Crc16 = GetCrc16Check(&SndBuf[1+4],0x06);//枕头（1）+帧长度前包字节（4）
	
//	SndBuf[ByteStation+DataLen+2] = Crc16;
//	SndBuf[ByteStation+DataLen+3] = Crc16>>8;
	
	SndBuf[ByteStation++] = Crc16>>8;
	SndBuf[ByteStation++] = Crc16;
	
//////////////////////////////////////////////////////////
	SndBufTmp[0] = SndBuf[0];						//准备数据发送
//	SndBufTmp[1] = SndBuf[1];
//	SndBufTmp[2] = SndBuf[2];						//准备数据发送
//	SndBufTmp[3] = SndBuf[3];
//	SndBufTmp[4] = SndBuf[4];
		
	
	AddHeadNum = 0;
	for(i = 1; i< ByteStation;i++ )				//数据，补移位 FRAM_HERD0
	{
		//SndBufTmp[i+AddHeadNum] = SndBuf[i];
		
		if(SndBuf[i] == FRAM_HERD0)					//7c
		{
			SndBufTmp[i+AddHeadNum] = HDLC_CODE0;
			AddHeadNum++;
			SndBufTmp[i+AddHeadNum] = HDLC_CODE1;
			//AddHeadNum++;
		}
		else if(SndBuf[i] == FRAM_END0)				//7e
		{
			SndBufTmp[i+AddHeadNum] = HDLC_CODE0;
			AddHeadNum++;
			SndBufTmp[i+AddHeadNum] = HDLC_CODE2;
			//AddHeadNum++;
		}
		else if(SndBuf[i] == HDLC_CODE0)			//7d		
		{
			SndBufTmp[i+AddHeadNum] = HDLC_CODE0;
			AddHeadNum++;
			SndBufTmp[i+AddHeadNum] = HDLC_CODE3;
			//AddHeadNum++;
		}	
		else
		{
			SndBufTmp[i+AddHeadNum] = SndBuf[i];
		}
	}

	SndBufTmp[ByteStation +AddHeadNum] = FRAM_END0;

	
//    WriteEN_TAX(1);	
//    WriteEN_TAX(1);		
	SendCOM3(SndBufTmp,ByteStation+AddHeadNum + 1);  // 数据标号+1=数据长度
//	WriteEN_TAX(0);			
}


#define		BUF_LEN		256

uint8	g_NoRs485ComFlg = 0;
//extern	uniRs485DataBuf g_uRs485Data;
//----------------------------------------------------------------------------
// 名    称：   void  RecTAX2Info(void)
// 功    能：   接收TAX2信息。
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
void  RecRs485(void)
{
	uint8		RecBuf[BUF_LEN] = {0};								//接收缓冲区
	uint8		DataBuf[BUF_LEN/2] = {0};								//
//	uint8		SendOilBuf[sizeof(stcFlshRec)];
	static		uint32		Time = 0;
//	uint32		i,j;
//	static	  uint32	TestTmp = 0;
	static	  uint8		LifeInfo = 0;
	uint8		HostCodeFlg;		
//	uint8		LifeInfo;
	uint8		CodeType;	
	uint8		IDNum;		
	uint32		RecLen;		
	uint32		DataLen;		   
	uint32		FlshRec;
			
			
	if( GetCom3FramRecEndFlg() == 1)								//有新的帧尾，进行数据处理
	{
		RecLen 	= ReadCOM3(RecBuf,sizeof(RecBuf));
		
		ClearCom3FramRecEndFlg();									//清标志，可重新取数
		
		if(!RecData(RecBuf,RecLen,DataBuf,DataLen))				//接受数据
		{
			//printfcom0("\r\n RS485数据接收失败!");
		}
		else
		{
			//printfcom0("\r\n RS485数据接收成功!");

			//////////////////////////////对数据解析
			HostCodeFlg = DataBuf[0];
			IDNum		= DataBuf[1];
			LifeInfo 	= DataBuf[2];
			CodeType 	= DataBuf[3];

			Time = GetSysTime();
			
//			//printfcom0("\r\n 数据 %x,%x,%x,%x",HostCodeFlg,IDNum,LifeInfo,CodeType);
			
			if( 	HostCodeFlg == HOST_CODE_FLG 
				&&	IDNum		== ID_NUM
				&&	CodeType	== CODE_TYPE
			  )
			{			

				FlshRec = g_CurFlshRecNum-1;				

				if(g_CurFlshRecNum)
				{
					ReadFlshRec((stcFlshRec *)RecBuf,FlshRec);
				}
				
				Sendrs485(RecBuf,sizeof(stcFlshRec),LifeInfo);	//发送数据			
				
				g_NoRs485ComFlg = 0;							//置通讯标志	通讯成功 
			}
			else if( 	HostCodeFlg == HOST_CODE_FLG 
			&&	IDNum		== ID_NUM
			&&	CodeType	== READ_REC_CODE
		 	 )
			 {
			 	 memcpy((uint8 *)&FlshRec,&DataBuf[4],sizeof(FlshRec));
				 
				if(g_CurFlshRecNum)
				{
					ReadFlshRec((stcFlshRec *)RecBuf,FlshRec);
				}
				
				Sendrs485(RecBuf,sizeof(stcFlshRec),LifeInfo);	//发送数据			
				
				g_NoRs485ComFlg = 0;							//置通讯标志	通讯成功 

			 }
		}
	}
	
	if(GetSysTime() - Time > 600)								//600ms无通讯，退出
	{
		g_NoRs485ComFlg = 1;
	}
}

//串口1的485通信任务
void	COM1RS485Task(void)
{
	static	uint32	 Time;
//	RecRs485();
	if(GetSysTime() - Time > 100)	
	{
		MoldeSendrs485();
		Time = GetSysTime();
	}
}



