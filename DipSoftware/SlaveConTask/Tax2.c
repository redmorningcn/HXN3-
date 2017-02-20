//#include    "config.h" 
//#include    "string.h" 
//#include    "CpuDrive.h" 
//#include    "Globe.h" 
//#include    "Tax2.h" 
//
#include 	<includes.h>
#include    "Tax2.h"

stcTAX2Full     l_sTAX2 = { 0 };                 		//外部缓冲区 放置完整的一幁 TAX2 供外部调用

#define         TAX2_BCK_HEADER     	0x39         	//TAX2协议后部,起始标识
#define         TAX2_BEF_HEADER     	0x38        	//TAX2协议前部,起始标识
//
uint8			l_TaxBefFlg = NO_ERROR;					
uint8			l_TaxBakFlg = NO_ERROR;
//
////----------------------------------------------------------------------------
//// 名    称：   uint8 GetCheckSum(uint8 *Buf uint32 Len)
//// 功    能:    取校验和
//// 入口参数：   Buf：求数组   Len：数组长度
//// 出口参数：   校验和
////----------------------------------------------------------------------------
uint8 GetCheckSum(uint8  Buf[], uint32 Len)
{
    uint32  i;
    uint8   CheckSum = 0;
    
    for(i = 0;i < Len; i++)
    {
        CheckSum += Buf[i];                             //求和
    }
    
    CheckSum = ~CheckSum + 1;                           //取反+1
    
    return  CheckSum;
}

//南瑞
uint8 GetCheckSumNR(uint8  Buf[], uint32 Len)
{
    int32  i;
    int8   CheckSum = 0;
    
    for(i = 0;i < Len; i++)
    {
        CheckSum += Buf[i];                             //求和
    }
    
    if((unsigned char)CheckSum >= 0x80)
    {
    	CheckSum = ~CheckSum + 1 +0x80;                       //取反+1
    }
    else
    {
    	CheckSum = CheckSum;                       	//取反+1
    }
    return  CheckSum;
}

//
////#define		EN_TAX2			P225						//油尺通信控制
////------------------------------------------------------------------------
//// 名    称：   void OpenTax2(void) 
//// 功    能：   打开Tax接收功能
//// 入口参数：   
//// 出口参数：   
////------------------------------------------------------------------------
//void OpenTax2(void) 
//{
////201400
////    IO2DIR_OUT(EN_TAX2);              
////                  					
////	IO2PIN_W(0,EN_TAX2);              					 
//		
////	OpenCOM0Tax(28800);								
//}

