#include <includes.h>

#define	LED_NUM  4
typedef	struct	_stcledflg_
{
		uint8	led[LED_NUM];
		uint32	time[LED_NUM];
}stcledflg;

stcledflg 	g_sledflg;

void	SetLedFlg(uint8	num,uint32	time)
{
	if(num < LED_NUM)
	{
		g_sledflg.led[num] 	= 1;
		g_sledflg.time[num] = time;
	}	
}

void	ManageLedFlg(void)
{
	uint32	i;
	uint8	ledbuf[]={0,1,2,3};
	
	for(i = 0;i < LED_NUM; i++)
	{		
		if(GetSysTime() - g_sledflg.time[i] > 150)
			g_sledflg.led[i] = 0;
				
		if(g_sledflg.led[i])
			OnLed(ledbuf[i],300,6,5);	
		else
			OffLed(ledbuf[i]);				
	}
}
