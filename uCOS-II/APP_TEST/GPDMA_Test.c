#include <includes.h>

uint32_t GulSrcDat[50] = { 	 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555,
							 0x55555555 };                                /* 存放源地址数据               */

uint32_t GulDesDat[50] = {0};                                             /* 存放目标地址数据             */


//
//void GPDMA_Init(void);
////Status GPDMA_Setup(GPDMA_Channel_CFG_Type *GPDMAChannelConfig, fnGPDMACbs_Type *pfnGPDMACbs);
//Status GPDMA_Setup(GPDMA_Channel_CFG_Type *GPDMAChannelConfig);
//IntStatus GPDMA_IntGetStatus(GPDMA_Status_Type type, uint8_t channel);
//void GPDMA_ClearIntPending(GPDMA_StateClear_Type type, uint8_t channel);
//void GPDMA_ChannelCmd(uint8_t channelNum, FunctionalState NewState);

//void dmaInit (uint32_t *pulSrc_Address,  uint32_t *pulDest_Address,  uint32_t ulDMA_Size)
void m2mdmaInit (uint32_t *pulSrc_Address,  uint32_t *pulDest_Address,  uint32_t ulDMA_Size)
{
	GPDMA_Channel_CFG_Type	GPDMAChannelConfig_Test;

	GPDMA_Init();				

	GPDMAChannelConfig_Test.ChannelNum 		= 0;
	GPDMAChannelConfig_Test.TransferSize 	= ulDMA_Size/4;
	GPDMAChannelConfig_Test.TransferWidth	= GPDMA_WIDTH_WORD;
	GPDMAChannelConfig_Test.SrcMemAddr 		= (uint32_t)pulSrc_Address;
	GPDMAChannelConfig_Test.DstMemAddr 		= (uint32_t)pulDest_Address;
	GPDMAChannelConfig_Test.TransferType 	= GPDMA_TRANSFERTYPE_M2M;
	GPDMAChannelConfig_Test.SrcConn 		= 0;
	GPDMAChannelConfig_Test.DstConn 		= 0;
	GPDMAChannelConfig_Test.DMALLI 			= 0;

	GPDMA_Setup((GPDMA_Channel_CFG_Type *)&GPDMAChannelConfig_Test);

	GPDMA_ChannelCmd(0,ENABLE);
                                                                     
}

/*********************************************************************************************************
** Function name:       main
** Descriptions:        GPDMA测试，LPC1700GPDMA可以访问所有SRAM，只需定义两个数组，经过DMA传输后，
**                      判断如果两个数组数据相等即证明GPDMA传输正确.测试时短接JP17，本例程实验现像为：
**                      如果GPDMA传输正确，蜂鸣器响两声；
**                      如果GPDMA传输错误，蜂鸣器响一声。
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void m2mdmaTask(void)
{
    uint32_t i;
    uint32_t ulflag = 0;                                                /* 判断传输是否正确，1表示DMA   */
                                                                        /* 传输正确，0表示DMA传输错误   */

    m2mdmaInit(GulSrcDat,GulDesDat,200);                                   /* GPDMA初始化                  */    

    
    /*
     *  比较源数组与目标数组是否相等，若相等则GPDMA传输正确，flag = 1 
     */ 
    for (i = 0; i <50; i++) {
        if (GulDesDat[i] != GulSrcDat[i]) {
            ulflag = 0;
            break;
        } else {
            ulflag = 1;
        }
    }



    /* 
     *  如果GPDMA传输正确，蜂鸣器响两声；如果GPDMA传输错误，蜂鸣器响一声
     */
    if (1 == ulflag) {
		printfcom0("\r\n  DMA test success!");                                                
        //beepNumber(2);
    } else {
        //beepNumber(1);
		printfcom0("\r\n  DMA test fault!");
    }
    while (1)
	{
		OSTimeDlyHMSM(0,0,0,100);
	}
}


