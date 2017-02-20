////#include  	"config.h"   
////#include	"string.h"
////#include	"Globe.h"
////#include	"HardDrive.h"
////#include	"CpuDrive.h"
////#include	"FramStore.h"
////#include	"Tax2.h"
////#include	"DipMath.h"
////#include	"SysDeal.h"
////#include	"DieselSpeed.h"
//
#include <includes.h>
#include "tmp.h"
//

#define		STORE_REC_TIME	60


uint8	GetStoreTime(void)
{
	stcSysRunPara 	sSysRunPara;

	if(GetSysRunPara((stcSysRunPara * )&sSysRunPara))
	{
		if(sSysRunPara.StoreTime)
		{
			//printfcom0("\r\n sSysRunPara.StoreTime %d",sSysRunPara.StoreTime);
			return	sSysRunPara.StoreTime;
		}	
	}

	//printfcom0("\r\n STORE_REC_TIME %d",sSysRunPara.StoreTime);
	return	STORE_REC_TIME;
}




//
//uint32			l_StoreDivide = 1;
//
///*
//uint32			l_StoreCnt;				//流水号				
//uint8			l_RecTypCod;       		//记录类型          	1   数据类型（开机、上班卡、下班卡、数据记录）
//uint8			l_DriverUnitNum[2];  	//司机单位编号      	2   //用来唯一确定司机
//uint32			l_MstLocoPower;        	//主机车功率          	2   外接设备测量
//uint32			l_SlvLocoPower;        	//从机车功率          	2   外接设备测量
//uint16 			l_MstDip;           	//主机油量          	2   主油尺油量(主从机级联时为主机油量,否则为本机车油量)
//uint16 			l_SlvDip;           	//从机油量          	2   主油尺油量(主从机级联时为从机油量,否则此油量值为空)
//uint16			l_MstDip1Prs;        	//压强            		2   主机油尺1压强值
//uint16			l_MstDip2Prs;        	//压强            		2   主机油尺2压强值
//uint16			l_SlvDip1Prs;       	//压强            		2   从机油尺1压强值
//uint16 			l_SlvDip2Prs;       	//压强            		2   从机油尺2压强值
//uint16			l_MstDensity;			//密度					2	主机燃油密度
//uint16			l_SlvDensity;			//密度					2	从机燃油密度
//uint32			l_GpsLongitude;			//经度					4	地理经度
//uint32			l_GpsLatitude;			//纬度					4	地理纬度
//uint16			l_GpsHeight;			//高度					4	地理高度
//uint16			l_MstEngRotSpd;			//主机柴油机转速		2	主机柴油机转速
//uint16			l_SlvEngRotSpd;			//从机柴油机转速		2	从机柴油机转速
//uint16 			l_JcRealType;			//机车型号				2   外部设置的机车型号
//uint16 			l_JcRealNo;				//机车编号				2   外部设置的机车编号
//uint8			l_ErrorCode;			//故障代码				1   0~255
//uint8 			l_DipValChgState;  		//油量变化状态   		1   油量变化情况分：两油尺增加/减小、变化平稳、轻微波动、剧烈波动
//uint8			l_MstDipTemp;			//温度					1	主机温度
//uint8			l_OilBoxModel;			//油箱模型代码			1	从机温度		
//
//
////-------------------------------------------------------------------------------
////函数名称:        void  ReadyStoreData(void)
////函数功能:        准备存储用的数据
////入口参数:        无
////出口参数:         
////函数调用:			
////-------------------------------------------------------------------------------
//void  ReadyStoreData(void)
//{
//	l_StoreCnt 			= g_CurFlshRecNum;
//	l_MstDip1Prs		= GetDip1Prs();
//	l_MstDip2Prs		= GetDip2Prs();	
//	l_MstDipTemp		= GetDipTmp();
//	l_DipValChgState	= GetPrsChgState();
//	l_MstDip			= g_DipVal;
//	l_ErrorCode			= GetStoreErrTypCod();
//	l_RecTypCod			= GetStoreEvtTypCod();
//	l_MstEngRotSpd		= GetDieselSpeed();	
//	l_OilBoxModel		= GetOilBoxCod();	
//}
//*/
//
//stcLogZone		l_sLogZone;
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void  StoreLog(void) 	
////函数功能:             存日志文件
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//void  StoreLog(void) 	
//{
//	static	stcFlshRec		sFlshRec;										//Flsh记录
//	static	stcDeviceInfo	sDeviceInfo;
//	
//	uint16			CrcCheck;		
//	uint16			DriveNum = 0xffff;		
//	
//	ReadCurFlshRec((stcFlshRec *)&sFlshRec);
//	
//	ReadHostInfo((stcDeviceInfo *)&sDeviceInfo);
//	
//	CrcCheck = GetCrc16Check((uint8 *)&sDeviceInfo,sizeof(stcDeviceInfo) - 2);
//
//	if(CrcCheck != sDeviceInfo.CrcCheck)
//	{
//		DriveNum = sDeviceInfo.DeviceNum;
//		
//		////printfcom0("\r\n机车出厂信息设置错误或没有设置！");
//	}
//	
//	ReadLogZone((stcLogZone *)&l_sLogZone);
//	
//	CrcCheck = GetCrc16Check((uint8 *)&l_sLogZone,sizeof(stcLogZone) - 2);
//	
//	if(CrcCheck != l_sLogZone.CrcCheck)
//	{
//		l_sLogZone.Times = 0;
//		
//		//printfcom0("\r\n日志文件错误！");
//	}
//
//	l_sLogZone.sLog[l_sLogZone.Times].StoreCnt 		= sFlshRec.StoreCnt;
//	l_sLogZone.sLog[l_sLogZone.Times].ErrorCode		= sFlshRec.ErrorCode;
//	l_sLogZone.sLog[l_sLogZone.Times].RecTypCod	 	= sFlshRec.RecTypCod;
//	l_sLogZone.sLog[l_sLogZone.Times].LocoTyp[0]	= sFlshRec.LocoTyp;
//	l_sLogZone.sLog[l_sLogZone.Times].LocoTyp[1]	= sFlshRec.E_LocoTyp;
//	l_sLogZone.sLog[l_sLogZone.Times].LocoNum[0]	= sFlshRec.LocoNum[0];
//	l_sLogZone.sLog[l_sLogZone.Times].LocoNum[1]	= sFlshRec.LocoNum[1];	
//	l_sLogZone.sLog[l_sLogZone.Times].DriveNum		= DriveNum;
//	
//	l_sLogZone.Times++;
//	
//	CrcCheck = GetCrc16Check((uint8 *)&l_sLogZone,sizeof(stcLogZone) - 2);
//	l_sLogZone.CrcCheck = CrcCheck;
//	
//	StoreLogZone((stcLogZone *)&l_sLogZone);
//}
//
////-------------------------------------------------------------------------------
////函数名称:        uint32  GetRecNumAddr(uint32 FlshRecNum)
////函数功能:        取记录流水号地址
////入口参数:        记录流水号
////出口参数:        记录流水号在FLASH中的地址
////函数调用:			
////-------------------------------------------------------------------------------
uint32  GetRecNumAddr(uint32 FlshRecNum)
{
    //return  (uint32)(FLSH_PROTECT_SIZE + ((FlshRecNum * sizeof(stcFlshRec)) % (FLSH_MAX_SIZE - FLSH_PROTECT_SIZE)));  //溢出问题					
    return  (uint32)(((FlshRecNum * sizeof(stcFlshRec)) % FLSH_MAX_SIZE));  //溢出问题					
}
//
//#define     FREQ_DOWN_STATE     1
//#define     FREQ_WAVE_STATE     2
//#define     FREQ_LAG_WAVE_STATE 3
//#define     FREQ_UP_STATE       4           		//频率变化状态
//#define     FREQ_STOP_STATE     5
////-------------------------------------------------------------------------------
////函数名称:        uint32  MathStoreDivede()
////函数功能:        取记录流水号地址
////入口参数:        记录流水号
////出口参数:        记录流水号在FLASH中的地址
////函数调用:			
////-------------------------------------------------------------------------------
//void	MathStoreDivide(void)
//{
//	static	uint32	Time = 0 ;
//	static	uint8	LstDipValChgState = FREQ_WAVE_STATE;
//	static	uint32	Timer = 0;
//	uint8	DipValChgState = FREQ_WAVE_STATE;
//	
//	if(GetSysTime() - Timer > 100)
//	{
//		Timer = GetSysTime();
//		
//		DipValChgState = GetPrsChgState();
//		
//		/*
//		if( DipValChgState == FREQ_UP_STATE)
//		{
//			l_StoreDivide = 12;
//			Time = 0;
//		}
//		
//		if((DipValChgState == FREQ_STOP_STATE) && ((LstDipValChgState == FREQ_WAVE_STATE) || (LstDipValChgState == FREQ_LAG_WAVE_STATE)))
//		{
//			l_StoreDivide = 12;
//			Time = 0;
//		}
//
//		if(((DipValChgState == FREQ_WAVE_STATE) || (DipValChgState == FREQ_LAG_WAVE_STATE)) && (LstDipValChgState == FREQ_STOP_STATE))
//		{
//			l_StoreDivide = 12;
//			Time = 0;
//		}			
//		*/
//		if(l_StoreDivide == 12)
//		{
//			Time++;
//			
//			if( Time > 60)
//			{
//				l_StoreDivide = 1;
//			}
//		}
//		
//		LstDipValChgState = DipValChgState;
//	}
//}
//
////-------------------------------------------------------------------------------
////函数名称:        uint32  GetStoreDivede()
////函数功能:        取记录流水号地址
////入口参数:        记录流水号
////出口参数:        记录流水号在FLASH中的地址
////函数调用:			
////-------------------------------------------------------------------------------
//uint32  GetStoreDivide()
//{
//    return  l_StoreDivide;  //溢出问题					
//}
//    
//uint8	l_FlshStoreErrEvtFlg = RIGHT_DATA;
//#define		FLSH_WRT_ERR_EVT	32
//
//extern	uint8	ReadFlshRec(stcFlshRec * sFlshRec,uint32	FlshRecNum);
//extern	uint8	JudgeLstFlsh(void);
//
//extern	uint16	GetReviseHight(void);
//

