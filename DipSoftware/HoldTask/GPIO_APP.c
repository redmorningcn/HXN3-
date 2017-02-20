#include 	<includes.h>  
#include 	"string.h"
#include    "stdio.h" 
#include    "stdarg.h"

void myDelay (uint32_t ulTime)
{
    uint32_t i;

    i = 0;
    while (ulTime--) {
        for (i = 0; i < 5000; i++);
    }
}

void	GPIO_SetOrClearValue(uint32_t GpioNum,uint8_t Val)
{
	uint32_t 	PortBuf[] = {PINSEL_PORT_0,PINSEL_PORT_1,PINSEL_PORT_2,PINSEL_PORT_3,PINSEL_PORT_4};
	uint8_t		PortNum;
	uint8_t		IoNum;

	PortNum = GpioNum/100;
	IoNum	= GpioNum%100;

	GPIO_SetDir(PortBuf[PortNum], 0x01ul<<IoNum,1);
	Val>0?GPIO_SetValue(PortBuf[PortNum], 0x01ul<<IoNum):
			  GPIO_ClearValue(PortBuf[PortNum], 0x01ul<<IoNum);
}

void	GPIO_PinselConfig(uint8_t GpioNum,uint8_t FuncNum)
{
	PINSEL_CFG_Type	PinCfg_Test;

	uint32_t 	PortBuf[] = {PINSEL_PORT_0,PINSEL_PORT_1,PINSEL_PORT_2,PINSEL_PORT_3,PINSEL_PORT_4};
	uint8_t		PortNum;
	uint8_t		IoNum;

	PortNum = GpioNum/100;
	IoNum	= GpioNum%100;

	PinCfg_Test.Portnum = PortBuf[PortNum];
	PinCfg_Test.Pinnum  = IoNum;
	PinCfg_Test.Funcnum = FuncNum;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
}

uint8_t	GPIO_ReadIoVal(uint32_t GpioNum)
{
	uint32_t 	PortBuf[] = {PINSEL_PORT_0,PINSEL_PORT_1,PINSEL_PORT_2,PINSEL_PORT_3,PINSEL_PORT_4};
	uint8_t		PortNum;
	uint8_t		IoNum;
	uint32_t 	PortVal;	

	PortNum = GpioNum/100;
	IoNum	= GpioNum%100;

	GPIO_SetDir(PortBuf[PortNum], 0x01ul<<IoNum,0);
	PortVal = GPIO_ReadValue(PortBuf[PortNum]);	
	
	if(PortVal & 1ul<<IoNum)
	{
		return	1;
	}

	return	0;
}
