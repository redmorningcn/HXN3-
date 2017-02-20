#ifndef __GPIO_APP_H__
#define __GPIO_APP_H__

extern	void myDelay (uint32_t ulTime);
extern	void	GPIO_SetOrClearValue(uint32_t GpioNum,uint8_t Val);
extern	void	GPIO_PinselConfig(uint8_t GpioNum,uint8_t FuncNum);
extern	uint8_t	GPIO_ReadIoVal(uint32_t GpioNum);



#endif /* GPIO_Test_H */
