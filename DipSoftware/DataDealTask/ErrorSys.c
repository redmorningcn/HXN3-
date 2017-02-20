////#include 	"config.h"                             
////#include 	"Globe.h"                             
////#include 	"HardDrive.h"                             
////#include 	"CpuDrive.h"                             
////#include 	"Tax2.h"                             
////#include 	"DipMath.h"                             
//
#include <includes.h>
////
////#define		ERR_DEAL_LEN		10
////stcFIFO		sErrDealFIFO;							//定义串口0接收FIFO结构
////uint8		ErrDealBuf[ERR_DEAL_LEN];				//定义接收缓冲区
//////
////typedef    struct  _stcErrDeal_
////{
////     uint8  CurErrFlg;                 			//错误标识
////     uint8  LstErrFlg;                 			//错误标识
////     uint8	Rev0;								//
////     uint8  TypCod;                   			//类型代码
////}stcErrDeal;
////
////static	stcErrDeal		sErrDeal[100];
//
//#define     ERR_BUF_LEN     	12         //
////stcFIFO     sErrFIFO;                      //定义串口0接收FIFO结构
//uint8       gErrBuf[ERR_BUF_LEN];           //定义接收缓冲区
//
//stcFIFO     sStoreErrFIFO;                      //定义串口0接收FIFO结构
//uint8       gStoreErrBuf[ERR_BUF_LEN];           //定义接收缓冲区
               
