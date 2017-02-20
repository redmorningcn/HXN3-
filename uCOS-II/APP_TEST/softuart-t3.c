#include <includes.h>

#define		HDLC_RXD			1
#define		EN_HDLC_RXD			129

#define		HDLC_RXC			5
#define		EN_HDLC_RXC			6

#define		TXD1				15
#define		RXD1				16
#define		EN_485_1 			122

#define		RXD3				1
#define		EN_485_3			129

#define		EN_HDLC_TXD			19
#define		HDLC_TXD			17
#define		HDLC_TXC			10
#define		RXD2				11
#define		EN_HDLC_TXC			128
#define		COM1_FRAM_END		0x2c
#define		COM1_FRAM_END0		0x10

#define 	SoftCOM_BPS     		9600                   	/* 串口通信波特率               */
#define     COM1_REVBUF_LEN		    256        				//串口接收

static		stcFIFO     sSoftCOMRecFIFO;                          //定义串口0接收FIFO结构
static		uint8       SoftCOMRecBuf[COM1_REVBUF_LEN];           //定义接收缓冲区

uint8	l_softsendbyteflg = 0;
uint8  	*l_hdlcsendbuf;
uint32	l_softsendlen = 0;



void	WritesSoftTxd(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(HDLC_TXD,1);
	}
	else
	{
		GPIO_SetOrClearValue(HDLC_TXD,0);		
	}	
}


void	WritesSoftTxc(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(HDLC_TXC,1);
	}
	else
	{
		GPIO_SetOrClearValue(HDLC_TXC,0);		
	}	
}


//uint8	ReadSoftRxd(void)
//{
//    uint8 temp;
//	temp = 	GPIO_ReadIoVal(RXD3);
//    return temp;
//}

//uint8	ReadSoftRxd1(void)
//{
//    uint8 temp;
//	temp = 	GPIO_ReadIoVal(RXD1);
//    return temp;
//}

uint8	ReadSoftRxdcp(void)
{
    uint8 temp;
	temp = 	GPIO_ReadIoVal(HDLC_RXD);
    return temp;
}

uint8	l_e3hdlcframendflg = 0;
void	Cleare3HdlcFramEndFlg(void)
{
	l_e3hdlcframendflg = 0;	
}

uint8	Gete3HdlcFramEndFlg(void)
{
	return 	l_e3hdlcframendflg;	
}

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		External interrupt 3 handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
//void EINT3_IRQHandler(void)	   //hdlc rec
//{
//  static	uint8 	recbytetmp 	= 0;
//  static	uint32	recbitnum 	= 0;
//  static	uint8	higbittimes = 0;
//  uint8	    movebitflg = 0;		 
//  uint8		recbittmp;
////  if(GPIO_GetIntStatus((RXD2/100), RXD2, 1))
//  {
//	  GPIO_ClearInt((RXD2/100),(1<<RXD2));
// 
//	  movebitflg = 0;
//	  recbitnum++;
//	  recbittmp = ReadSoftRxd();
//	  
//	  if(recbittmp)
//	  {
//	  	 higbittimes++;
//		 
//		 if(higbittimes >= 7) 
//		 {
//		 	 printfcom0("$");
//			 recbytetmp  = 0;
//			 higbittimes = 0;
//			 recbitnum   = 0;
//
//			 return; 
//		 }
//	  }
//	  else
//	  {
//	      if(higbittimes == 6)
//		  {
//			 if(recbitnum > 16)
//			 {
//			 	printfcom0(" --e30\r\n");
//				l_e3hdlcframendflg = 1;
//			 }
//
//			 recbytetmp = 0;
//			 higbittimes = 0;
//			 recbitnum = 0;
//			 
//			 return; 		  	 
//		  }
//		  else if(higbittimes == 5)
//		  {
//		  	 movebitflg = 1;
//			 recbitnum--;
//		  }
//
//		  higbittimes = 0;
//	  }
//
//	  if(movebitflg == 0)
//	  {
//		  recbytetmp = recbytetmp >> 1;
//	
//		  if(recbittmp)
//		  {
//		  	recbytetmp |= 0x80;
//		  }
//
//		  if(recbitnum%8 == 0)
//		  {
//		  	WriteFIFO((stcFIFO *)&sSoftCOMRecFIFO,(uint8 *)&recbytetmp,1); 
//            printfcom0("%02x-",recbytetmp);
//			recbytetmp = 0;
//		  }
//		}
//	}
//}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
void InitGpiosoftRxd(void)
{
	GPIO_IntCmd((RXD2/100),(1<<RXD2),1);
	NVIC_EnableIRQ(EINT3_IRQn);
}


