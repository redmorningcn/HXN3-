//#include  "config.h"
#include <includes.h>

//#define		EX_DOG		sp706
#define		WATCHDOG	28		//P028

/****************************************************************************
* 名称：void  InitWatchDog(void)
* 功能：初始化看门狗
* 入口参数：无
* 出口参数：无
****************************************************************************/
void  InitWatchDog(void)
{
	WDT_Init(WDT_CLKSRC_IRC,WDT_MODE_RESET);
	WDT_Start(2000000);
	FeedDog();
//	GPIO_PinselConfig(WATCHDOG,0);	
//
//	FeedDog();

}

/****************************************************************************
* 名称：void  FeedDog(void)
* 功能：看门狗喂狗操作。
* 入口参数：无
* 出口参数：无
****************************************************************************/
void  FeedDog(void)
{  
	WDT_Feed();
//   if(GPIO_ReadIoVal(WATCHDOG))
//   {
//   		GPIO_SetOrClearValue(WATCHDOG,0);
//   }
//   else
//   {
//   		GPIO_SetOrClearValue(WATCHDOG,1);	
//   }
}


/****************************************************************************
* 名称：void  FeedDog(void)
* 功能：看门狗喂狗操作。
* 入口参数：无
* 出口参数：无
****************************************************************************/
void  ResetSys(void)
{  
	while(1);	
}
