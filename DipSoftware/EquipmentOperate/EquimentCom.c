#include <includes.h>
#include "OperateCard.h"


uint8	l_led1com2flg = 0;
uint8	l_led2com3flg = 0;

uint8	GetLed1Com2Flg(void)
{
	return	l_led1com2flg;
}

uint8	GetLed2Com3Flg(void)
{
	return	l_led2com3flg;
}


uint8	GetFramRecEndFlgCom2(void)
{
	return GetCOM2EndFlg();
}

uint8	GetFramRecEndFlgCom3(void)
{
	return GetCOM3EndFlg();
}

void	ClearFramRecEndFlgCom3(void)
{
	ClearCOM3EndFlg();
}
void	ClearFramRecEndFlgCom2(void)
{
	ClearCOM2EndFlg();
}

//清接收完成标志  南瑞
void	ClearFramRecEndFlg(void)
{
	ClearCOM1EndFlg();
}

//uint16	ReadRs485Data(uint8 *Buf)
//{
//	return	ReadCOM1(Buf,256);
//}

uint16	ReadRs485DataCom2(uint8 *Buf)
{
	return	ReadCOM2(Buf,256);
}

uint16	ReadRs485DataCom3(uint8 *Buf)
{
	return	ReadCOM3(Buf,256);
}


uint8	l_befaddr = 0;


unsigned char GetRecaddr()
{
	return	l_befaddr;
}
unsigned char l_recFlg = 0;
unsigned char GetRecFlg(void)
{
	return l_recFlg;
}

unsigned int  l_eqiupmentcode = 0;



uint8	sentendflg = 0;
//uint8	l_befaddr = 0;
uint8	l_senddatacomflg = 0;

//uint8	l_readdataoprateflg = 0;
uint32	l_senddatastartnum = 0;
uint32	l_senddataendnum = 0;

uint8	GetSendDataComFlg(void)
{
	return	 l_senddatacomflg;
}

void	ClearSendDataComFlg(void)
{
	l_senddatacomflg = 0;
}

uint32	l_readdatadisplaytime = 0;

uint32	GetReadDataDisplayTime(void)
{
	return	l_readdatadisplaytime;
}

