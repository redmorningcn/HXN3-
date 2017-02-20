#ifndef __GPIO_Test_H__
#define __GPIO_Test_H__


#define  GPIO_CFG_TASK_START_STK_SIZE                     128

static  OS_STK  GPIO_TaskStartStk[GPIO_CFG_TASK_START_STK_SIZE];

void	GPIO_Test(void);

#endif /* GPIO_Test_H */
