#include <includes.h>

#define		CAP00	126
#define		CAP10	118
//#define		CAP20	4
#define		HDCL_RXC			5

///*********************************************************************************************************
//** Function name:     	uartInit
//** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
//** input parameters:    无
//** output parameters:   无
//** Returned value:      无
//*********************************************************************************************************/
//void Time0Init (void)
//{
////	UART_CFG_Type		UART_ConfigStruct_Test;
////	UART_FIFO_CFG_Type 	FIFOCfg_Test;
////	UART_INT_Type 		UARTIntCfg_Test;
//	TIM_TIMERCFG_Type TIM_ConfigStruct;
//	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;
//
////	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);
//
//
//	GPIO_PinselConfig(CAP00,3);
//
//	// Initialize timer 0, prescale count time of 1000000uS = 1S
//	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
////	TIM_ConfigStruct.PrescaleValue	= 1000000;
//	TIM_ConfigStruct.PrescaleValue	= 1;
//
//	// use channel 0, CAPn.0
//	TIM_CaptureConfigStruct.CaptureChannel = 0;
//	// DISABLE capture on CAPn.0 rising edge
//	TIM_CaptureConfigStruct.RisingEdge = DISABLE;
//	// Enable capture on CAPn.0 falling edge
//	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
//	// Generate capture interrupt
//	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;
//
//
//	// Set configuration for Tim_config and Tim_MatchConfig
//	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
//	TIM_ConfigCapture(LPC_TIM0, &TIM_CaptureConfigStruct);
//	TIM_ResetCounter(LPC_TIM0);
//
//
//	/* preemption = 1, sub-priority = 1 */
//	NVIC_SetPriority(TIMER0_IRQn, TIMER0_IRQn);
//	/* Enable interrupt for timer 0 */
//	NVIC_EnableIRQ(TIMER0_IRQn);
//	// To start timer 0
//	TIM_Cmd(LPC_TIM0,ENABLE);							
//}


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Time0Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct ;
	uint64_t clkdlycnt;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);


	// Initialize timer 0, prescale count time of fplk
//	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, MR0
	TIM_MatchConfigStruct.MatchChannel = 0;
	// Enable interrupt when MR0 matches the value in TC register
	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	//Enable reset on MR0: TIMER will reset if MR0 matches it
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	//Stop on MR0 if MR0 matches it
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	//Toggle MR0.0 pin if MR0 matches it
	TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
//	// Set Match value, count value of 10000 (10000 * 100uS = 1000000us = 1s --> 1 Hz)
//	TIM_MatchConfigStruct.MatchValue   = 10000;
	// Get Pclock of timer		 波特率计算
//	clkdlycnt = (uint64_t) getPClock(converPtrToTimeNum(LPC_TIM3));  softbount
//	TIM_MatchConfigStruct.MatchValue = 57;	
	TIM_MatchConfigStruct.MatchValue = (uint32)((CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER0) ) / (9600*2));

	printfcom0("\r\n CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3) %d ,%d",CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3),(uint32)((CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3) ) / 9600) );
	printfcom0("\r\n SystemCoreClock %d", SystemCoreClock);
	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);																																										   
	TIM_ConfigMatch(LPC_TIM0, &TIM_MatchConfigStruct);
	TIM_ResetCounter(LPC_TIM0);

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER0_IRQn, TIMER0_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER0_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM0,ENABLE);								
}


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Time1Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);


	GPIO_PinselConfig(CAP10,3);

	// Initialize timer 0, prescale count time of 1000000uS = 1S
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000000;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, CAPn.0
	TIM_CaptureConfigStruct.CaptureChannel = 0;
	// DISABLE capture on CAPn.0 rising edge
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;
	// Enable capture on CAPn.0 falling edge
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
	// Generate capture interrupt
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;


	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM1, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigCapture(LPC_TIM1, &TIM_CaptureConfigStruct);
	TIM_ResetCounter(LPC_TIM1);


	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER1_IRQn, TIMER1_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER1_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM1,ENABLE);							
}


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Time2Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);


	//GPIO_PinselConfig(CAP20,3);
	GPIO_PinselConfig(HDCL_RXC,3);

	// Initialize timer 0, prescale count time of 1000000uS = 1S
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000000;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, CAPn.0
//	TIM_CaptureConfigStruct.CaptureChannel = 0;
	TIM_CaptureConfigStruct.CaptureChannel = 1;
	// DISABLE capture on CAPn.0 rising edge
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;
//	TIM_CaptureConfigStruct.RisingEdge = ENABLE;
	// Enable capture on CAPn.0 falling edge
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
//	TIM_CaptureConfigStruct.FallingEdge = DISABLE;
	// Generate capture interrupt
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;


	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM2, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigCapture(LPC_TIM2, &TIM_CaptureConfigStruct);
	TIM_ResetCounter(LPC_TIM2);


	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER2_IRQn, TIMER2_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER2_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM2,ENABLE);							
}


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Time3Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct ;
	uint64_t clkdlycnt;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);


	// Initialize timer 0, prescale count time of fplk
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, MR0
	TIM_MatchConfigStruct.MatchChannel = 3;
	// Enable interrupt when MR0 matches the value in TC register
	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	//Enable reset on MR0: TIMER will reset if MR0 matches it
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	//Stop on MR0 if MR0 matches it
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	//Toggle MR0.0 pin if MR0 matches it
	TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
//	// Set Match value, count value of 10000 (10000 * 100uS = 1000000us = 1s --> 1 Hz)
//	TIM_MatchConfigStruct.MatchValue   = 10000;
	// Get Pclock of timer		 波特率计算
//	clkdlycnt = (uint64_t) getPClock(converPtrToTimeNum(LPC_TIM3));  softbount
//	TIM_MatchConfigStruct.MatchValue = (uint32)((CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3) ) / 9600);	
		TIM_MatchConfigStruct.MatchValue = (uint32)((CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3) ) / (9600*2));

	printfcom0("\r\n CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3) %d ,%d",CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3),(uint32)((CLKPWR_GetPCLK (CLKPWR_PCLKSEL_TIMER3) ) / 9600) );
	printfcom0("\r\n SystemCoreClock %d", SystemCoreClock);
	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM3, TIM_TIMER_MODE,&TIM_ConfigStruct);																																										   
	TIM_ConfigMatch(LPC_TIM3, &TIM_MatchConfigStruct);
	TIM_ResetCounter(LPC_TIM3);

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER3_IRQn, TIMER3_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER3_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM3,ENABLE);
								
}

