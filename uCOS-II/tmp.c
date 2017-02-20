#include    "includes.h"  


void	IO0PIN_R(uint8	x)
{
}

void	IO0CLR_W(uint8	x)
{
}

void	IO0SET_W(uint8	x)
{
}




void	IO0DIR_IN(uint8	x)   
{
}

void	 IO0DIR_OUT(uint8 x)  
{
}

void	 IO1DIR_OUT(uint8 x)  
{
}

void	 NOP(void)  
{
	FeedDog();
}


void	 IO2DIR_OUT(uint8 x)  
{
}
void	 IO2PIN_W(uint8	x) 
{
}
void	 IO1PIN_W(uint8	x) 
{
}

//void	ReCalPara(uint8	x)
//{
//}

uint8 ReadFlsh(uint32 Addr,uint8 *buf,uint32 Len)
{	
	return	MX25L1602_RD(Addr, Len,(INT8U* )buf);
}

INT8U	WriteFlsh(INT32U Dst, uint8 * sFlshRec, INT32U NByte)
{
	return	MX25L1602_WR(Dst,(INT8U*)sFlshRec,NByte);
}



void IO0PIN_W(uint8	Val,uint8	x)   
{
}


uint8	l_hostevtflg;
uint8	GetHostEvtFlg(void)
{
	return	 l_hostevtflg;
}

#define		START_EVT		31		
//----------------------------------------------------------------------------
// 名    称：   uint8 JudgeStartEvt(void)
// 功    能:    返回开机事件标识
// 入口参数： 
// 出口参数：
//----------------------------------------------------------------------------
uint8 	JudgeStartEvt(void)
{
	uint8	EvtType = RIGHT_DATA;
	static	uint32	Time = 0;
	
	EvtType = RIGHT_DATA;
	
	if( Time++ == 0 )
	{
		EvtType = START_EVT;	

		l_hostevtflg = 	START_EVT;
	}
	
	return	EvtType;
}

//----------------------------------------------------------------------------
// 名    称：   void PrinfSysInfo(void)
// 功    能:    系统初始化
// 入口参数：
// 出口参数：
//----------------------------------------------------------------------------
void	PrinfSysInfo(void)
{
	stcDeviceInfo		sDeviceInfo;
	stcReviseHight		sReviseHight;
	stcFixInfo  		sFix;
	stcDensity			sDensity;
	float				Density;
	int16				ReviseHight;
	uint8				OilBoxCod;


	DisplayTime();
	DelayX10ms(1*100);

	DisplaySet(100,1,"SV15");		
//	DisplaySet(100,1,"10.08");

	DisplaySet(100,1,"HV10");
	DelayX10ms(2*100);


	ReadHostInfo((stcDeviceInfo *)&sDeviceInfo);		//读出厂信息
	
	//printfcom0("\r\n 能耗硬件版本号:	");
	SendCOM0(sDeviceInfo.HardwareVer,sizeof(sDeviceInfo.HardwareVer));
	//printfcom0("\r\n 能耗软件版本号:	");
	SendCOM0(sDeviceInfo.SoftwareVer,sizeof(sDeviceInfo.SoftwareVer));
	
	//printfcom0("\r\n ");
	OilBoxCod = GetOilBoxCod();
	printfcom0("\r\n 油箱模型号:	%d",OilBoxCod);

	DisplaySet(150,1,"C_%u",OilBoxCod);	

	DelayX10ms(1*100);
  	if(ReadReviseHight((stcReviseHight *) &sReviseHight))
  	{	
  		ReviseHight = sReviseHight.ReviseHight / 10;
  		//printfcom0("\r\n 修正高度为:	%d",ReviseHight*10);
  		DisplaySet(100,1,"H_%d.",ReviseHight*10);		
	}
	DelayX10ms(1*100);
		
  	if( ReadDensity((stcDensity *) &sDensity))			//取密度
	{
		Density	=  ((float)sDensity.Density / 1000);
  		DisplaySet(60,1,"d_%d.",(uint16)(1000*Density));		
  	}
  	DelayX10ms(1*100);

 	ReadFixInfo((stcFixInfo *)&sFix);
 	DisplaySet(100,1,"%d",sFix.LocoTyp);
	DelayX10ms(1*100);		
 	//DisplaySet(100,1,"%d",(uint16)*sFix.LocoNum);		
 	DisplaySet(100,1,"N_%d",sFix.LocoNum[0]+sFix.LocoNum[1]*256);	
		
// 	DelayX10ms(2*100);

	DisplaySet(60,1,"        ");
  	DisplaySet(60,1,"88888888");		
 	DisplaySet(60,1,"        ");	
	
//	DelayX10ms(2*100);	
}

uint8 OneTask(void)   
{
	UART0Init();
	UART1Init();
	InitSoftCOM();
	InitLed();
	TestSoftCOM();

	UART2Init();
	UART3Init();

	InitDisplay();
	DisplayString("88888888");
	//ClaerDisplaySetWithoutStore();

	InitLed();
	DisplayString("         ");
	InitCardIO();
	InitFramIO();
	InitFlashIO();

	InitDS3231();
	InitEvtDealSys();

	InitAdc();

	Time0Init();
	Time1Init();
	Time2Init();


	return	1;
}

