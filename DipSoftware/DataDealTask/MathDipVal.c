////#include 	"config.h" 
////#include	"stdlib.h"
////#include	"stdio.h"
////
////#include	"string.h"
////#include	"Globe.h"
////#include	"DipMath.h"
////#include	"CpuDrive.h"
////#include	"FramStore.h"
////#include	"DipMath.h"
////#include	"math.h"
////#include	"Tax2.h"
////#include	"HardDrive.h"
//
//
#include 	<includes.h>
#include	"DipMath.h"

#define     FREQ_DOWN_STATE     1
#define     FREQ_WAVE_STATE     2
#define     FREQ_LAG_WAVE_STATE 3
#define     FREQ_UP_STATE       4           		//频率变化状态
#define     FREQ_STOP_STATE     5

#define     BUF_SIZE_DIP        30

int16  l_CurDipAvgPrs 	= 0;                     	//实际平均压强值
uint16  l_DipStorePrs 	= 0;                  		//频率的最终运算结果
uint8   l_PrsChgState 	= FREQ_WAVE_STATE;    		//频率波动状态

int16	l_Dip1Frq10SecChg;
int16	l_Dip2Frq10SecChg;

uint8	GetDebugModelDisHig(void)
{
	stcSysRunPara 	sSysRunPara;

	if(GetSysRunPara((stcSysRunPara * )&sSysRunPara))
	{
		if(sSysRunPara.DisHigFlg)
		{
			return	sSysRunPara.DisHigFlg;
		}	
	}

	return	0;
}


uint8	GetNoAvgFlg(void)
{
	stcSysRunPara 	sSysRunPara;

	if(GetSysRunPara((stcSysRunPara * )&sSysRunPara))
	{
		if(sSysRunPara.NoAvgFlg)
		{
			return	sSysRunPara.NoAvgFlg;
		}	
	}

	return	0;
}


	

//------------------------------------------------------------------------------
//名    称：    void  GetDip10SecChg(int16	CurDip1Prs,int16	CurDip2Prs )
//功    能：    测量状态变化判断
//入口参数：    油尺1，油尺2当前测量值
//出口参数：    
//------------------------------------------------------------------------------
void  GetDip10SecChg(int16	CurDip1Prs,int16	CurDip2Prs )
{
	static	uint32	Times = 0;
	static	int16	Dip1PrsBuf[12];
	static	int16	Dip2PrsBuf[12];	
	
	Dip1PrsBuf[Times %12] = CurDip1Prs;
	Dip2PrsBuf[Times %12] = CurDip2Prs;
    

	if(Times > 12)
	{
		l_Dip1Frq10SecChg = Dip1PrsBuf[Times %12] - Dip1PrsBuf[(Times - 11)%12];		//差值			
		l_Dip2Frq10SecChg = Dip2PrsBuf[Times %12] - Dip2PrsBuf[(Times - 11)%12];	
	}
	else
	{
		l_Dip1Frq10SecChg  = 0;
		l_Dip2Frq10SecChg  = 0;				
	}
	
	
	Times++;  	
}

#define		JUDGE_STATE_TIMES	15
////------------------------------------------------------------------------------
////名    称：    uint8  GetFrqChgState( void )
////功    能：    油尺状态判断
////入口参数：    无
////出口参数：    油量变化状态
////------------------------------------------------------------------------------
uint8  GetFrqChgState(int16	CurDip1Prs,int16	CurDip2Prs)
{
    static  int32  UpTimes = 0,DownTimes = 0,StopTimes = 0,WaveTimes = 0;
    static	uint8	FreqChgState = FREQ_WAVE_STATE;
    
    GetDip10SecChg(CurDip1Prs,CurDip2Prs);							//取10秒变化值
      
    if(((l_Dip1Frq10SecChg > 30) && (l_Dip2Frq10SecChg > 30)))		//同升
    {
        UpTimes++;
        DownTimes = WaveTimes = 0;
        //100815
      	StopTimes	= 0;

        if((UpTimes > JUDGE_STATE_TIMES))
        {        
	        StopTimes	= 0;
            UpTimes 	= 0;
            
            FreqChgState = FREQ_UP_STATE;
        }
    }
    else  if(((l_Dip1Frq10SecChg < -1) && (l_Dip2Frq10SecChg < -1)))		//同降	
    {
    	DownTimes++;
    	UpTimes = WaveTimes = 0;
		//100815
		if(abs(l_Dip1Frq10SecChg) > 30 || abs(l_Dip1Frq10SecChg) > 30)
		{
			StopTimes	= 0;
//			FreqChgState = FREQ_WAVE_STATE;
		}
		
        if((DownTimes > JUDGE_STATE_TIMES) )
        {        
	        StopTimes	= 0;
            DownTimes 	= 0;
            
            FreqChgState = FREQ_DOWN_STATE;
        }
    }
	else  if(	(abs(l_Dip1Frq10SecChg) < 15 ) && 
			 	(abs(l_Dip2Frq10SecChg) < 15 ))						//稳定
    {
        StopTimes++;
        UpTimes = DownTimes =  WaveTimes = 0;
                
        if(StopTimes > JUDGE_STATE_TIMES * 2)
        {
            StopTimes = 0;
            FreqChgState = FREQ_STOP_STATE;
        }
    }
    else
    {
        UpTimes = DownTimes = StopTimes = 0;						

        if( abs(l_Dip1Frq10SecChg - l_Dip2Frq10SecChg) > 300 )		//大波动
        {
	        WaveTimes 	= JUDGE_STATE_TIMES;
	        FreqChgState = FREQ_LAG_WAVE_STATE;
	    }
        else
        {
        	if(WaveTimes > 0)
            {
                WaveTimes--;
               	FreqChgState = FREQ_LAG_WAVE_STATE;	
            }
            else													//波动
            {
                FreqChgState = FREQ_WAVE_STATE;
            }
        }	    
    }
    
    return	FreqChgState;
}
 
