#include <includes.h>
//
//#define 	UART1_BPS              	9600                                    	/* 串口通信波特率               */
//#define     COM1_REVBUF_LEN     	32         		//串口接收


#define		DIP_PRE_DIF				84
#define		DIP_NO_COM_ERROR		83
#define		DIP1_DATA_ERROR			85
#define		DIP1_COM_ERROR			81
#define		DIP2_DATA_ERROR			75
#define		DIP2_COM_ERROR			71
#define		DIP1_LIMIT_ERROR		82
#define		DIP2_LIMIT_ERROR		72

#define     ERR_BUF_LEN     		20         	//
stcFIFO     sErrFIFO;                      		//定义串口0接收FIFO结构
uint8       gErrBuf[ERR_BUF_LEN];           	//定义接收缓冲区

stcFIFO     sStoreErrFIFO;                      //定义串口0接收FIFO结构
uint8       gStoreErrBuf[ERR_BUF_LEN];          //定义接收缓冲区

#define   	TAX2_ERR     		90            	//TAX2发生故障
#define   	HOST_DIP1_ERR		80         	    //油尺1发生故障
#define   	HOST_DIP2_ERR 		70          	//油尺2发生故障
#define    	CARD_ERR     		60           	//IC卡故障
#define    	HOST_PRO_ERR 		30          	//处理装置发生故障


void	InitErrDealSys(void)
{																
 	InitFIFO((stcFIFO *)&sErrFIFO,gErrBuf,sizeof(gErrBuf));	
}

void	StoreErrFlg(uint8	Errflg)
{
	WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Errflg,sizeof(Errflg));
}

uint8	GetErrorCode(void)
{
	uint8	num,errflg;
	num  = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小

	errflg = 0xff;
	if(num)
	{
		ReadFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&errflg,sizeof(errflg));
	}
	return	errflg;
}



void  StoreCurErrFlg(uint8	ErrFlg,uint8 ErrTyp)
{
	uint32	i,j;
	uint8	Buf[ERR_BUF_LEN];
	uint32	ErrNum;
	uint8	Tmp;

	ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);
	//printfcom0("\r\n ErrNum = %d, ErrTyp = %d,ErrFlg = %d",ErrNum,ErrTyp,ErrFlg);
	if(ErrFlg != RIGHT_DATA)
	{
		for(i = 0;i < ErrNum ;i++)
		{
			if(Buf[i] == ErrFlg)
			{
				return;
			}		
		}

		//printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
		WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
		WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
	}
	else  if(ErrFlg == RIGHT_DATA)
	{		
		for(i = 0;i < ErrNum;i++)
		{
			if((Buf[i] - Buf[i]%10) == ErrTyp)
			{
				Tmp = Buf[i]+100;
				//printfcom0("\r\n sizeof(gErrBuf)22 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
				WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&Tmp,sizeof(Tmp));

				for(j=0; j<ErrNum; j++)						
				{
					ReadFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Tmp,sizeof(Tmp));
					if(j != i )
					{
						//printfcom0("\r\n sizeof(gErrBuf)33 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	

						WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Buf[j],1);
					}
				}
			}
		}
		
		ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
		//printfcom0("\R\N ErrNum = %d",ErrNum);
	}
}





//	if(ErrFlg != RIGHT_DATA)
//	{	
//		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
//		{
//			if(i == ErrFlg)							
//			{
//				sErrDeal[i].CurErrFlg 	= ErrFlg;
//
//				return	;
//			}
//			/*
//			else if(ErrTyp != HOST_PRO_ERR)
//			{
//				sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
//			}
//			*/
//			else
//			{
//				sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
//			}
//		}
//	}
//	else
//	{
//		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
//		{
//			sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
//		}	
//	}
//}