////------------------------------------------------------------------------
//// 名    称：   void OpenTax2(void) 
//// 功    能：   打开Tax接收功能
//// 入口参数：   
//// 出口参数：   
////------------------------------------------------------------------------
//void CloseTax2(void) 
//{
////201400
////    IO2DIR_OUT(EN_TAX2);              
//                  					
////	IO2PIN_W(1,EN_TAX2);              					 							
//}
////----------------------------------------------------------------------------
//// 名    称：   uint8  RecTAX2Bak(void)
//// 功    能：   接收TAX2后部分。
//// 入口参数：   无
//// 出口参数：   无
////----------------------------------------------------------------------------
uint8  RecTAX2Bak(uint8	*Buf,uint32	RecBufLen)
{
    uint16		i;
    uint32		SizeofTaxBak;
    
    SizeofTaxBak = sizeof(l_sTAX2.sTAX2Bak);

    if( RecBufLen >= SizeofTaxBak)
    {
	    for(i = 0; i <= (RecBufLen - SizeofTaxBak);i++)
	    {
			if((Buf[i] == TAX2_BCK_HEADER))
			{
				if(Buf[i + SizeofTaxBak - 1] == GetCheckSum(&Buf[i],SizeofTaxBak - 1))
				{
					memcpy((uint8 *)&l_sTAX2.sTAX2Bak,&Buf[i],SizeofTaxBak);

					return	1;								//接收成功，退出
				}
			}
	    }
    }

    return	0;
}
///*
////----------------------------------------------------------------------------
//// 名    称：   uint8  RecTAX2Bak(void)
//// 功    能：   接收TAX2后部分。
//// 入口参数：   无
//// 出口参数：   无
////----------------------------------------------------------------------------
//uint8  RecTAX2Bak(uint8	*Buf,uint32	RecBufLen)
//{
//	uint8		TaxBakBuf[sizeof(l_sTAX2.sTAX2Bak)] = {0}; 
//    uint16		i;
//    uint32		SizeofTaxBak;
//    
//    SizeofTaxBak = sizeof(l_sTAX2.sTAX2Bak);
//
//    if( RecBufLen >= SizeofTaxBak)
//    {
//	    for(i = 0; i <= (RecBufLen - SizeofTaxBak);i++)
//	    {
//			if((Buf[i] == TAX2_BCK_HEADER))
//			{
//				memcpy(TaxBakBuf,&Buf[i],SizeofTaxBak);
//				
//				if(TaxBakBuf[SizeofTaxBak - 1] == GetCheckSum(TaxBakBuf,SizeofTaxBak - 1))
//				{
//					memcpy((uint8 *)&l_sTAX2.sTAX2Bak,TaxBakBuf,SizeofTaxBak);
//										
//					l_TaxBakFlg = 1;
//					return	1;								//接收成功，退出
//				}
//			}
//	    }
//    }
//    
//    l_TaxBakFlg = 0;
//    return	0;
//}
//
//
////----------------------------------------------------------------------------
//// 名    称：   uint8  RecTAX2Bef(void)
//// 功    能：   接收TAX2前部分。
//// 入口参数：   无
//// 出口参数：   无
////----------------------------------------------------------------------------
//uint8  RecTAX2Bef(uint8	*Buf,uint32	RecBufLen)
//{
//    uint8		TaxBefBuf[sizeof(l_sTAX2.sTAX2Bef)] = {0};
//    uint16		i;
//    uint32		SizeofTaxBef;
//    
//    SizeofTaxBef = sizeof(l_sTAX2.sTAX2Bef);
//    
//    if( RecBufLen >= SizeofTaxBef)
//    {
//		for(i = 0; i <= (RecBufLen  - SizeofTaxBef);i++)
//	    {
//			if(Buf[i] == TAX2_BEF_HEADER)
//			{
//				memcpy(TaxBefBuf,&Buf[i],SizeofTaxBef);
//				
//				if(TaxBefBuf[SizeofTaxBef - 1] == GetCheckSum(TaxBefBuf,SizeofTaxBef - 1))
//				{
//					memcpy((uint8 *)&l_sTAX2.sTAX2Bef,TaxBefBuf,SizeofTaxBef);
//										
//					l_TaxBefFlg = 1;
//					return 	1;								//接收成功，退出
//				}
//			}
//		}
//    }    
//	
//	l_TaxBefFlg = 0;
//    return	0;												//接收失败
//}
//*/
////----------------------------------------------------------------------------
//// 名    称：   uint8  RecTAX2Bef(void)
//// 功    能：   接收TAX2前部分。
//// 入口参数：   无
//// 出口参数：   无
////----------------------------------------------------------------------------
uint8  RecTAX2Bef(uint8	*Buf,uint32	RecBufLen)
{
    uint16		i;
    uint32		SizeofTaxBef;
    
    SizeofTaxBef = sizeof(l_sTAX2.sTAX2Bef);
    
    if( RecBufLen >= SizeofTaxBef)
    {
		for(i = 0; i <= (RecBufLen  - SizeofTaxBef);i++)
	    {
			if(Buf[i] == TAX2_BEF_HEADER )
			{
				if(Buf[i + SizeofTaxBef - 1] == GetCheckSum(&Buf[i],SizeofTaxBef - 1))
				{
					memcpy((uint8 *)&l_sTAX2.sTAX2Bef,&Buf[i],SizeofTaxBef);
										
					return 	1;								//接收成功，退出
				}
			}
		}
    }    

    return	0;												//接收失败
}
	
uint8	l_Tax2ComErrFlg = NO_ERROR;
//uint8	l_Tax2BefPackErrFlg = NO_ERROR;
//uint8	l_Tax2BakPackErrFlg = NO_ERROR;
//

uint8	GetTax2BefPackErrFlg(void)
{
	return	l_TaxBefFlg;
}

