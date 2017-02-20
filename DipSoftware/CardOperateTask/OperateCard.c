////#include 	"config.h"
////#include 	"String.h"
////#include	"Globe.h"
////#include	"HardDrive.h"
////#include	"CpuDrive.h"
////#include	"OperateCard.h"
////#include	"Tax2.h"
////#include	"FramStore.h"
//
#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h"
#include	"FRAM.h"
//
uint16	l_CardType;
uint8	l_FlgZoneErrEvent	= NO_OCCUR;
////-------------------------------------------------------------------------------------------------
////函数名称:             ReadCardFlg()
////函数功能:             读分区卡标识页,进行求要分区号
////入口参数:             无
////出口参数:             IC卡首页读取
////说明:                 
////--------------------------------------------------------------------------------------------------
//uint8	ReadCardFlg(stcCardFlg * sCardFlg)
//{	
//	////printfcom0("\r\n ReadCardFlg(stcCardFlg * sCardFlg)");
//	
//	ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));		
//	
//	////printfcom0("\r\n ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));");
//
//	////printfcom0("\r\n sCardFlg->sCardType.CrcCheck %d, CrcCheck %d",sCardFlg->sCardType.CrcCheck,GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2));
//
//	if(     (sCardFlg->sCardType.CardType[0] == sCardFlg->sCardType.CardType[1]) 
//		&& 	(sCardFlg->sCardType.CardType[1] == sCardFlg->sCardType.CardType[2])
//		&&	(sCardFlg->sCardType.CrcCheck == 
//		    GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2))
//	   )
//	{
//		l_CardType 		= sCardFlg->sCardType.CardType[0];			//IC卡 类型
//		
//		l_FlgZoneErrEvent = NO_OCCUR;								//IC卡 标识页错误事件
//		
//		//PrintfDebug("\r\n l_CardType %d",l_CardType);
//		
//		return 	1;
//	}
//	else
//	{
//		l_FlgZoneErrEvent = OCCUR;
//		l_CardType = 0x0000;
//		
//		return	0;
//	}
//}

uint8	ReadCardFlg(void)
{	
	////printfcom0("\r\n ReadCardFlg(stcCardFlg * sCardFlg)");
	stcCardType		sCardType;

	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID),(uint8 *)&sCardType,sizeof(stcCardType));		
	
	////printfcom0("\r\n ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));");

	////printfcom0("\r\n sCardFlg->sCardType.CrcCheck %d, CrcCheck %d",sCardFlg->sCardType.CrcCheck,GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2));

	if(     (sCardType.CardType[0] == sCardType.CardType[1]) 
		&& 	(sCardType.CardType[1] == sCardType.CardType[2])
		&&	(sCardType.CrcCheck == 
		    GetCrc16Check((uint8 *)&sCardType,sizeof(sCardType) -2))
	   )
	{
		l_CardType 		= sCardType.CardType[0];			//IC卡 类型
		
		l_FlgZoneErrEvent = NO_OCCUR;								//IC卡 标识页错误事件
		
		//PrintfDebug("\r\n l_CardType %d",l_CardType);
		
		return 	1;
	}
	else
	{
		l_FlgZoneErrEvent = OCCUR;
		l_CardType = 0x0000;
		
		return	0;
	}
}

//
////-------------------------------------------------------------------------------------------------
////函数名称:             ReadCOM0CardFlg()
////函数功能:             读分区卡标识页,进行求要分区号
////入口参数:             无
////出口参数:             IC卡首页读取
////说明:                 
////--------------------------------------------------------------------------------------------------
//uint8	ReadCOM0CardFlg(stcCardFlg * sCardFlg)
//{	
//	//PrintfDebug("\r\n ReadCardFlg(stcCardFlg * sCardFlg)");
//	
//	//ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));		
//	
//	//PrintfDebug("\r\n ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));");
//
//	if(     (sCardFlg->sCardType.CardType[0] == sCardFlg->sCardType.CardType[1]) 
//		&& 	(sCardFlg->sCardType.CardType[1] == sCardFlg->sCardType.CardType[2])
//		&&	(sCardFlg->sCardType.CrcCheck == 
//		    GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2))
//	   )
//	{
//		l_CardType 		= sCardFlg->sCardType.CardType[0];			//IC卡 类型
//		
//		l_FlgZoneErrEvent = NO_OCCUR;								//IC卡 标识页错误事件
//		
//		//PrintfDebug("\r\n l_CardType %d",l_CardType);
//		
//		return 	1;
//	}
//	else
//	{
//		l_FlgZoneErrEvent = OCCUR;
//		l_CardType = 0x0000;
//		
//		return	0;
//	}
//}
//
////--------------------------------------------------------------------------------------------
////函数名称:             WriteNormCard(void)   
////函数功能:             StartCardRecNum:开始流水号,EndCardRecNum:结束流水号
////入口参数:             流水号
////出口参数:             无
////说明:                 
////---------------------------------------------------------------------------------------------
void    WriteCardFlg(stcCardFlg*	sCardFlg)  
{
////	uint16	CrcTmp;
//	
////	CrcTmp = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg)-2);
//	
////	sCardFlg->CrcCheck = CrcTmp;
//	
//    WriteCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));
}