void  ErrDisplayIndicate(void)
{
	uint8	Led;
	uint8	ErrFlg;
	uint32	i;
	static	uint32	TaxTime = 0,Dip1Time = 0,Dip2Time = 0,CardTime = 0,HostTime = 0;	
	uint32	ErrDisplayTime;
	uint32	ErrNum;
	uint8	Buf[ERR_BUF_LEN];
	uint8	LightFlg;
	
	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);	

	LightFlg = 0;
	ErrDisplayTime = 3;
	for(i = 0; i < ErrNum ;i++)
	{		
		ErrFlg	= Buf[i];

		if(ErrFlg != RIGHT_DATA && ErrFlg < 100 )
		{
			Led 	= (ErrFlg  - (ErrFlg  % 10));		//指示灯的位置
			
			switch( Led )
			{
				case TAX2_ERR:		
								if(GetSysTime() - TaxTime > 100*ErrDisplayTime)					
								{
									TaxTime = GetSysTime();
								}
								OnLed(TAX2_LED,0xffffff,5,5);
								LightFlg |= 0x01<<1;
								break;
								
				case HOST_DIP1_ERR:				
								if(GetSysTime() - Dip1Time > 100*ErrDisplayTime)					
								{
									DisplaySet(60,1,"E-%u",ErrFlg);	
									Dip1Time = GetSysTime();
								}
								OnLed(DIP1_LED,0xffffff,5,5);
								LightFlg |= 0x01<<2;							
								break;	
							
				case HOST_DIP2_ERR:			
								if(GetSysTime() - Dip2Time > 100*ErrDisplayTime)					
								{
									DisplaySet(60,1,"E-%u",ErrFlg);	
									Dip2Time = GetSysTime();
								}
								OnLed(DIP2_LED,0xffffff,5,5);
								LightFlg |= 0x01<<2;							
								break;			

				case CARD_ERR:		
								if(GetSysTime() - CardTime > 100*ErrDisplayTime)					
								{
									DisplaySet(60,1,"E-%u",ErrFlg);	
									CardTime = GetSysTime();
								}
								OnLed(CARD_LED,0xffffff,5,5);
								LightFlg |= 0x01<<3;
								break;										

				case HOST_PRO_ERR:			
								if(GetSysTime() - HostTime > 100*ErrDisplayTime)					
								{
									DisplaySet(60,1,"E-%u",ErrFlg);	
									HostTime = GetSysTime();
								}
								OnLed(HOST_LED,0xffffff,5,5);
								LightFlg |= 0x01<<4;							
								break;										
				default:;
			}			
		}
	}	

	if((LightFlg & 0x01<<1) == 0)
	{
		OffLed(TAX2_LED);	
	}
	
	if((LightFlg & 0x01<<2) == 0)
	{
		OffLed(DIP1_LED);	
	}
	
	if((LightFlg & 0x01<<3) == 0)
	{
		OffLed(CARD_LED);	
	}
	
	if((LightFlg & 0x01<<4) == 0)
	{
		OffLed(HOST_LED);	
	}
}

void  ErrLedIndicate(void)																
{
	uint8	Led;
	uint8	ErrFlg;
	uint32	i;
	uint32	ErrNum;
	uint8	Buf[ERR_BUF_LEN];
	uint8	LightFlg;
	
	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);

	printfcom0("\r\n ErrNum %d",ErrNum);
	LightFlg = 0;

	for(i = 0; i < ErrNum ;i++)
	{
		ErrFlg	= Buf[i];

		if(ErrFlg != RIGHT_DATA && ErrFlg < 100)
		{
			Led 	= (ErrFlg  - (ErrFlg  % 10));		//指示灯的位置
			
			switch( Led )
			{
				case TAX2_ERR:			OnLed(TAX2_LED,0xffffff,5,5);
										LightFlg |= 0x01<<1;	break;					
				case HOST_DIP1_ERR:		OnLed(DIP1_LED,0xffffff,5,5);
										LightFlg |= 0x01<<2;	break;		
				case HOST_DIP2_ERR:		OnLed(DIP2_LED,0xffffff,5,5);
										LightFlg |= 0x01<<2;	break;									
				case CARD_ERR:			OnLed(CARD_LED,0xffffff,5,5);
										LightFlg |= 0x01<<3;	break;								
				case HOST_PRO_ERR:		OnLed(HOST_LED,0xffffff,5,5);
										LightFlg |= 0x01<<4;	break;											
				default:;
			}			
		}
	}
	
	printfcom0("\r\n LightFlg %d",LightFlg);
		
	if(LightFlg & 0x01<<1)
	{
		OffLed(TAX2_LED);	
	}
	
	if(LightFlg & 0x01<<2)
	{
		OffLed(DIP1_LED);	
	}
	
	if(LightFlg & 0x01<<3)
	{
		OffLed(CARD_LED);	
	}
	
	if(LightFlg & 0x01<<4)
	{
		OffLed(HOST_LED);	
	}

		//SysFastHoldTast();
