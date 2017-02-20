#include <includes.h>

extern 	void 	InputDebugState(void);
extern	void	PrinfDebugState(void);


//----------------------------------------------------------------------------
// 名    称：   void HardInit(void)
// 功    能:    硬件初始化
// 入口参数：	
// 出口参数：	
//----------------------------------------------------------------------------
void HardInit(void)
{
	//MCU
	InitTimer1();							//初始化定时器1系统时钟
	
	OpenCOM0Tax(28800);						//串口0初始化,波特率57600( 开关未开)
	
	OpenCOM1(9600);							//初始经串口1
	
#ifdef	HARD_VER_111122	
	mInitCH376Host();						//初始化USB
#endif

	InitI2CIO();							//初始化I2C总线

	InitAdc();								//初始比ADC
	
	InitPulse1T0();							//初始化频率测试
	//外部硬件
	InitDisplay();							//初始化显示
	
	InitICCard();							//初始化IC卡
	
	InitKey();								//初始化按键
	
	InitLed();								//初始化灯	
	
	InitDS3231();							//初始化时钟
		
	ResetFlash();							//复位Flsh
	
	InitFlshInfo();							//初始化Flsh
	
	ProtectFlash();							//Flash写保护
	
	ScanPowerAddr();						//扫描电量地址
}

extern	uint8 GetLocoModInfo(uint32	LocoTyp,uint32 ModeNum,stcLocoModNum *sLocoModNum);
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

	ReadHostInfo((stcDeviceInfo *)&sDeviceInfo);		//读出厂信息
	
	printfcom0("\r\n 能耗硬件版本号:	");
	SendCOM0(sDeviceInfo.HardwareVer,sizeof(sDeviceInfo.HardwareVer));
	printfcom0("\r\n 能耗软件版本号:	");
	SendCOM0(sDeviceInfo.SoftwareVer,sizeof(sDeviceInfo.SoftwareVer));
	
	printfcom0("\r\n ");
	OilBoxCod = GetOilBoxCod();
	printfcom0("\r\n 油箱模型号:	%d",OilBoxCod);

	DisplaySet(150,1,"C_%u",OilBoxCod);	

  	if(ReadReviseHight((stcReviseHight *) &sReviseHight))
  	{	
  		ReviseHight = sReviseHight.ReviseHight / 10;
  		printfcom0("\r\n 修正高度为:	%d",ReviseHight*10);
  		DisplaySet(100,1,"%d.",ReviseHight*10);		
	}
		
  	if( ReadDensity((stcDensity *) &sDensity))			//取密度
	{
		Density	=  ((float)sDensity.Density / 1000);
//  		printfcom0("\r\n 密度值:	%f",Density);
  		DisplaySet(60,1,"%d.",(uint16)(1000*Density));		
  	}
  	
 	ReadFixInfo((stcFixInfo *)&sFix);
 	DisplaySet(100,1,"%d",sFix.LocoTyp);		
 	//DisplaySet(100,1,"%d",(uint16)*sFix.LocoNum);		
 	DisplaySet(100,1,"%d",sFix.LocoNum[0]+sFix.LocoNum[1]*256);		
 
  	printfcom0("\r\n ");

  	DisplaySet(60,1,"88888888");		
 	DisplaySet(60,1,"        ");		
}

//----------------------------------------------------------------------------
// 名    称：   void	GetDeviceInfoStr(uint8 *Buf)
// 功    能:    软件初始化
// 入口参数： 
// 出口参数：
//----------------------------------------------------------------------------
void	GetDeviceInfoStr(uint8 *Buf)
{
	stcDeviceInfo		sDeviceInfo;
	uint8	Tmp;
	uint32	strLen,AllStrLen = 0;
	
	ReCalPara(0);
	
	printfcom0("\r\n 装置信息如下!");
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n \r\n 装置信息如下：");
	
	printfcom0("\r\n 能耗硬件版本号:	");
	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 设置的产品编号: %d",sDeviceInfo.DeviceNum);
	//printfcom0("\r\n strLen %d, AllStrLen = %d",strLen,AllStrLen);	
	
	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 设置的产品硬件版本号: %s",sDeviceInfo.HardwareVer);
	//printfcom0("\r\n strLen %d, AllStrLen = %d",strLen,AllStrLen);		
	//printfcom0("\r\n 能耗软件版本号:	");
	
	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 设置的产品软件版本号: %s",sDeviceInfo.SoftwareVer);
	printfcom0("\r\n strLen %d, AllStrLen = %d",strLen,AllStrLen);
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 设置的产品软件版本号: %d",Tmp);
	
#ifdef	HARD_VER_111122	
	Tmp = 1;
#endif		
	
#ifdef	HARD_VER_090426		
	if(Tmp == 0)
	{	
		printfcom0("\r\n 能耗软件版本号:	");
		AllStrLen += strLen;
		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 硬件版本: HV02");	
	}
	else
	{
		AllStrLen += strLen;
		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 硬件版本: HV03");			
	}	
#endif		

#ifdef	HARD_VER_090214			
		AllStrLen += strLen;
		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 硬件版本: HV01");			
#endif		

	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 软件版本: SV12.03.12");		
}