void CarddataOperate(unsigned char *buf,unsigned int Len)		
{
	unsigned int   datalen = 0;
	unsigned char  resflg = 1;
		
	if(Len < 4)
	{
//		printfcom0("\r\n 数据长度小于4");
		return	;
	}
	
	datalen = 0;
	memcpy((unsigned char *)&l_eqiupmentcode,&buf[datalen],sizeof(l_eqiupmentcode));
	datalen += sizeof(l_eqiupmentcode);
	
//	printfcom0("接收的数据类型 %x",l_eqiupmentcode);
	resflg = 1;
		
	if(l_eqiupmentcode != 0)
	{
		switch (l_eqiupmentcode)
		{
			unsigned int startnum;
			short  density; 
			stcTime		sTime;   
			short   hig; 
			char	modelnum;
			unsigned short locotype,loconum; 
			stcSysRunPara	sSysRunPara;
	
			case DATA_CARD_DIS: 
							  ClaerDisplaySetWithoutStore();
							  ReadCardDisplay(0);
							  printfcom0("\r\n\r\n ReadCardDisplay");
							  resflg = 0;
							  l_readdatadisplaytime = GetSysTime();
							  //DelayX10ms(200);
							  break; 
			case DATA_CARD_FIN: 
							  IndicateWriteCardFinsh();
							  printfcom0("\r\n IndicateWriteCardFinsh");
							  resflg = 0;
							  l_readdatadisplaytime = GetSysTime();
							  break; 									  			
			case DATA_CARD:   //卡数据读取
							  //startnum=0,endnum=0xffffffff;
//							  printfcom0("\r\n DATA_CARD 准备发送数据 ");
							  memcpy((unsigned char *)&l_senddatastartnum,&buf[datalen],sizeof(l_senddatastartnum));
							  datalen += sizeof(startnum);
							  memcpy((unsigned char *)&l_senddataendnum,&buf[datalen],sizeof(l_senddataendnum));  
							  
							  l_senddatacomflg = 1;
							  //l_readdataoprateflg = 1;
							  //EquipmentReadData(startnum,endnum);								//
							  resflg = 0;		
							  break;    
			case DENSITY_CARD: 
//				              printfcom0("\r\n DENSITY_CARD ");  
							  memcpy((unsigned char *)&density,&buf[datalen],sizeof(density));
							  
							  SetDen(density);
//							  printfcom0("\r\n density %d  数据长度 %d datalen %d  buf %x buf++ %x",density,sizeof(density),datalen,buf[datalen],buf[datalen+1]);  
							  break;    
			case MODEL_CARD:  
							  //printfcom0("\r\n MODEL_CARD "); 
							  SetModel(&buf[datalen],Len - datalen);	   
	 
							  break;   
			case TIME_CARD:   
//							  printfcom0("\r\n TIME_CARD ");
							  
							  memcpy((unsigned char *)&sTime,&buf[datalen],sizeof(sTime));
							  
//							  printfcom0("\r\n 时间：%d-%d-%d %d-%d-%d",sTime.Year,sTime.Month,sTime.Date,sTime.Hour,sTime.Min,sTime.Sec);
							  
							  WriteTime(sTime);
							  break; 
			case HIGHT_CARD:  
//							  printfcom0("\r\n HIGHT_CARD ");
							  
							  memcpy((unsigned char *)&hig,&buf[datalen],sizeof(hig));

//							  printfcom0("\r\n 高度：%d",hig);
							  
							  SetHight(hig);
							  break; 
			case COPY_CARD:  	
							  printfcom0("\r\n COPY_CARD ");
							  							  
						      break; 
			case MODEL_SELECT_CARD:
//							  printfcom0("\r\n MODEL_SELECT_CARD "); 
							  
							  memcpy((unsigned char *)&modelnum,&buf[datalen],sizeof(modelnum));

//							  printfcom0("\r\n 选模：%d",modelnum);

							  SetSel(modelnum);
							  break; 
			case FIX_CARD:  
//							  printfcom0("\r\n FIX_CARD ");

							  memcpy((unsigned char *)&locotype,&buf[datalen],sizeof(locotype));
							  datalen += sizeof(locotype);
							 
							  memcpy((unsigned char *)&loconum,&buf[datalen],sizeof(loconum));
							  
//							  printfcom0("\r\n 机车类型：%d，机车编号：%d",locotype,loconum);
							  
							  SetFix(locotype,loconum);
				     		  break; 
			case COPY_FRAM_CARD:  
							  printfcom0("\r\n COPY_FRAM_CARD "); 
							  break; 
			case EXPAND_CARD:  	
							  printfcom0("\r\n EXPAND_CARD "); 
							  break; 
			case SYS_RUN_PARA:  	
							  //printfcom0("\r\n 接收运行参数 "); 
							  memcpy((unsigned char *)&sSysRunPara,&buf[datalen],sizeof(sSysRunPara));
							  datalen += sizeof(sSysRunPara);
							  DisplaySet(250,1,"F.%2d T.%2d",sSysRunPara.PrintfFlg,sSysRunPara.StoreTime);
							  StoreSysRunPara(sSysRunPara);

							  break; 

			case CLEAR_ALL:  	
							  printfcom0("\r\n 清零"); 
							  DisplaySet(250,1,"C_ALL");
							  g_CurFlshRecNum 	= 0;
							  g_LshRedFlshRecNum  = 0;
							  g_LshRedFlshRecNum_gprs  = 0;

							StoreCurFlshRecNum(g_CurFlshRecNum);
							StoreLstRedFlshRecNum(g_LshRedFlshRecNum);
								StoreLstRedFlshRecNum_gprs(g_LshRedFlshRecNum);
							  break; 
			default: ;
//				   printfcom0("\r\n default "); 
		}
		
		l_eqiupmentcode = 0;

		if(resflg ==1)
		{
			ReCalPara(1);
		}
	}
}

void  CSNR_RecDeal(void)     									//主机
{
	unsigned char		RecBuf[256] = {0};						//接收缓冲区
	unsigned char		DataBuf[256] = {0};						//

	unsigned int		RecLen;		
	unsigned int		DataLen = 16;
	uint8				comflg = 0;	
	static	uint32		com2time = 0,com3time = 0;	
	static	uint8		com2errtimes =0,com3errtimes=0;
	static	uint32		errtime1 = 0,errtime2 = 0;;	
						
	if( 
			(GetFramRecEndFlgCom2() == 1	|| GetFramRecEndFlgCom3() == 1 )
		 && sentendflg == 1
		 )				//有新的帧尾，进行数据处理
	{
		
		sentendflg = 0; 
		
		if(GetFramRecEndFlgCom2() == 1)
		{
			l_led1com2flg = COM_LED_REC;
			com2errtimes = 0;
			comflg = 0;
			com2time = GetSysTime();
			RecLen 	= ReadRs485DataCom2(RecBuf);
		}
		else
		{
			l_led2com3flg = COM_LED_REC;
			com3errtimes = 0; 
			comflg = 1;
			com3time = GetSysTime();
			RecLen 	= ReadRs485DataCom3(RecBuf);
		}
		  															//发送指令后，等待接收
																			
		ClearFramRecEndFlgCom3();									//清标志，可重新取数
		ClearFramRecEndFlgCom2();		

		l_recFlg = 1;

		l_befaddr = CSNR_GetData(RecBuf,RecLen,DataBuf,(unsigned char*)&DataLen); 
	
		switch(l_befaddr)
		{
			case 0xCA: 
//					   printfcom0("\r\n pc端处理！");				//PC端处理

					   CarddataOperate(DataBuf,DataLen); 			//读卡器对接收的信息进行处理 
				break;
				
			case 0xC1: 
//						printfcom0("\r\n 无线处理！");				//无线模块
					   CarddataOperate(DataBuf,DataLen); 			//读卡器对接收的信息进行处理 
				break;
				
			case 0xC2: 
//						printfcom0("\r\n 数据读取装置处理！");		//数据读取装置
					   CarddataOperate(DataBuf,DataLen); 			//读卡器对接收的信息进行处理 
				break;
				
			case 0xC3: 
						printfcom0("\r\n 智能电量处理！");			//智能电量
				
				break;	
				
			default: ;
																	//错误信息
		}

		if((l_befaddr &0xC0) == 0xC0)
		{
//			printfcom0("\r\n comflg  %d,l_befaddr %d ",comflg,l_befaddr);
			if(comflg == 0)
			{
				l_led1com2flg = COM_LED_DATA; 			
			}
			else 
			{
				l_led2com3flg = COM_LED_DATA;	
			}
		}
	}
	else
	{
		if(GetSysTime() - com2time > 100)
		{
			if(GetSysTime() - errtime1 > 100 )
			{
				com2errtimes++;
			    errtime1	= GetSysTime();
			}
			
			if(	 com2errtimes > 2)
			{
				l_led1com2flg = 0;	
			}
		}

		if(GetSysTime() - com3time > 100)
		{
			if(GetSysTime() - errtime2 > 100 )
			{
				com3errtimes++;
			    errtime2	= GetSysTime();
			}

			if( com3errtimes > 2)
			{
				//printfcom0("\r\n l_led2com3flg %d",l_led2com3flg);
				l_led2com3flg = 0;	
			}
		}
	}
}


