#include <includes.h>



#define     LOCO_LW     20		//P0.15
#define     LOCO_QY     19		//P0.18
#define     LOCO_ZD     18		//P0.18
#define     LOCO_BK     17		//P0.18

//------------------------------------------------------------------------
//  名  称 ：void void InitI2CIO(void)
//  功  能 ：设置 SDA SCL 为普通IO口 进行模拟总线操作
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void	InitLocoStaIO(void)
{
	GPIO_PinselConfig(LOCO_LW,0);
	GPIO_PinselConfig(LOCO_QY,0);
	GPIO_PinselConfig(LOCO_ZD,0);
	GPIO_PinselConfig(LOCO_BK,0);
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCL(void)
//  功  能 ：读取 SCL 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadLOCO_LW(void)
{
    uint8 temp;

	temp = 	GPIO_ReadIoVal(LOCO_LW);
	nop();

    return temp;
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCL(void)
//  功  能 ：读取 SCL 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadLOCO_QY(void)
{
    uint8 temp;

	temp = 	GPIO_ReadIoVal(LOCO_QY);
	nop();

    return temp;
}


//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCL(void)
//  功  能 ：读取 SCL 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadLOCO_ZD(void)
{
    uint8 temp;

	temp = 	GPIO_ReadIoVal(LOCO_ZD);
	nop();

    return temp;
}


//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCL(void)
//  功  能 ：读取 SCL 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadLOCO_BK(void)
{
    uint8 temp;

	temp = 	GPIO_ReadIoVal(LOCO_BK);
	nop();

    return temp;
}

uint8	l_locoworksta = 0;


uint8	GetMyLocoWorkState(void)
{
	return l_locoworksta;
}	


void	CheckLocoStaTask(void)
{
	static	uint32	time;
	uint8	lwtmp,qytmp,zdtmp,bktmp;

	if(GetSysTime() - time > 120)
	{
		time  = GetSysTime();

		lwtmp = ReadLOCO_LW();
		qytmp = ReadLOCO_QY();
		zdtmp = ReadLOCO_ZD();
		bktmp = ReadLOCO_BK();

		if(lwtmp == 0)
		{
			l_locoworksta |= 0x01<<0;
			//printfcom0("\r\n lw");
			//return;	
		}
		else
		{
			l_locoworksta &= ~(0x01<<0);	
		}

		if(qytmp == 0)
		{
			l_locoworksta |= 0x01<<4;
			//printfcom0("\r\n qy");

			//return;	
		}
		else
		{
			l_locoworksta &= ~(0x01<<4);
		}

		if(zdtmp == 0)
		{
			l_locoworksta |= 0x01<<3;
			//printfcom0("\r\n zd");
			//return;	
		}
		else
		{
			l_locoworksta &= ~(0x01<<3);
		}

		if(bktmp == 0)
		{
			l_locoworksta |= 0x01<<2;
			//printfcom0("\r\n bk");

			//return;	
		}
		else
		{
			l_locoworksta &= ~(0x01<<2);			
		}

		//l_locoworksta = 0;
		return;
	}
}