extern	void	TestFramOneWord(void);
extern	void	TestFlashID(void);
extern	uint32	GetLstFlshRecNum(void);
//----------------------------------------------------------------------------
// 名    称：   void SoftInit(void)
// 功    能:    软件初始化
// 入口参数： 
// 出口参数：
//----------------------------------------------------------------------------
void SoftInit(void)
{	
	g_CurFlshRecNum 	= GetCurFlshRecNum();
	
	g_LshRedFlshRecNum  = GetLstFlshRecNum();
	
	if(g_CurFlshRecNum < g_LshRedFlshRecNum)  //如果当前流水号小于已取流水号，则已取流水号冲新赋值
	{
		printfcom0("\r\n g_CurFlshRecNum < g_LshRedFlshRecNum");
		g_LshRedFlshRecNum = g_CurFlshRecNum;
	}
	
	InputDebugState();						//进入系统调式模式	
	
	InitErrDealSys();						//错误处理系统
	
	InitEvtDealSys();						//初始化事件系统
	
	OpenTax2();								//打开TAX2通信
	
	InitWatchDog();							//初始化dog
	
	TestFlashID();

	TestFramOneWord();
	
	DelayX10ms(50);							//
}

extern	void IniLocoModTab(void);
//----------------------------------------------------------------------------
// 名    称：   void SysInit(void)
// 功    能:    系统初始化
// 入口参数：
// 出口参数：
//----------------------------------------------------------------------------
void SysInit(void)
{ 
	uint8	Tmp = 0;
	DisplaySet(100,1,"SV12");		
	DisplaySet(100,1,"10.02");
	
#ifdef	HARD_VER_111122	
	Tmp = 1;
#endif		
	
#ifdef	HARD_VER_090426		
	if(Tmp == 0)
	{	
		DisplaySet(100,1,"HV02");	
	}
	else
	{
		DisplaySet(100,1,"HV03");	
	}	
#endif		
#ifdef	HARD_VER_090214			
	DisplaySet(100,1,"HV01");		
#endif		
	//g_LshRedFlshRecNum 	= 0;
	
	printfcom0("\r\n 当前记录号：	%u",g_CurFlshRecNum);
	
	printfcom0("\r\n 读卡记录号：	%u",g_LshRedFlshRecNum);	
	
	printfcom0("\r\n ");
	
//	printfcom0("\r\n 运行模式：	%d  说明：1、为试验模式；0、为正常运行模式",g_TestModelFlg);	
		
	PrinfSysInfo();			
	
	PrinfDebugState();	
	
	IniLocoModTab();			//装置初始装置的模型编号
	
	DisplayTime();				//时间显示

	DelayX10ms(50);			
	
	printfcom0("\r\n ");
}


//----------------------------------------------------------------------------
// 名    称：   void IncDisplay(void)
// 功    能:    系统初始化
// 入口参数：
// 出口参数：
//----------------------------------------------------------------------------
void IncDisplay(void)
{ 
	static	uint32		Time = 0;
	static	uint32		Times = 0;
	static	int16		Prs1,Prs2;	
	static	uint8		i;

	Time = GetSysTime();

	for(i =0 ;i<8;)
	{
		
		COM0Task();
		
		//DelayX10ms(100);
		//COM1Task();
//		SysHoldTast();
			
		Prs1 = GetDip1Prs();
		Prs2 = GetDip2Prs();		
		
		//printfcom0("%4d.%4d",Prs1,Prs2);
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

	while(GetPlugFlg() == PLUG_IN_CARD)  //有东西插入
	{
		printfcom0("\r\n Plug Card!");
		
//		SysHoldTast();

		if(Times < 1*60)		//1分钟通信
		{	
			COM0Task();
		}
		
		//DelayX10ms(50);
					
		Prs1 = GetDip1Prs();
		Prs2 = GetDip2Prs();

		if(GetSysTime() - Time > 100)
		{		
			Time = GetSysTime();

			Times++;
			
			if(Prs1<10000 && Prs2 < 10000)
			{
				printfcom0("%4d.%4d",Prs1,Prs2);
				
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
				printfcom0("%4d.%4d",Prs1,Prs2);

				DisplaySet(100,1,"%d",Prs1);
				DisplaySet(100,1,"%d.",Prs2);
			}
		}
		
		if(Times > 2*60)		//2分钟退出
		{	
			DelayX10ms(200);
			return;
		}
	}	
	
	DelayX10ms(400);
	
	DisplaySet(150,1,"%d",g_CurFlshRecNum);
	DisplaySet(150,1,"%d.",g_LshRedFlshRecNum);

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
	}
	
	return	EvtType;
}

