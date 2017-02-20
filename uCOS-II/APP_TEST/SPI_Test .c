#include <includes.h>

/*
 *  读操作函数入口参数的宏
 */
#define	RDADDR		4090
#define	NOBYTES	    20
#define	RCVBUFPT	GucRdBuf

/*
 *  写操作函数入口参数的宏 
 */
#define	WRADDR		4090
#define	SNDBUFPT	GucWrBuf
#define	WRNOBYTES	20

uint32_t 	GulChipID = 0;
uint8_t 	GucWrBuf[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
uint8_t 	GucRdBuf[20];


/*********************************************************************************************************
** Function name:       main
** Descriptions:        测试SPI读写NorFlash。短接JP25，选择单步运行到102行，在kiel里查看GuiChipID为
**                      0x00c22015。全速运行，如SPI读写NorFlash错误，则蜂鸣器响一声，否则不响
**                      需特别注意：SPI与UART1共用引脚，在本例程调试时请将JP20的短线帽断开
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void SPITask (void)
{
    uint32_t 	i = 0;
    SPI_CFG_Type	SPI_ConfigStruct_Test;
	PINSEL_CFG_Type PinCfg_Test;

	PinCfg_Test.Portnum = PINSEL_PORT_0;
	PinCfg_Test.Funcnum = PINSEL_FUNC_3;

	PinCfg_Test.Pinnum = PINSEL_PIN_15;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	PinCfg_Test.Pinnum = PINSEL_PIN_17;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	PinCfg_Test.Pinnum = PINSEL_PIN_18;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);

	PinCfg_Test.Pinnum = PINSEL_PIN_16;
	PinCfg_Test.Funcnum = PINSEL_FUNC_0;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	GPIO_SetDir(PINSEL_PORT_0, 0x01ul<<PINSEL_PIN_16, 1);

	SPI_ConfigStructInit((SPI_CFG_Type *)&SPI_ConfigStruct_Test);
	SPI_Init((LPC_SPI_TypeDef *)LPC_SPI, (SPI_CFG_Type *)&SPI_ConfigStruct_Test);


//    SPIInit();    
    MX25L1602_RdID(Jedec_ID, &GulChipID);		                        /* 单步运行到此处时,在IAR里查看 */

   	printfcom0("\r\n GulChipID %x %x",GulChipID,&GulChipID);
                                                                        /* GuiChipID的值是否0x00c22015  */
    GulChipID &= ~0xFF000000;                                           /* 仅保留低24位数据             */            
    if (GulChipID != 0x00C22015) {
        while (1) {
           //BEEPON() ;
		   OSTimeDlyHMSM(0,0,0,100); 
        }
    }
    MX25L1602_Erase(0, 511);                                            /* 擦除芯片                     */

	i = 0xfaaf;
	MX25L1602_WR(0,(uint8_t *)&i,sizeof(i));
	MX25L1602_RD(0,sizeof(i),(uint8_t *)&i);
  	printfcom0("\r\n i %x %x",i,&i);

	i = 0xaffa;
	MX25L1602_WR(0,(uint8_t *)&i,sizeof(i));
	MX25L1602_RD(0,sizeof(i),(uint8_t *)&i);
  	printfcom0("\r\n i %x %x",i,&i);

    MX25L1602_WR(WRADDR, SNDBUFPT, WRNOBYTES);	                        /* 以0x2007为起始地址，将WrBuf  */
   	                                                                     /* 数组里的20个数据写入芯片     */
    MX25L1602_RD(RDADDR, NOBYTES, RCVBUFPT);                            /* 以0x2007为起始地址，读20个   */
     
    for (i = 0;i < 19;i++) {
        if (GucRdBuf[i] != GucWrBuf[i] ) {                              /* 若SPI读写不正确则程序就鸣叫  */
                                                                        /*  一声，否则SPI读写正确       */
            //beepNum(1); 
            while (1)
			{ 
				OSTimeDlyHMSM(0,0,0,100);  
			}    
        }
    }

    while (1)
	{
		OSTimeDlyHMSM(0,0,0,100);
	}
}