///*********************************************************************************************************
//** Function name:       dmaInit
//** Descriptions:        DMA通道0初始化函数(存储器到存储器)
//** input parameters:    puiSrc_Address：   存储区源地址
//**                      puiDest_Address：  存储区目标地址
//**                      uiDMA_Size：       传输字节个数
//** Output parameters:   无
//** Returned value:      无
//*********************************************************************************************************/
//void dmaInit (uint32_t *pulSrc_Address,  uint32_t *pulDest_Address,  uint32_t ulDMA_Size)
//{
//    
//	LPC_SC->PCONP  |= (1 << 29);                                        /* 使能GPDMA时钟                */
//    LPC_GPDMA->DMACIntTCClear   |= 0x01;                                /* 清除终端计数中断的标志       */
//    LPC_GPDMA->DMACIntErrClr    |= 0x01;                                /* 清除错误中断标志             */
//                                                                        /* 初始化DMA传输流              */
//    LPC_GPDMACH0->DMACCLLI = 0;                                         /* 下一个链表项无效，本次DMA传  */
//                                                                        /* 输流使用连续存储空间         */
//    LPC_GPDMACH0->DMACCControl    |=  ((ulDMA_Size/4)&0x0fff)
//                     |   (0x04 << 12)                                   /* 指定源突发传输大小为32位     */
//                     |   (0x04 << 15)                                   /* 指定目的突发传输大小为32位   */
//                     |   (0x02 << 18)                                   /* 指定源传输数据宽度为32位     */
//                     |   (0x02 << 21)                                   /* 指定目标传输数据宽度为32位   */
//                     |   (1 << 26)                                      /* 指定源地址自动增加           */
//                     |   (1 << 27)                                      /* 指定目标地址自动增加         */
//                     |   (0x80000000);                                  /* 配置传输流的中断             */
//                                                                        /* 使能通道0的终端计数中断      */  
//    LPC_GPDMACH0->DMACCSrcAddr = (uint32_t)pulSrc_Address;              /* 设置存储区源地址             */
//    LPC_GPDMACH0->DMACCDestAddr= (uint32_t)pulDest_Address;             /* 设置存储区目标地址           */                                                                       
//}
//
///*********************************************************************************************************
//** Function name:       gpdmaEnabe
//** Descriptions:        DMA及DMA通道0使能
//** input parameters:    无
//** Output parameters:   无
//** Returned value:      无
//*********************************************************************************************************/
//void gpdmaEnabe (void)
//{
//    LPC_GPDMA->DMACConfig    = 0x01;                                    /* 使能DMA，使能小端模式        */
//    LPC_GPDMACH0->DMACCConfig |= 0x01;                                  /* 使能通道0                    */
//}
//
///*********************************************************************************************************
//** Function name:       main
//** Descriptions:        GPDMA测试，LPC1700GPDMA可以访问所有SRAM，只需定义两个数组，经过DMA传输后，
//**                      判断如果两个数组数据相等即证明GPDMA传输正确.测试时短接JP17，本例程实验现像为：
//**                      如果GPDMA传输正确，蜂鸣器响两声；
//**                      如果GPDMA传输错误，蜂鸣器响一声。
//** input parameters:    无
//** Output parameters:   无
//** Returned value:      无
//*********************************************************************************************************/
//int main (void)
//{
//    uint32_t i;
//    uint32_t ulflag = 0;                                                /* 判断传输是否正确，1表示DMA   */
//                                                                        /* 传输正确，0表示DMA传输错误   */
//    SystemInit();                                                       /* 系统初始化，切勿删除         */
//
//    BEEPOFF();
//    dmaInit(GulSrcDat,GulDesDat,200);                                   /* GPDMA初始化                  */    
//    gpdmaEnabe();                                                       /* DMA使能                      */
//    
//    /*
//     *  比较源数组与目标数组是否相等，若相等则GPDMA传输正确，flag = 1 
//     */ 
//    for (i = 0; i <50; i++) {
//        if (GulDesDat[i] != GulSrcDat[i]) {
//            ulflag = 0;
//            break;
//        } else {
//            ulflag = 1;
//        }
//    }
//
//    /* 
//     *  如果GPDMA传输正确，蜂鸣器响两声；如果GPDMA传输错误，蜂鸣器响一声
//     */
//    if (1 == ulflag) {                                                
//        beepNumber(2);
//    } else {
//        beepNumber(1);
//    }
//    while (1);
//}
