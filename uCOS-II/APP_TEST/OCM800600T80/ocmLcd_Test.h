#ifndef __HMI_DRIVER_H__
#define __HMI_DRIVER_H__


#define  LCD_CFG_TASK_START_STK_SIZE                     1280u

static  OS_STK  LCD_TaskStartStk[LCD_CFG_TASK_START_STK_SIZE];



void 	LcdTask(void);


#endif /* UART_Test_H */