uint8 HoldTask(void)   
{
//	HoldDisplay();
	HoldLed();
//	HoldCard();								//IC卡维护

	return	1;
}

#define			PLUG_IN_CARD		1
//----------------------------------------------------------------------------
// 名    称：   void IncDisplay(void)
// 功    能:    系统初始化
// 入口参数：
// 出口参数：
//----------------------------------------------------------------------------
void IncDisplay(void)
{ 
	static	uint32		Time = 0;
//	static	uint32		Times = 0;
	int16	Prs1,Prs2;	
	uint8	i;

	Time = GetSysTime();

	for(i =0 ;i<3;)
	{
//		COM0Task();
		
		Prs1 = GetDip1Prs();
		Prs2 = GetDip2Prs();		
		
		//printfcom0("\r\n %4d.%4d",Prs1,Prs2);
		if(GetSysTime() - Time > 100)
		{		
			i++;
			Time = GetSysTime();
	
			if(i%2 == 0)
			{
				DisplaySet(100,1,"%4d.%4d.",Prs1,Prs2);
			}
			else
			{
				DisplaySet(100,1,"%4d.%4d",Prs1,Prs2);
			}
		}
	}


/*	while(GetPlugFlg() == PLUG_IN_CARD)  //有东西插入
	{
		COM0Task();

		if(Times < 1*20)		//1分钟通信
		{	
			COM0Task();
		}
					
		Prs1 = GetDip1Prs();
		Prs2 = GetDip2Prs();

		if(GetSysTime() - Time > 100)
		{		
			Time = GetSysTime();

			Times++;
			
			if(Prs1<10000 && Prs2 < 10000)
			{			
				if(Times%2 == 0)
				{
					DisplaySet(100,1,"%4d.%4d.",Prs1,Prs2);
				}
				else
				{
					DisplaySet(100,1,"%4d.%4d",Prs1,Prs2);
				}
			}
			else
			{
				DisplaySet(100,1,"%d",Prs1);
				DisplaySet(100,1,"%d.",Prs2);
			}
		}
		
		if(Times > 1*60)		//2分钟退出
		{	
			DelayX10ms(200);
			return;
		}
	}	
	
	DelayX10ms(200);
*/	
	DisplaySet(150,1,"%d",g_CurFlshRecNum);
	DisplaySet(150,1,"%d.",g_LshRedFlshRecNum);
	printfcom0("\r\n g_CurFlshRecNum %d, g_LshRedFlshRecNum %d",g_CurFlshRecNum,g_LshRedFlshRecNum);
}

void	OneTaskTimes(void)
{
	OneTask();
	
	g_CurFlshRecNum 	= GetCurFlshRecNum();
	g_LshRedFlshRecNum  = GetLstFlshRecNum();
	g_LshRedFlshRecNum_gprs  = GetLstFlshRecNum_gprs();


  printfcom0("\r\n 当前 %d,已读 %d,已发GPRS %d",g_CurFlshRecNum,g_LshRedFlshRecNum,g_LshRedFlshRecNum_gprs);
 	PrinfSysInfo();
//	IncDisplay();
//	InitEvtDealSys();
	InitErrDealSys();
}



void	LedTast(uint8	flg)
{
	static	uint32	Time = 0;
	uint8	led0com1flg 	= 0;
	uint8	led1com2flg 	= 0;
	uint8	led2com3flg 	= 0;
	uint8	locoworksta;
		
	if((GetSysTime()  - Time > 50) || flg == 1)
	{
		Time = GetSysTime();

		led0com1flg = GetLed0Com1Flg();
		switch(led0com1flg)
		{
			case  COM_LED_REC:
								OffLed(COM1_STA_LED);
								OnLed(COM1_STA_LED,3000,50,50);
								break; //慢闪
								
			case  COM_LED_DATA:
								OffLed(COM1_STA_LED);
								OnLed(COM1_STA_LED,3000,5,5);
								break;  //慢闪
			default:
//								printfcom0("\r\n com1 无通讯");
								OffLed(COM1_STA_LED);
		}

		led1com2flg = GetLed1Com2Flg();
		switch(led1com2flg)
		{
			case  COM_LED_REC:
								OffLed(COM2_STA_LED);
								OnLed(COM2_STA_LED,3000,55,55);
								break; //慢闪
								
			case  COM_LED_DATA:
								OffLed(COM2_STA_LED);
								OnLed(COM2_STA_LED,3000,6,6);
								break;  //慢闪
			default:
//								printfcom0("\r\n com2 无通讯");
								OffLed(COM2_STA_LED);
		}

		led2com3flg = GetLed2Com3Flg();
		switch(led2com3flg)
		{
			case  COM_LED_REC:
								OffLed(COM3_STA_LED);
								OnLed(COM3_STA_LED,3000,45,45);
								break; //慢闪
								
			case  COM_LED_DATA:
								OffLed(COM3_STA_LED);
								OnLed(COM3_STA_LED,3000,4,4);
								break;  //慢闪
			default:
//								printfcom0("\r\n com3 无通讯");
								OffLed(COM3_STA_LED);
		}

		if(GetMySpeed1())
		{
			OnLed(SPEED1_LED,3000,4,4);
		}
		else
		{
			OffLed(SPEED1_LED);
		}

		if(GetMySpeed2())
		{
			OnLed(SPEED2_LED,3000,4,4);
		}
		else
		{
			OffLed(SPEED2_LED);
		}

		if(GetMyEngRotSpd())
		{
			OnLed(CSPEED_LED,3000,4,4);
		}
		else
		{
			OffLed(CSPEED_LED);
		}

		locoworksta = GetMyLocoWorkState();
		switch(locoworksta)
		{
			case 0x01<<0:
					OnLed(LOCOSTA_LED,3000,2,2);
					break;
			case 0x01<<4:
					OnLed(LOCOSTA_LED,3000,10,10);
					break;
			case 0x01<<3:
					OnLed(LOCOSTA_LED,3000,90,40);
					break;
			case 0x01<<2:
					OnLed(LOCOSTA_LED,3000,150,60);
					break;
			default:
				OffLed(LOCOSTA_LED);

		}
	}
}