////------------------------------------------------------------------------------
////名    称：    void	GetDipPrsAvg(void)
////功    能：    取运算参数
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
int16	GetDipPrsAvg(int16	CurDip1Prs,int16	CurDip2Prs)
{
	int16	CurDipAvgPrs = 0;
//	static	uint32	Time = 0;
	static 	uint32	Times = 0;
	int32	PrsDef;

//////////////////////////////////////////
	if((GetMyDip1Err() & 0x03 )== 0x03)	  //油尺1故障
	{
		CurDip1Prs = 0;
	}

	if((GetMyDip2Err() & 0x03 )== 0x03)	  //油尺2故障
	{
		CurDip2Prs = 0;
	}
/////////////////////////////////////////////////	
	if(CurDip1Prs > 10000 || CurDip1Prs < -500 )  //20120611传感器最大值
	{
		CurDip1Prs = 0;
	}
	
	if(CurDip2Prs > 10000 || CurDip2Prs < -500 )
	{
		CurDip2Prs = 0;
	}


	PrsDef = CurDip1Prs - CurDip2Prs;

	//printfcom0("\r\n %d,%d,%d",CurDip1Prs,CurDip2Prs,PrsDef);	
	//if(CurDip1Prs > 1000 || CurDip2Prs >1000)   //根据K3所数据调整
	if(CurDip1Prs > 1000 || CurDip2Prs >1000)
	{
		if(fabs(PrsDef) > 2000 )
		{
			Times++;
			
			if(Times > 120)
			{
				if(CurDip1Prs < 500)
				{
					CurDip1Prs = 0;
				}
				else if(CurDip2Prs < 500)
				{
					CurDip2Prs = 0;
				}
			}
		}
		else
		{
			Times = 0;
		}
	}

	
	if(CurDip1Prs && CurDip2Prs  )							//求频率平均值
	{
		CurDipAvgPrs  =	(CurDip1Prs + CurDip2Prs) / 2;		//
	}
	else if( CurDip1Prs )
	{
		CurDipAvgPrs  = CurDip1Prs;
	}
	else if( CurDip2Prs )
	{
		CurDipAvgPrs  = CurDip2Prs;
	}
	//printfcom0("\r\n11 %d,%d,%d",CurDip1Prs,CurDip2Prs,CurDipAvgPrs);
	return	CurDipAvgPrs;
}
//
////------------------------------------------------------------------------------
////名    称：    void	GetMathPara(void)
////功    能：    取输入的运算参数
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
void	GetMathPara(void)
{
	int16	CurDip1Prs;
	int16	CurDip2Prs;

	CurDip1Prs	=	GetDip1Hig();
	CurDip2Prs	=	GetDip2Hig();

	l_CurDipAvgPrs 	= GetDipPrsAvg(CurDip1Prs,CurDip2Prs);		//平均值
	
	l_PrsChgState 	= GetFrqChgState(CurDip1Prs,CurDip2Prs);	//波动状态	
	
//	printfcom0("\r\n油1压强：%d,油2压强：%d,平均压强：%d"
//	    	,CurDip1Prs,CurDip2Prs,l_CurDipAvgPrs);	
//
}

