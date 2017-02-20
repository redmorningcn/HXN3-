#include    "includes.h"


uint8	SetDen(short density)
{
	stcDensity	sDensity;						//密度
	uint16		CrcCheck;

	sDensity.Density = density ;
	
	CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
	
	sDensity.CrcCheck = CrcCheck;
			
	if(StoreDensity((stcDensity *)&sDensity))
	{
		DisplaySet(100,1,"         ");
		DisplaySet(250,1,"D-%d",sDensity.Density);
		DisplaySet(100,1,"         ");
		
		printfcom0("\r\n 设置的密度值 %d",sDensity.Density);
		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
} 

uint8	SetHight(short 	Hight)
{
	stcReviseHight	sReviseHight;							//高度调整
	uint16		CrcCheck;
	short       StoreHight; 
		
	if(ReadReviseHight((stcReviseHight *)&sReviseHight))
	{
		StoreHight = sReviseHight.ReviseHight;
	}
	else
	{
		StoreHight = 0;
	}
	
	sReviseHight.ReviseHight = Hight;
	
	StoreHight = StoreHight + sReviseHight.ReviseHight;
	 	
	if(StoreHight > 500 ||  StoreHight < -500)
	{
		if(StoreHight > 500)
		{
			sReviseHight.ReviseHight = 500;
			DisplaySet(60,2,"TO_H");
			DisplaySet(60,2,"    ");
			DelayX10ms(250);
		}
		else
		{
			sReviseHight.ReviseHight = -500;
			DisplaySet(60,2,"TO_L");
			DisplaySet(60,2,"    ");
			DelayX10ms(250);					
		}
	}
	else
	{
		sReviseHight.ReviseHight = StoreHight;
	}

	CrcCheck = GetCrc16Check((uint8 *)&sReviseHight,sizeof(sReviseHight) - 2);
	
	sReviseHight.CrcCheck = CrcCheck;

	if(StoreReviseHight((stcReviseHight *)&sReviseHight))
	{
		DisplaySet(100,1,"         ");
		DisplaySet(250,1,"H %d.",sReviseHight.ReviseHight);
		DisplaySet(100,1,"         ");
	   	printfcom0("\r\n 设置的高度值 %d",sReviseHight.ReviseHight);

		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
} 

uint8	SetSel(uint8	ModelNum)
{						
	if(StoreSelectModel(ModelNum))
	{
		DisplaySet(100,1,"         ");
		DisplaySet(250,1,"S-%d.",ModelNum);
		DisplaySet(100,1,"         ");					
		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
}


uint8	SetFix(unsigned short 	locotype,unsigned short 	loconum)
{
	stcFixInfo	sFixInfo;							//高度调整
	uint16		CrcCheck;
		
	memcpy((uint8 *)&sFixInfo.LocoTyp,(uint8 *)&locotype,sizeof(locotype));
	memcpy((uint8 *)&sFixInfo.LocoNum,(uint8 *)&loconum,sizeof(loconum));

	DisplaySet(100,1,"         ");
	DisplaySet(250,1,"%4d.%4d",locotype,loconum);
	DisplaySet(100,1,"         ");

	CrcCheck = GetCrc16Check((uint8 *)&sFixInfo,sizeof(sFixInfo) - 2);
	sFixInfo.CrcCheck = CrcCheck;

	if(StoreFixInfo((stcFixInfo *)&sFixInfo))
	{
		SetSucceedIndicate();	
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		return	0;
	}
} 


unsigned char l_modelcardflg = 0;

unsigned char GetModelCardFlg(void)
{
	return	l_modelcardflg;
}

void ClearModelCardFlg(void)
{
	l_modelcardflg = 0;
}

extern stcModelCard  m_sModelCard;

#define		OIL_BOX_MODEL_ADDR				2000	//油箱模型地址
void	SetModel(unsigned char *buf,unsigned int Len)
{
 	static	unsigned char *pmodel;

 	unsigned int   modeldatanum = 0;
	unsigned int   readsize;	
	unsigned int   datalen = 0;
	unsigned int   i;
	uint32		ModelNumAdd;
	uint8		ModelNum;	

	datalen = 0;
			
	memcpy((unsigned char *)&modeldatanum,&buf[datalen],sizeof(modeldatanum));
	datalen += sizeof(modeldatanum);
	
	printfcom0("\r\n modeldatanum %d",modeldatanum);
	
	if(modeldatanum == 0)
	{
	   pmodel = (unsigned char *)&m_sModelCard;
	   printfcom0("\r\n 指针设值 pmodel %x,sizeof(m_sModelCard) %d",pmodel,sizeof(m_sModelCard));
	   l_modelcardflg = 1;
	}
	
	readsize	= 128<(Len-datalen)?128:(Len-datalen);
	memcpy(pmodel,&buf[datalen],readsize);
	
	StoreOilBoxModel(pmodel - (unsigned char *)&m_sModelCard,&buf[datalen],readsize);
	pmodel += readsize;

	printfcom0("\r\n pmodel - (unsigned char *)&m_sModelCard %d",pmodel - (unsigned char *)&m_sModelCard);
	
	if(modeldatanum == 0xffffffff)
	{
		l_modelcardflg = 0;
		
		printfcom0("\r\n 模型结束 sModel 点数，编号 %d,%d",m_sModelCard.sModelSemple[1].PotNum,m_sModelCard.sModelSemple[1].ModelNum );
		for(i = 0; i< m_sModelCard.sModelSemple[1].PotNum;i++)
		{
			printfcom0("\r\n 高度，油量 %d,%d",m_sModelCard.sModelSemple[1].sModPot[i].HigVal,m_sModelCard.sModelSemple[1].sModPot[i].DipVal ); 
		}

		for( i = 0;i < 64;i++)
		{
			printfcom0("\r\n 编号 %d,%d",m_sModelCard.sModelSemple[i].ModelNum ,m_sModelCard.sModelSemple[i].PotNum); 
		}

	  for(i = 0; i < 46;i++)
	  {
		  ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18 
		  				+ sizeof(stcModelSemple)*i + sizeof(stcModPot)*10 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

	      printfcom0("\r\n ModelNum %d",ModelNum); 
	  }
	}
}

uint8	ComSendData(unsigned int startnum, unsigned int endnum)
{
	uint32	FlshStartRecNum;
//	uint32	CardMaxRecNum;
	uint32	NoReadRecNum;
	uint32	lstrecnum;

	stcFlshRec		sFlshRec;

	unsigned int startrec;
	unsigned int endrec;

	g_LshRedFlshRecNum 		= ReadLstRedFlshRecNum();
	g_LshRedFlshRecNum_gprs = ReadLstRedFlshRecNum_gprs();

	if(GetRecaddr() == 0xC1)
	{
		lstrecnum = g_LshRedFlshRecNum;
	}

	if(GetRecaddr() == 0xC2)
	{
		lstrecnum = g_LshRedFlshRecNum_gprs;
	}
	
	startrec = lstrecnum > startnum?startnum:lstrecnum;
	endrec   = g_CurFlshRecNum > endnum?endnum:g_CurFlshRecNum;


//	printfcom0("\r\n startrec %d, g_LshRedFlshRecNum %d, startnum %d  ",startrec,g_LshRedFlshRecNum,startnum);
//	printfcom0("\r\n endrec %d, g_CurFlshRecNum %d, endnum %d  ",endrec,g_CurFlshRecNum,endnum);
	

	printfcom0("\r\n startnum %d,endnum %d",startnum,endnum);

	if(endrec > startrec)
	{
		if(g_CurFlshRecNum > (FLSH_MAX_SIZE)/(sizeof(stcFlshRec)) )
		{
			startrec = g_CurFlshRecNum -  (FLSH_MAX_SIZE)/(sizeof(stcFlshRec));
		}
		if(endrec > startrec)
		{
			NoReadRecNum	= (endrec - startrec);							//Flsh的未读记录长度
		}
		else
		{
			NoReadRecNum = 1;				
		}
	}
	else
	{
		NoReadRecNum = 0;
		if(GetRecaddr() == 0xC1)
		{
			StoreLstRedFlshRecNum(g_CurFlshRecNum);				//存最新的已读记录流水号
		}

		if(GetRecaddr() == 0xC2)
		{
			StoreLstRedFlshRecNum_gprs(g_CurFlshRecNum);				//存最新的已读记录流水号
		}
		return 0;
	}
	
//	CardMaxRecNum = 0xffffffff;		
//	NoReadRecNum  = GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);	//要写数据长度
	
//	FlshStartRecNum = endrec  - NoReadRecNum ;
	FlshStartRecNum = startrec;
		
	printfcom0("\r\n FlshStartRecNum %d,%d",FlshStartRecNum,NoReadRecNum);
				
//	while( NoReadRecNum--)
	{
		ReadFlshRec((stcFlshRec *)&sFlshRec,FlshStartRecNum);

		DataSend_CSNR(0x80,GetRecaddr(),(stcFlshRec *)&sFlshRec,sizeof(sFlshRec));	
		
//		DelayX10ms(2);				
//     	ReadCardDisplay(0);										//指示正在读卡
	}

//   	printfcom0("\r\n GetRecaddr() %x",GetRecaddr());
	if(GetRecaddr() == 0xC1)
	{
		g_LshRedFlshRecNum++;				//
		StoreLstRedFlshRecNum(g_LshRedFlshRecNum);
	}
	if(GetRecaddr() == 0xC2)
	{
		g_LshRedFlshRecNum_gprs++;				//
		StoreLstRedFlshRecNum(g_LshRedFlshRecNum_gprs);
	}

	return 1;
} 