void TIMER3_IRQHandler(void)	 //HDLC	  send
{
	static	uint32	time = 0;
	static	uint32	higbitnum = 0;
 	static	uint8	sendingendflg=0;
	static	uint8	zeroflg = 0;
	static	uint8	sendbitnum = 0;

	TIM_ClearIntPending(LPC_TIM3, TIM_MR3_INT);

	time++;
	WritesSoftTxc(time%2);	

	if(	(l_softsendbyteflg == 1 && l_softsendlen 
		&& sendingendflg == 0)
		|| zeroflg == 1	        //等补零完成
	   )
	{
		if(time %2)
		{
			if(zeroflg == 1)
			{
			   	WritesSoftTxd(0);
				higbitnum = 0;
				zeroflg = 0;
				printfcom0("@");
				return;
			}
				
		  if((*l_hdlcsendbuf)&(0x01<<(sendbitnum)))
		   {
				higbitnum++;
				
				WritesSoftTxd(1);
				if(higbitnum == 5)
				{
					zeroflg = 1;
				}
		   }
		   else
		   {
		   		WritesSoftTxd(0);
				higbitnum = 0;	
		   }

		   sendbitnum++; 
		   
		   if(sendbitnum == 8)
		   {
			   sendbitnum = 0;
			   l_hdlcsendbuf++;
			   l_softsendlen--;
			   if(l_softsendlen == 0)
			   { l_softsendbyteflg = 0; }
		   }	
		}
	}
	else
	{
		sendingendflg = 1;
		higbitnum = 0;
 
		if(time %2)
		{
			if(sendbitnum == 0 || sendbitnum == 7)	
			{
				WritesSoftTxd(0);	
			}
			else
			{
				WritesSoftTxd(1);
			}
			sendbitnum++;

		  	if(sendbitnum == 8)
			{
				sendingendflg = 0;
				sendbitnum = 0;	
			}
		}
	}		
}

static	uint32	l_time0times = 0;


void	Cleartime0times(void)
{	
	l_time0times = 0;
}

uint8	l_t0hdlcframendflg = 0;
void	Cleart0HdlcFramEndFlg(void)
{
	l_t0hdlcframendflg = 0;	
}

uint8	Gett0HdlcFramEndFlg(void)
{
	return 	l_t0hdlcframendflg;	
}


void TIMER2_IRQHandler(void)
{
  	static	uint8 	recbytetmp = 0;
	static	uint32	recbitnum = 0;
	static	uint32	higbittimes = 0;
	uint8	recbittmp;
  	uint8	movebitflg = 0;

	TIM_ClearIntPending(LPC_TIM2, TIM_CR1_INT);  
  
	movebitflg = 0;
	recbitnum++;
	recbittmp = ReadSoftRxdcp();
	  
	  if(recbittmp)
	  {
	  	 higbittimes++;
		 
		 if(higbittimes >= 7) 
		 {
		 	 printfcom0("*");
			 recbytetmp  = 0;
			 higbittimes = 0;
			 recbitnum   = 0;

			 return; 
		 }
	  }
	  else
	  {
	      if(higbittimes == 6)
		  {
			 if(recbitnum > 16)
			 {
			 	printfcom0(" --t0\r\n");
				l_t0hdlcframendflg = 1;
			 }

			 recbytetmp = 0;
			 higbittimes = 0;
			 recbitnum = 0;
			 
			 return; 		  	 
		  }
		  else if(higbittimes == 5)
		  {
		  	 movebitflg = 1;
			 recbitnum--;
		  }

		  higbittimes = 0;
	  }

	  if(movebitflg == 0)
	  {
		  recbytetmp = recbytetmp >> 1;
	
		  if(recbittmp)
		  {
		  	recbytetmp |= 0x80;
		  }

		  if(recbitnum%8 == 0)
		  {
		  	WriteFIFO((stcFIFO *)&sSoftCOMRecFIFO,(uint8 *)&recbytetmp,1); 
            printfcom0("%02x_",recbytetmp);
			recbytetmp = 0;
		  }
	}
}