//#define     FREQ_DOWN_STATE     1
//#define     FREQ_WAVE_STATE     2
//#define     FREQ_LAG_WAVE_STATE 3
//#define     FREQ_UP_STATE       4           		//频率变化状态
//#define     FREQ_STOP_STATE     5
//
//------------------------------------------------------------------------------
//名    称：    int16    GetDipPrsMinVal(int16    Frq)
//功    能：    取1分钟的平均值
//入口参数：    无
//出口参数：    无
//------------------------------------------------------------------------------
void    MinToMaxOder(int16 * Buf,uint32 BufSize)
{
	uint32	i,j;
	int32	Tmp;
	
	for(i = 0;i < BufSize;i++)
	{
		for(j = 0;j <BufSize-i-1;j++)
		{
			if(Buf[j] > Buf[j + 1])
			{
				Tmp = Buf[j + 1];
				Buf[j + 1] = Buf[j];
				Buf[j]  = Tmp;
			}
		}
	}
}

////------------------------------------------------------------------------------
////名    称：    int16    GetDipPrsMinVal(int16    Frq)
////功    能：    取1分钟的平均值
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
int16    GetDipPrs30SecVal(int16   PrsAvg)
{
	static	uint32	Times	= 0;
	static	int32	Sum30 = 0;
	static	int32	Sum5 = 0;
	int16	PrsAvg30 = 0;
	int16	PrsAvg10 = 0;
	int16	PrsAvg5  = 0;
	int16 	MinutePrsAvg;
	uint8	PrsChgState;
	int32	AvgTmp;
		
	PrsChgState = GetPrsChgState();

	if(GetSysTime()<60*100)
	{	
		return PrsAvg;
	}

	if(Times < 30)
	{
		Sum30 += PrsAvg;	
		if(Times < 5)
		{
			Sum5 += PrsAvg;
		}
		else
		{
			AvgTmp = Sum5 / 5; 
			Sum5  = Sum5 + PrsAvg - AvgTmp;			
		}

		Times++;
		return	PrsAvg;
	}
	else
	{
		AvgTmp = Sum30 / 30;
		Sum30  = Sum30 + PrsAvg - AvgTmp;		

		AvgTmp = Sum5 / 5; 
		Sum5  = Sum5 + PrsAvg - AvgTmp;		
	}

	PrsAvg30 	= Sum30 / 30;
	PrsAvg5 	= Sum5 / 5;
	PrsAvg10 	=(PrsAvg5*2 + PrsAvg30) / 3;

	if( (PrsChgState != FREQ_WAVE_STATE) && (PrsChgState != FREQ_LAG_WAVE_STATE))
	{
		if(PrsChgState == FREQ_STOP_STATE)
		{
			MinutePrsAvg = PrsAvg10;
		}
		else 
		{
			MinutePrsAvg = PrsAvg5;
		}
	}
	else
	{
		MinutePrsAvg = PrsAvg30;
	}
	
	Times++;
	return	MinutePrsAvg;
}
//
////------------------------------------------------------------------------------
////名    称：    int16    GetDipPrsMinVal(int16    Frq)
////功    能：    取1分钟的平均值
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
//int16    GetDipPrs20SecVal(int16   PrsAvg)
//{
//	static	uint32	Times	= 0;
//	static	int32	Sum	=  0;
//	static	int16	PrsAvg20 = 0;
//	static	int16	PrsAvg10 = 0;
//	static	int16	PrsAvg5  = 0;
//	static	int16	Buf20[20];
//	int32			i;	
//	int16			MinutePrsAvg;
//	uint8			PrsChgState;
//
//	PrsChgState = GetPrsChgState();
//		
//	Buf20[Times % 20] = PrsAvg;
//	
//	if(Times < 29)
//	{
//		if(Times < 4)
//		{
//			Sum = 0;
//			
//			for(i = 0;i <= Times;i++)
//			{
//				Sum += Buf20[(Times + 20 - i) % 20];
//			}
//			
//			PrsAvg20 = Sum / (Times + 1);
//			PrsAvg10 = PrsAvg20;
//			PrsAvg5  = PrsAvg20; 		
//		}
//		else if(Times < 9)
//		{
//			Sum = 0;
//			for(i = 0;i <= Times;i++)
//			{
//				Sum += Buf20[(Times + 20 - i) % 20];
//				
//				if(i == 4)
//				{
//					PrsAvg5 = Sum / 5;		
//				}
//			}
//			
//			PrsAvg20 = Sum / (Times + 1);
//			PrsAvg10 = PrsAvg20;
//		}
//		else
//		{
//			Sum = 0;
//			for(i = 0;i <= Times;i++)
//			{
//				Sum += Buf20[(Times + 20 - i) % 20];
//				
//				if(i == 4)
//				{
//					PrsAvg5 = Sum / 5;		
//				}
//				if(i == 9)
//				{
//					PrsAvg10 = Sum / 10;		
//				}				
//			}
//			
//			PrsAvg20 = Sum / (Times + 1);
//		}		
//	}
//	else
//	{
//		Sum = 0;
//		for(i = 0;i < 20;i++ )
//		{
//			Sum += Buf20[(Times + 20 - i) % 20];
//			
//			if(i == 4)
//			{
//				PrsAvg5 = Sum / 5;		
//			}
//			if(i == 9)
//			{
//				PrsAvg10 = Sum / 10;		
//			}
//			if(i == 19)
//			{
//				PrsAvg20 = Sum / 20;
//			}
//		}
//	}
//	
//	if( (PrsChgState != FREQ_WAVE_STATE) && (PrsChgState != FREQ_LAG_WAVE_STATE))
//	{
//		if(PrsChgState == FREQ_STOP_STATE)
//		{
//			MinutePrsAvg = PrsAvg10;
//		}
//		else 
//		{
//			MinutePrsAvg = PrsAvg5;
//		}
//	}
//	else
//	{
//		MinutePrsAvg = PrsAvg20;
//	}
//	
//	Times++;
//	
//	return	MinutePrsAvg;
//}
//
uint8		l_ModelErrFlg 		= NO_ERROR;		//模型故障
uint8		l_DensityErrFlg 	= NO_ERROR;		//密度值未设
//
float  	 	l_ReviseHight;              		//修正高度
float		l_Density;							//密度值
int32		l_AddDipVal;						//增加的油量值
int8		l_SetParaFlg        = NO_ERROR;		//参数设置事件
//
////------------------------------------------------------------------------------
////名    称：    void    GetMathModelPara(void)
////功    能：    取油量运算模型参数
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
void    GetMathModelPara(stcModelComplex * sComplexModel,uint8 	ReCalFlg)
{
	static	uint32	Times = 0 ;								//运算次数
	static	uint32	ErrTimes = 0 ;							//运算次数
	
	stcReviseHight	sReviseHight;
	stcDensity		sDensity;								//燃油密度
	stcAddDipVal	sAddDipVal;								//燃油密度
//	uint32		i;
//	//printfcom0("\r\n GetMathModelPara");
	if(ReCalFlg == 1)										//如果重新计算，计数器清零
	{
		Times 		= 0;
		ErrTimes 	= 0;
		l_SetParaFlg = ERROR;
	}
	else
	{
		l_SetParaFlg = NO_ERROR;
	}

	if(Times > 20) return ;	

  	if( GetOilBoxModel(sComplexModel))			
  	{		
  		l_ModelErrFlg = NO_ERROR;   
  	}
  	else
  	{	
  		ErrTimes++;		
  		
  		Times = ErrTimes / 10;
  		
  		l_ModelErrFlg = ERROR;							//油箱模型未设
  	}
	
	

			 
	if(Times++ == 0 )										//如果读出的模型错误码，则需多次读取	
  	{	  	
	  	if( ReadDensity((stcDensity *) &sDensity)
//	  		|| ReadDensity_Flsh((stcDensity *) &sDensity) 
			)			//取密度  20120213
	  	{
	  		l_Density	=  ((float)sDensity.Density / 1000);
			
	  		if(l_Density > 0.9 || l_Density < 0.75)
	  		{	
				l_DensityErrFlg = ERROR;
				
				l_Density = 0.845;
				
//				//printfcom0("\r\n读出密度值超限 l_Density = %f",l_Density);
	  		}
	  		else
	  		{
				l_DensityErrFlg = NO_ERROR;
	  		}
	  	}
	  	else
	  	{
	  		l_Density = 0.845;		
	  					
			l_DensityErrFlg = ERROR;
				
			//PrintfDebug("\r\nl_DensityErrFlg = ERROR; l_Density = %f",l_Density);
	  	}
//	  	
	  	if(ReadReviseHight((stcReviseHight *) &sReviseHight)
	  		//||ReadReviseHight_Flsh((stcReviseHight *) &sReviseHight)
		 )
	  	{	
	  		l_ReviseHight = sReviseHight.ReviseHight;
	  		
	  		if((l_ReviseHight > 500) || (l_ReviseHight < -500))
	  		{		
//				//printfcom0("\r\n修正高度值超限 l_ReviseHight = %f",l_ReviseHight);
	  		
	  			l_ReviseHight = 0;
	  		}
	  	}
	  	else
	  	{
	  		l_ReviseHight = 0;
	  	}
	  	
//	 	printfcom0("\r\n l_ReviseHight %d, %d",(int16)l_ReviseHight,(int16)(l_Density*1000));
	 									   
	  	if(ReadAddDipVal((stcAddDipVal *) &sAddDipVal))
	  	{
	  		l_AddDipVal = sAddDipVal.AddDipVal;
	  		if((l_AddDipVal > 100) || (l_AddDipVal < -100))
	  		{		
				//printfcom0("\r\n 油量增加值超限 l_AddDipVal = %d",l_AddDipVal);	  		
	  			l_AddDipVal = 0;
	  		}
	  	}
	  	else
	  	{
	  		l_AddDipVal = 0;
	  	}  	
  	}
}

