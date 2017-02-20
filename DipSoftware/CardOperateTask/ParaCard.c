////#include 	"config.h"
////#include 	"String.h"
////#include	"Globe.h"
////#include	"HardDrive.h"
////#include	"CpuDrive.h"
////#include	"OperateCard.h"
////#include	"FramStore.h"
////#include	"CardTest.h"
//
//
#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h" 
#include	"FRAM.h" 
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	SetSucceedIndicate(void)
////函数功能:             设置处理成功指示
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
void	SetSucceedIndicate(void)
{
//	DisplaySet(60,0,"SETS");	
//	DisplaySet(60,0,"        ");	
}

////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	StoreErrIndicate(void)
////函数功能:             存设置信息失败指示
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
void	StoreErrIndicate(void)
{
	DisplaySet(60,100,"STRE");	
	DisplaySet(60,100,"        ");	
}

////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	CrcCheckErrIndicate(void)
////函数功能:             设置信息校验和失败指示
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
void	CrcCheckErrIndicate(void)
{
	DisplaySet(60,100,"CRCE");	
	DisplaySet(60,100,"        ");	
}

////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	ModCard(stcCardFlg	sCardFlg)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
uint8	ModCard(void)
{
	uint8	buf[256];
	uint32	writedsize = 0;
	uint32	readsize = 0;
		
	while(writedsize < sizeof(stcModelCard))
	{
		readsize = (sizeof(stcModelCard)- writedsize)>256?
					256:(sizeof(stcModelCard)- writedsize);

		ReadCard(CARD_DATA_ADDR+writedsize,buf,readsize);

		StoreOilBoxModel(writedsize,buf,readsize);

		writedsize +=readsize;
	}

	DisplaySet(60,3,"      ");
	DisplaySet(60,3,"SETS");	
		
	return	1;
} 
//
//extern	stcModelCard	l_sModelCard;	 
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	COM0ModData(void)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//uint8	COM0ModData(void)
//{
//	uint16	CrcCheck;
//		
//	CrcCheck = GetCrc16Check((uint8 *)&l_sModelCard,sizeof(stcModelCard) - 2);
//		
//	if(CrcCheck == l_sModelCard.CrcCheck)				//校验和相等		
//	{			
//		//printfcom0("\r\nModCard(void) CCrcCheck == sModelCard.CrcCheck %d",l_sModelCard.CrcCheck);	
//
//		if(StoreOilBoxModel((stcModelCard *)&l_sModelCard))
//		{
//			SetSucceedIndicate();
//			return	1;
//		}
//		else
//		{
//			StoreErrIndicate();
//			return	0;
//		}
//	}
//	
//	CrcCheckErrIndicate();	
//
//	return	0;
//} 
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	DensityCard(stcCardFlg	sCardFlg)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
////uint8	DensityCard(stcCardFlg *	sCardFlg)
////{
////	static	stcDensity	sDensity;						//密度
////	uint16		CrcCheck;
////	
////	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
////	
////	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
////	{
////		sDensity = sCardFlg->sCardPara.sDensity;
////		
////		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
////		
////		if(CrcCheck == sDensity.CrcCheck)				//校验和相等		
////		{			
////			//PrintfDebug("\r\n sDensity.Density %d",sDensity.Density );
////			
////			if(StoreDensity((stcDensity *)&sDensity))
////			{
////				DisplaySet(150,1,"%d",sDensity.Density);
////				
////				SetSucceedIndicate();	
////				
////				return	1;
////			}
////			else
////			{
////				StoreErrIndicate();	
////				
////				return	0;
////			}
////		}
////	}
////	
////	CrcCheckErrIndicate();
////		
////	return	0;
////}

uint8	ReadCardPara(stcCardPara * sCardPara)
{
	uint16		CrcCheck;
	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType),
			(uint8 *)sCardPara,sizeof(stcCardPara));

	CrcCheck = GetCrc16Check((uint8 *)sCardPara,sizeof(stcCardPara) - 2);
	
	if(CrcCheck == sCardPara->CrcCheck)		
	{
		return	1;
	}
	else
	{
		return	0;
	}
}