#define		START_EVT		31	
uint8	 GetRecTyp(void)
{
	static uint8	times = 0;
	
	if(times == 0)	 
	{
		times++;	
		return	START_EVT;
	}

	return	RIGHT_DATA;
}

uint32	GetMyMstLocoPower(void)
{
	return	1;
}


#define		SOFT_VER	10
////-------------------------------------------------------------------------------
////函数名称:        void  StoreData(void)
////函数功能:        存储数据
////入口参数:        无
////出口参数:         
////函数调用:			
////-------------------------------------------------------------------------------
void  StoreData(void)
{	
	uint32			FlshAddr;										//Flash存储地址
	stcFlshRec		sFlshRec={0};									//Flsh记录
	stcTime			sTime;											//系统时间
	stcFixInfo 		sFixInfo;			

	g_CurFlshRecNum 	= GetCurFlshRecNum();
	sFlshRec.StoreCnt	= g_CurFlshRecNum;						 

	sFlshRec.RecTypCod	= GetRecTyp();

	sFlshRec.Myspeed1	= GetMySpeed1();
	sFlshRec.Myspeed2	= GetMySpeed2();

	sFlshRec.MstDip		= g_DipVal;
	
	sFlshRec.MyKileMeter= GetMyKileMeter();

	sFlshRec.MyMstLocoPower= GetMyMstLocoPower(); 

	sFlshRec.Myhig1		= GetDip1Hig();
	sFlshRec.Myhig2		= GetDip2Hig();	

	ReadTime((stcTime *)&sTime);
	sFlshRec.MyYear		= sTime.Year;			
	sFlshRec.MyMonth	= sTime.Month;			
	sFlshRec.MyData		= sTime.Date;			
	sFlshRec.MyHour		= sTime.Hour;			
	sFlshRec.MyMinute	= sTime.Min;			
	sFlshRec.MySecond	= sTime.Sec;

	sFlshRec.MstDensity = GetDensityVal();

	sFlshRec.MyAddspeed	= GetAddSpeed();

	sFlshRec.MyDip		= g_DipVal;

	sFlshRec.MyEngRotSpd= GetMyEngRotSpd();

	ReadFixInfo((stcFixInfo *)&sFixInfo);
	sFlshRec.JcRealType	= sFixInfo.LocoTyp + sFixInfo.E_LocoTyp*256 ;
	memcpy((uint8 *)&sFlshRec.JcRealNo,(uint8 *)&sFixInfo.LocoNum,sizeof(sFlshRec.JcRealNo));

	sFlshRec.ErrNum		= GetHostErrNum();
	sFlshRec.ErrorCode	= GetErrorCode();

	sFlshRec.MyLocoWorkState = GetMyLocoWorkState();

	sFlshRec.OilBoxModel= GetOilBoxCod();

	sFlshRec.SoftVes 	= SOFT_VER;


	sFlshRec.MyDip1Tmp = GetMyDip1Tmp();	  		//油尺1温度
	sFlshRec.MyDip2Tmp = GetMyDip2Tmp();			//油尺2温度
		
	sFlshRec.MyDip1Err = GetMyDip1Err();
	sFlshRec.MyDip2Err = GetMyDip2Err();
		
	sFlshRec.MyDip1Den = GetMyDip1Den();
	sFlshRec.MyDip2Den = GetMyDip2Den();

	sFlshRec.CrcCheck = GetCrc16Check((uint8 *)&sFlshRec,sizeof(sFlshRec) - 2);

  	FlshAddr = GetRecNumAddr( g_CurFlshRecNum );
	if(!WriteFlsh(FlshAddr, (uint16 *)&sFlshRec, sizeof(sFlshRec)))
	{}
	ReadFlshRec((stcFlshRec *)&sFlshRec,g_CurFlshRecNum);
	printfcom0("\r\n stcFlshRec.StoreCnt %d",sFlshRec.StoreCnt);

	g_CurFlshRecNum++;
	
	StoreCurFlshRecNum( g_CurFlshRecNum );           		//把流水号存入铁电
}

