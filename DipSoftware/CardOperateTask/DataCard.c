//#include 	"config.h"
//#include 	"String.h"
//#include	"Globe.h"
//#include	"HardDrive.h"
//#include	"StoreRec.h"
//#include	"CpuDrive.h"
//#include	"FramStore.h"
//#include	"OperateCard.h"
//#include	"stdlib.h" 

#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h"
//#include	"flash.h"

#define		CARD_BUF_LEN		1024			//IC卡处理缓冲区大小	


//----------------------------------------------------------------------
//函数名称:  	uint32  GetWritePageLen(uint32 Start, uint32 WriteLen,uint32 MaxWriteLen)
//函数功能:  	求写将要完成下页写长度
//入口参数:   	StartAddr:IC卡起始写地址;FinishLen:已写地址,MaxWriteLen:要写地址
//出口参数:   	
//说明:                 
//-----------------------------------------------------------------------
uint32  GetWritePageLen(uint32 StartAddr, uint32 FinishLen,uint32 MaxWriteLen)
{
    uint32  	PageSize;
    uint32  	PageSegLen;
    uint32  	NoWriteLen;
	
	PageSize = GetCardPageSize();
	
    PageSegLen = PageSize - ((StartAddr + FinishLen) % PageSize);		//从首往尾写

    NoWriteLen = MaxWriteLen - FinishLen;

    if( PageSegLen < NoWriteLen)
    {
         return PageSegLen;
    }
    else
    {
        return  NoWriteLen;
    }
}

//----------------------------------------------------------------------
//函数名称:  	stcFlshRec    FlshRecToCardRec( stcFlshRec   sFlshRec)
//函数功能:  	将油尺记录FLASH转化为IC卡记录
//入口参数:   	FLASH记录
//出口参数:   	IC卡记录
//说明:                 
//-----------------------------------------------------------------------
stcFlshRec    FlshRecToCardRec( stcFlshRec   sFlshRec)
{
	stcFlshRec  sCardRec;		
	memcpy((uint8 *)&sCardRec,(uint8 *)&sFlshRec,sizeof(sCardRec));
	
	return	sCardRec;
}

//extern	void	SysHoldTast(void);

//----------------------------------------------------------------------
//函数名称:  	void    ReadCardDisplay(uint8	 Sct)
//函数功能:  	将油尺记录FLASH转化为IC卡记录
//入口参数:   	FLASH记录
//出口参数:   	IC卡记录
//说明:                 
//-----------------------------------------------------------------------
void    ReadCardDisplay(uint8	 Sct)
{
	uint8	i = 0;
	
//	if(GetSysTime() % 100 < 12)
	{
		i = 0;
		while(i < 10 )
		{
			DisplaySet(10,2,"%u  %u",Sct,i);
			i++;
		}
		
		//OnLed(WRITE_CARD_LED,10,5,5);
	}													//xitong 
}