uint8	WriteCardPara(stcCardPara * sCardPara)
{
	uint16		CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)sCardPara,sizeof(stcCardPara) - 2);

	sCardPara->CrcCheck = CrcCheck;

	WriteCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType),
			(uint8 *)sCardPara,sizeof(stcCardPara));
	
	return 1;	
}

uint16	GetCardDensityVal(void)
{
	stcDensity	sDensity;						//密度
	stcCardPara	sCardPara;
	uint16		CrcCheck;
	
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sDensity = sCardPara.sDensity;
		
		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
		
		if(CrcCheck == sDensity.CrcCheck)				//校验和相等		
		{			
			if(StoreDensity((stcDensity *)&sDensity))
			{
				DisplaySet(150,1,"%d",sDensity.Density);
				
				SetSucceedIndicate();	
				
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				
				return	0;
			}
		}
	}
	
	CrcCheckErrIndicate();
		
	return	0;
}

uint8	DensityCard(void)
{
	stcDensity	sDensity;						//密度
	stcCardPara	sCardPara;
	uint16		CrcCheck;
	
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sDensity = sCardPara.sDensity;
		
		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
		
		if(CrcCheck == sDensity.CrcCheck)				//校验和相等		
		{			
			if(StoreDensity((stcDensity *)&sDensity))
			{
				DisplaySet(150,1,"%d",sDensity.Density);
				
				SetSucceedIndicate();	
				
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				
				return	0;
			}
		}
	}
	
	CrcCheckErrIndicate();
		
	return	0;
} 
 
//
//extern	uint8 StoreDenChangeTimes(uint32  Times);
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshTimes(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
//extern	uint32 ReadDenChangeTimes(void);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	DenDataCard(stcCardFlg	sCardFlg)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
uint8	DenDataCard(stcCardFlg *	sCardFlg)
{

	DensityCard();

	DisplaySet(100,1,"DATA.");
	
	DataCard(0);												//数据卡，进行数据转取
		
	return	1;
} 

////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	DataDensityCard(stcCardFlg	sCardFlg)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//void	DataDensityCard(stcCardFlg *	sCardFlg)
//{
//	static	stcDensity	sDensity;						//密度
//	uint16		CrcCheck;
//	
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	
//	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
//	{
//		sDensity = sCardFlg->sCardPara.sDensity;
//		
//		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
//		
//		if(CrcCheck == sDensity.CrcCheck)				//校验和相等		
//		{			
//			if(sDensity.AddOilStationNum == 1)
//			{
//				//PrintfDebug("\r\n sDensity.Density %d",sDensity.Density );
//				
//				if(StoreDensity((stcDensity *)&sDensity))
//				{
//					SetSucceedIndicate();	
//				}
//			}
//		}
//	}	
//} 
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void	ComModCard(stcCardFlg	sCardFlg)
////函数功能:           	特殊模型卡
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//uint8	ComModCard(stcCardFlg	* sCardFlg)
//{
//	static	stcModelComplex	sModelComplex;	
//	uint32	CardAddLen = 0;
//	uint32	FlshAddLen = 0;
//	uint8	i;
//	uint8	CardFlg;
//	uint8	FlshFlg;
//	uint8   *p;
//	uint32	j;
//	
//	FlshAddLen = 0;
//		
//	UnProtectFlash();
//	
//	CardAddLen = sizeof(stcModelCard);
//
//	for(i = 0; i< 1; i++)
//	{
//		CardFlg = ReadCard(CARD_DATA_ADDR + CardAddLen,(uint8 *)&sModelComplex,sizeof(stcModelComplex));
//		FlshFlg = WriteFlsh(FRAM_SIZE + FlshAddLen,(uint16 *)&sModelComplex,sizeof(stcModelComplex));
//    	
//    	p = (uint8 *)&sModelComplex;
//    	
//    	
//    	
//    	
//    	
//    	//printfcom0("\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
//    	for(j=0;j < sizeof(stcModelComplex);j++)
//    	{
//    		//printfcom0("%2x",*(p++));
//    	}
//    	//printfcom0("\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
//
//    	//printfcom0("\r\n  ModelNum %d;i =%d,CardFlg %d,CARD_DATA_ADDR + CardAddLen %d",sModelComplex.ModelNum,i,CardFlg,CARD_DATA_ADDR + CardAddLen);
//
//		////printfcom0("\r\n\r\n  OilBoxTypCod  %d   %d \r\n",OilBoxTypCod,sComplexModel->ModelNum);
//
//		CardAddLen += sizeof(stcModelComplex);
//		FlshAddLen += sizeof(stcModelComplex);
//	}
//	
//
//	ProtectFlash();
//
//	if(CardFlg == TRUE && FlshFlg == TRUE)
//	{
//		SetSucceedIndicate();
//		DisplaySet(60,2,"SETS");	
//		DisplaySet(60,2,"        ");	
//	}
//	else
//	{
//		DisplaySet(60,2,"ERRO");	
//		DisplaySet(60,2,"        ");	
//		//printfcom0("\r\n CardFlg =%d,FlshFlg =%d,",CardFlg,FlshFlg);
//	}
//	
//	return	1;
//} 
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void	DensityCard(stcCardFlg	sCardFlg)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//uint8	TimeCard(stcCardFlg	* sCardFlg)
//{
///*
//	stcTime			sTime;							
//	uint16			CrcCheck;
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	
//	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
//	{
//		sTime = sCardFlg->sCardPara.sTime;
//		
//		CrcCheck = GetCrc16Check((uint8 *)&sTime,sizeof(sTime) - 2);
//		
//		if(CrcCheck == sTime.CrcCheck)				//校验和相等		
//		{
//			DisplaySet(100,1,"STIM");	
//			
//			WriteTime(sTime);
//	
//			SetSucceedIndicate();	
//			return	1;
//		}
//	}
//	
//	CrcCheckErrIndicate();
//*/		
//	return	0;
//} 
//
////extern	void	UsbSetAddDipVal( int16	Dip );
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	SetDataCard(stcCardFlg	* sCardFlg)
////函数功能:             置数据卡
////入口参数:             整个卡结构体
////出口参数:             是否成功
////--------------------------------------------------------------------------------------------------
uint8	SetDataCard(void)
{
	stcCardPara	sCardPara;
	
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
//		 AddDipVal = sCardPara.SetVal;
	}
	
	return 1;
} 