void	DisplayOnceInfo(void)
{
	int16	hig1,hig2;
	uint16  speed1,speed2;
	uint16	cspeed;
	uint8	worksta;

	hig1 	= GetDip1Hig();
	hig2 	= GetDip2Hig();
	speed1 	= GetMySpeed1();
	speed2 	= GetMySpeed2();
	cspeed 	= GetMyEngRotSpd();
	worksta	= GetMyLocoWorkState();


	DisplaySet(150,1,"%4u.%4u",hig1%10000,hig2%10000);
	DisplaySet(150,1,"V-%u",speed1%1000);
	DisplaySet(150,1,"V.%u",speed2%1000);
	DisplaySet(150,1,"C.%u",cspeed%10000);
	DisplaySet(150,1,"%u",worksta);

//	printfcom0("\r\n hig1 %d,%d,%d,%d,%d,%d ",hig1,hig2,speed1,speed2,cspeed,worksta);
}


void	DisplayDipVal()
{
	static	uint32	Time = 0;
	static	uint32	times = 0;
	static	uint32	ZeroTimes = 0;
	static	uint32	errtimes = 0;
	uint8	hosterrflg;
	uint8	diperrflg;
	
	if(GetSysTime()  - Time > 150)
	{
		Time = GetSysTime();
		times++;

		if(times < 10)
		{
			if(times == 5)
			{	
				DisplayOnceInfo();
			}
			DelayX10ms(50);
			return;
		}

		hosterrflg = GetHostErrFlg();
		diperrflg  = GetDipErrFlg();

		if(hosterrflg != RIGHT_DATA || diperrflg != RIGHT_DATA)
		{
			errtimes++;
			if(errtimes % 4 == 0)
			{
				 if(hosterrflg != RIGHT_DATA  )
				 {
					DisplaySet(50,1,"E-%u",hosterrflg);	//显示油量值
				 }
				 if(diperrflg != RIGHT_DATA  )
				 {
					DisplaySet(50,1,"E-%u",diperrflg);	//显示油量值
				 }

				 return;
			}
		}

		if(g_DipDisVal)
		{
			DisplaySet(60,1,"%u",g_DipDisVal % 10000);	//显示油量值
			ZeroTimes = 0;
		}	
		else
		{
			ZeroTimes++;
			if(ZeroTimes > 5)
			{
				DisplaySet(60,1,"%u",g_DipDisVal % 10000);	//显示油量值
			}
		}		
		
		if(times %20 == 0)
		{
			InitDisplay();
		}
		
		OnLed(RUN_LED,3000,5,5);
	}
}	

uint8 TestTask(void)  
{
	uint32	FlshAddr;

	stcFlshRec sFlshRec;

	g_CurFlshRecNum++;
 	StoreCurFlshRecNum( g_CurFlshRecNum );           		//把流水号存入铁电
	ReadCurFlshRecNum( g_CurFlshRecNum );           		//把流水号存入铁电	
	//printfcom0("\r\n g_CurFlshRecNum %d",g_CurFlshRecNum);

  	FlshAddr = GetRecNumAddr( g_CurFlshRecNum );
    
	sFlshRec.StoreCnt =  g_CurFlshRecNum;
	if(!WriteFlsh(FlshAddr, (uint8 *)&sFlshRec, sizeof(sFlshRec)))
	{
		//printfcom0("\r\n WriteFlsh %d",FlshAddr);		
	}

	WriteFlsh(FlshAddr, (uint8 *)&sFlshRec, sizeof(sFlshRec));
	//printfcom0("\r\n sFlshRec.StoreCnt %d",sFlshRec.StoreCnt);
	return 1;
}

extern	stcFIFO 	sErrFIFO;
extern	stcFIFO		sStoreErrFIFO;
extern	stcFIFO     sUART6RecFIFO;                          //定义串口0接收FIFO结构

