#include <includes.h>

#define     EVT_BUF_LEN     	12         //
static	stcFIFO     sEvtFIFO;                      //定义串口0接收FIFO结构
static	uint8       gEvtBuf[EVT_BUF_LEN];           //定义接收缓冲区

//数据类型
#define   	TAX2_EVT     	90                  //TAX2发生故障
#define   	HOST_DIP1_EVT	80                  //油尺1发生故障
#define   	HOST_DIP2_EVT 	70                  //油尺2发生故障
#define    	CARD_EVT     	60                  //IC卡故障
#define    	HOST_PRO_EVT 	30                  //处理装置发生故障


void	InitEvtDealSys(void)
{
//	InitEvtSysFlg();																			
	
	InitFIFO((stcFIFO *)&sEvtFIFO,gEvtBuf,sizeof(gEvtBuf));	
}

void  StoreCurEvtFlg(uint8	EvtFlg,uint8 EvtTyp)
{
	uint32	i;
	uint8	Buf[EVT_BUF_LEN];
	uint32	EvtNum;

	EvtNum = GetNoReadSizeFIFO((stcFIFO *)&sEvtFIFO);      	//求未读空间大小
	OnlyReadFIFO((stcFIFO *)&sEvtFIFO,Buf,EvtNum);
	//printfcom0("\r\n EvtNum = %d, EvtTyp = %d,EvtFlg = %d",EvtNum,EvtTyp,EvtFlg);

	if(EvtFlg != RIGHT_DATA)
	{
		for(i = 0;i < EvtNum ;i++)
		{
			if(Buf[i] == EvtFlg)
			{
				return;
			}		
		}

		printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,%d,",sizeof(gEvtBuf), GetNoReadSizeFIFO((stcFIFO *)&sEvtFIFO),EvtTyp);	
		WriteFIFO((stcFIFO *)&sEvtFIFO,(uint8 *)&EvtFlg,sizeof(EvtFlg));
	}

}

uint8  GetStoreEvtTypCod(void)
{
	uint8	EvtTypCod = RIGHT_DATA;
	
	if( ReadFIFO(&sEvtFIFO,&EvtTypCod,sizeof(EvtTypCod)) )
	{
		return	EvtTypCod;								//成功,返回读取代码
	}
	else
	{	
		return 	EvtTypCod;								//正确,返回0xFF
	}	
}


uint8 	JudgeHostEvt(void)
{
	uint8	EvtTypeTmp;
	uint8	EvtType[10];
	uint8	i;
	uint8	EvtBuf[10];
	uint8	Time = 0;
		
	EvtTypeTmp    = RIGHT_DATA;
	
	for(i = 0; i< 10;i++)
	{
		EvtType[i] = RIGHT_DATA;
	}
	
	EvtType[0] = JudgeStartEvt();	
	EvtType[3] = JudgeOilEvt();
	
	Time = 0;
	for(i = 0 ; i < 10;i++)
	{
		if(EvtType[i] != RIGHT_DATA)
		{
			EvtBuf[Time++%10] = EvtType[i];
		}
	}

	if( Time )
	{
		EvtTypeTmp = EvtBuf[--Time%10];
	}

	return	EvtTypeTmp;
}

void  EvtDealSys(void)
{
	static	uint32	Time = 0;
	
	uint8	EvtFlg;
		
	if(GetSysTime() - Time > 100)
	{
		EvtFlg = JudgeHostEvt();						//
		StoreCurEvtFlg(EvtFlg,HOST_PRO_EVT);		    
		
//		EvtFlg = JudgeTAX2Evt();						//TAX2通信事件
//		StoreCurEvtFlg(EvtFlg,TAX2_EVT);
				
		EvtFlg = JudgeCardEvt();						//Card事件
		StoreCurEvtFlg(EvtFlg,CARD_EVT);
			
		Time = GetSysTime();	
	}
}