uint8	GetTax2BakPackErrFlg(void)
{
	return	l_TaxBakFlg;
}

#define		TAX_BUF_LEN		128
////----------------------------------------------------------------------------
//// 名    称：   void  RecTAX2Info(void)
//// 功    能：   接收TAX2信息。
//// 入口参数：   无
//// 出口参数：   无
////----------------------------------------------------------------------------
void  RecTAX2Info(void)
{
	uint8		Buf[TAX_BUF_LEN] = {0};								//接收缓冲区
	uint32		RecLen;				
	static		uint32		Time = 0;
	
	if( GetSysTime() - Time > 100)	
	{
		RecLen 		= 	ReadCOM2(Buf,sizeof(Buf));	

		if(	RecLen)	
		{	
			l_Tax2ComErrFlg = NO_ERROR;
			
			if(RecTAX2Bef(Buf,RecLen))
			{
				l_TaxBefFlg = NO_ERROR;
			}
			else
			{
				l_TaxBefFlg = ERROR;
			}	
									
			if(RecTAX2Bak(Buf,RecLen))		
			{
				l_TaxBakFlg = NO_ERROR;
			}
			else
			{
				l_TaxBakFlg = ERROR;
			}								
		}
		else
		{
			l_Tax2ComErrFlg = ERROR;
		}	
		
		Time = GetSysTime();
	}
}

////----------------------------------------------------------------------------
//// 名    称：   void  TestTAX2Info(void)
//// 功    能：   测试TAX2箱信息。
//// 入口参数：   无
//// 出口参数：   无
////----------------------------------------------------------------------------
//void  TestTAX2Info(void)
//{
//	static		uint32		Time = 0;
//	static		uint32		Times = 0;
//	uint8		Buf[sizeof(l_sTAX2)] = {0};
//	//OpenTax2();								//打开TAX2通信
//
//	if(GetSysTime() - Time > 50)
//	{
//		
//		RecTAX2Info();
//		
//		if(l_Tax2ComErrFlg == NO_ERROR &&Times > 5)
//		{
//			SendCOM0((uint8 *)&l_sTAX2.sTAX2Bef,sizeof(l_sTAX2.sTAX2Bef));
//			
//			SendCOM0((uint8 *)&l_sTAX2.sTAX2Bak,sizeof(l_sTAX2.sTAX2Bak));
//		}
//				
//		Time = GetSysTime();
//		Times++;
//		//////printfcom0("%u\r\n",Times);
//		
//		memcpy((uint8 *)&l_sTAX2,Buf,sizeof(Buf));
//	}
//	
//	//////printfcom0("%u\r\n",Time);
//}
//
////----------------------------------------------------------------------------
//// 名    称：   stcTAX2Full GetTAX2Info( void )
//// 功    能：   获取TAX2信息 供外部访问
//// 入口参数：  
//// 出口参数：   
////----------------------------------------------------------------------------
uint8 GetTAX2Info( stcTAX2Full	* sTAX2Full )
{
	if(GetTax2BefPackErrFlg() == NO_ERROR )
	{
		sTAX2Full->sTAX2Bef = l_sTAX2.sTAX2Bef;
	}

	if(GetTax2BakPackErrFlg() == NO_ERROR)
	{
		sTAX2Full->sTAX2Bak = l_sTAX2.sTAX2Bak;
	}
	
    return  1;
}
//
////----------------------------------------------------------------------------
//// 名    称：   uint8 GetTax2ComErrFlg( void )
//// 功    能：   TAX2无通信信号
//// 入口参数：  
//// 出口参数：   
////----------------------------------------------------------------------------
uint8 GetTax2ComErrFlg( void )
{
	return	l_Tax2ComErrFlg;
}
//
uint8	l_TaxBefErrFlg = NO_ERROR;
uint8	l_TaxBakErrFlg = NO_ERROR;
//----------------------------------------------------------------------------
// 名    称：   uint8 GetTaxBefErrFlg( void )
// 功    能：   取TAX2前部分信号错误
// 入口参数：  
// 出口参数：   
//----------------------------------------------------------------------------
uint8 GetTaxBefErrFlg( void )
{
	static	uint32	ErrTime = 0;
	
	if(l_TaxBefFlg == ERROR)
	{
		ErrTime++;
		if(ErrTime > 5)
		{
			l_TaxBefErrFlg = ERROR;
		}
	}
	else
	{
		ErrTime = 0;
		l_TaxBefErrFlg = NO_ERROR;
	}

	return	l_TaxBefErrFlg;
}
//
////----------------------------------------------------------------------------
//// 名    称：   uint8 GetTaxBakErrFlg( void )
//// 功    能：   取TAX2后部分信号错误
//// 入口参数：  
//// 出口参数：   
////----------------------------------------------------------------------------
uint8 GetTaxBakErrFlg( void )
{
	static	uint32	ErrTime = 0;
	
	if(l_TaxBakFlg == ERROR)
	{
		ErrTime++;
		if(ErrTime > 5)
		{
			l_TaxBakErrFlg = ERROR;
		}
	}
	else
	{
		ErrTime = 0;
		l_TaxBakErrFlg = NO_ERROR;
	}

	return	l_TaxBakErrFlg;
}