//extern	stcCardFlg	l_sCardFlg;
//
////--------------------------------------------------------------------------------------------
////函数名称:             uint8    CheckWriteCardFlgCrc(uint16 Crc16)    
////函数功能:             读标志页校验
////入口参数:             无
////出口参数:             标志页校验,正确返回1，否则为零
////说明:                 
////---------------------------------------------------------------------------------------------
//uint8    CheckWriteCardFlgCrc(uint16 Crc16 )  
//{
////	uint16	CrcTmp;
////	
////	ReadCardFlg((stcCardFlg *)&l_sCardFlg);
////    
////    ReadCard(CARD_FLG_ADDR + sizeof(stcCardFlg)-2,(uint8 *)&CrcTmp,sizeof(CrcTmp));
////    
////    CrcTmp = GetCrc16Check((uint8 *)&l_sCardFlg,sizeof(stcCardFlg) -2);
////
////    ////printfcom0("\r\n CrcTmp %d,Crc16 ,%d",CrcTmp,Crc16);
////    
////    if(Crc16 == CrcTmp)
////    {
////    	return	NO_ERROR;
////    }
////    else
////    {
////    	return	ERROR;
////    }
//}
//

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicatePullOutCard(void)
{
	OffLed(WRITE_CARD_LED);
	OffLed(CARD_FULL_LED);	
	OffLed(CARD_LED);	
}
//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateCardTypErr(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NCTP");									//IC卡类型错误		
	DisplaySet(60,0xffff,"    ");									//IC卡类型错误		
	OnLed(CARD_LED,1,50000,0);		
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateCardNoSet(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NSET");									//IC卡类型错误		
	DisplaySet(60,0xffff,"    ");									//IC卡类型错误		
	OnLed(CARD_LED,1,50000,0);		
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateCardNoDef(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NDEF");									//IC卡类型错误		
	DisplaySet(60,0xffff,"    ");									//IC卡类型错误	
	OnLed(CARD_LED,1,50000,0);		
}

extern	uint8	l_CardErrorFlg;
//
////static stcCardFlg	l_sCardFlg;
////static	stcCardFlg	l_sCardFlg = {0};
//stcCardFlg	l_sCardFlg = {0};
//
//
//extern	void    KeySetDensity(void);
////extern	void	ClosePluseInput(void);
////extern	void	ReStartPluse(void);
//extern	void	ReCalPara(uint8 Flg)	;
//extern	uint8	ComModCard(stcCardFlg	* sCardFlg);
//extern	uint8	ExpandCard(stcCardFlg	* sCardFlg);
//extern	uint8   WriteExpandAddTest(void);
//extern	uint8	l_WriteFlgErrCardEvtFlg;
//extern	uint8	DenDataCard(stcCardFlg *	sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             OperationCard(void)    
////函数功能:             操作IC卡
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
void    OperationCard(void)  
{
	uint8	ResetFlg;
	static	uint32	PlugTime = 0;
	static	uint32	SysTime = 0;
	static	uint8	PlugErrFlg = 0;
	static	uint8	PlugCardLongTime = 0;
	
	ResetFlg = FALSE ;
		
	if(GetPlugFlg() == PLUG_IN_CARD)
	{
		if(PlugCardLongTime == 1)
		{
			if(PlugErrFlg == 1)
			{
				DisplaySet(100,1,"NCTP");									//IC卡类型错误		
				DisplaySet(100,1,"    ");									//IC卡类型错误		
				DelayX10ms(250);
			}

			return;
		}

		ClaerDisplaySet();													//清显示缓冲区
		OffAllLed();														//关所有发光二极管
		OnLed(RUN_LED,30000,5,5);											//清显示缓冲区		
		DisplaySet(50,1,"    ");										

		//CloseTax2();

		if(PlugICCard() == TRUE)										//有卡插入，再进行相关操作
		{	
			if(ReadCardFlg())					//读IC卡标志页
			{
				switch( l_CardType )
				{
					case DATA_CARD:	DisplaySet(100,1,"DATA");
									DataCard(0);	
									break;									
					case DENSITY_CARD:									//密度卡
									DisplaySet(100,1,"DENS");						
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}		
									break;
					case MODEL_CARD:									//模型卡
									DisplaySet(100,1,"MODE");						
									if(ModCard())
									{
										ResetFlg = TRUE;
									}	
										
									break;				
//					case COM_MODEL_CARD:								//时间卡
//									DisplaySet(100,1,"SETC");						
//									if(ComModCard())
//									{
//										ResetFlg = TRUE;
//									}	
//									break;	
					case SET_DATA_CARD:									//置数卡	
									DisplaySet(100,1,"SETD");						
									if(SetDataCard())
									{
										ResetFlg = TRUE;
									}
									break;		
					case HIGHT_CARD:									//高度调整卡
									DisplaySet(100,1,"HIGT");						
									if(HightCard())
									{
										ResetFlg = TRUE;
									}
									break;															
					case COPY_CARD:										//数据拷贝卡//还未写入内容
									DisplaySet(100,1,"COPY");						
									DataCard(1);
									break;
					case MODEL_SELECT_CARD:								//模型选择卡
									DisplaySet(100,1,"SELE");						
 									if(ModelSelectCard())
									{
										ResetFlg = TRUE;
									} 									
 									break;	
//					case DEBUG_CARD:									//调试卡
//									DisplaySet(100,1,"DEBU");						
//									DebugCard((stcCardFlg *)&l_sCardFlg);									
//									break;
					case FIX_CARD:										//装车卡
									DisplaySet(100,1,"FIXC");						
									if(FixCard())
									{
										ResetFlg = TRUE;
									}									
									break;					
//					case COPY_FRAM_CARD:								//铁电复制卡
//									DisplaySet(100,1,"FRAC");						
//									CopyFramCard((stcCardFlg *)&l_sCardFlg);									
//									break;		
					case EXPAND_CARD:									//扩展卡 //20120409
									DisplaySet(100,1,"EXPD");						
									ExpandCard();									
									break;		
					case DATA_CARD + DENSITY_CARD:						//密度卡+数据卡 (不马上刷新数据)  密度结构增加DenChageTimes，
									DisplaySet(100,1,"DDEN");						
									DenDataCard();
//		
//									break;
					case DATA_CARD + DENSITY_CARD+HIGHT_CARD:						//密度卡+数据卡（马上刷新数据）
									DisplaySet(100,1,"DDHN");						
									DenDataCard();
									ResetFlg = TRUE;
									break;			
//														
//					case DENSITY_CARD + MODEL_CARD:						//密度卡+模型卡
//									DisplaySet(100,1,"DEMO");						
//									
//									if(DensityCard((stcCardFlg *)&l_sCardFlg))
//									{
//										ResetFlg = TRUE;
//									}									
//									
//									if(ModCard())
//									{
//										ResetFlg = TRUE;
//									}									
//									break;
					case DENSITY_CARD + FIX_CARD + MODEL_CARD:			//密度卡+装车卡+模型卡
									DisplaySet(100,1,"DFMC");						
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(ModCard())
									{
										ResetFlg = TRUE;
									}									
									
									if(FixCard())
									{
										ResetFlg = TRUE;
									}
									break;
									
					case DENSITY_CARD + FIX_CARD + MODEL_CARD + HIGHT_CARD:	//密度卡+装车卡+模型卡+高度卡
									DisplaySet(100,1,"DFMH");						
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(ModCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(FixCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(HightCard())
									{
										ResetFlg = TRUE;
									}
																		
									break;
					case DENSITY_CARD + FIX_CARD + HIGHT_CARD:				//密度卡+装车卡+高度卡
									if(DisplaySet(100,1,"DFHC"))
									{
										ResetFlg = TRUE;
									}
																		
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(FixCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(HightCard())
									{
										ResetFlg = TRUE;
									}									
									break;									
					default:	
									IndicateCardNoDef();	
				}
			}	
			else
			{
				DelayX10ms(10);
				IndicateCardNoSet();
			}	
			
			PlugErrFlg = 0;		
		}
		else 
		{
			PlugErrFlg = 1;
			
			IndicateCardTypErr();
		}		

		while(GetPlugFlg() == PLUG_IN_CARD)								//等IC卡退出		
		{
			PlugTime++;													//插入IC卡，记时
							
			SysTime = GetSysTime();		
			while(GetSysTime() - SysTime < 100)							//1S
			{
				NOP();
			}
				
			if(PlugErrFlg == 1)											//卡错误，等10秒则退出
			{
				if(PlugTime	> 20)
				{
					PlugCardLongTime = 1;
					break;
				}			
			}
			else														////卡，等5分钟则退出
			{
				if(PlugTime	> 90)
				{
					PlugCardLongTime = 1;
					break;
				}			
			}

			NOP();
		}
		DelayX10ms(150);												//拔卡推出事等待

		
		if(PlugErrFlg == 1 && PlugTime > 500)							//插卡错误，退出操作
		{
			DelayX10ms(50);
		}
		
		if(ResetFlg == TRUE)											//参数设好后，重起
		{
			ReCalPara(1);												//油尺参数重新计算

			DelayX10ms(20);
			
//			ResetSys();													//
		}		
											//清显示缓冲区
		ResumeDisplaySet();												//恢复显示缓冲区
		
		if(PlugCardLongTime == 1 && PlugErrFlg == 0)
		{
			//OffLed(WRITE_CARD_LED);
			//OffLed(CARD_FULL_LED);	
			//OffLed(CARD_LED);	
		}
		else
		{
			IndicatePullOutCard();
		}
		
		g_PullCardTime = GetSysTime();
	}
	else
	{
		PlugTime = 0;													//插入次数清零
		PlugErrFlg = 0;
			
		l_CardErrorFlg = NO_ERROR;
		
		PlugCardLongTime = 0;
		
		OffLed(WRITE_CARD_LED);
		OffLed(CARD_FULL_LED);	
	}
}
//
///*
//uint8	SetKeyPressed(void)
//{
//	//return 1;
//	return	(KeyPressed());
//}
//*/
//
//#define		MAX_SET_TIME  20
//extern	float		l_Density;							//密度值
//extern	uint16	GetDensityVal(void);
////20111024
////-------------------------------------------------------------------------------------------------
////函数名称:             void    KeySetDensity(void)     
////函数功能:             操作IC卡
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//void    KeySetDensity(void)  
//{
////	uint8	ResetFlg;
//	
////	ResetFlg = FALSE ;
//
////  
//	static	stcDensity sDensity;
//
//	uint32	DisplayVal;
//	uint32	KeyDownTime = 0;
//	uint32	SysTime;
//	uint16	Density;
//	uint32	CalDensity;
//	uint16  CrcCheck;
//	
//	DisplayVal = g_DipVal;													//正在显示的油量
//	
//	while(GetPlugFlg() == PLUG_IN_CARD)										//
//	{ 
//		SysTime = GetSysTime();												
//		
//		//SysHoldTast();
//		//while(1)
//		{
//			if(SetKeyPressed())												//按下设置键
//			{
//				if(KeyDownTime == 0)										// 第一次按下设置键
//				{
//					ClaerDisplaySet();										//清显示缓冲区
//					
//					DisplayVal = g_DipVal;
//					
//					DisplaySet(100,1,"%u",DisplayVal);
//				}
//				else
//				{
//					if(KeyDownTime < (MAX_SET_TIME/2))
//					{
//						DisplayVal = g_DipVal + KeyDownTime*10;
//					}
//					else
//					{
//						if(g_DipVal > MAX_SET_TIME*10)						//向负方向循环
//						{
//							DisplayVal = g_DipVal + KeyDownTime*10 - MAX_SET_TIME*10;
//						}		
//						else
//						{
//							DisplayVal = 10*MAX_SET_TIME /2 + KeyDownTime*10 - MAX_SET_TIME*10;
//						}		
//					}
//					
//					ClaerDisplaySet();										//清显示缓冲区
//					DisplaySet(60,1,"%u",DisplayVal);
//				}
//				
//				KeyDownTime = (KeyDownTime+1)%MAX_SET_TIME;					//按键次数加
//				while(SetKeyPressed()){};										//等待按键松开
//				DelayX10ms(20);												//等待一段时间退出	
//				
//				SysTime = GetSysTime();	
//			}
//			else															//未按下或松开按键
//			{
//				//DelayX10ms(10);											//等待一段时间退出	
//			}
//		}
//		
//		if(GetSysTime() - SysTime > 1000)
//		{
//			break;
//		}
//	}
//	
//	
//	if(KeyDownTime != 0)													//准备计算密度
//	{
//		Density = GetDensityVal();											//取密度值
//		
//		//printfcom0("\n \rDisplayVal %u,g_DipVal %u",DisplayVal,g_DipVal);
//
//		if(g_DipVal > 3400)
//		{
//			if(DisplayVal > g_DipVal)
//			{
//				CalDensity = Density -  ((uint32)Density *(DisplayVal - g_DipVal) / (g_DipVal - 3400));
//			}
//			else
//			{
//				CalDensity = Density + ((uint32)Density *(g_DipVal - DisplayVal) / (g_DipVal - 3400));
//			}
//	  	}
//	  	else
//	  	{
//			if(DisplayVal > g_DipVal)
//			{
//				CalDensity = Density -  ((uint32)Density *(DisplayVal - g_DipVal) / (g_DipVal));
//			}
//			else
//			{
//				CalDensity = Density +  ((uint32)Density *(g_DipVal - DisplayVal) / (g_DipVal));
//			}
//	  	}
//	  	
//	  	//printfcom0("\n \rCalDensity %u,Density %u",CalDensity,Density);
//	  	
//	  	if(CalDensity > 770 && CalDensity < 900)							//限值
//	  	{
//	  		sDensity.Density = CalDensity;
//	  	}
//	  	
//		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
//		//GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
//		sDensity.CrcCheck = CrcCheck;
//		
//		//if(CrcCheck == sDensity.CrcCheck)									//校验和相等,存密度		
//		//{			
//		//PrintfDebug("\r\n sDensity.Density %d",sDensity.Density );
//		
//		if(StoreDensity((stcDensity *)&sDensity))
//		{
//			//SetSucceedIndicate();	
//		}
//		else
//		{
//			//StoreErrIndicate();	
//		}
//		//}
//		
//		//printfcom0("\r\n l_Density %f",l_Density);
//		
//		l_Density = (float)CalDensity / 1000;
//		
//		//printfcom0("\r\n l_Density %f",l_Density);	
//	}
//	/*	*/
//	ClaerDisplaySet();										//清显示缓冲区
//
//}
////-------------------------------------------------------------------------------------------------
////函数名称:             OperationCOM0ModelCard(void)    
////函数功能:             操作从串口0接受到的数据
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//void    OperationCOM0ModelCard(void)  
//{
///*
//	uint16	ResetFlg;
//	
//	ClaerDisplaySet();											//清显示缓冲区
//	OffAllLed();												//关所有发光二极管
//	OnLed(RUN_LED,30000,5,5);									//清显示缓冲区		
//	CloseTax2();
//		
//	PrintfDebug("\r\n OperationCard");
//
//	if(ReadCOM0CardFlg((stcCardFlg	*)&l_sCardFlg))					//读IC卡标志页
//	{
//		switch( l_CardType )
//		{
//			case DATA_CARD:	DisplaySet(100,1,"DATA");
//							DataCard((stcCardFlg *)&l_sCardFlg);	
//							break;									
//				
//			case DENSITY_CARD:									//密度卡
//							DisplaySet(150,1,"DENS");						
//							
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}		
//							break;				
//			case MODEL_CARD:									//模型卡
//							DisplaySet(150,1,"MODE");						
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}		
//							break;				
//			case COM_FIX_CARD:										//时间卡
//							//DisplaySet(100,1,"SETT");						
//							//TimeCard((stcCardFlg *)&l_sCardFlg);		
//							break;	
//			case SET_DATA_CARD:									//置数卡	//还未写入内容
//							DisplaySet(100,1,"SETD");						
//							if(SetDataCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//							break;		
//			case HIGHT_CARD:									//高度调整卡
//							DisplaySet(150,1,"HIGT");						
//							if(HightCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//							break;															
//			case COPY_CARD:										//数据拷贝卡//还未写入内容
//							DisplaySet(100,1,"COPY");						
//							DataCopyCard((stcCardFlg *)&l_sCardFlg);
//							break;
//			case MODEL_SELECT_CARD:								//模型选择卡
//							DisplaySet(100,1,"SELE");						
//							if(ModelSelectCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							} 									
//							break;	
//			case DEBUG_CARD:									//调试卡
//							DisplaySet(100,1,"DEBU");						
//							DebugCard((stcCardFlg *)&l_sCardFlg);									
//							break;
//			case FIX_CARD:										//装车卡
//							DisplaySet(100,1,"FIXC");						
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}									
//							break;					
//			case COPY_FRAM_CARD:								//铁电复制卡
//							DisplaySet(100,1,"FRAC");						
//							CopyFramCard((stcCardFlg *)&l_sCardFlg);									
//							break;						
//			case DENSITY_CARD + MODEL_CARD:						//密度卡+模型卡
//							DisplaySet(100,1,"DEMO");						
//							
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}									
//							
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}									
//							break;
//			case DENSITY_CARD + FIX_CARD + MODEL_CARD:			//密度卡+装车卡+模型卡
//							DisplaySet(100,1,"DFMC");						
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}									
//							
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//							break;
//							
//			case DENSITY_CARD + FIX_CARD + MODEL_CARD + HIGHT_CARD:	//密度卡+装车卡+模型卡+高度卡
//							DisplaySet(100,1,"DFMH");						
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(HightCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							break;
//			case DENSITY_CARD + FIX_CARD + HIGHT_CARD:				//密度卡+装车卡+高度卡
//							if(DisplaySet(100,1,"DFHC"))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(HightCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}									
//							break;									
//			default:	
//							IndicateCardNoDef();	
//		}
//	}	
//	else
//	{
//		DelayX10ms(10);
//		IndicateCardNoSet();
//	}	
//*/		
//}
//
////-------------------------------------------------------------------------------------------------
////函数名称:             CardTask(void)    
////函数功能:             操作IC卡任务
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
void    CardTask(void)  
{
	OperationCard();
}
//
#define		PLUG_CARD_EVT			61
#define		NU_FINISH_CARD_EVT		62
#define		SET_PARA_EVT			63
#define		READ_DATA_EVT			64
#define		WRITE_FLGA_EVT			65
#define		PLUG_USB_EVT			66
#define		USB_READ_EVT			67
#define		USB_SET_EVT				68

//
//extern	uint8	GetSetParaFlg(void);
//extern	uint8	GetReadDataFlg(void);
//extern	void	SetReadDataFlgTrue(void);
//extern	uint8	SetParaFlgTrue(void);
//extern	void	ResetPlugFlgEvt(void);
//extern	void	ResetUnFihCardEvtFlg(void);
//extern	uint8	GetWriteFlgErrCardEvtFlg(void);
////extern	uint8	GetPlugUsbFlg(void);
////extern	void	SetPlugUsbFlgTrue(void);
////extern	void	SetUsbSetFlgTrue(void);
//extern	void	SetUsbReadDataFlgTrue(void);
////extern	uint8	GetUsbSetFlg(void);
//extern	uint8	GetUsbReadDataFlg(void);
//
////-------------------------------------------------------------------------------
////函数名称:        	uint8	JudgeCardEvt(void)
////函数功能:       	判断Flsh事件
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
uint8	JudgeCardEvt(void)
{
	uint8	EvtType = RIGHT_DATA;

	if(GetPlugFlg() == PLUG_IN_CARD)
	{
		EvtType = PLUG_CARD_EVT;
		ResetPlugFlgEvt();
	}
	else if(GetUnFihCardEvtFlg() == ERROR)
	{
		EvtType = NU_FINISH_CARD_EVT;
		ResetUnFihCardEvtFlg();
	}
	else if(GetSetParaFlg() == ERROR)   
	{
		EvtType = SET_PARA_EVT;
		SetParaFlgTrue();
	}	
	else if(GetReadDataFlg() == ERROR)
	{
		EvtType = READ_DATA_EVT;
		SetReadDataFlgTrue();
	}		
//	else if(GetWriteFlgErrCardEvtFlg() == ERROR)
//	{
//		EvtType = WRITE_FLGA_EVT;
//		SetReadDataFlgTrue();
//	}
////	else if(GetPlugUsbFlg() == ERROR)
////	{
////		EvtType = PLUG_USB_EVT;
////		SetPlugUsbFlgTrue();
////	}
////	else if(GetUsbSetFlg() == ERROR)
////	{
////		EvtType = USB_SET_EVT;
////		SetUsbSetFlgTrue();
////	}
////	else if(GetUsbReadDataFlg() == ERROR)
////	{
////		EvtType = USB_READ_EVT;
////		SetUsbReadDataFlgTrue();
////	}
//	
	return	EvtType;
}
////