////
////#define 	UART1_BPS              	9600                                    	/* 串口通信波特率               */
////#define     COM1_REVBUF_LEN     	32         		//串口接收
//
//
//#define     ERR_BUF_LEN     	12         //
//stcFIFO     sErrFIFO;                      //定义串口0接收FIFO结构
//uint8       gErrBuf[ERR_BUF_LEN];           //定义接收缓冲区
//
//stcFIFO     sStoreErrFIFO;                      //定义串口0接收FIFO结构
//uint8       gStoreErrBuf[ERR_BUF_LEN];           //定义接收缓冲区
//
//#define   	TAX2_ERR     	90                  //TAX2发生故障
//#define   	HOST_DIP1_ERR	80                  //油尺1发生故障
//#define   	HOST_DIP2_ERR 	70                  //油尺2发生故障
//#define    	CARD_ERR     	60                  //IC卡故障
//#define    	HOST_PRO_ERR 	30                  //处理装置发生故障
//
//
//void	InitErrDealSys(void)
//{																
// 	InitFIFO((stcFIFO *)&sErrFIFO,gErrBuf,sizeof(gErrBuf));
//	InitFIFO((stcFIFO *)&sStoreErrFIFO,gStoreErrBuf,sizeof(gStoreErrBuf));
//	//printfcom0("sizeof(gErrBuf) %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//}
//
//void  StoreCurErrFlg(uint8	ErrFlg,uint8 ErrTyp)
//{
//	uint32	i,j;
//	uint8	Buf[ERR_BUF_LEN];
//	uint32	ErrNum;
//	uint8	Tmp;
//
//	ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);
//	//printfcom0("\r\n ErrNum = %d, ErrTyp = %d,ErrFlg = %d",ErrNum,ErrTyp,ErrFlg);
//	if(ErrFlg != RIGHT_DATA)
//	{
//		for(i = 0;i < ErrNum ;i++)
//		{
//			if(Buf[i] == ErrFlg)
//			{
//				return;
//			}		
//		}
//
//		//printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//		WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
//		WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
//	}
//	else  if(ErrFlg == RIGHT_DATA)
//	{		
//		for(i = 0;i < ErrNum;i++)
//		{
//			if((Buf[i] - Buf[i]%10) == ErrTyp)
//			{
//				Tmp = Buf[i]+100;
//				//printfcom0("\r\n sizeof(gErrBuf)22 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//				WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&Tmp,sizeof(Tmp));
//
//				for(j=0; j<ErrNum; j++)						
//				{
//					ReadFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Tmp,sizeof(Tmp));
//					if(j != i )
//					{
//						//printfcom0("\r\n sizeof(gErrBuf)33 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//
//						WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Buf[j],1);
//					}
//				}
//			}
//		}
//		
//		ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//		//printfcom0("\R\N ErrNum = %d",ErrNum);
//	}
//}
//
//
//
//
//
////	if(ErrFlg != RIGHT_DATA)
////	{	
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			if(i == ErrFlg)							
////			{
////				sErrDeal[i].CurErrFlg 	= ErrFlg;
////
////				return	;
////			}
////			/*
////			else if(ErrTyp != HOST_PRO_ERR)
////			{
////				sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
////			}
////			*/
////			else
////			{
////				sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
////			}
////		}
////	}
////	else
////	{
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
////		}	
////	}
////}
//
//void  ErrDisplayIndicate(void)
//{
//	uint8	Led;
//	uint8	ErrFlg;
//	uint32	i;
//	static	uint32	TaxTime = 0,Dip1Time = 0,Dip2Time = 0,CardTime = 0,HostTime = 0;	
//	uint32	ErrDisplayTime;
//	uint32	ErrNum;
//	uint8	Buf[ERR_BUF_LEN];
//	uint8	LightFlg;
//	
//	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);	
//
//	ErrDisplayTime = 3;
//	//printfcom0("\r\n !!Indicate11 ErrFlg %d,ErrNum %d",ErrFlg,ErrNum);	
//	for(i = 0; i < ErrNum ;i++)
//	{
//		//SysFastHoldTast();
//		
//		ErrFlg	= Buf[i];
//		//printfcom0("\r\n !!Indicate ErrFlg %d,ErrNum %d",ErrFlg,ErrNum);
//
//		if(ErrFlg != RIGHT_DATA && ErrFlg < 100 )
//		{
//			Led 	= (ErrFlg  - (ErrFlg  % 10));		//指示灯的位置
//			
//			switch( Led )
//			{
//				case TAX2_ERR:		
//								if(GetSysTime() - TaxTime > 100*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									//DisplaySet(60,1,"E-%u",ErrFlg);
//									TaxTime = GetSysTime();
//								}
//								break;
//								
//				case HOST_DIP1_ERR:				
//								if(GetSysTime() - Dip1Time > 100*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									Dip1Time = GetSysTime();
//								}							
//								break;	
//							
//				case HOST_DIP2_ERR:			
//								if(GetSysTime() - Dip2Time > 100*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									Dip2Time = GetSysTime();
//								}							
//								break;			
//
//				case CARD_ERR:		
//								if(GetSysTime() - CardTime > 100*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									CardTime = GetSysTime();
//								}
//								break;										
//
//				case HOST_PRO_ERR:			
//								if(GetSysTime() - HostTime > 100*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									HostTime = GetSysTime();
//								}							
//								break;										
//				default:;
//			}			
//		}
//	}	
//}
//
//void  ErrLedIndicate(void)
//{
//	uint8	Led;
//	uint8	ErrFlg;
//	uint32	i;
//	uint32	ErrNum;
//	uint8	Buf[ERR_BUF_LEN];
//	uint8	LightFlg;
//	
//	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);
//
//	LightFlg = 0;
//	//printfcom0("\r\n !!Indicate1221 ErrFlg %d,ErrNum %d, Light %d",ErrFlg,ErrNum,LightFlg);	
//
//	for(i = 0; i < ErrNum ;i++)
//	{
//		//SysFastHoldTast();
//	//printfcom0("\r\n !!Indicate122122 ErrFlg %d,ErrNum %d, Light %d",ErrFlg,ErrNum,LightFlg);	
//		ErrFlg	= Buf[i];
//
//		if(ErrFlg != RIGHT_DATA && ErrFlg < 100)
//		{
//			Led 	= (ErrFlg  - (ErrFlg  % 10));		//指示灯的位置
//			
//			switch( Led )
//			{
//				case TAX2_ERR:			OnLed(TAX2_LED,0xffffff,5,5);
//										LightFlg |= 0x01<<1;	break;					
//				case HOST_DIP1_ERR:		OnLed(DIP1_LED,0xffffff,5,5);
//										LightFlg |= 0x01<<2;	break;		
//				case HOST_DIP2_ERR:		OnLed(DIP2_LED,0xffffff,5,5);
//										LightFlg |= 0x01<<3;	break;									
//				case CARD_ERR:			OnLed(CARD_LED,0xffffff,5,5);
//										LightFlg |= 0x01<<3;	break;								
//				case HOST_PRO_ERR:		OnLed(HOST_LED,0xffffff,5,5);
//										LightFlg |= 0x01<<4;	break;											
//				default:;
//			}			
//		}
//	}
//	//printfcom0("\r\n !!Indicate122133 ErrFlg %d,ErrNum %d, Light %d",ErrFlg,ErrNum,LightFlg);	
////	for(i = 0; i < ErrNum ;i++)
//	{
//		for(i = 0;i < 8;i++)	
//		{			
//			if(LightFlg & 0x01<<1)
//			{
//				OffLed(TAX2_LED);	
//			}
//			else if(LightFlg & 0x01<<2)
//			{
//				OffLed(DIP1_LED);	
//			}
//			else if(LightFlg & 0x01<<3)
//			{
//				OffLed(CARD_LED);	
//			}
//			else if(LightFlg & 0x01<<4)
//			{
//				OffLed(HOST_LED);	
//			}
//		}
//		//SysFastHoldTast();
//////		
//////		ErrFlg	= sErrDeal[i].TypCod;
//
////		if(ErrFlg != RIGHT_DATA)
////		{
////			Led 	= (ErrFlg - (ErrFlg  % 10));		//指示灯的位置
////			
////			switch( LightFlg )
////			{
////				case TAX2_ERR + 100:	OffLed(TAX2_LED);			break;	
////								
////				case HOST_DIP1_ERR+100:	OffLed(DIP1_LED);			break;		
////								
////				case HOST_DIP2_ERR+100:	OffLed(DIP2_LED);			break;	
////								
////				case CARD_ERR + 100:	OffLed(CARD_LED);			break;		
////
////				case HOST_PRO_ERR+100:	OffLed(HOST_LED);			break;		
////									
////				default:;
////			}			
////		}
//	}
//}
//
//uint8  GetStoreErrTypCod(void)
//{
//	uint8	ErrTypCod = RIGHT_DATA;
//	
//	if( ReadFIFO(&sStoreErrFIFO,&ErrTypCod,sizeof(ErrTypCod)) )
//	{
//		return	ErrTypCod;								//成功,返回读取代码
//	}
//	else
//	{
//		return 	ErrTypCod;								//正确,返回0xFF
//	}
//}
//
//void	ErrIndicate(void)
//{
//	ErrDisplayIndicate();
//	
//	ErrLedIndicate();
//}
//
//
//uint8  JudgeHostError(void)
//{
//	uint8	ErrFlg1,ErrFlg2,ErrFlg;
//	uint8	ErrFlg3;
//	uint8	ErrFlg4;
////	static	uint32	Times = 0;
//	
//	ErrFlg1 = JudgeCalcError();						//运算参数
//	ErrFlg2 = JudgeEr2450Err();						//电池电压
//	ErrFlg3 = JudgeFlashIDErrFlg();					//FLSH的ID号读取错误
//	ErrFlg4 = JudgeFramWordEvt();					//铁电测单字
//
//	if(ErrFlg2 != RIGHT_DATA)
//	{	
//		ErrFlg = ErrFlg2;
//	}
//	else if(ErrFlg3 != RIGHT_DATA)
//	{	
//		ErrFlg = ErrFlg3;
//	}
//	else if (ErrFlg4 != RIGHT_DATA)
//	{
//		ErrFlg = ErrFlg4;
//	}
//	else if (ErrFlg1 != RIGHT_DATA)
//	{
//		ErrFlg = ErrFlg1;
//	}	
//	else
//	{
//		ErrFlg = RIGHT_DATA;
//	/*
//		if(Times++ % 2)
//		{
//			ErrFlg = ErrFlg1;
//		}
//		else
//		{
//			ErrFlg = ErrFlg2;
//		}
//	*/
//	}
//	
//	return	ErrFlg;
//}
//
//
//void  ErrDealSys(void)
//{
//	static	uint32	Time = 0;
//	static	uint32	Times = 0;
//	
//	uint8	ErrFlg;
////	uint8	i;
//	
//
//	if((GetSysTime() - Time > 100) && (GetSysTime() - g_PullCardTime) > 100)
//	{
//		if( Times > 0)
//		{
////			i=0;
//			
//			ErrFlg = JudgeTAX2Error();						//TAX2通信
//			StoreCurErrFlg(ErrFlg,TAX2_ERR); 
////			//printfcom0("\r\n  Error %d,I = %d ",ErrFlg,i++);
//
//			ErrFlg = JudgeDip1Error();						//测量装置故障
//			StoreCurErrFlg(ErrFlg,HOST_DIP1_ERR); 
////			//printfcom0("\r\n  Error %d,I = %d ",ErrFlg,i++);
//					
//			ErrFlg = JudgeDip2Error();						//测量装置故障
//			StoreCurErrFlg(ErrFlg,HOST_DIP2_ERR);		
////			//printfcom0("\r\n  Error %d,I = %d ",ErrFlg,i++);
//						
////			//printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeHostError();						//运算参数
//			StoreCurErrFlg(ErrFlg,HOST_PRO_ERR);	
//			
//
//			ErrFlg = JudgeCardError();						//IC卡故障
//			StoreCurErrFlg(ErrFlg,CARD_ERR);	
////			//printfcom0("\r\n  Error %d,I = %d ",ErrFlg,i++);
//		
////				
//			ErrIndicate();									//指示故障 
//		}
////		
//		Times++;
//			
//		Time = GetSysTime();								
//	}
//}
//
//
//
//
////uint8       UART1RecBuf[COM1_REVBUF_LEN];           //定义接收缓冲区
////uint8		l_COM1TempRev;
////uint8       GulNum1;                                 /* 串口接收数据的个数           */
////
/////*********************************************************************************************************
////* Function Name:        UART1_IRQHandler
////* Description:          UART1 中断处理函数
////* Input:                None
////* Output:               None
////* Return:               None
////*********************************************************************************************************/
////void UART1_IRQHandler (void)
////{
////   GulNum1 = 0;
////       
////    while ((LPC_UART1->IIR & 0x01) == 0){                               /*  判断是否有中断挂起          */
////        switch (LPC_UART1->IIR & 0x0E){                                 /*  判断中断标志                */
////        
////            case 0x04:                                                  /*  接收数据中断                */
//////                GucRcvNew = 1;                                          /*  置接收新数据标志            */
////                for (GulNum1 = 0; GulNum1 < 8; GulNum1++){                 /*  连续接收8个字节             */
////			        l_COM1TempRev = LPC_UART1->RBR;                    	//注意读U0RBR会清空接收中断标志
////    				WriteFIFO((stcFIFO *)&sUART1RecFIFO,(uint8 *)&l_COM1TempRev,1); 
////                }
////                break;
////            
////            case 0x0C:                                                  /*  字符超时中断                */
//////                GucRcvNew = 1;
////                while ((LPC_UART1->LSR & 0x01) == 0x01){                /*  判断数据是否接收完毕        */ 
////			        l_COM1TempRev = LPC_UART1->RBR;                    	//注意读U0RBR会清空接收中断标志
////    				WriteFIFO((stcFIFO *)&sUART1RecFIFO,(uint8 *)&l_COM1TempRev,1);                 
////				}
////                break;
////                
////            default:
////                break;
////        }
////    } 
////}
////  
////
////#define		TXD1		15
////#define		RXD1		16
////#define		EN_485_1 	122
////
////uint8	GetUart1Status(void)
////{
////	return	UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART1);
////}
////
////void WriteEN_485_1(uint8 temp)
////{
////	
////	if(temp)		
////	{
////		GPIO_SetOrClearValue(EN_485_1,1);
////	}
////	else
////	{
////		GPIO_SetOrClearValue(EN_485_1,0);		
////	}	
////	nop();	
//////	IO0DIR_OUT(SCK1);					//P0.17 SCK1
//////	IO0PIN_W(temp,SCK1);
////}
////
////
/////*********************************************************************************************************
////** Function name:     	uartInit
////** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
////** input parameters:    无
////** output parameters:   无
////** Returned value:      无
////*********************************************************************************************************/
////void uart1Init (void)
////{
////	UART_CFG_Type		UART_ConfigStruct_Test;
////	UART_FIFO_CFG_Type 	FIFOCfg_Test;
////	UART_INT_Type 		UARTIntCfg_Test;
////
////	GPIO_PinselConfig(RXD1,1);
////	GPIO_PinselConfig(TXD1,1);	
////
////	UART_ConfigStruct_Test.Baud_rate = UART1_BPS;
////	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
////	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
////	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
////	
////	UART_Init((LPC_UART_TypeDef *)LPC_UART1,(UART_CFG_Type *)&UART_ConfigStruct_Test);
////	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1,ENABLE);
////
////	FIFOCfg_Test.FIFO_DMAMode = DISABLE;
////	FIFOCfg_Test.FIFO_Level = UART_FIFO_TRGLEV2;
////	FIFOCfg_Test.FIFO_ResetRxBuf = ENABLE;
////	FIFOCfg_Test.FIFO_ResetTxBuf = ENABLE;	
////	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART1, (UART_FIFO_CFG_Type *)&FIFOCfg_Test);
////
////	UARTIntCfg_Test = UART_INTCFG_RBR;	
////	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1, UARTIntCfg_Test,ENABLE);
////
////  	
////	InitFIFO((stcFIFO *)&sUART1RecFIFO,UART1RecBuf,sizeof(UART1RecBuf));
////
////
////	NVIC_EnableIRQ(UART1_IRQn);
////	NVIC_SetPriority(UART1_IRQn, 6);									
////}
////
////uint32 ReadCOM1(uint8 *buf,uint32 len) 
////{
////    uint32 RealLen;                                             //实际读的长度
////    uint32 RevBufLen;                                           //读、写间差值,即读缓冲区的总长度
////
////    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART1RecFIFO);   //求还没有读取空间数据个数
////    
////    if(RevBufLen > len)
////    {
////        RealLen = len;                                  		//读取想要求的数据长度
////    }
////    else
////    {
////        RealLen = RevBufLen;                        			//读取实际数据长度
////    }
////    
////    ReadFIFO((stcFIFO *)&sUART1RecFIFO,buf,RealLen);
////
////    return RealLen;
////}
////
////uint8 SendCOM1(void *buf,uint32 len)
////{
////    if( (!len) )
////    {
////        return FALSE;
////    }   
////
////	UART_Send((LPC_UART_TypeDef *)LPC_UART1,buf,len,BLOCKING);
////    
////    return TRUE;    
////}
////
//////void uartTask(void)
//////{
////////INT8U	Tmp=0x5a;
////////INT8U	Flg;
////////uint32_t 	GulChipID = 0;
////////uint8	GucRcvBuf[64];
////////uint32	len;
//////
//////
////////DisplaySet(100,2,"12345678");
//////
//////	//for(Tem = )
////////	while(1)
//////	{
////////		Tmp	= GulNum;
////////		
////////		len = GetNoReadSizeFIFO((stcFIFO *)&sUART1RecFIFO);
////////
////////		if(len > 0)
////////		{
////////			OnLed(1,100,10,10);
////////
//////////			ReadFIFO((stcFIFO *)&sUART1RecFIFO,GucRcvBuf,len);
//////////			UART_Send((LPC_UART_TypeDef *)LPC_UART1,GucRcvBuf,len,BLOCKING);
////////		}
////////			
//////////		TaskTest();
//////		ScanTask();
//////
////////		OSTimeDlyHMSM(0,0,0,100);
//////	}	
//////}
////
////
