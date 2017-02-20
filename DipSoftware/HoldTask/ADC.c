#include <includes.h>
#include  "lpc17xx_adc.h"

#define  	BATTERY_ADC 		130



void InitAdc(void)
{
	GPIO_PinselConfig(BATTERY_ADC,3);

	ADC_Init(LPC_ADC, 200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN4,DISABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_ADINTEN4,ENABLE);	

//	GPIO_SetOrClearValue(BATTERY_ADC,1);
//	while(1);							
}

float		BatterVal;


uint16 ReadAdc(void)
{
	uint16_t	adc_value = 0;
	uint32	time;
//	InitAdc();
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
//  Wait conversion complete
	time = GetSysTime();
//	while((GetSysTime() - time) < 100);
	
	while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_ADINTEN4,ADC_DATA_DONE)))
	{
		if(GetSysTime() - time > 100)
		{
			printfcom0("\r\n11 %d",adc_value);
			return 0;
		}
	}
	adc_value = ADC_ChannelGetData(LPC_ADC,ADC_ADINTEN4);
	//printfcom0("\r\n %d",adc_value*3000*2/4096);
	adc_value = adc_value*3000*2/4096;
	return adc_value;
}


//---------------------------------------------------------------------
//名    称：    void	InitAdc(void)
//功    能：   	初始化ADC
//入口参数：    
//出口参数：    
//--------------------------------------------------------------------
//void	InitAdc(void)
//{
//	uint32	AdcCode = 0;
//
// 	PINSEL2 &= 0xFFFFFFDF;								//初始化端口
// 	PINSEL2 |= 0x00000010;
// 	PINSEL2 |= 0x00000080;
//
//	AdcCode = ADDR;
//	
//	AdcCode = 0;
//	    												/* 进行ADC模块设置，其中x<<n表示第n位设置为x(若x超过一位，则向高位顺延) */
//    AdcCode = (1 << 7)                 	|				/* SEL = 1 ，选择通道0 */
//           (0x000000ff << 8) 			| 				/* CLKDIV = Fpclk / 1000000 - 1 ，即转换时钟为1MHz */
//           (0 << 16)                    |				/* BURST = 0 ，软件控制转换操作 */
//           (0 << 17)                    | 				/* CLKS = 0 ，使用11clock转换 */
//           (1 << 21)                    | 				/* PDN = 1 ， 正常工作模式(非掉电转换模式) */
//           (0 << 22)                    | 				/* TEST1:0 = 00 ，正常工作模式(非测试模式) */
//           (1 << 24)                    | 				/* START = 1 ，直接启动ADC转换 */
//           (0 << 27);									/* EDGE = 0 (CAP/MAT引脚下降沿触发ADC转换)	 */
//	
//	ADCR = 	AdcCode;
//}

//------------------------------------------------------------------------
//  名  称 ：void ReadAdc(void)
//  功  能 ：读ADC值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
//uint16 ReadAdc(void)
//{
////	uint32	i;
//	uint32	AdcData;
//	uint16	AdcVal;
//	uint32	Time;
//	
//	
//	Time = GetSysTime();
//	ADCR = ADCR | (1 << 24);      
//
//	do
//	{
//		DelayX10ms(1);
//		AdcData = ADDR;
//		
//		if(GetSysTime() - Time > 1*100)
//		{
//			break;
//		}
//	}while((AdcData & 0x80000000) == 0);
//		
//	AdcVal = ((AdcData>>6) & 0xffff03ff);
//	
//	return	AdcVal;
//}


//------------------------------------------------------------------------
//  名  称 ：float GetBotVolt(void)
//  功  能 ：取电池电压值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
int16 GetBotVolt(void)
{
//	int16	AdcVccVal;
	uint16			AdcVal;
	
	AdcVal 		= ReadAdc();

//	AdcVccVal 	= (float)((float)AdcVal / 1024)*3.3*2;
	
	return	AdcVal;
}

#define		RIGHT_DATA			0xff
#define		BOT_LOW_VOL_ERR		31
#define		BOT_LOW_VAL  		2800
								//2800mV
//------------------------------------------------------------------------
//  名  称 ：uint8 JudgeEr2450Err(void)
//  功  能 ：读ADC值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8	JudgeEr2450Err(void)
{
	int16	Er2450Volt;
	static	uint32	Time  = 0;
	static	uint32	Times = 0;
	static	uint8	ErrTyp = RIGHT_DATA;
	
	if(GetSysTime() - Time > 100)
	{
		Time	= GetSysTime();
	
		Er2450Volt = GetBotVolt();

		//printfcom0("\r\n battery volateg %d",Er2450Volt);

		if(Er2450Volt < BOT_LOW_VAL)
		{
			Times++;
		}
		else
		{
			Times = 0;
		}
		
		if(Times > 10)
		{
			ErrTyp = BOT_LOW_VOL_ERR;
		}
		else
		{
			ErrTyp = RIGHT_DATA;
		}
	}
		
	return	ErrTyp;
}