////------------------------------------------------------------------------------
////名    称：    int16    GetDensityVal(void)
////功    能：    返回密度值
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
uint8	GetSetParaFlg(void)
{
	return	l_SetParaFlg;	
}
//
////------------------------------------------------------------------------------
////名    称：    int16    GetDensityVal(void)
////功    能：    返回密度值
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
uint8	SetParaFlgTrue(void)
{
	return	l_SetParaFlg = NO_ERROR;	
}
////------------------------------------------------------------------------------
////名    称：    int16    GetDensityVal(void)
////功    能：    返回密度值
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
uint16	GetDensityVal(void)
{
	return	1000*l_Density;	
}
//
////------------------------------------------------------------------------------
////名    称：    int16    GetDensityVal(void)
////功    能：    返回密度值
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
uint16	GetReviseHight(void)
{
	return	l_ReviseHight;	
}
//
//
////------------------------------------------------------------------------------
////名    称：    int16    InitHXn5Model(int16    Frq)
////功    能：    油尺油量值计算方法
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
////void    InitHXn5Model(void)
////{
///*
//	stcModPot	sModPot[200] = 
//	{
//		285,227,
//		569,495,
//		857,766,
//		897,805,
//		949,855,
//		1001,905,
//		1052,955,
//		1103,1004,
//		1155,1054,  
//		1208,1104,
//		1262,1154,
//		1314,1204,
//		1370,1254,
//		1421,1304,
//		1473,1354,
//		1525,1403,
//		1575,1453,
//		1625,1503,
//		1678,1553,
//		1730,1603,
//		1780,1653,
//		1832,1703,
//		1886,1752,
//		1936,1802,
//		1986,1852,
//		2036,1902,
//		2086,1952,
//		2137,2002,
//		2189,2052,
//		2241,2102,
//		2293,2151,
//		2345,2201,
//		2395,2250,
//		2446,2300,
//		2496,2349,
//		2546,2399,
//		2596,2448,
//		2646,2498,
//		2696,2546,
//		2748,2596,
//		2805,2645,
//		2853,2695,
//		2899,2744,
//		2954,2794,
//		3001,2844,
//		3054,2893,
//		3100,2943,
//		3147,2993,
//		3194,3043,
//		3244,3093,
//		3292,3143,
//		3340,3193,
//		3390,3243,
//		3440,3292,
//		3495,3342,
//		3543,3392,
//		3594,3442,
//		3645,3492,
//		3689,3542,
//		3737,3592,
//		3787,3642,
//		3838,3691,
//		3882,3741,
//		3931,3791,
//		3977,3841,
//		4027,3891,
//		4078,3941,
//		4125,3991,
//		4170,4041,
//		4215,4090,
//		4263,4140,
//		4317,4189,
//		4360,4239,
//		4410,4288,
//		4454,4337,
//		4504,4387,
//		4551,4436,
//		4600,4484,
//		4642,4533,
//		4691,4583,
//		4738,4632,
//		4785,4681,
//		4830,4731,
//		4875,4781,
//		4920,4831,
//		4964,4881,
//		5012,4930,
//		5057,4980,
//		5107,5030,
//		5146,5069,
//		5187,5115,
//		5243,5178,
//		5287,5227,
//		5332,5277,
//		5379,5329,
//		5425,5381,
//		5470,5431,
//		5512,5479,
//		5559,5531,
//		5565,5538,
//		5618,5598,
//		5669,5657,
//		5720,5717,
//		5774,5777,
//		5827,5836,
//		5879,5896,
//		5894,5911,
//		5997,5970,
//		6103,6030,
//		6207,6090,
//		6312,6149,
//		6413,6209,
//		6512,6268,
//		6608,6328,
//		6692,6388,
//		6773,6447,
//		6854,6507,
//		6935,6566,
//		7016,6626,
//		7069,6665,
//		7138,6715,
//		7206,6765,
//		7275,6815,
//		7343,6864,
//		7412,6914,
//		7480,6964,
//		7549,7014,
//		7617,7063,
//		7686,7113,
//		7755,7163,
//		7823,7213,
//		7892,7263,
//		7960,7312,
//		8029,7363,
//		8097,7412,
//		8166,7462,
//		8234,7511,
//		8303,7562,
//		8371,7611,
//		8440,7661,
//		8508,7711,
//		8577,7761,
//		8645,7810,
//		8714,7860,
//		8782,7910,
//		8851,7960,
//		8919,8009,
//		8988,8059,
//		9056,8109,
//		9125,8159,
//		9193,8208,
//		9262,8258,
//		9331,8309,
//		9399,8358,
//		9468,8408,
//		9536,8457,
//		9605,8508,
//		9673,8557,
//		9742,8607,
//		9810,8657,
//		9879,8707,
//		9947,8756,
//		10016,8806,
//		10084,8856,
//		10153,8906,
//		10221,8955,
//		10294,9008,
//		10357,9054,
//		11612,9966,		
//	};						
//
//	l_sModel.PotNum = 169;
//	l_sModel.StartHight = 0;
//	//l_sModel.PotNum = 87;
//	//l_sModel.StartHight = 0;
//	
//	memcpy((uint8 *)l_sModel.sModPot,(uint8 *)sModPot,sizeof(l_sModel.sModPot));
//*/
////}	
//
uint8			l_ModelParaErrFlg = NO_ERROR;
stcModelComplex	l_sModel = {0};		
//------------------------------------------------------------------------------
//名    称：    int16    GetDipMathVal(int16    Frq)
//功    能：    油尺油量值计算方法
//入口参数：    无
//出口参数：    无
//------------------------------------------------------------------------------
uint16    GetDipMathVal(int16   Prs)
{
  	float 		DipVal = 0;                  		
  	float 		Hight;                  			
	float		MinHig,MaxHig;	
	float		MinDip,MaxDip;					
	float		fTmp; 	
	float  	 	StartHight;              			

	uint32		ModelPotNum;
	uint32		i;
	
	GetMathModelPara((stcModelComplex *)&l_sModel,0);		//模型参数	

	ModelPotNum = l_sModel.PotNum;
	StartHight	= l_sModel.StartHight;
//	printfcom0("\r\n l_sModel.PotNum %d",l_sModel.PotNum);
//	for(i = 0; i <  ModelPotNum; i++)
//	{
//		printfcom0("\r\n %d,%d",l_sModel.sModPot[i].HigVal,l_sModel.sModPot[i].DipVal);	
//	}
//	ModelNum	= l_sModel.ModelNum;
	
//	memcpy((uint8 *)sModPot,(uint8 *)l_sModel.sModPot,sizeof(sModPot));	

		//201509
//  	Hight = ((float)Prs)/(G * l_Density );			//计算高度
	Hight = Prs;      //输入直接为高度	

//	Hight += ((float)StartHight / 10  + (float)l_ReviseHight / 10);	
	Hight += ((float)StartHight   + (float)l_ReviseHight );	
  	
	printfcom0("\r\n Hight %d,Prs %d",(int)Hight,(int)Prs);

  	for(i = 1; i <  ModelPotNum; i++)					//计算点的个数
  	{
		////printfcom0("\r\n l_sModel");
		fTmp 	= 	l_sModel.sModPot[i-1].HigVal;
///		MinHig 	= fTmp / 10;
		MinHig 	= fTmp;

		fTmp 	= 	l_sModel.sModPot[i].HigVal;
//		MaxHig 	= fTmp / 10;
		MaxHig 	= fTmp;

		fTmp 	= 	l_sModel.sModPot[i-1].DipVal;
		MinDip 	= fTmp ;

		fTmp 	= 	l_sModel.sModPot[i].DipVal;
		MaxDip 	= fTmp ;
		
//		printfcom0("\r\n l_sModel3 %d,%d,%d,%d Hight %d",(int)MinHig,(int)MaxHig,(int)MinDip,(int)MaxDip,(int16)Hight);
				
		if(MinHig == MaxHig)							//计算模型中出现两个相同点
		{
			l_ModelParaErrFlg = ERROR;
			
			//printfcom0("\r\n***油箱模型错误，MinHig == MaxHig");	
			
			DisplaySet(60,1,"E-OL");					//显示油量值

			return	Hight;
		}
		else
		{
			l_ModelParaErrFlg = NO_ERROR;
		}
		////printfcom0("\r\n l_MinHig <= Hight");
		if(MinHig <= Hight && Hight < MaxHig)		//计算油量
		{	
			DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));

			break;
		}
	
		if(i == 1)									//小于最小高度
		{			
			if(Hight < MinHig)
			{
				DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				
				break;
			}
		}
		
		if(i == (ModelPotNum - 1))					//大于最大高度
		{
			
			if(Hight >= MaxHig)
			{
				DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
			}
		}
	}