////		
////		ErrFlg	= sErrDeal[i].TypCod;

//		if(ErrFlg != RIGHT_DATA)
//		{
//			Led 	= (ErrFlg - (ErrFlg  % 10));		//指示灯的位置
//			
//			switch( LightFlg )
//			{
//				case TAX2_ERR + 100:	OffLed(TAX2_LED);			break;	
//								
//				case HOST_DIP1_ERR+100:	OffLed(DIP1_LED);			break;		
//								
//				case HOST_DIP2_ERR+100:	OffLed(DIP2_LED);			break;	
//								
//				case CARD_ERR + 100:	OffLed(CARD_LED);			break;		
//
//				case HOST_PRO_ERR+100:	OffLed(HOST_LED);			break;		
//									
//				default:;
//			}			
//		}
}

uint8  GetStoreErrTypCod(void)
{
	uint8	ErrTypCod = RIGHT_DATA;
	
	if( ReadFIFO(&sStoreErrFIFO,&ErrTypCod,sizeof(ErrTypCod)) )
	{
		return	ErrTypCod;								//成功,返回读取代码
	}
	else
	{
		return 	ErrTypCod;								//正确,返回0xFF
	}
}

void	ErrIndicate(void)
{
	ErrDisplayIndicate();
	
//	ErrLedIndicate();
}


uint8  JudgeHostError(void)
{
//	uint8	ErrFlg1= RIGHT_DATA;
	uint8	ErrFlg2= RIGHT_DATA;
	uint8	ErrFlg = RIGHT_DATA;
	uint8	ErrFlg3= RIGHT_DATA;
	uint8	ErrFlg4= RIGHT_DATA;
//	static	uint32	Times = 0;
	
//	ErrFlg1 = JudgeCalcError();						//运算参数
	ErrFlg2 = JudgeEr2450Err();						//电池电压
	ErrFlg3 = JudgeFlashIDErrFlg();					//FLSH的ID号读取错误
	ErrFlg4 = JudgeFramWordEvt();					//铁电测单字

	if(ErrFlg4 != RIGHT_DATA)
	{	
		ErrFlg = ErrFlg4;
	}
	else if(ErrFlg3 != RIGHT_DATA)
	{	
		ErrFlg = ErrFlg3;
	}
	else if (ErrFlg2 != RIGHT_DATA)
	{
		ErrFlg = ErrFlg2;
	}
//	else if (ErrFlg1 != RIGHT_DATA)
//	{
//		ErrFlg = ErrFlg1;
//	}	
	else
	{
		ErrFlg = RIGHT_DATA;
	/*
		if(Times++ % 2)
		{
			ErrFlg = ErrFlg1;
		}
		else
		{
			ErrFlg = ErrFlg2;
		}
	*/
	}
	
	return	ErrFlg;
}


void  ErrDealSys(void)
{	
	uint8	ErrFlg;

	if((GetSysTime() % 100) == 0 )
	{
		ErrFlg = JudgeTAX2Error();						//TAX2通信
		StoreCurErrFlg(ErrFlg,TAX2_ERR); 

		ErrFlg = JudgeDip1Error();						//测量装置故障
		StoreCurErrFlg(ErrFlg,HOST_DIP1_ERR); 
				
		ErrFlg = JudgeDip2Error();						//测量装置故障
		StoreCurErrFlg(ErrFlg,HOST_DIP2_ERR);		

		ErrFlg = JudgeHostError();						//运算参数
		StoreCurErrFlg(ErrFlg,HOST_PRO_ERR);	
		
		ErrFlg = JudgeCardError();						//IC卡故障
		StoreCurErrFlg(ErrFlg,CARD_ERR);	
		
		ErrIndicate();									//指示故障 							
	}
}