////-------------------------------------------------------------------------------------------------
////函数名称:             void	HightCard(stcCardFlg	sCardFlg)
////函数功能:             高度修正卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
uint8	HightCard(void)
{
	stcReviseHight	sReviseHight;							//高度调整
	uint16		CrcCheck;
	int16		StoreHight;	
	stcCardPara	sCardPara;
		
	if(ReadReviseHight((stcReviseHight *)&sReviseHight))
	{
		StoreHight = sReviseHight.ReviseHight;
	}
	else
	{
		StoreHight = 0;
	}
		
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sReviseHight = sCardPara.sReviseHight;
		
		CrcCheck = GetCrc16Check((uint8 *)&sReviseHight,sizeof(sReviseHight) - 2);
		
		if(CrcCheck == sReviseHight.CrcCheck)				//校验和相等		
		{
		//	DisplaySet(150,1,"SHIG");
			StoreHight = StoreHight + sReviseHight.ReviseHight; 	
			if(StoreHight > 500 ||  StoreHight < -500)
			{
				if(StoreHight > 500)
				{
					sReviseHight.ReviseHight = 500;
					DisplaySet(60,2,"TO_H");
					DisplaySet(60,2,"    ");
					DelayX10ms(250);
				}
				else
				{
					sReviseHight.ReviseHight = -500;
					DisplaySet(60,2,"TO_L");
					DisplaySet(60,2,"    ");
					DelayX10ms(250);					
				}
			}
			else
			{
				sReviseHight.ReviseHight = StoreHight;
			}
			
			CrcCheck = GetCrc16Check((uint8 *)&sReviseHight,sizeof(sReviseHight) - 2);
			sReviseHight.CrcCheck = CrcCheck;
			
			if(StoreReviseHight((stcReviseHight *)&sReviseHight))
			{
				DisplaySet(150,1,"%d",sReviseHight.ReviseHight);

				SetSucceedIndicate();	
				
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				
				return	0;
			}
		}
	}
	
	CrcCheckErrIndicate();
		
	return	0;
} 