unsigned int GetHostBuf(unsigned char *Buf)
{
//	memcpy(Buf,(unsigned char *)&g_cardsta,sizeof(g_cardsta));
//	printfcom0("len %d,g_cardsta %d",sizeof(g_cardsta),g_cardsta); 
//	return 	sizeof(g_cardsta);
	return	0;
}

void	HostStationSend_CSNR(void)
{
	unsigned char HostBuf[64];
	unsigned int  Len;
	unsigned char addr;
	
	Len = GetHostBuf(HostBuf);
	
	addr = 0xCF;
	
	DataSend_CSNR(0x80,addr,HostBuf,Len);	

}

void HostScan(void)
{
	static	unsigned char 	tmp = 0;
	static	unsigned int 	time = 0;
//	static	unsigned int	rectimes
	unsigned char 		 	ScanAddrList[5]={0xC1,0xC2,0xC3,0xC4,0xCA};
	uint8	hostbuf[32];
	uint32	len;
	uint8	modelnum;
	uint16	dip;
//	unsigned char 		 	ScanAddrList[9]={0xCA,0xCA,0xCA,0xCA,0xCA,0xCA,0xCA,0xCA,0xCA};
	
	len = 0;
	if(GetSysTime() - time > 20 || GetRecFlg())
	{
		memcpy(&hostbuf[len],(unsigned char *)&l_befaddr,sizeof(l_befaddr))	;
		len += sizeof(l_befaddr);
		
		modelnum = GetOilBoxCod();
		memcpy(&hostbuf[len],(unsigned char *)&modelnum,sizeof(modelnum))	;
		len += sizeof(modelnum);
		
		dip = g_DipVal;
		memcpy(&hostbuf[len],(unsigned char *)&dip,sizeof(dip));
		len += sizeof(dip);

		memcpy(&hostbuf[len],(unsigned char *)&g_CurFlshRecNum,sizeof(g_CurFlshRecNum))	;
		len += sizeof(g_CurFlshRecNum);		
		
		//if(GetRecAddr())				
		DataSend_CSNR(0x80,ScanAddrList[tmp%5],hostbuf,len);
//		printfcom0("\r\n l_befaddr %d,%d,%d,%d",l_befaddr,modelnum,dip,g_CurFlshRecNum);
		tmp++;
		sentendflg = 1;
		l_recFlg = 0; 
		time 	 = GetSysTime(); 
	}
}

void  EquipmentComTask(void)   
{
	static	 unsigned int   time;

	if(GetSendDataComFlg() == 1)     //readdata
	{		
		if(ComSendData(l_senddatastartnum,l_senddataendnum))
		{
			l_senddatastartnum++;
			return;
		}
		else
		{
			ClearSendDataComFlg();
		}
	}

	if(GetModelCardFlg() == 0) 	  	//set model
	{
	 	HostScan();  
		time = GetSysTime(); 

		CSNR_RecDeal();
	}
	else
	{
		while(GetModelCardFlg() == 1)
		{
			sentendflg = 1;
			if(GetSysTime() - time > 10*100 )    //模型卡退出
			{
//				ClearModelCardFlg();
			}

			CSNR_RecDeal();

			CirculatesTask();
		}
	}
}