uint8	l_hosterrnum = 0;

uint8	GetHostErrNum(void)
{
	return	 l_hosterrnum;
}

void	ErrTimesAdd(void)
{
	l_hosterrnum++;	
}

void	ErrTimesDec(void)
{
	if(l_hosterrnum)
	{
		l_hosterrnum--;
	}	
}


uint8	l_diperrflg = 0;

uint8	GetDipErrFlg(void)
{
	return	l_diperrflg;
}

void	JudgeDipError(void)
{
	static	uint8	dip1errtimes = 0,dip2errtimes = 0;
	
	if((GetCom1Dip1ErrFlg() == ERROR) &&( GetCom1Dip2ErrFlg()== ERROR))
	{
		dip1errtimes++;
		dip2errtimes++;
		if(dip1errtimes >3 && dip2errtimes>3)
		{
			l_diperrflg = DIP_NO_COM_ERROR;
		}
	}
	else if((GetCom1Dip1ErrFlg() == ERROR))
	{
		 dip1errtimes++;
		 dip2errtimes = 0;
		 if(dip1errtimes >3 )
		 {
		 	l_diperrflg = DIP1_COM_ERROR;
		 }
	}
	else if((GetCom1Dip2ErrFlg() == ERROR))
	{
		 dip1errtimes=0;
		 dip2errtimes++;
		 if(dip2errtimes >3 )
		 {
		 	l_diperrflg = DIP2_COM_ERROR;
		 }
	}
	else
	{
		 dip1errtimes =0;
		 dip2errtimes =0;
		 l_diperrflg  =RIGHT_DATA;
	}
}



void	StoreDipErrFlg(void)
{
	uint8	errflg = 0;
	static	uint8	lockflg = 0;
	static	uint8	lsterrflg = 0;

	JudgeDipError();

	errflg = GetDipErrFlg();	
	if(errflg && (lockflg == 0))
	{
		StoreErrFlg(errflg);
		lsterrflg = errflg;

		ErrTimesAdd();
		lockflg = 1;
		printfcom0("\r\n StoreDipErrFlg %d,",errflg);
	}

	if((errflg == 0) && (lockflg == 1))
	{
		StoreErrFlg(lsterrflg+100);
		ErrTimesDec();
		lockflg = 0;
		
		printfcom0("\r\n 1StoreDipErrFlg %d,",lsterrflg +100);	
	}		
}


uint8	l_hosterrflg = 0;

uint8	GetHostErrFlg(void)
{
	return	l_hosterrflg;
}

void	StoreHostErrFlg(void)
{
	uint8	errflg = 0;
	static	uint8	lockflg = 0;
	static	uint8	lsterrflg = 0;

	errflg = JudgeHostError();

//	errflg = GetHostErrFlg();
	l_hosterrflg = errflg ;

	if(errflg && (lockflg == 0))
	{
		StoreErrFlg(errflg);
		lsterrflg = errflg;

		ErrTimesAdd();
		lockflg = 1;
		printfcom0("\r\n StoreDipErrFlg %d,",errflg);
	}

	if((errflg == 0) && (lockflg == 1))
	{
		StoreErrFlg(lsterrflg+100);
		ErrTimesDec();
		lockflg = 0;
		
		printfcom0("\r\n 1StoreDipErrFlg %d,",lsterrflg +100);	
	}		
}


void	ErrDealTask(void)
{
	static uint32	time ;
	
	if(	GetSysTime() - time >50 )
	{
		time = GetSysTime();

		if( GetSysTime() > 10*100)
		{
			StoreDipErrFlg(); 
	   	}

		StoreHostErrFlg();
	}
}
