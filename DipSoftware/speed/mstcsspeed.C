#include <includes.h>
#include <FRAM.h>

//ÿȦ���峣��
#define		PPR		200
//pi = 3.14 * 100
#define		PI		314
//�ֶ�ֱ�� 1.1m * 10
#define		DIM		11
//��̳��� PPR *10*100*1000  
#define		PI_DIM_MUL		(10*100)


uint32	mPluseSumCntcs = 0;
//-------------------------------------------------------------------------------
//��������:         GetFrqCnt()
//��������:         ȡƵ��ֵ
//��ڲ���:         ��		 
//���ڲ���:         
//-------------------------------------------------------------------------------
uint32  GetFrq3SumCnt(void)
{
	return	mPluseSumCntcs;
}

uint32	m_TimecsSum = 0;
uint32	m_AddPlusecs = 0;
uint32	m_PlusecsChgFlg = 0;
static	stcSpeedPluse	m_sSpeedcsPluse;


#define	MATH_PLUSE_TIME	 (2*1000*1000)
#define	MATH_PLUSE_NUM 	 200



//void TIMER2_IRQHandler(void)
//{
//	//printfcom0(";;");
//	if (TIM_GetIntCaptureStatus(LPC_TIM2,TIM_MR0_INT))
//	{
//		TIM_ClearIntCapturePending(LPC_TIM2,TIM_MR0_INT);
//
//		m_TimecsSum += TIM_GetCaptureValue(LPC_TIM2,TIM_COUNTER_INCAP0);
//		TIM_ResetCounter(LPC_TIM2);
//
//		m_AddPlusecs++;
//		mPluseSumCntcs++;
//
//		if(m_AddPlusecs == MATH_PLUSE_NUM || m_TimecsSum > MATH_PLUSE_TIME) 		//500�������1��ʱ�䵽
//		{
//			m_sSpeedcsPluse.TimeCnt 	= 	m_TimecsSum;
//			m_sSpeedcsPluse.PluseCnt	=   m_AddPlusecs;
//				
//			m_AddPlusecs = 0;
//			m_TimecsSum = 0;
//			m_PlusecsChgFlg = 1;
//		}
//	}
//}


uint16  l_speedcs = 0;
uint16	GetMyEngRotSpd(void)
{
	return	l_speedcs;
}

void GetSpeedPlusecs(stcSpeedPluse * sSpeedPluse)
{
	static	uint32	Time;
	
	sSpeedPluse->PluseCnt = m_sSpeedcsPluse.PluseCnt;
	sSpeedPluse->TimeCnt  = m_sSpeedcsPluse.TimeCnt;

	if(m_PlusecsChgFlg == 1)							//�����ۼӴ���,
	{
		m_PlusecsChgFlg = 0;
		Time = GetSysTime();
	}
		
	if(GetSysTime() - Time > 350)					//����2��û���£�����    ---  ����ˢ��ʱ��2��
	{	
//		printfcom0("\r\n outtime");
		sSpeedPluse->PluseCnt = 0;
		sSpeedPluse->TimeCnt = 0;
	}	
}

//���㹫ʽ��V = ��PI * DIM * n * 3600��/ (( DPR *1000*10*100 )*(t/12000000);
//------------------------------------------------------------------------------
//��    �ܣ�    ��������̣��ֶ���̣��Զ������
//��ڲ�����    
//���ڲ�����    
//------------------------------------------------------------------------------
void  CalcSpeedcs( void )
{
	uint32	PluseCnt = 0;
	uint32	TimeCnt;
	uint32	DistInSec;
	uint16	speed;
	uint32	cstime     = 0;
	uint32	times = 0;
	uint32	avg;
	
	stcSpeedPluse	sSpeedPluse;				//����

	GetSpeedPlusecs((stcSpeedPluse * )&sSpeedPluse);
	
//	if(sSpeedPluse.TimeCnt)
//	{
//		if(times < 3)
//		{		
			PluseCnt 		= sSpeedPluse.PluseCnt;
			cstime	 		= sSpeedPluse.TimeCnt;
//		}
//		else
//		{
//			avg =  PluseCnt/3;
//			PluseCnt = PluseCnt - avg + sSpeedPluse.PluseCnt;
//			avg =  cstime/3;
//			cstime   = cstime - sSpeedPluse.PluseCnt;
//		}
//
		l_speedcs = (PluseCnt * 60 * 1000) / (cstime/1000);

//		printfcom0("\r\n cstime %d,%d,%d",PluseCnt,cstime,(PluseCnt * 60 * 1000*1000));
//		printfcom0("\r\n \r\n Speedcs %d \r\n ",l_speedcs);
//
//		times++;
//	}
//	l_speedcs = speed;
//	printfcom0("\r\n ");
//	printfcom0("\r\n \r\n Speedcs %d \r\n ",l_speedcs);
}

