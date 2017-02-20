#include <includes.h>
#include <FRAM.h>

//每圈脉冲常量
#define		PPR		200
//pi = 3.14 * 100
#define		PI		314
//轮对直径 1.1m * 10
#define		DIM		11
//里程常数 PPR *10*100*1000  
#define		PI_DIM_MUL		(10*100)


uint32	mPluseSumCnt1 = 0;
//-------------------------------------------------------------------------------
//函数名称:         GetFrqCnt()
//函数功能:         取频率值
//入口参数:         无		 
//出口参数:         
//-------------------------------------------------------------------------------
uint32  GetFrq2SumCnt(void)
{
	return	mPluseSumCnt1;
}

uint32	m_Time1Sum = 0;
uint32	m_AddPluse1 = 0;
uint32	m_Pluse1ChgFlg = 0;
static	stcSpeedPluse	m_sSpeed2Pluse;


#define	MATH_PLUSE_TIME	 (1*1000*1000)
#define	MATH_PLUSE_NUM 	 500



void TIMER1_IRQHandler(void)
{
	if (TIM_GetIntCaptureStatus(LPC_TIM1,TIM_MR0_INT))
	{
		TIM_ClearIntCapturePending(LPC_TIM1,TIM_MR0_INT);

		m_Time1Sum += TIM_GetCaptureValue(LPC_TIM1,TIM_COUNTER_INCAP0);
		TIM_ResetCounter(LPC_TIM1);

		m_AddPluse1++;
		mPluseSumCnt1++;

		if(m_AddPluse1 == MATH_PLUSE_NUM || m_Time1Sum > MATH_PLUSE_TIME) 		//500个脉冲或1秒时间到
		{
			m_sSpeed2Pluse.TimeCnt 	= 	m_Time1Sum;
			m_sSpeed2Pluse.PluseCnt	=   m_AddPluse1;
				
			m_AddPluse1 = 0;
			m_Time1Sum = 0;
			m_Pluse1ChgFlg = 1;
		}
	}
}


uint16  l_speed2 = 0;
int32	l_addspeed2 = 0;
uint16	GetMySpeed2(void)
{
	return	l_speed2;
}

int32	GetMyAddSpeed2(void)
{
	return	l_addspeed2;
}

void GetSpeedPluse2(stcSpeedPluse * sSpeedPluse)
{
	static	uint32	Time;
	
	sSpeedPluse->PluseCnt = m_sSpeed2Pluse.PluseCnt;
	sSpeedPluse->TimeCnt  = m_sSpeed2Pluse.TimeCnt;

	if(m_Pluse1ChgFlg == 1)							//脉冲累加处理,
	{
		m_Pluse1ChgFlg = 0;
		Time = GetSysTime();
	}
		
	if(GetSysTime() - Time > 200)					//超过2秒没更新，清零    ---  最后的刷新时间2秒
	{	
//		printfcom0("\r\n outtime");
		sSpeedPluse->PluseCnt = 0;
		sSpeedPluse->TimeCnt = 0;
	}	
}

//计算公式：V = （PI * DIM * n * 3600）/ (( DPR *1000*10*100 )*(t/12000000);
//------------------------------------------------------------------------------
//功    能：    计算总里程，分段里程，自定义里程
//入口参数：    
//出口参数：    
//------------------------------------------------------------------------------
void  CalcSpeed2( void )
{
	uint32	PluseCnt;
	uint32	TimeCnt;
	uint32	DistInSec;
	uint16	speed;
	static	int32	lstaddspeed;
	
	stcSpeedPluse	sSpeedPluse;				//计数

	GetSpeedPluse2((stcSpeedPluse * )&sSpeedPluse);
		
	PluseCnt = sSpeedPluse.PluseCnt;
	TimeCnt	 = sSpeedPluse.TimeCnt;
	
	if(TimeCnt > 2)
	{
		DistInSec = PluseCnt*PI*DIM;			//单位时间内运行距离  （未除系数）	 
												// V = s/t <==> ((n/N)*100pi*10d)/t  (m/us)    （PI和DIM分别放大100和10倍 PI_DIM_MUL = 100*100 ）
												//<==> ((n*pi*d)/N/t)*(1000*1000*3600）/(1000*PI_DIM_MUL))  (km/h)	 
												//<==>  ((n*pi*d)*(36/2))/t

		DistInSec =  (DistInSec*(36/2));

		if((DistInSec % TimeCnt) > TimeCnt/2 )   //4舍5入
		{
			speed = DistInSec / TimeCnt	+1;		
		}
		else
		{
			speed = DistInSec / TimeCnt;
		}

		if(PluseCnt > 5)
		{
			if(lstaddspeed)
			{
				l_addspeed2 = TimeCnt/PluseCnt - lstaddspeed;		
			}
			lstaddspeed = 	TimeCnt/PluseCnt;
		}
	}	
	else
	{
		speed = 0;
	}	

	l_speed2 = speed;
//	printfcom0("\r\n \r\n Speed2 %d \r\n ",speed);
}