//uint8	l_RoadNumChgEvtFlg = RIGHT_DATA;
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8  JudgeTAX2Data(stcTAX2Full sTAX) 
////函数功能:             对TAX2的数据进行合理、合法性进行判断
////入口参数:             TAX2信息
////出口参数:             内部故障类型
////--------------------------------------------------------------------------------------------------
uint8  JudgeTAX2Data(stcTAX2Full sTAX) 
{
//    uint8       		Sec,Min,Data,Mouth,Hour,RoadNum;
//    static	uint32     	Times;
//    static	uint32   	Time = 0,LstTime = 0;
//    static	uint32   	TimeSys = 0;
//    static	stcTAX2Full	sTAXTmp;
//    static	uint8		LstRoadNum;
//    static	uint8		LstLstRoadNum;
//
//    RoadNum = sTAX.sTAX2Bak.RoadNum;					//交号改变判断	
//    if( Times++ )
//    {
//    	if((RoadNum == LstRoadNum) && (LstRoadNum != LstLstRoadNum) && (Times > 2))
//    	{
////2014    		l_RoadNumChgEvtFlg = TAX_ROAD_NUM_CHG_EVT;
//    	}
//    	else
//    	{
////2014    		l_RoadNumChgEvtFlg = RIGHT_DATA;
//    	}
//    }
//  
//  	LstLstRoadNum 	= LstRoadNum;
//    LstRoadNum 		= RoadNum;
//        
//    memcpy((uint8 *)&Time,sTAX.sTAX2Bak.Time,sizeof(Time));
//
//    Sec	  	= Time  & (0xff >> 2);
//    Min		= (Time >> 6 ) & (0xff >> 2);
//    Hour    = (Time >> 12) & (0xff >> 3);
//    Data    = (Time >> 17) & (0xff >> 3);
//    Mouth   = (Time >> 22) & (0xff >> 4);
//    
//    if(( Sec > 60) || (Min  > 60) || ( Hour  >  24) 
//    		|| (Data  > 31) || (Mouth  >  12))			//时间不合法
//    {
////2014        return  TAX_TIME_RULE_ERR;
//    }
//
//    if(GetSysTime() - TimeSys > 100*5 && GetSysTime() > 100*60)			//30S判断一次
//    {
//		if( memcmp((uint8 *)&sTAXTmp,(uint8 *)&sTAX,sizeof(sTAX)) == 0) //数据不更新
//		{
////2014			return 	TAX_INFO_NO_CHG_ERR;
//		}
//		
//		if(Time < LstTime)							//时间不合理
//		{
////2014			return	TAX_TIME_REASON_ERR;
//		}
//    	
//		LstTime 	= Time;
//		sTAXTmp 	= sTAX;
//		
//		TimeSys 	= GetSysTime();
//	} 
//	
	return	RIGHT_DATA;   
	 
}
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8  GetRoadNumChgEvtFlg(void)  
////函数功能:             TAX箱交路号改变事件
////入口参数:             TAX2信息
////出口参数:             时间合理,返回TRUE
////--------------------------------------------------------------------------------------------------
//uint8  GetRoadNumChgEvtFlg(void) 
//{
//	return	l_RoadNumChgEvtFlg;
//}
//
////-------------------------------------------------------------------------------------------------
////函数名称:            	uint8  JudgeTAX2Evt(void)  
////函数功能:             对TAX2箱信息通信中的事件判断
////入口参数:             
////出口参数:             
////--------------------------------------------------------------------------------------------------
uint8  JudgeTAX2Evt(void) 
{
//	uint8	TaxEvtType;
//	
//	TaxEvtType = GetRoadNumChgEvtFlg();			//交号改变事件
//	
//	return	TaxEvtType;
	return 1;
}