////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	ModelSelectCard(stcCardFlg	* sCardFlg)
////函数功能:             模型选择卡
////入口参数:             整个卡结构体
////出口参数:             是否成功
////--------------------------------------------------------------------------------------------------
uint8	ModelSelectCard(void)
{
	uint8			ModelNum;							

	stcCardPara	sCardPara;

	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		ModelNum = sCardPara.SetVal;

		if(StoreSelectModel(ModelNum))
		{
			DisplaySet(150,1,"%d",ModelNum);			
			SetSucceedIndicate();	
			
			return	1;
		}
		else
		{
			StoreErrIndicate();	
			
			return	0;
		}
		
	}
	
	CrcCheckErrIndicate();
		
	return	0;
}
//
//extern	float		l_Density;		
//extern	float  		l_ReviseHight;              		//修正高度
//extern  void		ReCalPara(uint8	Flg);
//extern	int16  		GetDip1Prs(void);
//extern	int16  		GetDip2Prs(void);
//extern	uint8  		GetOilBoxCod(void);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	DebugCard(stcCardFlg	* sCardFlg)
////函数功能:             调试卡
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//uint8	DebugCard(stcCardFlg	* sCardFlg)
//{
//	uint32	AllStrLen = 0;
//	int16	CurDip1Prs;
//	int16	CurDip2Prs;
//	uint8	ModNum;
//	uint16	Density;
//	uint16	Hight;
//	uint16	CrcCheck;
//	
//	ReCalPara(1);
//
//	CurDip1Prs	=	GetDip1Prs();
//	CurDip2Prs	=	GetDip2Prs();
//	ModNum		=  	GetOilBoxCod();
//	Density		=  	(uint16)(l_Density*1000);
//	Hight		= 	(uint16)l_ReviseHight;
//	
//	DisplaySet(150,1,"DIP1");								
//	DisplaySet(200,1,"%d",CurDip1Prs);					
//	
//	DisplaySet(150,1,"DIP2");								
//	DisplaySet(200,1,"%d",CurDip2Prs);					
//	
//	DisplaySet(150,1,"MODE");								
//	DisplaySet(200,1,"C_%d",ModNum);							
//	
//	DisplaySet(150,1,"DENS");
//	DisplaySet(200,1,"%d",Density);
//	
//	DisplaySet(150,1,"HIGH");
//	DisplaySet(200,1,"%d",Hight);	
//	
//	PrintfTime();
//	DisplayTime();
//
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&CurDip1Prs,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&CurDip2Prs,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&ModNum,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&Density,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&Hight,2);
//	
//	AllStrLen += 2;
//	sCardFlg->sCardPara.sDebugCard.BufLen = AllStrLen;			//有效数据长度
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara.sDebugCard,sizeof(sCardFlg->sCardPara.sDebugCard )- 2);
//	sCardFlg->sCardPara.sDebugCard.CrcCheck = CrcCheck;
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	sCardFlg->sCardPara.CrcCheck = CrcCheck;	
//	
//	CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) - 2);
//	sCardFlg->CrcCheck = CrcCheck;		
//	
//	WriteCardFlg(sCardFlg);										//修改IC卡标志页	
//	
//	return 	1;
//	
///*
//	static	stcDebugCard	sDebugCard;							//高度调整
//	uint16	CrcCheck;
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	
//	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
//	{
//		sDebugCard = sCardFlg->sCardPara.sDebugCard;
//		
//		CrcCheck = GetCrc16Check((uint8 *)&sDebugCard,sizeof(sDebugCard) - 2);
//		
//		if(CrcCheck == sDebugCard.CrcCheck)				//校验和相等		
//		{
//			DisplaySet(100,1,"SDBG");	
//			
//			if(StoreReviseHight((stcReviseHight *)&sDebugCard))
//			{
//				SetSucceedIndicate();	
//				
//				return	1;
//			}
//			else
//			{
//				StoreErrIndicate();	
//				
//				return	0;
//			}
//		}
//	}
//	
//	CrcCheckErrIndicate();
//		
//	return	0;
//*/
//}
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	FixCard(stcCardFlg	* sCardFlg)
////函数功能:             高度修正卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
uint8	FixCard(void)
{
	stcFixInfo		sFixInfo;							//高度调整
	uint16		CrcCheck;
	stcCardPara	sCardPara;

	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sFixInfo = sCardPara.sFixInfo;
		
		CrcCheck = GetCrc16Check((uint8 *)&sFixInfo,sizeof(sFixInfo) - 2);
		
		if(CrcCheck == sFixInfo.CrcCheck)				//校验和相等		
		{
			DisplaySet(100,1,"%d",sFixInfo.LocoTyp);	
			DisplaySet(100,1,"%d",sFixInfo.LocoNum[1]*256+sFixInfo.LocoNum[0]);	
			
			if(StoreFixInfo((stcFixInfo *)&sFixInfo))
			{
				SetSucceedIndicate();	
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				return	0;
			}
		}

	}
	
	CrcCheckErrIndicate();
		
	return	0;
} 
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	CopyFramCard(stcCardFlg	* sCardFlg)
////函数功能:             高度修正卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//uint8	CopyFramCard(stcCardFlg	* sCardFlg)
//{
//	DisplaySet(100,1,"CFRA");	
//
//	FramToCard();
//	
//	SetSucceedIndicate();	
//	
//	return	1;
//} 
//
#define	TIME_ADD_CARD	0x01
#define	TIME_SUB_CARD	0x02
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	ExpandCard(stcCardFlg	* sCardFlg)
////函数功能:             扩展卡
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
uint8	ExpandCard(void)
{
	uint8	CardType;
	uint32	i;
	uint32	DisTime = 40;		//500ms
	uint32	Time 	= 0;		//500ms
	uint32	Times 	= 0;	
	
	stcTime		sTime;
	stcCardPara	sCardPara;

	if(!ReadCardPara((stcCardPara *)	&sCardPara))
	{	return 0;}


/*	
#ifdef	HARD_VER_090426	
	DisplaySet(150,1,"%u-%u-%u",sTime.Year,sTime.Month,sTime.Date);
	DisplaySet(60,1,"         ");	
	DisplaySet(350,1,"%u-%u-%u.",sTime.Hour,sTime.Min,sTime.Sec);	//等待时间补充
	DisplaySet(60,1,"         ");	
#endif
*/
	CardType = sCardPara.Reserve0;							//卡类型
	
	ReadTime((stcTime *)&sTime);
	i = sTime.Sec + sTime.Min * 60 +  sTime.Hour * 60 * 60;	

	while(1)
	{
		if(CardType == TIME_ADD_CARD)	
		{
			i++;
		}	
		else if(CardType == TIME_SUB_CARD)	
		{
			i--;	
		}
		else
		{
			//printfcom0("\r\n 不是时间卡");
			break;
		}
		
		i = i % (60*60*24);
		
		Times++;
		
		sTime.Sec  =   i % 60;
		sTime.Min  =  (i / 60 ) % 60;
		sTime.Hour =  ((i/60)/60) % 24;
		
		DisplaySet(1,1,"%02u-%02u-%02u.",sTime.Hour,sTime.Min,sTime.Sec);		//
		DelayX10ms(1);		

		Time = GetSysTime();
		while(GetSysTime() - Time < DisTime)
		{
		//SysHoldTast();;
		}
		
		if(DisTime > 4)
		{
			DisTime -= Times/10;		
		}
		
		if(GetPlugFlg() != PLUG_IN_CARD)
		{
			DelayX10ms(200);
			WriteTime(sTime);
			DelayX10ms(100);
			break;
		}
	}
	
	return	1;
} 
