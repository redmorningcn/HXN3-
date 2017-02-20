#include <includes.h>

#define		TXD3			0
#define		RXD3			1
#define		EN_485_3		129

#define		COM3_FRAM_END	0x2c
#define		COM3_FRAM_END0	0x10

#define 	UART3_BPS       57600                                    	/* 串口通信波特率               */
#define     COM3_REVBUF_LEN 256        							//串口接收

static		stcFIFO     sUART3RecFIFO;                          //定义串口0接收FIFO结构
static		uint8       UART3RecBuf[COM3_REVBUF_LEN];           //定义接收缓冲区
uint8		l_COM3TempRev;
uint8       RecNumCom3;                                 		/* 串口接收数据的个数           */
uint8		l_COM3EndFlg = 0;
uint32		l_COM3ConnTime = 0;
uint8		l_COM3StartFlg = 0;
uint8		l_COM3TimeOutFlg = 0;
uint8		l_COM3FramRecEndFlg = 0;

void WriteEN_485_3(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(EN_485_3,1);
	}
	else
	{
		GPIO_SetOrClearValue(EN_485_3,0);		
	}	
}

uint8	com3RecTmp0 = 0,com3RecTmp1 = 0,com3RecTmp2 = 0;

uint8	com3recbuftmp[256];
uint32	com3rectmp = 0;
/*********************************************************************************************************
* Function Name:        UART3_IRQHandler
* Description:          UART3 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void UART3_IRQHandler (void)
{
   RecNumCom3 = 0;
       
    while ((LPC_UART3->IIR & 0x01) == 0){                               /*  判断是否有中断挂起          */
       	l_COM3ConnTime = GetSysTime();
		l_COM3StartFlg = 1;
		//l_COM3TimeOutFlg = 0;

	    switch (LPC_UART3->IIR & 0x0E){                                 /*  判断中断标志                */
        
            case 0x04:                                                  /*  接收数据中断                */
                for (RecNumCom3 = 0; RecNumCom3 < 8; RecNumCom3++){                 /*  连续接收8个字节             */
			        l_COM3TempRev = LPC_UART3->RBR;                    	//注意读U0RBR会清空接收中断标志
//    				WriteFIFO((stcFIFO *)&sUART3RecFIFO,(uint8 *)&l_COM3TempRev,1); 
					memcpy(&com3recbuftmp[com3rectmp++],(uint8 *)&l_COM3TempRev,1);
				   	
				//	printfcom0("%c",l_COM3TempRev);

					com3RecTmp2 = com3RecTmp1;
					com3RecTmp1 = com3RecTmp0;
					com3RecTmp0	= l_COM3TempRev;

					if(		(com3RecTmp0 == COM3_FRAM_END)
						 && (com3RecTmp1 == COM3_FRAM_END0)
						 && (com3RecTmp2 != COM3_FRAM_END0) )
					{
						l_COM3FramRecEndFlg = 1;							//帧接收完成，标志位赋值
						
						WriteFIFO((stcFIFO *)&sUART3RecFIFO,com3recbuftmp,com3rectmp);
						com3rectmp = 0;	
					}
                }
                break;
            
            case 0x0C:                                                  /*  字符超时中断                */
                while ((LPC_UART3->LSR & 0x01) == 0x01){                /*  判断数据是否接收完毕        */ 
			        l_COM3TempRev = LPC_UART3->RBR;                    	//注意读U0RBR会清空接收中断标志

					memcpy(&com3recbuftmp[com3rectmp++],(uint8 *)&l_COM3TempRev,1);
    			//	WriteFIFO((stcFIFO *)&sUART3RecFIFO,(uint8 *)&l_COM3TempRev,1);    
				//	printfcom0("%c",l_COM3TempRev);

					com3RecTmp2 = com3RecTmp1;
					com3RecTmp1 = com3RecTmp0;
					com3RecTmp0	= l_COM3TempRev;

					if(		(com3RecTmp0 == COM3_FRAM_END)
						 && (com3RecTmp1 == COM3_FRAM_END0)
						 && (com3RecTmp2 != COM3_FRAM_END0) )
					{
						l_COM3FramRecEndFlg = 1;							//帧接收完成，标志位赋值
						
						WriteFIFO((stcFIFO *)&sUART3RecFIFO,com3recbuftmp,com3rectmp);
						com3rectmp = 0;	
						return ;
					}
				}
				l_COM3TimeOutFlg = 1;

				WriteFIFO((stcFIFO *)&sUART3RecFIFO,com3recbuftmp,com3rectmp);
				com3rectmp = 0;
                break;
                
            default:
                break;
        }
    } 
}
 
