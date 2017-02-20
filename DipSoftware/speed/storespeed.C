#include <includes.h>
#include <FRAM.h>

//extern	stcDist g_sDist;



//------------------------------------------------------------------------
//  功  能 ：存油箱模型
// 入口参数：无
// 出口参数：当前流水号
//------------------------------------------------------------------------
uint8	StoresDistFram(stcDist * sDist)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sDist,sizeof(stcDist) - 2);
	
	sDist->Crc16 = CrcCheck;
	

	if(! WriteFM24CL64(DEN_FRAM_ADD,(uint8 *)sDist, sizeof(stcDist)))
	{Flg = FALSE;}
	
	if(! WriteFM24CL64(DEN_FRAM_ADD_BCK,(uint8 *)sDist, sizeof(stcDist)))
	{Flg = FALSE;}		

	return	Flg;
}

//------------------------------------------------------------------------
//  功  能 ：读燃油密度错误
// 入口参数：燃油密度指针
// 出口参数：操作成功：返回1；否则，返回0
//------------------------------------------------------------------------
uint8	ReadDistFram(stcDist * sDist)
{
	uint16		CrcCheck;
	uint16		Flg;
	stcDist   	sDistTmp;
	uint32		i;
	uint8		*p;

	Flg = FALSE;

	if( ReadFM24CL64(DEN_FRAM_ADD,(uint8 *)&sDistTmp, sizeof(stcDist)))
	{
		CrcCheck = GetCrc16Check((uint8 *)&sDistTmp,sizeof(stcDist) - 2);
		
		if((CrcCheck == sDistTmp.Crc16))
		{		
			if(CrcCheck)						
			{
				//sDist = &sDistTmp;
				memcpy((uint8 *)sDist,(uint8 *)&sDistTmp,sizeof(stcDist));
				Flg = TRUE;
				return	Flg;
			}
			else 
			{	
				p = (uint8 *)&sDistTmp;
				
				for(i = 0; i < sizeof(stcDist);i++)
				{
					if( * p )
					{
						//sDist = &sDistTmp;
						memcpy((uint8 *)sDist,(uint8 *)&sDistTmp,sizeof(stcDist));

						Flg = TRUE;
						return	Flg;
					}
				}
			}
		}
		printfcom0("\r\n 读里程CRC错误！");
	}
	else
	{
		printfcom0("\r\n 读里程错误！");
	}
	
	if( ReadFM24CL64(DEN_FRAM_ADD_BCK,(uint8 *)&sDistTmp, sizeof(stcDist)))
	{
		CrcCheck = GetCrc16Check((uint8 *)&sDistTmp,sizeof(stcDist) - 2);
		
		if((CrcCheck == sDistTmp.Crc16))
		{		
			if(CrcCheck)						
			{
				//sDist = &sDistTmp;
				memcpy((uint8 *)sDist,(uint8 *)&sDistTmp,sizeof(stcDist));

				Flg = TRUE;
				return	Flg;
			}
			else 
			{
				p = (uint8 *)&sDistTmp;
				
				for(i = 0; i < sizeof(stcDist);i++)
				{
					if( * p )
					{
						//sDist = &sDistTmp;
						memcpy((uint8 *)sDist,(uint8 *)&sDistTmp,sizeof(stcDist));

						Flg = TRUE;
						return	Flg;
					}
				}
			}
		}
		
		printfcom0("\r\n 读里程BCK CRC错误！");
	}
	else
	{
		printfcom0("\r\n 读里程BCK 错误！");
	}
		
	return	Flg;
}
//读里程
uint8	ReadDist(stcDist  *g_sDist)
{
	uint8	Flg;
	
	Flg = ReadDistFram( g_sDist);
	if(Flg != TRUE)
	{
		g_sDist->A_sDist.ModDPR	 = 0;
		g_sDist->A_sDist.Dist	 = 0;

		g_sDist->E_sDist.ModDPR	 = 0;
		g_sDist->E_sDist.Dist	 = 0;		
		
		g_sDist->C_sDist.ModDPR	 = 0;
		g_sDist->C_sDist.Dist	 = 0;	
		printfcom0("\r\n Flg %d 读里程数！",Flg);
	}
//	

	return	Flg;
}


//存里程
uint8	StoresDist( stcDist * g_sDist)
{
	uint8	Flg;
	
	Flg = StoresDistFram(g_sDist);
	
//	printfcom0("\r\n Sores Speed an distance Data To Fram");
	return	Flg;
}