//#define	STORE_REC_ONE_SEC	1
////-------------------------------------------------------------------------------
////函数名称:        void  StoreDataPro(void)
////函数功能:        存储数据
////入口参数:        无
////出口参数:         
////函数调用:			
////-------------------------------------------------------------------------------
void  StoreDataPro(void)
{
	static	uint32	Time = 0;	
	
	if(
			#ifndef	STORE_REC_ONE_SEC	
	(GetSysTime() - Time > (100 * GetStoreTime() )) &&  
			#endif	    
	(GetSysTime() > 30*100) && (GetSysTime() - Time > 100)
	  )	
	{
		StoreData();
		
		Time = GetSysTime();
	}
}
//
//
////-------------------------------------------------------------------------------
////函数名称:        	uint8	GetFlshStoreErrEvtFlg(void)
////函数功能:       	存储流水任务
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
//uint8	JudgeLstFlsh(void)
//{
//	static	uint32	Times = 0;
//	stcFlshRec		LstsFlshRec;
//	uint16			CrcCheck;
//	uint8			Flg;
//
//	Times++;
//	
//	Flg = TRUE;
//	
//	if(g_CurFlshRecNum)
//	{
//		if(ReadFlshRec((stcFlshRec *)&LstsFlshRec,g_CurFlshRecNum - 1))
//		{	
//			CrcCheck = GetCrc16Check((uint8 *)&LstsFlshRec,sizeof(stcFlshRec) - 2);
//
//			if((CrcCheck != LstsFlshRec.CrcCheck))
//			{
//				l_FlshStoreErrEvtFlg = FLSH_WRT_ERR_EVT;
//
//				if((Times == 1) ) 
//				{
//					Flg = FALSE;
//				}
//			}
//		}
//	}	
//	
//	return	Flg;
//}
//
////-------------------------------------------------------------------------------
////函数名称:        	uint8	GetFlshStoreErrEvtFlg(void)
////函数功能:       	存储流水任务
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
//uint8	GetFlshStoreErrEvtFlg(void)
//{
//	return	l_FlshStoreErrEvtFlg;
//}
//
//
////-------------------------------------------------------------------------------
////函数名称:        	void	StoreRecTask(void)
////函数功能:       	存记录任务
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
void	StoreRecTask(void)
{
	StoreDataPro();							//存数据进程
}
//
//#define		FLSH_WRT_ERR_EVT	32
////-------------------------------------------------------------------------------
////函数名称:        	stcFlshRec	ReadFlshRec(uint32	FlshRecNum)
////函数功能:       	读指定流水号的FLSH记录
////入口参数:        	无
////出口参数:      	指定流水号的Flsh记录
////-------------------------------------------------------------------------------
uint8	ReadFlshRec(stcFlshRec * sFlshRec,uint32	FlshRecNum)
{
	uint32		FlshAddr;
	//uint16		CrcCheck;
	
	FlshAddr = GetRecNumAddr( FlshRecNum );						
	
	if(ReadFlsh(FlshAddr,(uint16 *)sFlshRec,sizeof(stcFlshRec)))
	{
	/*
		CrcCheck = GetCrc16Check((uint8 *)sFlshRec,sizeof(stcFlshRec) - 2);
		
		if(CrcCheck != sFlshRec->CrcCheck)
		{
			if(sFlshRec->RecTypCod == RIGHT_DATA)
			{
				sFlshRec->RecTypCod = FLSH_WRT_ERR_EVT;
			}
			
			CrcCheck = GetCrc16Check((uint8 *)sFlshRec,sizeof(stcFlshRec) - 2);

			sFlshRec->CrcCheck = CrcCheck;
		}
	*/	
		return 1;
	}
	
	return	0;
}
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void  ShowFlshRec(stcFlshRec sDip) 
////函数功能:             将记录转变为比较容易读的格式
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
//void  ShowFlshRec(stcFlshRec sDip) 
//{
//	uint8       Second,Minute,Data,Mouth,Hour;
//	uint16      RelSpeed;
//	uint32      Time;
//	uint16		CrcCheck;				
//	
//	int16 		MstDip1Prs;
//	int16 		MstDip2Prs;	
//	int8 		DipValChgState;
//	int16 		MstDip;
//	int16 		SlvDip;
//	int8 		ErrorCode;
//	int8 		RecTypCod;
//
//	MstDip1Prs  	= sDip.MstDip1Prs;
//	MstDip2Prs		= sDip.MstDip2Prs;	
//	DipValChgState	= sDip.DipValChgState;
//	MstDip			= sDip.MstDip;
//	SlvDip			= sDip.SlvDip;
//	ErrorCode		= sDip.ErrorCode;
//	RecTypCod		= sDip.RecTypCod;
//		
//	CrcCheck = GetCrc16Check((uint8 *)&sDip,sizeof(stcFlshRec) - 2);
//	
//	if(CrcCheck != sDip.CrcCheck)
//	{
//		//printfcom0("\r\n记录校验错误！");   
//	}
//		
//    RelSpeed= (uint16)sDip.RelSpeed[0] + (sDip.RelSpeed[1] &(1))*256;
//    
//	memcpy((uint8 *)&Time,sDip.Time,sizeof(Time));
//
//    Second 	= Time  & (0xff >> 2);
//    Minute 	= (Time >> 6 ) & (0xff >> 2);
//    Hour   	= (Time >> 12) & (0xff >> 3);
//    Data   	= (Time >> 17) & (0xff >> 3);
//    Mouth  	= (Time >> 22) & (0xff >> 4);
//    
//   // //printfcom0("\r\n%u-%u %u:%u:%u,",Mouth,Data,Hour,Minute,Second);
//    //printfcom0("\r\n%u-%u %u:%u:%u,",sDip.MyMonth,sDip.MyData,sDip.MyHour,sDip.MyMinute,sDip.MySecond);   
//    //printfcom0("%u,",RelSpeed);      
//  	//printfcom0("%u,%u,%u,%u,%u,%u,%u",MstDip1Prs,MstDip2Prs,MstDip,SlvDip,DipValChgState,ErrorCode,RecTypCod);
//
//}
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void  PrintfAllFlshRec(void) 
////函数功能:             打印记录
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
//void  PrintfAllFlshRec(void) 
//{
//	uint32	i;
//	uint32	StartFlshRecNum;		
//	uint32	FlshMaxNum;		
//	stcFlshRec	sFlshRec;		
//	
//	FlshMaxNum		= FLSH_MAX_SIZE/sizeof(stcFlshRec);
//	
//	if(g_CurFlshRecNum > FlshMaxNum)
//	{
//		StartFlshRecNum = g_CurFlshRecNum - FlshMaxNum ;
//	}
//	else
//	{
//		StartFlshRecNum = 1;
//	}
//	
//	//printfcom0("\r\n流水号,油尺1,油尺2,油量,显示油量,速度,日期,公里标,故障代码,变化状态\r\n");
//	//printfcom0("\r\nStartFlshRecNum:%u,g_CurFlshRecNum:%u\r\n",StartFlshRecNum,g_CurFlshRecNum);
//	for(i = g_CurFlshRecNum;i >= StartFlshRecNum;i--)			//流水号从最初到最发送记录号
//	{
//		//SysFastHoldTast();
//			
//		ReadFlshRec((stcFlshRec *)&sFlshRec,i);		
//		
//		ShowFlshRec(sFlshRec);									//将记录打印出来
//	}
//}
