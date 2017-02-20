#include <includes.h>
#include <WaveData.h>
/* UART Init/DeInit functions --------------------------------------------------*/
//extern volatile uint8_t       GucRcvNew;                                /* 串口接收新数据的标志         */
//extern          uint8_t       GucRcvBuf[10] ;                           /* 串口接收数据缓冲区           */
//extern          uint32_t      GulNum;                                   /* 串口接收数据的个数           */
//
//#define UART_BPS              57600                                    	/* 串口通信波特率               */
//volatile  uint8_t GucRcvNew;                                            /* 串口接收新数据的标志         */
//uint8_t           GucRcvBuf[10] ;                                       /* 串口接收数据缓冲区           */
//uint32_t          GulNum;                                               /* 串口接收数据的个数           */


/*********************************************************************************************************
* Function Name:        UART0_IRQHandler
* Description:          UART0 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void I2S_IRQHandler (void)
{
//    GulNum = 0;
//       
//    while ((LPC_UART0->IIR & 0x01) == 0){                               /*  判断是否有中断挂起          */
//        switch (LPC_UART0->IIR & 0x0E){                                 /*  判断中断标志                */
//        
//            case 0x04:                                                  /*  接收数据中断                */
//                GucRcvNew = 1;                                          /*  置接收新数据标志            */
//                for (GulNum = 0; GulNum < 8; GulNum++){                 /*  连续接收8个字节             */
//                GucRcvBuf[GulNum] = LPC_UART0->RBR;
//                }
//                break;
//            
//            case 0x0C:                                                  /*  字符超时中断                */
//                GucRcvNew = 1;
//                while ((LPC_UART0->LSR & 0x01) == 0x01){                /*  判断数据是否接收完毕        */ 
//                    GucRcvBuf[GulNum] = LPC_UART0->RBR;
//                    GulNum++;
//                }
//                break;
//                
//            default:
//                break;
//        }
//    } 
}
#define	WORDWIDTH_MASK	     0x3
#define	TRACKNSEL_MASK	     0x4
#define WSHALF_MASK		     0x00007fc0
#define	WSHALFPERIOD  	     0x0f

/*********************************************************************************************************
** Function name:     	I2SInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void I2SInit (void)
{
	PINSEL_CFG_Type	PinCfg_Test;
	I2S_MODEConf_Type ModeConfig_Test;
	I2S_CFG_Type ConfigStruct_Test;
//    uint32_t  uiDAOValue;

 	I2S_Init(LPC_I2S);

    LPC_SC->PCLKSEL1    = 0x00;                                         /*  选择I2S时钟为CCLK/4         */
	
	PinCfg_Test.Portnum = PINSEL_PORT_0;
	PinCfg_Test.Funcnum = PINSEL_FUNC_1; 
	
	PinCfg_Test.Pinnum = PINSEL_PIN_7;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	
	PinCfg_Test.Pinnum = PINSEL_PIN_8;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);

	PinCfg_Test.Pinnum = PINSEL_PIN_9;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);		

	PinCfg_Test.Portnum = PINSEL_PORT_4;
	PinCfg_Test.Pinnum = PINSEL_PIN_29;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
                                                                                  
	ConfigStruct_Test.wordwidth = I2S_WORDWIDTH_16;
	ConfigStruct_Test.mono 		= I2S_MONO;
	ConfigStruct_Test.stop 		= I2S_STOP_ENABLE;
	ConfigStruct_Test.reset 	= I2S_RESET_DISABLE;
	ConfigStruct_Test.ws_sel 	= I2S_MASTER_MODE;
	ConfigStruct_Test.mute 		= I2S_MUTE_ENABLE;
	I2S_Config(LPC_I2S,I2S_TX_MODE,(I2S_CFG_Type *)&ConfigStruct_Test);

	I2S_FreqConfig(LPC_I2S,16000*2,I2S_TX_MODE);  //? 

	ModeConfig_Test.clksel 	= I2S_CLKSEL_FRDCLK;
	ModeConfig_Test.fpin 	= I2S_4PIN_DISABLE;
	ModeConfig_Test.mcena 	= I2S_MCLK_ENABLE;
 	I2S_ModeConfig(LPC_I2S,(I2S_MODEConf_Type*)&ModeConfig_Test,I2S_TX_MODE);    

	I2S_Start(LPC_I2S);
}

void  I2SStingPut (uint8_t *puiData,  uint32_t uiSnd_N) 
{
    uint32_t  uiCnt    = 0;
    uint32_t  uiWavDat = 0;

	                                                                                  
    if ((puiData == 0) && (uiSnd_N == 0)) {                             /*  语音数据或长度无效          */          
        return;
    }

    for (; uiSnd_N >= 4; uiSnd_N -= 4, uiCnt += 4) {                    /*  长度大于4，循环发送         */
  	    uiWavDat	= (puiData[uiCnt + 0] << 0)                         /*  读取数据                    */
		            | (puiData[uiCnt + 1] << 8)
		            | (puiData[uiCnt + 2] << 16)
		            | (puiData[uiCnt + 3] << 24);
       
        I2S_Send(LPC_I2S, uiWavDat);
       
        //while (((LPC_I2S->I2SSTATE >> 16) & 0xFF) != 0) {               /*  等待发送完成                */
          while (((I2S_GetLevel(LPC_I2S,I2S_TX_MODE)) & 0xFF) > 4) {               /*  等待发送完成                */  
		   ;
        }
    }
    
    uiWavDat = 0;
    while (uiSnd_N--) {                                                 /*  长度少于4，不能全部填充发送 */
        uiWavDat |= puiData[uiCnt + uiSnd_N];                           /*  先读取高位数据              */
	    uiWavDat  = uiWavDat << 8;                                      /*  高位数据左移8位             */
    }
   	
	I2S_Send(LPC_I2S, uiWavDat);

    //while (((LPC_I2S->I2SSTATE >> 16) & 0xFF) != 0) {                   /*  等待最后一帧数据发送完毕    */
	while (((I2S_GetLevel(LPC_I2S,I2S_TX_MODE)) & 0xFF) != 0) {               /*  等待发送完成                */
        ;
    }
}

void I2STask(void)
{
	I2SInit();

	while(1)
	{
       	I2SStingPut((uint8_t *)&GucWaveData[44], sizeof(GucWaveData) - 44); 
		OSTimeDlyHMSM(0,0,0,100);
	}	
//uint8_t I2S_GetLevel(LPC_I2S_TypeDef *I2Sx, uint8_t TRMode);
//
//void I2S_Send(LPC_I2S_TypeDef *I2Sx, uint32_t BufferData);
//void I2S_Start(LPC_I2S_TypeDef *I2Sx);


//	INT8U	Tmp=0x5a;
//
//
//	uartInit();
//
//	while(1)
//	{
//		Tmp	= GulNum;
//		//if(GucRcvNew)
//		{
//			GucRcvNew = 0;
//			//printfcom0("\r\t read");
//			UART_Send((LPC_UART_TypeDef *)LPC_UART0,GucRcvBuf,Tmp,NONE_BLOCKING);
//			//UART_SendByte((LPC_UART_TypeDef *)LPC_UART0,Tmp);
//		}
//
//		OSTimeDlyHMSM(0,0,0,100);
//	}	
}