uint8	m_TaxNoErrFlg = TRUE;
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8  JudgeTAX2Error(stcTAX2Full sTAX) 
////函数功能:             对TAX2箱信息通信正确性可靠性进行判断
////入口参数:             TAX2信息
////出口参数:             时间合理,返回TRUE
////--------------------------------------------------------------------------------------------------
uint8  JudgeTAX2Error(void) 
{
	uint8			TaxErrorType = RIGHT_DATA;
	stcTAX2Full		sTAX;
//	static			uint32		Time = 0;
	
	GetTAX2Info((stcTAX2Full *)&sTAX);

//	if( GetSysTime() - Time > 100)	//大于2分钟
	{
//		Time = GetSysTime();

		if(GetTax2ComErrFlg() == NO_ERROR)
		{
			if(GetTaxBefErrFlg() == NO_ERROR && GetTaxBakErrFlg() == NO_ERROR)
			{
//				TaxErrorType = JudgeTAX2Data(sTAX);				//判断内容故障类型
			}
			else if(GetTaxBakErrFlg() == NO_ERROR)
			{
				TaxErrorType = TAX_BEF_REC_ERR;
			}
			else
			{
				TaxErrorType = TAX_BAK_REC_ERR;
			}
		}
		else
		{
			TaxErrorType = NO_TAX_COM_ERR;
		}
		
		if(TaxErrorType == RIGHT_DATA)
		{
			m_TaxNoErrFlg = TRUE;
		}
		else
		{
			m_TaxNoErrFlg = FALSE;
		}
	}
	
	return	TaxErrorType;
}

uint8	m_NoSpeedFlg = FALSE;
////-------------------------------------------------------------------------------------------------
////函数名称:             void  ShowTAX2Info(stcTAX2Full sTAX) 
////函数功能:             打印TAX2时间,公里标信息
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
void  GetTAX2SpeedInfo(void) 
{
//	stcTAX2Full		sTAX;
//	uint32			TaxSpeed;
//	static	uint32	Time = 0;		
//	static	uint32	Times = 0;		
//	
//	GetTAX2Info((stcTAX2Full *)&sTAX);
//	
//	if(GetSysTime() - Time > 100)
//	{
//		Time = GetSysTime();
//		
//		Times++;
//		
//		if(Times > 30)
//		{
//			if(m_TaxNoErrFlg == TRUE)
//			{
//				TaxSpeed = (uint32)sTAX.sTAX2Bak.RelSpeed[0] + (uint32)((sTAX.sTAX2Bak.RelSpeed[1]<<7)>>7)*256;
//				
//				if(TaxSpeed == 0) 					//速度为零
//				{
//					m_NoSpeedFlg = TRUE;
//					//////printfcom0("\r\n 速度为零");
//				}
//				else
//				{
//					//////printfcom0("\r\n 速度为%u",TaxSpeed);
//				
//					m_NoSpeedFlg = FALSE;
//				}
//			}
//		}
//	}
}

////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	GetNoSpeedFlg(void)
////函数功能:             取速度为零的标识
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
uint8	GetNoSpeedFlg(void)
{
	return	m_NoSpeedFlg;
}

