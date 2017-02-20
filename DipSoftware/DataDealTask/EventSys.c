//////#include 	"config.h"                             
//////#include 	"Globe.h"                             
//////#include 	"HardDrive.h"                             
//////#include 	"CpuDrive.h"                             
//////#include 	"Tax2.h"                             
//////#include 	"DipMath.h"                             
//////#include 	"FramStore.h"                             
//////#include 	"StoreRec.h"                             
//////#include 	"OperateCard.h"                             
//
//#include <includes.h>
//
////#define		EVT_DEAL_LEN		20
////stcFIFO		sEvtDealFIFO;						//定义串口0接收FIFO结构
////uint8		EvtDealBuf[EVT_DEAL_LEN];			//定义接收缓冲区
//
//#define     EVT_BUF_LEN     	12         //
//stcFIFO     sEvtFIFO;                      //定义串口0接收FIFO结构
//uint8       gEvtBuf[EVT_BUF_LEN];           //定义接收缓冲区
//
////数据类型
//#define   	TAX2_EVT     	90                  //TAX2发生故障
//#define   	HOST_DIP1_EVT	80                  //油尺1发生故障
//#define   	HOST_DIP2_EVT 	70                  //油尺2发生故障
//#define    	CARD_EVT     	60                  //IC卡故障
//#define    	HOST_PRO_EVT 	30                  //处理装置发生故障
////
////typedef    struct  _stcEvtDeal_
////{
////     uint8  CurEvtFlg;                 			//当前事件标识
////     uint8  LstEvtFlg;                 			//上次事件标识
////     uint8  TypCod;                   			//类型代码
////     uint8	Reserve0;							//预留0	
////}stcEvtDeal;
////
////stcEvtDeal		sEvtDeal[100];
////
//////------------------------------------------------------------------------
////// 名    称：   void  InitEvtSys(void)
////// 功    能：   初始化IC错误系统
////// 入口参数： 	无
////// 出口参数:	
//////------------------------------------------------------------------------
////void  InitEvtSysFlg(void)
////{
////	uint32	i;
////	
////	for(i = 0 ; i < 100; i++)
////	{
////		//SysFastHoldTast();
////		
////		sEvtDeal[i].CurEvtFlg	= RIGHT_DATA;	//当前标识
////		sEvtDeal[i].LstEvtFlg	= RIGHT_DATA;	//上次标识
////		sEvtDeal[i].TypCod 		= RIGHT_DATA;	//类型代码
////	}
////}
////
/////*
//////------------------------------------------------------------------------
////// 名    称：   void  StoreCurEvtFlg(uint8	EvtFlg)
////// 功    能：   存事件代码 
////// 入口参数：   无
////// 出口参数：   故障代码
//////------------------------------------------------------------------------
////void  StoreCurEvtFlg(uint8	EvtFlg)
////{
////	uint32	i;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		if(EvtFlg != RIGHT_DATA)
////		{
////			if(i == EvtFlg)
////			{
////				sEvtDeal[i].CurEvtFlg 	= EvtFlg;
////			}
////		}
////	}
////}
////
////*/
//////------------------------------------------------------------------------
////// 名    称：   void  ErrDeal(void)
////// 功    能：   油尺1故障处理
////// 入口参数：   无
////// 出口参数：   故障代码
//////------------------------------------------------------------------------
//void  StoreCurEvtFlg(uint8	EvtFlg,uint8 EvtTyp)
//{
//	uint32	i,j;
//	uint8	Buf[EVT_BUF_LEN];
//	uint32	EvtNum;
//	uint8	Tmp;
//
//	EvtNum = GetNoReadSizeFIFO((stcFIFO *)&sEvtFIFO);      	//求未读空间大小
//	OnlyReadFIFO((stcFIFO *)&sEvtFIFO,Buf,EvtNum);
//	printfcom0("\r\n EvtNum = %d, EvtTyp = %d,EvtFlg = %d",EvtNum,EvtTyp,EvtFlg);
//
//	if(EvtFlg != RIGHT_DATA)
//	{
//		for(i = 0;i < EvtNum ;i++)
//		{
//			if(Buf[i] == EvtFlg)
//			{
//				return;
//			}		
//		}
//
//		printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,",sizeof(gEvtBuf), GetNoReadSizeFIFO((stcFIFO *)&sEvtFIFO));	
//		WriteFIFO((stcFIFO *)&sEvtFIFO,(uint8 *)&EvtFlg,sizeof(EvtFlg));
//	}
////	if(ErrFlg != RIGHT_DATA)
////	{	
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			if(i == ErrFlg)							
////			{
////				sEvtDeal[i].CurEvtFlg 	= ErrFlg;
////
////				return	;
////			}
////			//else if(ErrTyp != HOST_PRO_EVT)
////			else
////			{
////				sEvtDeal[i].CurEvtFlg 	= RIGHT_DATA;
////			}
////		}
////	}
////	else
////	{
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			sEvtDeal[i].CurEvtFlg 	= RIGHT_DATA;
////		}	
////	}
//}
//
//////------------------------------------------------------------------------
////// 名    称：   void  EvtDeal(void)
////// 功    能：   油尺1故障处理
////// 入口参数：   无
////// 出口参数：   故障代码
//////------------------------------------------------------------------------
////void  EvtDeal(void)
////{
////	uint32	i;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////		
////		if(sEvtDeal[i].CurEvtFlg != RIGHT_DATA)
////		{
////			sEvtDeal[i].TypCod 		= sEvtDeal[i].CurEvtFlg;					//类型代码
////			
////			//PrintfCOM0("\r\n sEvtDeal[i].CurEvtFlg %d",sEvtDeal[i].CurEvtFlg);
////		}
////		else
////		{
////			sEvtDeal[i].TypCod		= RIGHT_DATA;					//事件恢复（和故障处理不同，事件只记录产生的时间，不记录结束时间） 
////		}
////		
////		sEvtDeal[i].LstEvtFlg 	= sEvtDeal[i].CurEvtFlg;			
////	}
////}
////
//////------------------------------------------------------------------------
////// 名    称：   void	InitEvtDealSys(void)
////// 功    能：   初始化事件存放缓冲区
////// 入口参数：	无
////// 出口参数:	无
//////------------------------------------------------------------------------
//void	InitEvtDealSys(void)
//{
////	InitEvtSysFlg();																			
//	
//	InitFIFO((stcFIFO *)&sEvtFIFO,gEvtBuf,sizeof(gEvtBuf));	
//}
////
//////------------------------------------------------------------------------
////// 名    称：   void  CardEvtDeal(void)
////// 功    能：   初始化错误代码缓冲区
////// 入口参数：	无
////// 出口参数:	无
////// 说明:如果出现多故障,则先向应优先级高的故障
//////------------------------------------------------------------------------
////uint8	GetEvtNoWriteNum(void)
////{
////	uint8	NoWriteNum;
////	static	uint32	Time 	= 0;
////	static	uint32	Timer 	= 0;
////	
////	NoWriteNum = GetNoReadSizeFIFO((stcFIFO *)&sEvtDealFIFO);
////	
////	if((NoWriteNum &&  (GetSysTime() > 60*100)) && GetSysTime() - Timer > 100)
////	{
////		Timer = GetSysTime();
////		Time++;
////	}
////	
////	if(Time > 30)					//过多事件，影响数据存储
////	{
////		NoWriteNum = 0;
////	}
////	
////	return	NoWriteNum;
////}
////
//////------------------------------------------------------------------------
////// 名    称：   void  StoreEvtCode(void)
////// 功    能：   存事件代码 
////// 入口参数：   无
////// 出口参数：   故障代码
//////------------------------------------------------------------------------
////void  StoreEvtCode(void)
////{
////	uint32	i;
////	uint8	EvtTypCod;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////		
////		if(sEvtDeal[i].TypCod != RIGHT_DATA)
////		{
////			EvtTypCod = sEvtDeal[i].TypCod;
////
////			WriteFIFO((stcFIFO *)&sEvtDealFIFO,(uint8 *)&EvtTypCod,1 );
////			
////			//PrintfCOM0("\r\n sEvtDeal[%d].TypCod %d",i,EvtTypCod);
////		}
////	}
////}
////
//////------------------------------------------------------------------------
////// 名    称：   uint8  GetStoreEvtTyp(void)
////// 功    能：   取Flsh存储时的故障代码
////// 入口参数：	无
////// 出口参数:	无
////// 说明:		存故障代码
//////------------------------------------------------------------------------
//uint8  GetStoreEvtTypCod(void)
//{
//	uint8	EvtTypCod = RIGHT_DATA;
//	
//	if( ReadFIFO(&sEvtFIFO,&EvtTypCod,sizeof(EvtTypCod)) )
//	{
//		return	EvtTypCod;								//成功,返回读取代码
//	}
//	else
//	{
//		return 	EvtTypCod;								//正确,返回0xFF
//	}
//}
//
//////----------------------------------------------------------------------------
////// 名    称：   uint8 JudgeStartEvt(void)
////// 功    能:    返回开机事件标识
////// 入口参数： 
////// 出口参数：
//////----------------------------------------------------------------------------
//uint8 	JudgeHostEvt(void)
//{
//	uint8	EvtTypeTmp;
//	uint8	EvtType[10];
//	uint8	i;
//	uint8	EvtBuf[10];
//	uint8	Time = 0;
//		
//	EvtTypeTmp    = RIGHT_DATA;
//	
//	for(i = 0; i< 10;i++)
//	{
//		EvtType[i] = RIGHT_DATA;
//	}
//	
//	EvtType[0] = JudgeStartEvt();
//	EvtType[1] = JudgeFlshEvt();	
//	EvtType[2] = JudgeFramEvt();	
//	EvtType[3] = JudgeOilEvt();
//	
//	for(i = 0 ; i < 10;i++)
//	{
//		if(EvtType[i] != RIGHT_DATA)
//		{
//			EvtBuf[Time++%10] = EvtType[i];
//			
//			//PrintfCOM0("\r\n \r\n EvtType[i] %d",EvtType[i]);
//		}
//	}
//	
//	if( Time )
//	{
//		EvtTypeTmp = EvtBuf[--Time%10];
//	}
//
//	return	EvtTypeTmp;
//}
//
/////**/
//////------------------------------------------------------------------------
////// 名    称：   void  EvtDealSys(void)
////// 功    能：   事件处理系统
////// 入口参数：	无
////// 出口参数:	无
////// 
//////------------------------------------------------------------------------
//void  EvtDealSys(void)
//{
//	static	uint32	Time = 0;
//	
//	uint8	EvtFlg;
//		
//	if(GetSysTime() - Time > 100)
//	{
////		/*
////		EvtFlg = JudgeStartEvt();									
////		StoreCurEvtFlg(EvtFlg);
////		
////		EvtFlg = JudgeFlshEvt();									
////		StoreCurEvtFlg(EvtFlg);		
////		
////		//EvtFlg = JudgeFramEvt();									
////		//StoreCurEvtFlg(EvtFlg);			
////			
////		EvtFlg = JudgeOilEvt();									
////		StoreCurEvtFlg(EvtFlg);			
////					
////		EvtFlg = JudgeTAX2Evt();						//TAX2通信事件
////		StoreCurEvtFlg(EvtFlg);
////		
////		EvtFlg = JudgeCardEvt();						//Card事件
////		StoreCurEvtFlg(EvtFlg);
////		*/
//		EvtFlg = JudgeHostEvt();						//
//		StoreCurEvtFlg(EvtFlg,HOST_PRO_EVT);
//		
////		EvtFlg = JudgeTAX2Evt();						//TAX2通信事件
////		StoreCurEvtFlg(EvtFlg,TAX2_EVT);
////				
////		EvtFlg = JudgeCardEvt();						//Card事件
////		StoreCurEvtFlg(EvtFlg,CARD_EVT);
////			
////		EvtDeal();										//故障运算
////		
////		StoreEvtCode();									//存故障代码
////			
////		Time = GetSysTime();	
//	}
//}
//