//void TIMER2_IRQHandler(void)
//{
//	if (TIM_GetIntCaptureStatus(LPC_TIM2,TIM_MR0_INT))
//	{
//		TIM_ClearIntCapturePending(LPC_TIM2,TIM_MR0_INT);
//		
////		if(GetSoftRecHigTimes()==6) 
//		{	
//			TIM_ResetCounter(LPC_TIM0);
//			Cleartime0times();	
//		}
//	}
//}

uint8 SendSoftCOM(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   

//	WriteEN_485_3(1);

	l_softsendbyteflg = 1;
	l_softsendlen = len;
	l_hdlcsendbuf = buf;

	while(l_softsendbyteflg == 1);

//	WriteEN_485_3(0);   

	return TRUE;  	
}
				   
uint32 ReadSoftCOM(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //实际读的长度
    uint32 RevBufLen;                                           //读、写间差值,即读缓冲区的总长度

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sSoftCOMRecFIFO);   //求还没有读取空间数据个数
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//读取想要求的数据长度
    }
    else
    {
        RealLen = RevBufLen;                        			//读取实际数据长度
    }
    
    ReadFIFO((stcFIFO *)&sSoftCOMRecFIFO,buf,RealLen);

    return RealLen;
}

void InitSoftCOM(void)
{
	InitFIFO((stcFIFO *)&sSoftCOMRecFIFO,SoftCOMRecBuf,sizeof(SoftCOMRecBuf));

//	GPIO_PinselConfig(RXD2,0);
	GPIO_PinselConfig(HDLC_TXC,0);	
	GPIO_PinselConfig(EN_HDLC_TXC,0);
	GPIO_SetOrClearValue(EN_HDLC_TXC,1);   	

// 	GPIO_PinselConfig(RXD3,0);
	GPIO_PinselConfig(HDLC_TXD,0);	
	GPIO_PinselConfig(EN_HDLC_TXD,0);
	GPIO_SetOrClearValue(EN_HDLC_TXD,1);
//	Time2Init();       //hdlc脉冲口信号进入，边沿
//	Time0Init();	   //定时

	Time2Init();       //hdlc时钟脉冲口信号进入，边沿	
	GPIO_PinselConfig(EN_HDLC_RXC,0);
	GPIO_SetOrClearValue(EN_HDLC_RXC,0);

	GPIO_PinselConfig(HDLC_RXD,0);
	GPIO_PinselConfig(EN_HDLC_RXD,0);
	GPIO_SetOrClearValue(EN_HDLC_RXD,0);


	Time3Init();	  //hdlc发送 uart2脉冲，uart3信号
//	WriteEN_485_2(1); 
//	WriteEN_485_3(1);

//	InitGpiosoftRxd();  //hdlc采集	
//	WriteEN_485_2(0); 
//	WriteEN_485_3(0);
//	while(1);

}




void	TestSoftCOM(void)
{
//hdlctes();
	InitWatchDog();

	while(1)
	{
		HdlcDeal();

		ManageLedFlg();

		SetLedFlg(RUN_STA_LED,GetSysTime());
		
		//OnLed(RUN_STA_LED,300,4,4);
	}
}