////-------------------------------------------------------------------------------------------------
////函数名称:             void  ShowTAX2Info(stcTAX2Full sTAX) 
////函数功能:             打印TAX2时间,公里标信息
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
//void  ShowTAX2Info(stcTAX2Full sTAX) 
//{
//    uint16      RelSpeed;
//    uint8       Second,Minute,Data,Mouth,Hour;
//    uint16      Year;
//    uint32      Time;
//    float       KmMark;
//    
//    RelSpeed= (uint16)sTAX.sTAX2Bak.RelSpeed[0] + (sTAX.sTAX2Bak.RelSpeed[1] &(1))*256;
//
//    memcpy((uint8 *)&Time,sTAX.sTAX2Bak.Time,sizeof(Time));
//    	
//    Second  = Time  & (0xff >> 2);
//    Minute  = (Time >> 6 ) & (0xff >> 2);
//    Hour    = (Time >> 12) & (0xff >> 3);
//    Data    = (Time >> 17) & (0xff >> 3);
//    Mouth   = (Time >> 22) & (0xff >> 4);
//    Year    = 2009;
//    
//    KmMark = ((uint32)sTAX.sTAX2Bak.KmMark[0] + (uint32)sTAX.sTAX2Bak.KmMark[1]*256 
//            + (uint32)sTAX.sTAX2Bak.KmMark[2]*256*256)/1000;
//    
//    ////printfcom0("\r\n %u-%u %u:%u:%u,%u,%f",
////    Mouth,Data,Hour,Minute,Second,RelSpeed,KmMark);    //记录输出	
//}
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void  Tax2Task(void)
////函数功能:             TAX2处理
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
void  Tax2Task(void)
{
//	////printfcom0("\r\n\r\nTax2Task(void)");
    
	RecTAX2Info();
	
//	GetTAX2SpeedInfo();
}
//
//#ifdef	TEST_OPEN
////-------------------------------------------------------------------------------------------------
////函数名称:             void  SimulateTax(void)
////函数功能:             TAX2模拟器
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
//void  ReadSimsTaxData(stcTAX2Full *sTax)
//{
//    uint8   	CheckSum;        		//检查和            1   为前面所有字节累加和的二进制补码  
//	stcTime		sTime;
//	uint32		RealSpeed;
//	uint32		Time;
//	uint32		KmMark;
//	uint16		LocoNum;
//	uint16		MstDriverNum;
//	
//	sTax->sTAX2Bef.TAX2BefAdrCod 	= 0x38;
//	sTax->sTAX2Bef.NewFlg			= 0x67;
//	sTax->sTAX2Bef.CheckSum = GetCheckSum((uint8 *)&sTax->sTAX2Bef,sizeof(sTax->sTAX2Bef) -1);
//
//    sTax->sTAX2Bak.TAX2BakAdrCod = 0x39;
//
//    ReadTime((stcTime *)&sTime);											// 时间 
//	Time	=  sTime.Sec + sTime.Min * (1 << 6) + sTime.Hour * (1 << 12) 
//				+ sTime.Date * (1 << 17) + sTime.Month * (1 << 22) + sTime.Year * (1 << 26);
//	memcpy((uint8 *)&sTax->sTAX2Bak.Time,(uint8 *)&Time,sizeof(Time));
//	   
//    RealSpeed	= GetSetTaxSpeed();		// 取TAX箱信息]
//	memcpy((uint8 *)&sTax->sTAX2Bak.RelSpeed,(uint8 *)&RealSpeed,sizeof(sTax->sTAX2Bak.RelSpeed));
//
//	KmMark	= RealSpeed * ((GetSysTime()/10)/36);  	//((GetSysTime()/100)/3600) 单位：m
//	memcpy((uint8 *)&sTax->sTAX2Bak.KmMark,(uint8 *)&KmMark,sizeof(KmMark));
//
//    //sTax->sTAX2Bak.LocoTyp						=  GetSetTaxLocoTyp();		// 取TAX箱机车型号    
//    sTax->sTAX2Bak.LocoTyp						=  0;		// 取TAX箱机车型号  
//      
//	//LocoNum	=  GetSetTaxLocoNum();					// 取TAX箱机车编号
//	LocoNum	=  0;					// 取TAX箱机车编号
//	memcpy((uint8 *)&sTax->sTAX2Bak.LocoNum,(uint8 *)&LocoNum,sizeof(sTax->sTAX2Bak.LocoNum));
//
//	MstDriverNum	=  GetSetTaxDriverNum();		// 取TAX箱司机号
//	memcpy((uint8 *)&sTax->sTAX2Bak.MstDriverNum,(uint8 *)&MstDriverNum,sizeof(sTax->sTAX2Bak.MstDriverNum));
//													// 公里标
//
//	sTax->sTAX2Bak.CheckSum = GetCheckSum((uint8 *)&sTax->sTAX2Bak,sizeof(sTax->sTAX2Bak) -1);
//        
//}
//
//#define	USB_INT_SUCCESS		0x14			/* USB事务或者传输操作成功 */
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void	SendSimsTaxData(stcTAX2Full *sTax);			//发送TAX数据
////函数功能:             发送TAX数据
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
//void	SendSimsTaxData(stcTAX2Full * sTax)			//发送TAX数据
//{
//	SendCOM0((uint8 *)sTax,sizeof(stcTAX2Full));	//发送TAX信息
//}
//
//extern	void  	ReadSimsTaxData(stcTAX2Full *sTax);
//extern	void	SendSimsTaxData(stcTAX2Full * sTax);			//发送TAX数据
//#endif
//
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void  SimulateTax(void)
////函数功能:             TAX2模拟器
////入口参数:             无
////出口参数:             无
////说明:                 
////--------------------------------------------------------------------------------------------------
//void  SimulateTax(void)
//{
//
//#ifdef	TEST_OPEN
//	stcTAX2Full	sTax;
//	uint32		Time;
//	
////   OpenTaxSent();								//打开串口，准备数据发送
//
////	memset((uint8 *)&sTax,0,sizeof(stcTAX2Full));
//	
//    //while(1)
//    {	
////    	SysHoldTast();
//    	
//    	if(GetSysTime() - Time > 100)				//20ms
//    	{
//    	#ifdef	HARD_VER_111122	
//
//		//	if( CH376DiskConnect() == USB_INT_SUCCESS )//连接USB,U盘插入
//		//	{
//	   	//		UsbSetTaxHost();						//用U盘设置TAX信息					
//	   	//	}
//	   		
//		#endif
//			ReadSimsTaxData((stcTAX2Full *)&sTax);		//读TAX箱模拟器数据
//
//			SendSimsTaxData((stcTAX2Full *)&sTax);		//发送TAX数据
//			
//			Time = GetSysTime();
//			
//			//DelayX10ms(100);
//		}
//	}
//	
//#endif
//}
//
//
//#ifdef	TEST_OPEN
//
//
//#define	LOCO_KEY	P021
//#define	ON_LINE		P024
//#define	CS_IN		P022
//
//void	InitIO(void)
//{
//	SETFUN_P016_31X(GPIO,LOCO_KEY);
//	IO0DIR_OUT(LOCO_KEY);
//	
//	SETFUN_P016_31X(GPIO,ON_LINE);
//	IO0DIR_OUT(ON_LINE);
//	
//	SETFUN_P016_31X(GPIO,CS_IN);
//	IO0DIR_OUT(CS_IN);
//}
//
//void  SimulatePluse(void)
//{
//	//SimulateDip();							//仿真油尺		
//	static	uint32	Time;
//	static	uint32	Times;
//	
//	if(GetSysTime() - Time > 10 )
//	{
//		Time = GetSysTime();
//		Times++;
//		
//		if(Times %2 == 0)
//		{
//			IO0SET_W(LOCO_KEY);
//			IO0SET_W(ON_LINE);
//		}
//		else
//		{
//			IO0CLR_W(LOCO_KEY);
//			IO0CLR_W(ON_LINE);
//		}
//	}
//}
//	
//uint32	CS_Times;
//
//void	SimulateHoldCs(void)
//{
//	CS_Times++;
//	if(CS_Times %2 ==0)
//	{
//		IO0SET_W(CS_IN);
//	}
//	else
//	{
//		IO0CLR_W(CS_IN);
//	}
//}
//	
//#endif
//
//
//void Simulate(void)
//{
//#ifdef	TEST_OPEN
//	
//	InitIO();								//初始化脉冲发送的IO口
//
//	while(1)
//	{
//		if(SetKeyPressed() == FALSE)
//		{
////			SysHoldTast();
//
//			SimulateTax();						//仿真TAX箱
//		
//			SimulateDip();						//仿真油尺		
//			
//			SimulatePluse();					//模拟脉冲发送
//		}
//	}
//	
//#endif
//}
//	  
//
//	
