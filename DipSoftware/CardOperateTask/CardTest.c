//#include 	"config.h"
//#include 	"String.h"
//#include	"Globe.h"
//#include	"HardDrive.h"
//#include	"CpuDrive.h"
//#include	"OperateCard.h"
//#include	"FramStore.h"
//#include	"DipMath.h"

#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h"
#include	"FRAM.h"

stcCardFlg		m_sCardFlg;
stcModelCard	m_sModelCard;
stcModel		m_sModel;

extern uint8    GetDf7G60OilBoxModel(stcModel * sModel);
extern uint8    GetDf7G80OilBoxModel(stcModel * sModel);
extern uint8    GetDf7G20OilBoxModel(stcModel * sModel);
extern uint8    GetDf7G50OilBoxModel(stcModel * sModel);
extern uint8    GetDf12G50OilBoxModel(stcModel * sModel);
extern uint8    GetDf7C5675OilBoxModel(stcModel * sModel);

///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
//名    称：    estDipModel(void)(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
//uint8    WriteCardOilModelTest(void)
//{
//	uint16			CardType;
//	uint16			CrcCheck;
//	uint32			i;
//	
//	CardType = MODEL_CARD;
//	
//	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
//	
//	for(i = 0 ; i < 3; i++)
//	{
//		m_sCardFlg.sCardType.CardType[i] = CardType;
//	}
//	
//	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
//	m_sCardFlg.sCardType.CrcCheck = CrcCheck;
//	
//	GetDf4bOilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[0] = m_sModel;
//	
//	GetDf4dOilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[1] = m_sModel;
//	
//	GetDf5OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[2] = m_sModel;
//	
//	GetDf7cOilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[3] = m_sModel;
//	
//	GetDf8bOilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[4] = m_sModel;
//
//	GetDf11OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[5] = m_sModel;
//
//	GetDf8OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[6] = m_sModel;
//	
//	GetDf7xOilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[7] = m_sModel;	
//	
//	GetDf7G60OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[9] = m_sModel;	
//	
//	GetDf7G80OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[10] = m_sModel;	
//		
//	GetDf7G20OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[11] = m_sModel;	
//	
//	GetDf7G50OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[12] = m_sModel;		
//	
//	GetDf12G40OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[13] = m_sModel;			
//	
//	GetDf12G50OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[14] = m_sModel;			
//	
//	GetDf12G17OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[15] = m_sModel;			
//	
//	GetDf5G20OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[16] = m_sModel;			
//	
//	GetDf7C5675OilBoxModel((stcModel *)&m_sModel);
//	m_sModelCard.sModel[17] = m_sModel;		
//		
//	CrcCheck = GetCrc16Check((uint8 *)&m_sModelCard,sizeof(stcModelCard) - 2);
//	m_sModelCard.CrcCheck	= CrcCheck;	
//
//	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
//	CrcCheck	= CrcCheck;	
//	
//	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
//	m_sCardFlg.CrcCheck = CrcCheck;
//	
//	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
//	
//	WriteCard(CARD_DATA_ADDR,(uint8 *)&m_sModelCard,sizeof(stcModelCard));
//
//	return 1;
//}

extern	void   stcModelTostcModelComplex(stcModelComplex * sComplexModel,stcModel	* sModel);

//------------------------------------------------------------------------------
//名    称：    estDipModel(void)(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
//uint8    WriteCardComModelTest(void)
//{
//	uint16			CardType;
//	uint16			CrcCheck;
//	uint32			i;
//	static			stcModelComplex	sModelComplex;	
//	uint32			CardAddLen = 0;
//	uint8			CardFlg;
//	 
//	CardType = COM_MODEL_CARD;
//	
//	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
//	
//	for(i = 0 ; i < 3; i++)
//	{
//		m_sCardFlg.sCardType.CardType[i] = CardType;
//	}
//	
//	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
//	m_sCardFlg.sCardType.CrcCheck = CrcCheck;
//	
//	CardAddLen = sizeof(stcModelCard);
//	
//	for(i = 0; i< 1; i++)
//	{
//		GetDf7cOilBoxModel((stcModel *)&m_sModel);
//		stcModelTostcModelComplex((stcModelComplex *)&sModelComplex,(stcModel *)&m_sModel);				//100829
//
//		sModelComplex.ModelNum  = 32;
//		//printfcom0("\r\n sModelComplex.ModelNum 31 +i= %d ",sModelComplex.ModelNum);
//		CrcCheck = GetCrc16Check((uint8 *)&sModelComplex,sizeof(stcModelComplex) - 2);
//		sModelComplex.CrcCheck  	= CrcCheck;
//    	CardFlg = WriteCard(CARD_DATA_ADDR + CardAddLen,(uint8 *)&sModelComplex,sizeof(stcModelComplex));
//
//		CardAddLen += sizeof(stcModelComplex);
//
//	}
//	
////	CrcCheck = GetCrc16Check((uint8 *)&m_sModelCard,sizeof(stcModelCard) - 2);
////	m_sModelCard.CrcCheck	= CrcCheck;	
//
//	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
//	CrcCheck	= CrcCheck;	
//	
//	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
//	m_sCardFlg.CrcCheck = CrcCheck;
//	
//	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
//	
////	WriteCard(CARD_DATA_ADDR,(uint8 *)&m_sModelCard,sizeof(stcModelCard));
//
//	return 1;
//}
//------------------------------------------------------------------------------
//名    称：    uint8    WriteCardDataCardTest(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WritesSetDipCardTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;

	CardType = SET_DATA_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	m_sCardFlg.sCardPara.SetVal = 10;				//油量增加10

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
	
	m_sCardFlg.WriteCardTimes = 0;
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
		
	return 1;
}