//----------------------------------------------------------------------------
// 名    称：   void PrinfDebugState(void)
// 功    能:    系统初始化
// 入口参数：
// 出口参数：
//----------------------------------------------------------------------------
void	PrinfDebugState(void)
{
	printfcom0("\r\n \r\n ");	
	printfcom0("\r\n 调试模型对应关系:");
	
	printfcom0("\r\n 装置运行：	<--->	* 设备信息设置和生产测试!");
	printfcom0("\r\n 时间显示：	<--->	* 显示时间!");
	printfcom0("\r\n 卡满：	   	<--->	* 将未读取的数据记录从串口读出!");
	printfcom0("\r\n 写卡完成：	<--->	* 串口零接收再从串口零发送出来!");
	printfcom0("\r\n 其它：	   	<--->	* IC卡调试，可做几种比较简单的卡!");
	printfcom0("\r\n TAXII： 	  <--->	* 进行接收TAXII测试!");
	printfcom0("\r\n 测量：	  	<--->	* 用IC卡取装置内所有的数据!");
	printfcom0("\r\n IC卡：	  	<--->	* 设备信息设置和生产测试!");
	
	printfcom0("\r\n \r\n ");	
}

extern	void	 TestUsb(void);
extern	uint8	 ComModCard(stcCardFlg	* sCardFlg);
extern	uint8    WriteCardComModelTest(void);
extern	uint8    WritesSetDipCardTest(void);
extern	uint8    WritesTestCardTest(void);
extern	uint8    WriteExpandAddTest(void);
extern	uint8    WriteExpandSubTest(void);
extern	uint8    WriteDenDataCardTest(void);

const char *MemorySizeInf[]  ={"512k","1M", "2M", "4M", "8M", "16M", "32M","64M"};	