void	HoldCOM3ConnSta(void)
{
	if((GetSysTime()-l_COM3ConnTime > 2 && l_COM3StartFlg == 1 )
		||(l_COM3TimeOutFlg == 1))
	{
		l_COM3EndFlg = 1;
		l_COM3StartFlg = 0;
		l_COM3TimeOutFlg = 0;
	}
}

uint8	GetCOM3FramRecEndFlg(void)
{
	return	l_COM3FramRecEndFlg;
}

void	ClearCOM3FramRecEndFlg(void)
{
	l_COM3FramRecEndFlg = 0;
}
 
uint8	GetCOM3EndFlg(void)
{
	HoldCOM3ConnSta();
	if(GetCOM3FramRecEndFlg())
	{
		//printfcom0("\r\n GetCOM1FramRecEndFlg %d",GetCOM1FramRecEndFlg());
		return GetCOM3FramRecEndFlg();
	}
	else
	{
		return l_COM3EndFlg;
	}
}

void	ClearCOM3EndFlg(void)
{
	l_COM3EndFlg 	= 0;
	l_COM3StartFlg 	= 0;
	l_COM3TimeOutFlg = 0;

	ClearCOM3FramRecEndFlg();
}  



/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void UART3Init (void)
{
	UART_CFG_Type		UART_ConfigStruct_Test;
	UART_FIFO_CFG_Type 	FIFOCfg_Test;
	UART_INT_Type 		UARTIntCfg_Test;

	GPIO_PinselConfig(RXD3,2);
	GPIO_PinselConfig(TXD3,2);	
	GPIO_PinselConfig(EN_485_3,0);
	WriteEN_485_3(0);

	UART_ConfigStruct_Test.Baud_rate = UART3_BPS;
	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART3,(UART_CFG_Type *)&UART_ConfigStruct_Test);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART3,ENABLE);

	FIFOCfg_Test.FIFO_DMAMode = DISABLE;
	FIFOCfg_Test.FIFO_Level = UART_FIFO_TRGLEV2;
	FIFOCfg_Test.FIFO_ResetRxBuf = ENABLE;
	FIFOCfg_Test.FIFO_ResetTxBuf = ENABLE;	
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART3, (UART_FIFO_CFG_Type *)&FIFOCfg_Test);

	UARTIntCfg_Test = UART_INTCFG_RBR;	
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART3, UARTIntCfg_Test,ENABLE);
  	
	InitFIFO((stcFIFO *)&sUART3RecFIFO,UART3RecBuf,sizeof(UART3RecBuf));

	NVIC_EnableIRQ(UART3_IRQn);
	NVIC_SetPriority(UART3_IRQn, UART3_IRQn);									
}

uint32 ReadCOM3(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //实际读的长度
    uint32 RevBufLen;                                           //读、写间差值,即读缓冲区的总长度

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART3RecFIFO);   //求还没有读取空间数据个数
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//读取想要求的数据长度
    }
    else
    {
        RealLen = RevBufLen;                        			//读取实际数据长度
    }
    
    ReadFIFO((stcFIFO *)&sUART3RecFIFO,buf,RealLen);

    return RealLen;
}

uint32 ReadCOM3NoClear(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //实际读的长度
    uint32 RevBufLen;                                           //读、写间差值,即读缓冲区的总长度

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART3RecFIFO);   //求还没有读取空间数据个数
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//读取想要求的数据长度
    }
    else
    {
        RealLen = RevBufLen;                        			//读取实际数据长度
    }
    
    OnlyReadFIFO((stcFIFO *)&sUART3RecFIFO,buf,RealLen);

    return RealLen;
}

uint8	GetUart3Status(void)
{
	return	UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART3);
}

uint8 SendCOM3(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   

	station = GetUart3Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart3Status();
	}

	WriteEN_485_3(1);

	UART_Send((LPC_UART_TypeDef *)LPC_UART3,buf,len,BLOCKING);

	station = GetUart3Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart3Status();
	}

	WriteEN_485_3(0);    

    return TRUE;    
}

uint8	SendCOM3s(void *buf)
{
	UARTPuts((LPC_UART_TypeDef *)LPC_UART3,buf);
	return	1;
}

uint8	GetCom3FramRecEndFlg(void)
{
	return	l_COM3FramRecEndFlg;
}

void	ClearCom3FramRecEndFlg(void)
{
	l_COM3FramRecEndFlg = 0;
}