extern	void	ReCalPara(uint8	Flg);

//------------------------------------------------------------------------------
//名    称：    uint8    WriteCardDataCardTest(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WritesTestCardTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;

	CardType = DEBUG_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
	
	m_sCardFlg.WriteCardTimes = 0;
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
		
	return 1;
}
//------------------------------------------------------------------------------
//名    称：    uint8    WriteCardDataCardTest(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteCardDataCardTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;

	CardType = DATA_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
	
	m_sCardFlg.WriteCardTimes = 0;
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
		
	return 1;
}


//------------------------------------------------------------------------------
//名    称：    estDipModel(void)(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteCardTimeCardTest(void)
{
/*
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
	
	CardType = TIME_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;
	
	//09-10-15 11:20:00
	m_sCardFlg.sCardPara.sTime.Sec 	= 0;
	m_sCardFlg.sCardPara.sTime.Min 	= 20;
	m_sCardFlg.sCardPara.sTime.Hour	= 11;
	m_sCardFlg.sCardPara.sTime.Date 	= 15;
	m_sCardFlg.sCardPara.sTime.Month 	= 10;
	m_sCardFlg.sCardPara.sTime.Year	= 9;
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara.sTime,sizeof(m_sCardFlg.sCardPara.sTime) - 2);
	m_sCardFlg.sCardPara.sTime.CrcCheck	= CrcCheck;
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
	
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
*/
	return 1;

}

//------------------------------------------------------------------------------
//名    称：    WriteDensityCardTest(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteDensityCardTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
		
	CardType = DENSITY_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.sDensity.Density	= 835;	
		
	//PrintfDebug("\r\n sDensity.Density %d",m_sCardFlg.sCardPara.sDensity.Density);

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara.sDensity,sizeof(m_sCardFlg.sCardPara.sDensity) - 2);
	m_sCardFlg.sCardPara.sDensity.CrcCheck	= CrcCheck;	
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
		
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
			
	return 1;
}

//------------------------------------------------------------------------------
//名    称：    WriteDensityCardTest(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteDenDataCardTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
		
	CardType = DENSITY_CARD+DATA_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.sDensity.Density	= 830+(GetSysTime()/100)%50;	
		
	m_sCardFlg.sCardPara.sDensity.DenChageTimes = 10+GetSysTime();
		
	//PrintfDebug("\r\n sDensity.Density %d",m_sCardFlg.sCardPara.sDensity.Density);

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara.sDensity,sizeof(m_sCardFlg.sCardPara.sDensity) - 2);
	m_sCardFlg.sCardPara.sDensity.CrcCheck	= CrcCheck;	
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
		
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
			
	return 1;
}
//------------------------------------------------------------------------------
//名    称：    WriteCopyCardTest(void)
//功    能：    复制卡
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteCopyCardTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
		
	CardType = COPY_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
			
	return 1;
}


//------------------------------------------------------------------------------
//名    称：    WriteCopyCardTest(void)
//功    能：    复制卡
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteCopyFramTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
		
	CardType = COPY_FRAM_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
			
	return 1;
}

//------------------------------------------------------------------------------
//名    称：    WriteCopyCardTest(void)
//功    能：    复制卡
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteExpandAddTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
		
	CardType = EXPAND_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	m_sCardFlg.sCardPara.Reserve0	= 1;		
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
		
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
			
	return 1;
}