//	printfcom0("\r\n DipVal = %d ",(int16)DipVal);
	DipVal += l_AddDipVal;
//	printfcom0("\r\n DipVal +l_AddDipVal = %d ",(int16)DipVal);
	
    return  DipVal;
}

//------------------------------------------------------------------------------
//名    称：    uint8	GetModelErrFlg(void)	
//功    能：    计算油尺状态变化值
//入口参数：    无
//出口参数：    无
//------------------------------------------------------------------------------
uint8	GetModelErrFlg(void)	
{
	return	l_ModelErrFlg;
}
//
//------------------------------------------------------------------------------
//名    称：    uint8	GetDensityErrFlg(void)	
//功    能：    计算油尺状态变化值
//入口参数：    无
//出口参数：    无
//------------------------------------------------------------------------------
uint8	GetDensityErrFlg(void)	
{
	return	l_DensityErrFlg;
}

////------------------------------------------------------------------------------
//名    称：    uint8	GetModelParaErrFlg(void)	
//功    能：    计算油尺状态变化值
//入口参数：    无
//出口参数：    无
//------------------------------------------------------------------------------
uint8	GetModelParaErrFlg(void)	
{
	return	l_ModelParaErrFlg;
}
//
//------------------------------------------------------------------------------
//名    称：    uint8	GetPrsChgState(void)
//功    能：    计算油尺状态变化值
//入口参数：    无
//出口参数：    无
//------------------------------------------------------------------------------
uint8	GetPrsChgState(void)	
{
	return	 l_PrsChgState;
}