//----------------------------------------------------------------------------
// 名    称：  void InputDebugState(void)
// 功    能:   按下按键进入相应调试方式
// 入口参数：
// 出口参数：
//----------------------------------------------------------------------------
void InputDebugState(void)
{
	uint32 	EndTime;
	uint32	KeyFlag = 0;
	uint32	i,j;
	char*	pString[] = 
	{
		"* ",
		"* 测试串口输入油箱模型",
		"* 将未读取的数据记录从串口读出！",
		"* 进行接收TAXII测试！",
		"* IC卡调试，可做几种比较简单的卡！",
		"* 串口零接收再从串口零发送出来！",
		"* 串口设置参数！",
		"* 显示时间",
		"* 设备信息设置和生产测试！",
	};

#ifdef	HARD_VER_090426
	while(KeyPressed())
	{
		KeyFlag = 1;
		for(i = 8 ; 0 < i;i--)
		{
			if(i>4)
			{
				j = 12 - i;
			}
			else
			{
				j = 4 - i;
			}
			
#ifdef	HARD_VER_111122
			LightLed(j);	
#else
			LightLed(i - 1);	
#endif
			printfcom0("\r\n LightLed(%u)",i);	
			EndTime = GetSysTime() + 1*100;	
			while(GetSysTime() < EndTime )
			{
				if(KeyLoosen())
				{
					KeyFlag = 2;
					printfcom0("\r\n * Input Debug State:");
					printfcom0(pString[i]);
		  			printfcom0("\r\n \r\n ");					
					break;
				}
			} 
#ifdef	HARD_VER_111122			
			UnLightLed(j);
#else			
			UnLightLed(i - 1);
#endif
			if(KeyFlag == 2)
			{
				break;
			}
		}
	}
	
	OffAllLed();
	
	if(!KeyFlag || KeyFlag != 2)								//没有按键
	{
		return;
	}
	
	switch(8 - i)
#endif

#ifdef	HARD_VER_090214
	while(KeyPressed())
	{
		KeyFlag = 1;
		for(i = 0 ; 0 < 8;i++)
		{
			LightLed(i);		
			EndTime = GetSysTime() + 1*100;	
			while(GetSysTime() < EndTime )
			{
				if(KeyLoosen())
				{
					KeyFlag = 2;
					printfcom0("\r\n * Input Debug State:");
					printfcom0(pString[i]);
		  			printfcom0("\r\n \r\n ");					
					break;
				}
			} 
			UnLightLed(i);
			if(KeyFlag == 2)
			{
				break;
			}
		}
	}
	
	OffAllLed();
	
	if(!KeyFlag || KeyFlag != 2)									//没有按键
	{
		return;
	}
	
	switch( i )	
#endif
	
	{
		case 0:	
				FactoryTest();	break;								//生产测试	

		case 1:	DisplayString("DIST");								//显示时间
				
				while(1)
				{	
					uint32	Time = 0;
					
					if(GetSysTime() - Time > 100)
					{
						PrintfTime();
						DisplayTime();
					}
					
//					SysHoldTast();
				}
				
				break;
//---------------------------------------------				
		case 2:		
				DisplayString("FOUT");	
				OpenCOM0(57600);									//打开串口0
				PrintfAllFlshRec();
				while(1);
				break;
//---------------------------------------------				
		case 3:
				DisplayString("CMOD");							
		
				DelayX10ms(100);
		
				//COM0GetModelCard();
						
				break;
//---------------------------------------------				
		case 4: 
				DisplayString("CSET");								//显示时间
		
				while(1)	
				{
					while(!PlugICCard())
					{;}		
					
						
					DisplayString("OILS");							//模型
					WriteCardOilModelTest();				
					printfcom0("\r\n WriteCardOilModelTest\r\n ");					
					DelayX10ms(200);	
					
					DisplayString("DATA");							//数据
					printfcom0("\r\n WriteCardDataCardTest\r\n ");					
					WriteCardDataCardTest();
					DelayX10ms(200);	
						
					//DisplayString("TIME");						//时间
					//printfcom0("\r\n WriteCardTimeCardTest\r\n ");					
					//WriteCardTimeCardTest();
					//DelayX10ms(200);
					
					DisplayString("DENS");							//密度
					printfcom0("\r\n WriteDensityCardTest\r\n ");					
					WriteDensityCardTest();
					DelayX10ms(200);	

					DisplayString("DDNS");							//密度+数据
					printfcom0("\r\n WriteDensityCardTest\r\n ");					
					WriteDenDataCardTest();
					DelayX10ms(200);	
					
					DisplayString("DDHS");							//密度+数据+gao
					printfcom0("\r\n WriteDensityCardTest\r\n ");					
					WriteDenDataCardTest();
					DelayX10ms(200);	
								
					DisplayString("COPY");							//复制卡
					printfcom0("\r\n WriteCopyCardTest\r\n ");					
					WriteCopyCardTest();
					DelayX10ms(400);	

					DisplayString("FRMC");							//复制卡
					WriteCopyFramTest();
					printfcom0("\r\n WriteCopyFramTest\r\n ");					
					DelayX10ms(200);	
					
					DisplayString("SETV");							//置数卡
					WritesSetDipCardTest();
					printfcom0("\r\n WritesSetDipCardTest\r\n ");					
					DelayX10ms(200);	
									
					DisplayString("TEST");							//置数卡
					WritesTestCardTest();
					printfcom0("\r\n WritesTestCardTest\r\n ");					
					DelayX10ms(200);	
									
					DisplayString("SETC");							//
					WriteCardComModelTest();
					printfcom0("\r\n WriteCardComModelTest\r\n ");					
					DelayX10ms(200);	
					
					DisplayString("TIMA");							//特殊模型卡 
					WriteExpandAddTest();
					printfcom0("\r\n WriteExpandAddTest\r\n ");					
					DelayX10ms(200);		
									
					DisplayString("TIMS");							//特殊模型卡
					WriteExpandSubTest();
					printfcom0("\r\n WriteCardComModelTest\r\n ");		
								
					DelayX10ms(200);						DisplayString("RIND");							//读索引
					printfcom0("\r\n ReadCardIndexTest\r\n ");					
					ReadCardIndexTest();
					DelayX10ms(500);										
				}	
		break;
//---------------------------------------------				
		case 5:
				DisplayString("C0-0.");							
				
				printfcom0("\r\n 串口零接收TAX箱信息，串口0以波特率28800转发TAX箱信息;\r\n ");					
				
				//COM0SendCardFlg();
				OpenTax2();											//打开TAX2通信

				while(1)
				{						
					TestTAX2Info();				
				}
				break;
				/*
				DisplayString("FTOC");							

				g_LshRedFlshRecNum 	= 0;

				while(!PlugICCard())
				{;}		
				
				FramToCard();
				
				DisplayString("FTRA");							

				while(1)
				{;}
				*/
		break;
//---------------------------------------------		
		case 6:
				
				
				DisplayString("C0-0");	
				OpenTax2();											//打开TAX2通信

				while(1)
				{						
					COM0ToCOM0();
				}
		
				//DisplayString("TEST");							
				
				//g_TestModelFlg = 1;
				/**/
				//DisplayString("PARR");	
				
				//DataCardPartRead();
								
				DelayX10ms(200);
				break;
		break;
//---------------------------------------------	
		case 7:
				DisplayString("SMOD");							

				printfcom0("\r\n 测试串口输入油箱模型");
				while(1)
				{
				//	COM0SetModel();
				}
				break;				
		break;
//---------------------------------------------	
				
		default:
		break;
	}
}
/**/