//------------------------------------------------------------------------------
//名    称：    WriteCopyCardTest(void)
//功    能：    复制卡
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
uint8    WriteExpandSubTest(void)
{
	uint16		CardType;
	uint16		CrcCheck;
	uint32		i;
		
	CardType = EXPAND_CARD;
	
	ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
	
	for(i = 0 ; i < 3; i++)
	{
		m_sCardFlg.sCardType.CardType[i] = CardType;
	}
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardType,sizeof(m_sCardFlg.sCardType) - 2);
	m_sCardFlg.sCardType.CrcCheck = CrcCheck;

	m_sCardFlg.sCardPara.Reserve0	= 2;		
	
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg.sCardPara,sizeof(m_sCardFlg.sCardPara) - 2);
	m_sCardFlg.sCardPara.CrcCheck	= CrcCheck;	
		
	CrcCheck = GetCrc16Check((uint8 *)&m_sCardFlg,sizeof(m_sCardFlg) - 2);
	m_sCardFlg.CrcCheck = CrcCheck;
		
	WriteCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg));
			
	return 1;
}
//------------------------------------------------------------------------------
//名    称：    ReadCardIndexTest(void)
//功    能：    Df5油箱模型
//入口参数：    无
//出口参数：    Df5的油箱模型
//------------------------------------------------------------------------------
//uint8    ReadCardIndexTest(void)
//{
//	uint16		CardType;
//	uint32		i;
//		
//	CardType = DENSITY_CARD;
//	
//	if(ReadCard(CARD_FLG_ADDR,(uint8 *)&m_sCardFlg,sizeof(m_sCardFlg)))
//	{		
//		//printfcom0("\r\nWriteCardTimes %d",m_sCardFlg.WriteCardTimes);
//		
//		for(i = 0 ; i < 100; i++)
//		{	
//			//SysFastHoldTast();
//
//			//PrintfDebug("\r\nStartAddr[%d] %d, EndAddr[%d] %d",
//			//			i,m_sCardFlg.sCardIndex[i].StartAddr,i,m_sCardFlg.sCardIndex[i].EndAddr);
//		}
//	}
//
//	return 1;
//}

//-------------------------------------------------------------------------------
//函数名称:        	stcFlshRec	ReadFlshRec(uint32	FlshRecNum)
//函数功能:       	读指定流水号的FLSH记录
//入口参数:        	无
//出口参数:      	指定流水号的Flsh记录
//-------------------------------------------------------------------------------
uint8	ReadCardRec(stcFlshRec * sFlshRec,uint32	Addr)
{
	if(ReadCard(Addr,(uint8 *)sFlshRec,sizeof(stcFlshRec)))
	{
		return 1;
	}
	
	return	0;
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void  ShowFlshRec(stcFlshRec sDip) 
//函数功能:             将记录转变为比较容易读的格式
//入口参数:             无
//出口参数:             无
//说明:                 
//--------------------------------------------------------------------------------------------------
//void  ShowCardRec(stcFlshRec sDip) 
//{
//	uint8       Second,Minute,Data,Mouth,Hour;
//	uint16      RelSpeed;
//	uint32      Time;
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
//    //printfcom0("\r\n%u-%u %u:%u:%u\t",Mouth,Data,Hour,Minute,Second);
//    ////printfcom0(" %u-%u %u:%u:%u,%u,%u,%u,%u,%u,%u",sDip.MyYear,sDip.MyMonth,sDip.MyHour,sDip.MyMinute,sDip.MySecond);   
//    //printfcom0(" %u,%u",RelSpeed,sDip.MstDip);      
//}

extern	uint16	l_CardType;
//-------------------------------------------------------------------------------------------------
//函数名称:             void  PrintfCardRec(void) 
//函数功能:             打印记录
//入口参数:             无
//出口参数:             无
//说明:                 
//--------------------------------------------------------------------------------------------------
//void  PrintfCardRec(void) 
//{
//	uint32	i;
//	uint32		StartRecAddr;		
//	stcFlshRec	sCardRec;					
//	uint32	Time;
//	
//	if(PlugICCard() == TRUE)										//有卡插入，再进行相关操作
//	{				
//		if(ReadCardFlg((stcCardFlg	*)&m_sCardFlg))					//读IC卡标志页
//		{
//			if( l_CardType == DATA_CARD )
//			{		
//				for(i = 0 ; i < m_sCardFlg.WriteCardTimes;i++ )
//				{
//					StartRecAddr = m_sCardFlg.sCardIndex[i].StartAddr;
//					
//					while(StartRecAddr < m_sCardFlg.sCardIndex[i].EndAddr)
//					{
//						ReadCardRec((stcFlshRec *)&sCardRec,StartRecAddr);
//						ShowCardRec(sCardRec);					//将记录打印出来
//						
//						StartRecAddr += sizeof(sCardRec);
//					}
//				}
//			}
//		}
//
//		Time = GetSysTime();
//		while(PlugICCard() == TRUE)									//等IC卡退出		
//		{
//			if(GetSysTime() - Time > 30*100)
//			{
//				break;
//			}
//		}			
//	}	
//}

//-------------------------------------------------------------------------------------------------
//函数名称:             void  FramToCard(void) 
//函数功能:             铁电数据到IC卡
//入口参数:             无
//出口参数:             无
//说明:                 
//--------------------------------------------------------------------------------------------------
void 	FramToCard(void) 
{
	static	uint8	Buf[FRAM_SIZE / 16];
	uint32	Addr = 0;
	uint32	i;
	
	for(i = 0;i < 16; i++)
	{
		ReadFM24CL64(Addr,Buf,sizeof(Buf));
		
		WriteCard(Addr + CARD_DATA_ADDR,Buf,sizeof(Buf));
		
		Addr += sizeof(Buf);
	}
}