//extern	void	StoreFramToFlsh(void);
////------------------------------------------------------------------------------
////名    称：    void	ReCalPara(void)
////功    能：    重新计算参数
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
void	ReCalPara(uint8	Flg)	
{
	GetMathModelPara((stcModelComplex *)&l_sModel,1);			//模型参数		
}
//
//
////------------------------------------------------------------------------------
////名    称：    void	GetDeviceParaStr(uint8 *Buf)
////功    能：    重新计算参数
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
//void	GetDeviceParaStr(uint8 *Buf)
//{
//	uint32	strLen,AllStrLen = 0;
//	uint32	i;
//	
//	ReCalPara(1);
//	
//	//printfcom0("\r\n 设备运行参数如下!");
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 设备运行参数如下：");
//
//	AllStrLen += strLen;
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 密度：%f  ",l_Density);
//
//	AllStrLen += strLen;
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 高度：%f",l_ReviseHight);
//	
//	AllStrLen += strLen;
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 油箱模型编号：%d",GetOilBoxCod());
//	
//	AllStrLen += strLen;
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 油箱模型参数：");
//	
//	AllStrLen += strLen;
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 模型编数：%d,模型点数：%d,起始高度：%d",
//											l_sModel.ModelNum,l_sModel.PotNum,l_sModel.StartHight);	
//	
//	DisplaySet(150,1,"MODE");								//显示油箱模型
//	DisplaySet(200,1,"C_%d",GetOilBoxCod());				//显示油箱模型
//	
//	DisplaySet(150,1,"DENS");
//	DisplaySet(200,1,"%d",(uint32)l_Density*1000);
//	
//	DisplaySet(150,1,"HIGH");
//	DisplaySet(200,1,"%d",(uint32)l_ReviseHight);
//	
//											
//	//油箱模型											
//	for(i = 0 ; i < l_sModel.PotNum;i++)							
//	{
//		AllStrLen += strLen;
//		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n 高度：%d,油量：%d"
//						,l_sModel.sModPot[i].HigVal,l_sModel.sModPot[i].DipVal);
//	}
//}
//
//
////------------------------------------------------------------------------------
////名    称：    void	CalcDip(void)
////功    能：    计算油尺油量
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------------
void	CalcDip(void)							
{
	static	uint32		Time = 0;
	int16	Avg30SecPrs;
   
	if(GetSysTime() - Time > 100 )					
	{
		GetMathPara();											//取运算参数
		
		Avg30SecPrs = GetDipPrs30SecVal(l_CurDipAvgPrs);		//计算30S的平均值

		if(GetNoAvgFlg() || GetSetModelFlg())
		{
			Avg30SecPrs = l_CurDipAvgPrs;	
		}
//			
////	Avg10SecPrs = GetDipPrs20SecVal(l_CurDipAvgPrs);		//计算20S的平均值
												
		g_DipDisVal = GetDipMathVal(Avg30SecPrs);				//计算油量值
		
		g_DipVal 	= g_DipDisVal;

		if(GetDebugModelDisHig())								//
		{
			g_DipVal = l_CurDipAvgPrs;
			
			printfcom0("\r\n g_DipVal,%d l_CurDipAvgPrs %d",g_DipVal,l_CurDipAvgPrs);	
		}
		
		Time = GetSysTime();
	}
}