////------------------------------------------------------------------------
//// 名    称：   void  InitErrSys(void)
//// 功    能：   初始化IC错误系统
//// 入口参数： 	无
//// 出口参数:	
////------------------------------------------------------------------------
//
////数据类型
//#define   	TAX2_ERR     	90                  //TAX2发生故障
//#define   	HOST_DIP1_ERR	80                  //油尺1发生故障
//#define   	HOST_DIP2_ERR 	70                  //油尺2发生故障
//#define    	CARD_ERR     	60                  //IC卡故障
//#define    	HOST_PRO_ERR 	30                  //处理装置发生故障
//
//extern stcFIFO     sUART1RecFIFO;                          //定义串口0接收FIFO结构;
////------------------------------------------------------------------------
//// 名    称：   void  ErrDeal(void)
//// 功    能：   油尺1故障处理
//// 入口参数：   无
//// 出口参数：   故障代码
////------------------------------------------------------------------------
//void  StoreCurErrFlg(uint8	ErrFlg,uint8 ErrTyp)
//{
//	uint32	i,j;
//	uint8	Buf[ERR_BUF_LEN];
//	uint32	ErrNum;
//	uint8	Tmp;
//
//
//	//printfcom0("ErrNum = %d, ErrTyp = %d",ErrNum,ErrTyp);
//
//	ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//
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
//		printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//		//WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
//		//WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
//	}
//	else  if(ErrFlg == RIGHT_DATA)
//	{		
//		for(i = 0;i < ErrNum;i++)
//		{
//			if((Buf[i] - Buf[i]%10) == ErrTyp)
//			{
//				Tmp = Buf[i]+100;
//				printfcom0("\r\n sizeof(gErrBuf)22 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//				//WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&Tmp,sizeof(Tmp));
//
//				for(j=0; j<ErrNum; j++)						
//				{
//					ReadFIFO((stcFIFO *)&sErrFIFO,(uint8 *)Tmp,sizeof(Tmp));
//					if(j != i )
//					{
//						printfcom0("\r\n sizeof(gErrBuf)33 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//
//						//WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Buf[j],1);
//					}
//				}
//			}
//		}
//		
//		ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//		printfcom0("\R\N ErrNum = %d",ErrNum);
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
//
////------------------------------------------------------------------------
//// 名    称：   void  ErrDeal(void)
//// 功    能：   故障运算处理，判断是否进行运算
//// 入口参数：   无
//// 出口参数：   故障代码
////------------------------------------------------------------------------
//void  ErrDeal(void)
//{
//	uint32	i;
//
//
//
////
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////
////		if(sErrDeal[i].CurErrFlg == sErrDeal[i].LstErrFlg)
////		{
////			sErrDeal[i].TypCod	= RIGHT_DATA;					//类型代码
////		}
////		else if(sErrDeal[i].LstErrFlg == RIGHT_DATA)
////		{
////			sErrDeal[i].TypCod	= sErrDeal[i].CurErrFlg;		//出现故障
////		}
////		else if(sErrDeal[i].CurErrFlg == RIGHT_DATA)
////		{
////			sErrDeal[i].TypCod	= sErrDeal[i].LstErrFlg + 100;	//故障恢复
////		}
////		
////		sErrDeal[i].LstErrFlg 	= sErrDeal[i].CurErrFlg;
////	}
//}
//
////------------------------------------------------------------------------
//// 名    称：   void  OffErrIndicate(void)
//// 功    能：   关故障指示
//// 入口参数：   无
//// 出口参数：   
////------------------------------------------------------------------------
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
//	for(i = 0; i < ErrNum ;i++)
//	{
//		//SysFastHoldTast();
//
//		ErrFlg	= Buf[i];
//
//		if(ErrFlg != RIGHT_DATA && ErrFlg < 100)
//		{
//			Led 	= (ErrFlg  - (ErrFlg  % 10));		//指示灯的位置
//			
//			switch( Led )
//			{
//				case TAX2_ERR:			OnLed(TAX2_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<1;	break;					
//				case HOST_DIP1_ERR:		OnLed(DIP1_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<2;	break;		
//				case HOST_DIP2_ERR:		OnLed(DIP2_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<3;	break;									
//				case CARD_ERR:			OnLed(CARD_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<3;	break;								
//				case HOST_PRO_ERR:		OnLed(HOST_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<4;	break;											
//				default:;
//			}			
//		}
//	}
//
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
////------------------------------------------------------------------------
//// 名    称：   void  ErrDisplayIndicate(void)
//// 功    能：   故障指示
//// 入口参数：   无
//// 出口参数：   
////------------------------------------------------------------------------
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
//
//	
//	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//求未读空间大小
//	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);	
//
//	ErrDisplayTime = 3;
//	
//	for(i = 0; i < ErrNum ;i++)
//	{
//		//SysFastHoldTast();
//		
//		ErrFlg	= Buf[i];
//
//		if(ErrFlg != RIGHT_DATA && ErrFlg < 100 )
//		{
//			Led 	= (ErrFlg  - (ErrFlg  % 10));		//指示灯的位置
//			
//			switch( Led )
//			{
//				case TAX2_ERR:		
//								if(GetSysTime() - TaxTime > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									//DisplaySet(60,1,"E-%u",ErrFlg);
//									TaxTime = GetSysTime();
//								}
//								break;
//								
//				case HOST_DIP1_ERR:				
//								if(GetSysTime() - Dip1Time > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									Dip1Time = GetSysTime();
//								}							
//								break;	
//							
//				case HOST_DIP2_ERR:			
//								if(GetSysTime() - Dip2Time > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									Dip2Time = GetSysTime();
//								}							
//								break;			
//
//				case CARD_ERR:		
//								if(GetSysTime() - CardTime > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									CardTime = GetSysTime();
//								}
//								break;										
//
//				case HOST_PRO_ERR:			
//								if(GetSysTime() - HostTime > 200*ErrDisplayTime)					
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
////------------------------------------------------------------------------
//// 名    称：   void	ErrIndicate(void)
//// 功    能：   故障指示
//// 入口参数：	无
//// 出口参数:	无
////------------------------------------------------------------------------
//void	ErrIndicate(void)
//{
//	ErrDisplayIndicate();
//	
//	ErrLedIndicate();
//}
//
////------------------------------------------------------------------------
//// 名    称：   void	InitErrDealSys(void)
//// 功    能：   初始化错误代码缓冲区
//// 入口参数：	无
//// 出口参数:	无
////------------------------------------------------------------------------
//void	InitErrDealSys(void)
//{																
//// 	InitFIFO((stcFIFO *)&sErrFIFO,gErrBuf,sizeof(gErrBuf));
////	InitFIFO((stcFIFO *)&sStoreErrFIFO,gStoreErrBuf,sizeof(gStoreErrBuf));
////	printfcom0("sizeof(gErrBuf) %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//}
//
////------------------------------------------------------------------------
//// 名    称：   void  StoreErrCode(void)
//// 功    能：   油尺1故障处理
//// 入口参数：   无
//// 出口参数：   故障代码
////------------------------------------------------------------------------
//void  StoreErrCode(void)
//{
//	uint32	i;
//	uint8	ErrTypCod;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////		
////		if(sErrDeal[i].TypCod != RIGHT_DATA)
////		{
////			ErrTypCod = sErrDeal[i].TypCod;
////			
////			WriteFIFO((stcFIFO *)&sErrDealFIFO,(uint8 *)&ErrTypCod,1 );
////		}
////	}
//}
//
////------------------------------------------------------------------------
//// 名    称：   uint8  GetStoreErrTyp(void)
//// 功    能：   取Flsh存储时的故障代码
//// 入口参数：	无
//// 出口参数:	无
//// 说明:		存故障代码
////------------------------------------------------------------------------
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
//extern	uint8 JudgeFlashIDErrFlg( void );
//extern	uint8 JudgeFramWordEvt( void );
//
//#define		FLSH_ID_ERR		36
////------------------------------------------------------------------------
//// 名    称：   void  JudgeHostError(void)
//// 功    能：   故障处理系统
//// 入口参数：	无
//// 出口参数:	无
////------------------------------------------------------------------------
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
////------------------------------------------------------------------------
//// 名    称：   void  ErrDealSys(void)
//// 功    能：   故障处理系统
//// 入口参数：	无
//// 出口参数:	无
//// 说明:如果出现多故障,则先向应优先级高的故障
////------------------------------------------------------------------------
//void  ErrDealSys(void)
//{
//	static	uint32	Time = 0;
//	static	uint32	Times = 0;
//	
//	uint8	ErrFlg;
//	uint8	i;
//	
//
//	if((GetSysTime() - Time > 100) && (GetSysTime() - g_PullCardTime) > 100)
//	{
//		if( Times > 0)
//		{
//			i=0;
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeTAX2Error();						//TAX2通信
//			StoreCurErrFlg(ErrFlg,TAX2_ERR); 
//
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeDip1Error();						//测量装置故障
//			StoreCurErrFlg(ErrFlg,HOST_DIP1_ERR); 
//		
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeDip2Error();						//测量装置故障
//			StoreCurErrFlg(ErrFlg,HOST_DIP2_ERR);		
//			
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeHostError();						//运算参数
//			StoreCurErrFlg(ErrFlg,HOST_PRO_ERR);	
//			
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeCardError();						//IC卡故障
//			StoreCurErrFlg(ErrFlg,CARD_ERR);	
//			
//			printfcom0("\r\n  Error %d ",i++);																						
//			ErrDeal();										//故障运算
//
//			printfcom0("\r\n  Error %d ",i++);
//			StoreErrCode();									//存故障代码	
//				
//			ErrIndicate();									//指示故障 
//		}
//		
//		Times++;
//			
//		Time = GetSysTime();								
//	}
//}
