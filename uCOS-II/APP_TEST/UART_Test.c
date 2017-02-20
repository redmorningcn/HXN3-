#include <includes.h>

#define 	UART0_BPS              	9600                                    	/* 串口通信波特率               */
#define     COM0_REVBUF_LEN     	32         		//串口接收
stcFIFO     sUART0RecFIFO;                          //定义串口0接收FIFO结构
uint8       UART0RecBuf[COM0_REVBUF_LEN];           //定义接收缓冲区
uint8		l_COM0TempRev;
uint8       GulNum;                                 /* 串口接收数据的个数           */

/*********************************************************************************************************
* Function Name:        UART0_IRQHandler
* Description:          UART0 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void UART0_IRQHandler (void)
{
   GulNum = 0;
       
    while ((LPC_UART0->IIR & 0x01) == 0){                               /*  判断是否有中断挂起          */
        switch (LPC_UART0->IIR & 0x0E){                                 /*  判断中断标志                */
        
            case 0x04:                                                  /*  接收数据中断                */
//                GucRcvNew = 1;                                          /*  置接收新数据标志            */
                for (GulNum = 0; GulNum < 8; GulNum++){                 /*  连续接收8个字节             */
			        l_COM0TempRev = LPC_UART0->RBR;                    	//注意读U0RBR会清空接收中断标志
    				WriteFIFO((stcFIFO *)&sUART0RecFIFO,(uint8 *)&l_COM0TempRev,1); 
                }
                break;
            
            case 0x0C:                                                  /*  字符超时中断                */
//                GucRcvNew = 1;
                while ((LPC_UART0->LSR & 0x01) == 0x01){                /*  判断数据是否接收完毕        */ 
			        l_COM0TempRev = LPC_UART0->RBR;                    	//注意读U0RBR会清空接收中断标志
    				WriteFIFO((stcFIFO *)&sUART0RecFIFO,(uint8 *)&l_COM0TempRev,1);                 
				}
                break;
                
            default:
                break;
        }
    } 
}
  

#define		TXD0		2
#define		RXD0		3
#define		EN_485_0   27



void WriteEN_485_0(uint8 temp)
{
	
	if(temp)		
	{
		GPIO_SetOrClearValue(EN_485_0,1);
	}
	else
	{
		GPIO_SetOrClearValue(EN_485_0,0);		
	}	
	nop();	
//	IO0DIR_OUT(SCK1);					//P0.17 SCK1
//	IO0PIN_W(temp,SCK1);
}

/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uartInit (void)
{
	UART_CFG_Type		UART_ConfigStruct_Test;
	UART_FIFO_CFG_Type 	FIFOCfg_Test;
	UART_INT_Type 		UARTIntCfg_Test;

	GPIO_PinselConfig(RXD0,1);
	GPIO_PinselConfig(TXD0,1);	
	GPIO_PinselConfig(EN_485_0,0);

	//WriteEN_485_0(0);

	UART_ConfigStruct_Test.Baud_rate = UART0_BPS;
	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART0,(UART_CFG_Type *)&UART_ConfigStruct_Test);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0,ENABLE);

	FIFOCfg_Test.FIFO_DMAMode = DISABLE;
	FIFOCfg_Test.FIFO_Level = UART_FIFO_TRGLEV2;
	FIFOCfg_Test.FIFO_ResetRxBuf = ENABLE;
	FIFOCfg_Test.FIFO_ResetTxBuf = ENABLE;	
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, (UART_FIFO_CFG_Type *)&FIFOCfg_Test);

	UARTIntCfg_Test = UART_INTCFG_RBR;	
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UARTIntCfg_Test,ENABLE);

  	
	InitFIFO((stcFIFO *)&sUART0RecFIFO,UART0RecBuf,sizeof(UART0RecBuf));


	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, 5);									
}

uint32 ReadCOM0(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //实际读的长度
    uint32 RevBufLen;                                           //读、写间差值,即读缓冲区的总长度

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART0RecFIFO);   //求还没有读取空间数据个数
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//读取想要求的数据长度
    }
    else
    {
        RealLen = RevBufLen;                        			//读取实际数据长度
    }
    
    ReadFIFO((stcFIFO *)&sUART0RecFIFO,buf,RealLen);

    return RealLen;
}

uint8	GetUart0Status(void)
{
	return	UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART0);
}

uint8 SendCOM0(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   
	
	station = GetUart0Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart0Status();
	}


	UART_Send((LPC_UART_TypeDef *)LPC_UART0,buf,len,BLOCKING);

	station = GetUart0Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart0Status();
	}

    return TRUE;    
}
uint8 SendCOM0WaitAnd(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   
	
	station = GetUart0Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart0Status();
	}
	WriteEN_485_0(1);

	UART_Send((LPC_UART_TypeDef *)LPC_UART0,buf,len,BLOCKING);

	station = GetUart0Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart0Status();
	}
	WriteEN_485_0(0);

    
    return TRUE;    
}

void uartTask(void)
{
//INT8U	Tmp=0x5a;
//INT8U	Flg;
//uint32_t 	GulChipID = 0;
//uint8	GucRcvBuf[64];
//uint32	len;


//DisplaySet(100,2,"12345678");

	//for(Tem = )
//	while(1)
	{
//		Tmp	= GulNum;
//		
//		len = GetNoReadSizeFIFO((stcFIFO *)&sUART0RecFIFO);
//
//		if(len > 0)
//		{
//			OnLed(1,100,10,10);
//
////			ReadFIFO((stcFIFO *)&sUART0RecFIFO,GucRcvBuf,len);
////			UART_Send((LPC_UART_TypeDef *)LPC_UART0,GucRcvBuf,len,BLOCKING);
//		}
//			
////		TaskTest();
		ScanTask();

//		OSTimeDlyHMSM(0,0,0,100);
	}	
}