//extern	uint8	GetSelModelErrFlg(void);
//
#define		UN_SET_MATH_PARP			32					//没有进行参数设置
#define		UN_SET_OIL_BOX_MODEL		33					//没有设置油箱模型
#define		UN_SET_DENSITY				34					//没有设置密度
#define		SET_OIL_BOX_MODEL_ERR		35					//设置的油箱模型错误
////-------------------------------------------------------------------------------------------------
////函数名称:            	uint8  JudgeCalcError(void) 
////函数功能:             对计算过程的参数进行正确性判断
////入口参数:            
////出口参数:             
////--------------------------------------------------------------------------------------------------
uint8  JudgeCalcError(void) 
{
//	static		uint32		Time = 0;
	uint8		ErrorType = RIGHT_DATA;
	
//	if( GetSysTime() - Time > 100)	
	{
//		Time = GetSysTime();

		if(GetDensityErrFlg() == NO_ERROR && GetModelErrFlg() == NO_ERROR )
		{
			if( GetModelParaErrFlg()  == NO_ERROR)
			{
				ErrorType = RIGHT_DATA;
			}
			else
			{
				ErrorType = SET_OIL_BOX_MODEL_ERR;				//模型错误
			}
		}
		else  if( ( GetModelErrFlg()  == ERROR) && (GetDensityErrFlg() ==  ERROR) )	//未设参数
		{
			ErrorType = UN_SET_MATH_PARP;
		}
		else if( GetDensityErrFlg() == NO_ERROR)
		{
			ErrorType = UN_SET_OIL_BOX_MODEL;
		}
		else
		{
			ErrorType = UN_SET_DENSITY;
		}
	}
	
	return	ErrorType;
}

