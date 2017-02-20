#include <includes.h>

extern	void	OneTask(void);
extern	void	ScanTask(void);

void	GPIO_Test(void)
{
	SYSTICK_InternalInit(10);
	SYSTICK_Cmd(ENABLE);
	SYSTICK_IntCmd(ENABLE);

  	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);                            /* set Priority for Cortex-M0 System Interrupts */
}