//----------------------------------------------------------------------
//函数名称:  	uint8  StoreCardRec(uint32   FlshStartRecNum,uint32	FlshRecCnt,uint32	CardStartAddr )
//函数功能:  	存IC卡记录
//入口参数:   	FlshStartRecNum:起始Flsh记录号,FlshRecCnt:记录个数,StartCardRecAddr:IC卡起始地址
//出口参数:   	
//说明:                 
//-----------------------------------------------------------------------
uint8  StoreCardRec(uint32   FlshStartRecNum,uint32	FlshRecCnt,uint32	CardStartAddr,uint32	WriteTimes )
{
	uint8			CardBuf[1024];
	uint32			FlshRecNum;											//Flsh记录流水号
	uint32			MaxWriteLen;										//最大要写卡长度
	uint32			FinishLen = 0;										//已写长度
	uint32			WritePageLen;	
	uint32			NextRecCardAddr;
	uint32			BufWriteLen = 0;
	
	stcFlshRec		sFlshRec;
	
	FlshRecNum	= FlshStartRecNum;
	MaxWriteLen = FlshRecCnt * sizeof(sFlshRec);					
				
	BufWriteLen = 0;
	while( FinishLen < MaxWriteLen)
	{
		ReadFlshRec((stcFlshRec *)&sFlshRec,FlshRecNum++);

		WritePageLen = GetWritePageLen(CardStartAddr,FinishLen,MaxWriteLen);
			
		memcpy(&CardBuf[BufWriteLen],(uint8 *)&sFlshRec,sizeof(sFlshRec));
		BufWriteLen += sizeof(sFlshRec);

		if(WritePageLen == BufWriteLen || WritePageLen < BufWriteLen)
		{
			NextRecCardAddr = CardStartAddr + FinishLen;				//IC卡下一地址
			 	
   			WriteCard(NextRecCardAddr,CardBuf,WritePageLen);      		//写卡
     		
     		FinishLen += WritePageLen;									//将要完成写长度

     		ReadCardDisplay(WriteTimes);								//指示正在读卡

			BufWriteLen = 0;
		}
		if(GetPlugFlg() == NO_PLUG_IN_CARD)								//拨卡退出
		{
			return FALSE;
		}
	}

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
//函数名称:             uint32	GetReadFlshRecCnt(uint32 ZoneMaxRecNum)	   
//函数功能:             取分区应读取的记录数
//入口参数:             分区最大记录数
//出口参数:             记录数
//--------------------------------------------------------------------------------------------------
uint32	GetReadFlshRecCnt(uint32 NoReadRecNum,uint32 ZoneMaxRecNum)
{	
	uint32	FlshMaxRec;
	
	FlshMaxRec = (FLSH_MAX_SIZE)/(sizeof(stcFlshRec));
	
	////printfcom0("\r\n FlshMaxRec %d",FlshMaxRec);
	if(NoReadRecNum >= ZoneMaxRecNum)
	{
		if(ZoneMaxRecNum > FlshMaxRec)
		{
			return	FlshMaxRec;
		}
		
		return	ZoneMaxRecNum;
	}
	else
	{
		if(NoReadRecNum > FlshMaxRec)
		{
			return	FlshMaxRec;
		}
			
		return	NoReadRecNum;
	}
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateWriteCardFinsh(void)
{
	DelayX10ms(10);	
	ClaerDisplaySetWithoutStore();
//	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"good");
	DisplaySet(60,100,"    ");	
	//printfcom0("\r\n Good!!");
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFlgErr(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateWriteCardFlgErr(void)
{
	DelayX10ms(10);	
	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"E_IC");
	DisplaySet(60,100,"    ");	
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFlgErr(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateUSBFlgErr(void)
{
	DelayX10ms(10);	
	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"E_US");
	DisplaySet(60,100,"    ");	
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	IndicateRecordFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateRecordFinsh(void)
{
	DelayX10ms(10);	
	ClaerDisplaySetWithoutStore();
	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"ALL");
	DisplaySet(60,100,"    ");	
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateCardFull(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,100,"FULL");
	DisplaySet(60,100,"    ");
	OnLed(CARD_FULL_LED,0xffffff,5,5);
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	void	IndicateWriteCardFinsh(void)	   
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	IndicateWriteNoFinsh(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NUNF");
	DisplaySet(60,0xffff,"    ");
}

uint8	l_UnFihCardEvtFlg = NO_ERROR;
//uint8	l_WriteFlgErrCardEvtFlg = NO_ERROR;

void	DataDensityCard(stcCardFlg *	sCardFlg);
////-------------------------------------------------------------------------------------------------
////函数名称:             void	OperationNormCard(void);	   
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//void	DataCard(void)
//{
//	uint32	FlshRecCnt;	
//	uint32	FlshStartRecNum;
//	uint32	CardEndAddr;
//	uint32	CardStartAddr;
//	uint32	CardMaxRecNum;
//	uint32	NoReadRecNum;
//	uint16	CrcCheck;
//	static	stcDeviceInfo 	sDeviceInfo;
//	static	stcFixInfo		sFixInfo;						
//	
//	//PrintfDebug("\r\nDataCard");
//	
////	DataDensityCard(sCardFlg);  					//数据密度卡
//	
//	g_LshRedFlshRecNum = ReadLstRedFlshRecNum();
//	
//	if(sCardFlg->WriteCardTimes >= 100)	
//	{	
//		sCardFlg->WriteCardTimes = 0;
//	}
//		
//	if(sCardFlg->WriteCardTimes == 0)
//	{
//		CardStartAddr = CARD_DATA_ADDR;
//	}
//	else
//	{
//		CardStartAddr 	= sCardFlg->sCardIndex[sCardFlg->WriteCardTimes - 1].EndAddr;
//		
//		if(CardStartAddr < CARD_DATA_ADDR)
//		{
//			CardStartAddr = CARD_DATA_ADDR;
//		}
//	}
//	
//	if(g_CurFlshRecNum > g_LshRedFlshRecNum)
//	{
//		NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);		//Flsh的未读记录长度
//	}
//	else
//	{
//		NoReadRecNum = 0;
//	}
//	
//	CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);	//取IC卡未写空间长度
//		
//	FlshRecCnt 		= GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);	//要写数据长度
//	
//	FlshStartRecNum = g_CurFlshRecNum  - FlshRecCnt ;
//
//	////printfcom0("\r\nNoReadRecNum %d,CardMaxRecNum %d,FlshRecCnt %d,FlshStartRecNum %d sCardFlg->WriteCardTimes %d,GetToEndLen(CardStartAddr) %d",
//	//NoReadRecNum,CardMaxRecNum,FlshRecCnt,FlshStartRecNum,sCardFlg->WriteCardTimes,GetToEndLen(CardStartAddr));
//	//printfcom0("\r\n FlshStartRecNum %d NoReadRecNum %d",FlshStartRecNum,NoReadRecNum);
//
//	if((sCardFlg->WriteCardTimes < 100)  && ( CardMaxRecNum >20))			//卡写满
//	{
//		l_UnFihCardEvtFlg = NO_ERROR;
//
//		if( NoReadRecNum > 1 )												//未读记录条数须大于1才能读取数据	
//		{
//			if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,sCardFlg->WriteCardTimes))		//返回1 写卡完成
//			{
//				uint8	i;
//				uint8	Tmp;
//				uint16	DataTmp;
//				uint8	Buf[5] = {'0','0','0','0','0'};
//			
//				ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
//				
//				ReadFixInfo((stcFixInfo * )&sFixInfo);
//				
//				memcpy(sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].ProNum
//							,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
//		
//				DataTmp = sDeviceInfo.DeviceNum;
//				for(i = 0; i < 5;i++)
//				{
//					Tmp = DataTmp%10;
//					DataTmp /= 10;
//					if(DataTmp != 0)
//					{
//						Buf[5-1-i] = Tmp + '0';
//					}
//				}
//				
//				memcpy(&sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].LocoType[0]	= sFixInfo.LocoTyp;
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].LocoType[1]	= sFixInfo.E_LocoTyp;	
//				memcpy(sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].StartAddr	= CardStartAddr;
//				CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].EndAddr 		= CardEndAddr;
//				//sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecLen		= CardEndAddr - CardStartAddr;
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecLen		=  FlshRecCnt * sizeof(stcFlshRec);
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecNum		= FlshRecCnt;
//				
//				sCardFlg->WriteCardTimes++;									
//
//				CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) -2);
//
//				sCardFlg->CrcCheck = CrcCheck;									
//
//				WriteCardFlg(sCardFlg);									//修改IC卡标志页
//							
// 				if(CheckWriteCardFlgCrc(CrcCheck) == NO_ERROR)
// 				{
//					StoreLstRedFlshRecNum(g_CurFlshRecNum);				//存最新的已读记录流水号
//				
//					g_LshRedFlshRecNum = g_CurFlshRecNum;				//
// 				
//					IndicateWriteCardFinsh();							//
//					
//					DelayX10ms(10);	
//				}
//				else
//				{
//					l_WriteFlgErrCardEvtFlg = ERROR;
//					
//					sCardFlg->sCardID.Reserve1 = 65;					//重写标志页的标志
//					
//					CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) -2); //重写校验
//
//					sCardFlg->CrcCheck = CrcCheck;					
//					
//					WriteCardFlg(sCardFlg);									//重新修改IC卡标志页,不在判断
//	 				
//	 				if(CheckWriteCardFlgCrc(CrcCheck) == NO_ERROR)			//重新刷新
//	 				{
//						StoreLstRedFlshRecNum(g_CurFlshRecNum);				//存最新的已读记录流水号
//					
//						g_LshRedFlshRecNum = g_CurFlshRecNum;				//
//	 				
//						IndicateWriteCardFinsh();							//
//					}
//					else
//					{
//						IndicateWriteCardFlgErr();							//
//					}
//				}
//			}
//			else														//写卡错误操作
//			{
//				l_UnFihCardEvtFlg = ERROR;
//				
//				DelayX10ms(10);	
//				
//				IndicateWriteNoFinsh();									//写卡未完成指示
//				
//				DelayX10ms(500);										//未写完
//			}
//		}
//		else
//		{
//			IndicateWriteCardFinsh();									//
//		}
//	}
//	else
//	{
//		IndicateCardFull();
//	}
//} 

void	DataCard(uint8 copyflg)
{
	uint32	FlshRecCnt;	
	uint32	FlshStartRecNum;
	uint32	CardEndAddr;
	uint32	CardStartAddr;
	uint32	CardMaxRecNum;
	uint32	NoReadRecNum;
//	uint16	CrcCheck;
	stcDeviceInfo 	sDeviceInfo;
	stcFixInfo		sFixInfo;						
	uint16	WriteCardTimes;
	stcCardIndex	sCardIndex;
	uint32	CardAddrTmp;


	DelayX10ms(10);

	g_LshRedFlshRecNum = ReadLstRedFlshRecNum();
	if(copyflg == 1) //copy
	{
		g_LshRedFlshRecNum = 1;	
	}
	
	CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)+sizeof(stcCardPara)+sizeof(stcCardIndex)*100;
	ReadCard(CardAddrTmp,(uint8 *)&WriteCardTimes,sizeof(WriteCardTimes));	

	if(WriteCardTimes >= 100)	
	{	
		WriteCardTimes = 0;
	}
			
	if(WriteCardTimes == 0)
	{
		CardStartAddr = CARD_DATA_ADDR;
	}
	else
	{
		CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
				+sizeof(stcCardPara)+sizeof(stcCardIndex)*(WriteCardTimes-1);
		ReadCard(CardAddrTmp,(uint8 *)&sCardIndex,sizeof(stcCardIndex));

		CardStartAddr 	= sCardIndex.EndAddr;
		
		if(CardStartAddr < CARD_DATA_ADDR)
		{
			CardStartAddr = CARD_DATA_ADDR;
		}
	}

	CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
				+sizeof(stcCardPara)+sizeof(stcCardIndex)*WriteCardTimes;
	ReadCard(CardAddrTmp,(uint8 *)&sCardIndex,sizeof(stcCardIndex));
		
	if(g_CurFlshRecNum > g_LshRedFlshRecNum)
	{
		NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);		//Flsh的未读记录长度
	}
	else
	{
		NoReadRecNum = 0;
	}
	
	CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);	//取IC卡未写空间长度
		
	FlshRecCnt 		= GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);	//要写数据长度
	
	FlshStartRecNum = g_CurFlshRecNum  - FlshRecCnt ;

	printfcom0("\r\n %d,%d,%d,%d,%d",g_CurFlshRecNum,g_LshRedFlshRecNum,NoReadRecNum,FlshRecCnt,FlshStartRecNum);
	if((WriteCardTimes < 100)  && ( CardMaxRecNum >20))			//卡写满
	{
		l_UnFihCardEvtFlg = NO_ERROR;

		if( NoReadRecNum > 1 )												//未读记录条数须大于1才能读取数据	
		{
			if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,WriteCardTimes))		//返回1 写卡完成
			{
				uint8	i;
				uint8	Tmp;
				uint16	DataTmp;
				uint8	Buf[5] = {'0','0','0','0','0'};
			
				ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
				
				ReadFixInfo((stcFixInfo * )&sFixInfo);
				
				memcpy(sCardIndex.ProNum
							,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
		
				DataTmp = sDeviceInfo.DeviceNum;
				for(i = 0; i < 5;i++)
				{
					Tmp = DataTmp%10;
					DataTmp /= 10;
					if(DataTmp != 0)
					{
						Buf[5-1-i] = Tmp + '0';
					}
				}
				
				memcpy(&sCardIndex.ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
				sCardIndex.LocoType[0]	= sFixInfo.LocoTyp;
				sCardIndex.LocoType[1]	= sFixInfo.E_LocoTyp;	
				memcpy(sCardIndex.LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
				sCardIndex.StartAddr	= CardStartAddr;
				CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
				sCardIndex.EndAddr 		= CardEndAddr;
				//sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecLen		= CardEndAddr - CardStartAddr;
				sCardIndex.RecLen		=  FlshRecCnt * sizeof(stcFlshRec);
				sCardIndex.RecNum		= FlshRecCnt;
				
				WriteCardTimes++;									

				CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
							+sizeof(stcCardPara)+sizeof(stcCardIndex)*100; 
				WriteCard(CardAddrTmp,(uint8 *)&WriteCardTimes,sizeof(WriteCardTimes));	

				CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
							+sizeof(stcCardPara)+sizeof(stcCardIndex)*(WriteCardTimes-1); 
				WriteCard(CardAddrTmp,(uint8 *)&sCardIndex,sizeof(stcCardIndex));

				if(copyflg == 0)
				{
					StoreLstRedFlshRecNum(g_CurFlshRecNum);				//存最新的已读记录流水号
				
					g_LshRedFlshRecNum = g_CurFlshRecNum;				//
				}
				DelayX10ms(10);
				IndicateWriteCardFinsh();							//
				
				DelayX10ms(10);	
			}
			else														//写卡错误操作
			{
				l_UnFihCardEvtFlg = ERROR;
				
				DelayX10ms(10);	
				
				IndicateWriteNoFinsh();									//写卡未完成指示
				
				DelayX10ms(500);										//未写完
			}
		}
		else
		{
			IndicateWriteCardFinsh();									//
		}
	}
	else
	{
		IndicateCardFull();
	}

	printfcom0("\r\n %d,%d,%d,%d",FlshRecCnt,g_LshRedFlshRecNum,NoReadRecNum,FlshStartRecNum);

} 

extern  stcCardFlg	l_sCardFlg;
extern	uint16	l_CardType;

//-------------------------------------------------------------------------------------------------
//函数名称:             void	DataCardPartRead(void)
//函数功能:             普通卡处理
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	DataCardPartRead(void)
{
/*
	static	stcDeviceInfo 	sDeviceInfo;
	static	stcFixInfo		sFixInfo;		
	uint32	FlshRecCnt;	
	uint32	FlshStartRecNum;
	uint32	CardEndAddr;
	uint32	CardStartAddr;
	uint32	CardMaxRecNum;
	uint32	NoReadRecNum;
	uint16	CrcCheck;
	uint32	FinshRecCnt = 0;
	uint32	CardTime = 0;

	PrintfDebug("\r\nDataCard");
	
	ClaerDisplaySet();												//清显示缓冲区
	OffAllLed();													//关所有发光二极管
	OnLed(RUN_LED,30000,5,5);										//清显示缓冲区		
	//CloseTax2();
		
	PrintfDebug("\r\n OperationCard");
	
	DisplaySet(100,1,"PRCD");

	while(1)
	{
		if(PlugICCard() == TRUE)										//有卡插入，再进行相关操作
		{	
			ClaerDisplaySet();												//清显示缓冲区
				
			ReadCardFlg((stcCardFlg *)&l_sCardFlg);
			
			if( l_CardType == DATA_CARD )
			{
				CardTime++;
				
				if(l_sCardFlg.WriteCardTimes >= 100)	
				{	
					l_sCardFlg.WriteCardTimes = 0;
				}
					
				if(l_sCardFlg.WriteCardTimes == 0)						//地址对齐
				{
					CardStartAddr = CARD_DATA_ADDR;
				}
				else
				{
					CardStartAddr 	= l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes - 1].EndAddr;
					
					if(CardStartAddr < CARD_DATA_ADDR)
					{
						CardStartAddr = CARD_DATA_ADDR;
					}
					
					if((CardStartAddr - CARD_DATA_ADDR) %  sizeof(stcFlshRec))	//地址对齐
					{
						CardStartAddr = CardStartAddr - (CardStartAddr - CARD_DATA_ADDR) %  sizeof(stcFlshRec);
					}
				}
				
				g_LshRedFlshRecNum = 0;												//
				
				if((g_CurFlshRecNum - g_LshRedFlshRecNum) /(FLSH_MAX_SIZE/(sizeof(stcFlshRec))))
				{
					NoReadRecNum = FLSH_MAX_SIZE/(sizeof(stcFlshRec));
				}
				else
				{
					NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);			//Flsh的未读记录长度
				}
				
				if(NoReadRecNum <=  FinshRecCnt + 100)									//数据记录全读完
				{
					IndicateRecordFinsh();
					
					while(PlugICCard() == TRUE)
					{
						NOP();
					}
					
					break;
				}
				
				CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);		//取IC卡未写空间长度
					
				FlshRecCnt 		= GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);		//要写数据长度
				
				FlshStartRecNum = g_CurFlshRecNum  - FlshRecCnt -  FinshRecCnt;    		//开始本次写时起始流水号
				
				FinshRecCnt += FlshRecCnt;												//已完成的流水号个数

				//printfcom0("\r\nNoReadRecNum %d,CardMaxRecNum %d,FlshRecCnt %d,FlshStartRecNum %d l_sCardFlg.WriteCardTimes %d,GetToEndLen(CardStartAddr) %d",
				NoReadRecNum,CardMaxRecNum,FlshRecCnt,FlshStartRecNum,l_sCardFlg.WriteCardTimes,GetToEndLen(CardStartAddr));
				
				if((l_sCardFlg.WriteCardTimes < 100)  && ( CardMaxRecNum > 20))			//卡写满
				{
					l_UnFihCardEvtFlg = NO_ERROR;

					if( NoReadRecNum > 1 )											//未读记录条数须大于1才能读取数据	
					{
						if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,l_sCardFlg.WriteCardTimes))		//返回1 写卡完成
						{
							uint8	i;
							uint8	Tmp;
							uint16	DataTmp;
							uint8	Buf[5] = {'0','0','0','0','0'};
						
							ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
							
							ReadFixInfo((stcFixInfo * )&sFixInfo);
							
							memcpy(l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].ProNum
										,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
					
							DataTmp = sDeviceInfo.DeviceNum;
							for(i = 0; i < 5;i++)
							{
								Tmp = DataTmp%10;
								DataTmp /= 10;
								if(DataTmp != 0)
								{
									Buf[5-1-i] = Tmp + '0';
								}
							}
							
							memcpy(&l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].LocoType[0]	= sFixInfo.LocoTyp;
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].LocoType[1]	= sFixInfo.E_LocoTyp;	
							memcpy(l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].StartAddr= CardStartAddr;
							CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].EndAddr 	= CardEndAddr;
							//l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].RecLen	= CardEndAddr - CardStartAddr;
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].RecLen	=  FlshRecCnt * sizeof(stcFlshRec);
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].RecNum	= FlshRecCnt;
							
							l_sCardFlg.WriteCardTimes++;									

							CrcCheck = GetCrc16Check((uint8 *)&l_sCardFlg,sizeof(stcCardFlg) -2);

							l_sCardFlg.CrcCheck = CrcCheck;									

							WriteCardFlg((stcCardFlg *)&l_sCardFlg);					//修改IC卡标志页
										
							//StoreLstRedFlshRecNum(g_CurFlshRecNum);					//存最新的已读记录流水号
							
							//g_LshRedFlshRecNum = g_CurFlshRecNum;
							
							IndicateWriteCardFinsh();									//

						}
						else															//写卡错误操作
						{
							l_UnFihCardEvtFlg = ERROR;
							
							DelayX10ms(10);	
							
							IndicateWriteNoFinsh();										//写卡未完成指示
							
							DelayX10ms(500);											//未写完
						}
					}
					else
					{
						IndicateWriteCardFinsh();								//

					}

				}
				else
				{
					IndicateCardFull();
				}
				
				while(PlugICCard() == TRUE)
				{
					NOP();
				}				
				
				DelayX10ms(500);												//拨卡后，延时5S
				ClaerDisplaySet();												//清显示缓冲区
				DisplaySet(100,5,"%u",CardTime);
			}
			else
			{
				DisplaySet(100,10,"UNDF");
				DisplaySet(100,10,"     ");
				while( PlugICCard() != TRUE)
				{
					NOP();
				}
				
				ClaerDisplaySet();												//清显示缓冲区
			}
		}
		else
		{
			DisplaySet(100,1,"PRCD");

			while( PlugICCard() != TRUE)
			{
				NOP();
			}
		}
	}
*/
} 


//-------------------------------------------------------------------------------------------------
//函数名称:             void	GetUnFihCardEvtFlg(void)
//函数功能:             取未完成数据转储标识
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
uint8	GetUnFihCardEvtFlg(void)
{
	return	l_UnFihCardEvtFlg;
}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	GetUnFihCardEvtFlg(void)
//函数功能:             取未完成数据转储标识
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
//uint8	GetWriteFlgErrCardEvtFlg(void)
//{
//	return	l_WriteFlgErrCardEvtFlg;
//}

//-------------------------------------------------------------------------------------------------
//函数名称:             void	GetUnFihCardEvtFlg(void)
//函数功能:             取未完成数据转储标识
//入口参数:             无
//出口参数:             无
//--------------------------------------------------------------------------------------------------
void	ResetUnFihCardEvtFlg(void)
{
	l_UnFihCardEvtFlg = NO_ERROR;
}

//----------------------------------------------------------------------
//函数名称:  	void    ReadCopyCardDisplay(uint8	 Sct)
//函数功能:  	将油尺记录FLASH转化为IC卡记录
//入口参数:   	FLASH记录
//出口参数:   	IC卡记录
//说明:                 
//-----------------------------------------------------------------------
void    ReadCopyCardDisplay(uint8	 Sct)
{
	uint8	i = 0;
	
	while(i < 10 )
	{
		DisplaySet(3,10000,"       %u",i);
		i++;
	}
}

extern	uint32		l_CardPageSize;	
extern	uint32		l_CardPageNum;
//-------------------------------------------------------------------------------------------------
//函数名称:             uint32	GetCardMaxRecNum(void)
//函数功能:             取一张IC卡最大能存最大的数据记录数
//入口参数:             整个卡结构体
//出口参数:             是否成功
//--------------------------------------------------------------------------------------------------
uint32	GetCardMaxRecNum(void)
{
	uint32	RecNum;
	
	RecNum = (l_CardPageNum*l_CardPageSize - CARD_DATA_ADDR)/ sizeof(stcFlshRec);
	
	return	RecNum;
}

//-------------------------------------------------------------------------------------------------
//函数名称:             uint8	DataCopyCard(stcCardFlg	* sCardFlg)
//函数功能:             置数据卡
//入口参数:             整个卡结构体
//出口参数:             是否成功
//--------------------------------------------------------------------------------------------------
//uint8	DataCopyCard(void)
//{
////	uint32	FlshRecCnt;	
////	uint32	FlshStartRecNum;
////	uint32	CardStartAddr;
////	uint32	CardEndAddr;
////	uint32	CardMaxRecNum;
////	uint32	NoReadRecNum;
////	uint16	CrcCheck;	
////	uint32	Time;
////	stcDeviceInfo 	sDeviceInfo;
////	stcFixInfo		sFixInfo;	
////	uint16	WriteCardTimes;
////	stcCardIndex	sCardIndex[100];
////
////	
////	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)+sizeof(stcCardPara)+sizeof(stcCardIndex)*100,
////			(uint8 *)&WriteCardTimes,sizeof(stcCardType));	
////	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)+sizeof(stcCardPara),
////			(uint8 *)&sCardIndex[0],sizeof(stcCardIndex)*100);			
////	
////	if(g_CurFlshRecNum > 1 && g_CurFlshRecNum > g_LshRedFlshRecNum)
////	{
////		NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);			//Flsh的未读记录长度
////	}
////	else
////	{
////		NoReadRecNum = 0;
////	}
////	
////	CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);			//取IC卡未写空间长度
////		
////	FlshRecCnt 		= GetCardMaxRecNum() - 1;	//要写数据长度
////	
////	if(g_CurFlshRecNum > FlshRecCnt)
////	{
////		FlshStartRecNum = g_CurFlshRecNum - FlshRecCnt;
////	}
////	else
////	{
////		FlshRecCnt = g_CurFlshRecNum;
////
////		FlshStartRecNum = 0;
////	}
////	
////	CardStartAddr = CARD_DATA_ADDR;
////	
////	if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,WriteCardTimes))		//返回1 写卡完成
////	{
////		uint8	i;
////		uint8	Tmp;
////		uint16	DataTmp;
////		uint8	Buf[5] = {'0','0','0','0','0'};
////	
////		ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
////		
////		ReadFixInfo((stcFixInfo * )&sFixInfo);
////		
////		memcpy(sCardIndex[WriteCardTimes].ProNum
////					,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
////
////		DataTmp = sDeviceInfo.DeviceNum;
////		for(i = 0; i < 5;i++)
////		{
////			Tmp = DataTmp%10;
////			DataTmp /= 10;
////			if(DataTmp != 0)
////			{
////				Buf[5-1-i] = Tmp + '0';
////			}
////		}
////		
////		memcpy(&sCardIndex[WriteCardTimes].ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
////		sCardIndex[WriteCardTimes].LocoType[0]	= sFixInfo.LocoTyp;
////		sCardIndex[WriteCardTimes].LocoType[1]	= sFixInfo.E_LocoTyp;	
////		memcpy(sCardIndex[WriteCardTimes].LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
////		sCardIndex[WriteCardTimes].StartAddr= CardStartAddr;
////		CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
////		sCardIndex[WriteCardTimes].EndAddr 	= CardEndAddr;
////		//sCardIndex[WriteCardTimes].RecLen	= CardEndAddr - CardStartAddr;
////		sCardIndex[WriteCardTimes].RecLen	=  FlshRecCnt * sizeof(stcFlshRec);
////		sCardIndex[WriteCardTimes].RecNum	= FlshRecCnt;
////		
////		WriteCardTimes++;									
////
//////		CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) -2);
//////
//////		CrcCheck = CrcCheck;									
////
//////		WriteCardFlg(sCardFlg);									//修改IC卡标志页
////					
////		//StoreLstRedFlshRecNum(g_CurFlshRecNum );				//存最新的已读记录流水号
////		
////		//g_LshRedFlshRecNum = g_CurFlshRecNum;
////		
////		IndicateWriteCardFinsh();								//	
////	}
////	else															//写卡错误操作
////	{
////		DelayX10ms(10);	
////		
////		IndicateWriteNoFinsh();										//写卡未完成指示
////		
////		DelayX10ms(500);											//未写完
////	}
////
////	Time = GetSysTime();	
////	
////	while(PlugICCard())
////	{
////		NOP();
////		//SysHoldTast();
////		
////		if(GetSysTime() - Time > 20*100)
////		{
////			break;
////		}
////	}
////	
////	return 1;
//}
//		
