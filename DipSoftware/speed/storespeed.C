#include <includes.h>
#include <FRAM.h>

//extern	stcDist g_sDist;



//------------------------------------------------------------------------
//  ��  �� ��������ģ��
// ��ڲ�������
// ���ڲ�������ǰ��ˮ��
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
//  ��  �� ����ȼ���ܶȴ���
// ��ڲ�����ȼ���ܶ�ָ��
// ���ڲ����������ɹ�������1�����򣬷���0
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
		printfcom0("\r\n �����CRC����");
	}
	else
	{
		printfcom0("\r\n ����̴���");
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
		
		printfcom0("\r\n �����BCK CRC����");
	}
	else
	{
		printfcom0("\r\n �����BCK ����");
	}
		
	return	Flg;
}
//�����
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
		printfcom0("\r\n Flg %d ���������",Flg);
	}
//	

	return	Flg;
}


//�����
uint8	StoresDist( stcDist * g_sDist)
{
	uint8	Flg;
	
	Flg = StoresDistFram(g_sDist);
	
//	printfcom0("\r\n Sores Speed an distance Data To Fram");
	return	Flg;
}