#define 	ADD_OIL_EVT			34
#define 	ADD_OIL_FIN_EVT		35
#define 	STOP_TO_WAVE		36
#define 	WAVE_TO_STOP		37

//
#define     FREQ_DOWN_STATE     1
#define     FREQ_WAVE_STATE     2
#define     FREQ_LAG_WAVE_STATE 3
#define     FREQ_UP_STATE       4           		//频率变化状态
#define     FREQ_STOP_STATE     5

//-------------------------------------------------------------------------------
//函数名称:        	uint8	JudgeOilEvt(void)
//函数功能:       	判断Flsh事件
//入口参数:        	无
//出口参数:      	无
//-------------------------------------------------------------------------------
uint8	JudgeOilEvt(void)
{
	static	uint32	C_Times = 0;
	static	uint8	l_PrsState,C_PrsState;
	uint8	EvtFlg = RIGHT_DATA;
	
	EvtFlg = RIGHT_DATA;
	
	C_Times++;
	
	C_PrsState = GetPrsChgState();
	
	if(C_Times > 1)
	{
		if((C_PrsState != l_PrsState) && (C_PrsState == FREQ_UP_STATE))
		{
			EvtFlg = ADD_OIL_EVT;
		}
		
		if((C_PrsState != l_PrsState) && (l_PrsState == FREQ_UP_STATE))
		{
			EvtFlg = ADD_OIL_FIN_EVT;
		}
		
		if((C_PrsState == FREQ_WAVE_STATE || C_PrsState == FREQ_LAG_WAVE_STATE) && (l_PrsState == FREQ_STOP_STATE))
		{
			EvtFlg = STOP_TO_WAVE;
		}

		if((C_PrsState == FREQ_STOP_STATE) && (l_PrsState == FREQ_WAVE_STATE || l_PrsState == FREQ_LAG_WAVE_STATE))
		{
			EvtFlg = WAVE_TO_STOP;
		}
	}
	
	l_PrsState = C_PrsState;
	
	return	EvtFlg;
}
