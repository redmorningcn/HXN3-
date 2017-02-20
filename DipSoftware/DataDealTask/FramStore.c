////#include 	"config.h"   
////#include 	"string.h"   
////#include	"Globe.h"
////#include	"CpuDrive.h"
////#include	"HardDrive.h"
//
#include <includes.h>
#include "FRAM.h"
/*
#define		CUR_FLSH_REC_NUM				0		//CPU当前记录流水号铁电存贮首地址 
#define		LST_RED_FLSH_REC_NUM			12		//CPU运行状态铁电存贮首地址
#define		OIL_REVISE_HIGHT_ADDR			24		//油尺修正高度
#define		OIL_DENSITY_ADDR				32		//油尺密度
#define		ADD_DIP_VAL_ADDR				72		//增加油量值
#define		SELECT_MODEL_ADDR				90		//油箱模型选择地址
#define		HOST_DEVICE_INFO_ADDR			100		//主机出厂信息铁电存贮地址
#define		FIX_INFO_ADDR					150		//设备初装车铁电存贮首地址
#define		CUR_REC_ADDR					200		//最新记录地址
#define		DEBUG_INFO_ADDR					350		//调试地址
#define		LOG_INFO_ADDR					500		//日志存贮首地址
//#define		LOG_INFO_ADDR					600		//日志存贮首地址

#define		OIL_BOX_MODEL_ADDR				2000	//油箱模型地址	

#define		FRAM_ERR_EVT					33
*/

uint8		l_FramWriteErrEvtFlg 	= RIGHT_DATA;
uint8		l_FramReadErrEvtFlg 	= RIGHT_DATA;
////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreCurFlashRecNum(uint32  RecNum)
////  功  能 ：	存能耗统计装置记录流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
uint8 StoreCurFlshRecNum(uint32  RecNum)
{
	uint16  Crc16Check;
	uint8	Buf[6];
	uint8	Flg;
	
	Flg = TRUE;
	
	memcpy(Buf,(uint8 *)&RecNum,sizeof(RecNum));

	Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);						//取校验
	
	memcpy(&Buf[sizeof(RecNum)],(uint8 *)&Crc16Check,sizeof(Crc16Check));

	if(!WriteFM24CL64(CUR_FLSH_REC_NUM, Buf, sizeof(Buf)))					//存信息
	{
		printfcom0("\r\nWrite StoreCurFlshRecNum Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = 	FALSE;
	}
	
	if(!WriteFM24CL64(CUR_FLSH_REC_NUM + sizeof(Buf), Buf, sizeof(Buf)))	//存信息备件
	{
		printfcom0("\r\nWrite StoreCurFlshRecNumBak Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}	
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshRecNum(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
uint32 ReadCurFlshRecNum(void)
{
	uint16	CrcCheck;
	uint8	Buf[6];
	uint32	FlshRecNum = 0;

	if(!ReadFM24CL64(CUR_FLSH_REC_NUM, Buf, sizeof(Buf)))
	{
		printfcom0("\r\n a读当前流水号错误! ");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));

			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n 读当前流水号校验错误！");
		}
	}

	if(!ReadFM24CL64(CUR_FLSH_REC_NUM + sizeof(Buf), Buf, sizeof(Buf)))
	{
		printfcom0("\r\n读当前流水号备份错误!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
			
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n当前流水号备份校验错误！");
		}		
	}
 	
 	return	FlshRecNum;
}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreCurFlashTimes(uint32  Times)
////  功  能 ：	存能耗统计装置记录流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//uint8 StoreDenChangeTimes(uint32  Times)
//{
////	//uint16  Crc16Check;
////	//uint8	Buf[4];
////	uint8	Flg;
////	
////	Flg = TRUE;
////	
////	//memcpy(Buf,(uint8 *)&Times,sizeof(Times));
////
////	//Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);						//取校验
////	
////	//memcpy(&Buf[sizeof(Times)],(uint8 *)&Crc16Check,sizeof(Crc16Check));
////
////	if(!WriteFM24CL64(OIL_DEN_CHAGE_TIMES_ADDR, (uint8 *)&Times, sizeof(Times)))	//存信息
////	{
////		printfcom0("\r\n	Write OIL_DEN_CHAGE_TIMES_ADDR Error!");
////		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
////		Flg = 	FALSE;
////	}
////	
////	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshTimes(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
//uint32 ReadDenChangeTimes(void)
//{
////	//uint16	CrcCheck;
////	//uint8	Buf[6];
////	uint32	Times = 0;
////
////	l_FramReadErrEvtFlg = RIGHT_DATA;
////
////	if(!ReadFM24CL64(OIL_DEN_CHAGE_TIMES_ADDR, (uint8 *)&Times, sizeof(Times)))
////	{
////		printfcom0("\r\n OIL_DEN_CHAGE_TIMES_ADDR错误!");
////	}
////
//// 	return	Times;
//}
//
uint8	l_ReadDataFlg = NO_ERROR;
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreLstRedFlshRecNumBck(uint32  RecNum)
////  功  能 ：	存能耗统计装置最后1次读卡结束流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
uint8 StoreLstRedFlshRecNum(uint32  RecNum)
{
	uint16  Crc16Check;
	uint8	Buf[6];
	uint8	Flg;

	Flg = TRUE;
	
	l_ReadDataFlg = ERROR;
	
	memcpy(Buf,(uint8 *)&RecNum,sizeof(RecNum));

	Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);		
	
	memcpy(&Buf[sizeof(RecNum)],(uint8 *)&Crc16Check,sizeof(Crc16Check));

	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM, Buf, sizeof(Buf)))					//存信息
	{
		printfcom0("\r\nWrite StoreCurFlshRecNum Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
		Flg = FALSE;
	}
	
	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM + sizeof(Buf), Buf, sizeof(Buf)))	//存信息备件
	{
		printfcom0("\r\nWrite StoreCurFlshRecNumBak Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}	
	
	return	Flg;
}
uint8 StoreLstRedFlshRecNum_gprs(uint32  RecNum)
{
	uint16  Crc16Check;
	uint8	Buf[6];
	uint8	Flg;

	Flg = TRUE;
	
	l_ReadDataFlg = ERROR;
	
	memcpy(Buf,(uint8 *)&RecNum,sizeof(RecNum));

	Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);		
	
	memcpy(&Buf[sizeof(RecNum)],(uint8 *)&Crc16Check,sizeof(Crc16Check));

	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM_GPRS, Buf, sizeof(Buf)))					//存信息
	{
		printfcom0("\r\nWrite StoreCurFlshRecNum Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
		Flg = FALSE;
	}
	
	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM_GPRS + sizeof(Buf), Buf, sizeof(Buf)))	//存信息备件
	{
		printfcom0("\r\nWrite StoreCurFlshRecNumBak Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}	
	
	return	Flg;
}

//
uint8	GetReadDataFlg(void)
{
	return	l_ReadDataFlg;
}
//
void	SetReadDataFlgTrue(void)
{
	l_ReadDataFlg = NO_ERROR;
}
//
////------------------------------------------------------------------------
////  名  称 ：	uint32 ReadLstRedFlshRecNum(void)
////  功  能 ：	读存能耗统计装置上次写记录流水号
//// 入口参数：	无
//// 出口参数：	最后写卡的记录流水号
////------------------------------------------------------------------------
uint32 ReadLstRedFlshRecNum(void)
{
	uint16	CrcCheck;
	uint8	Buf[6];
	uint32	FlshRecNum = 0;

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM, Buf, sizeof(Buf)))
	{
		printfcom0("\r\n读最后一次写卡流水号错误!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
	
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n最后一次写卡流水号校验错误！");
		}			
	}

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM + sizeof(Buf),Buf, sizeof(Buf)))
	{
		printfcom0("\r\n读最后一次写卡流水号错误!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
			
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n最后一次写卡流水号校验错误！");
		}			
	}
 	
 	return	FlshRecNum;
}

////------------------------------------------------------------------------
////  名  称 ：	uint32 ReadLstRedFlshRecNum(void)
////  功  能 ：	读存能耗统计装置上次写记录流水号
//// 入口参数：	无
//// 出口参数：	最后写卡的记录流水号
////------------------------------------------------------------------------
uint32 ReadLstRedFlshRecNum_gprs(void)
{
	uint16	CrcCheck;
	uint8	Buf[6];
	uint32	FlshRecNum = 0;

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM_GPRS, Buf, sizeof(Buf)))
	{
		printfcom0("\r\n读最后一次写卡流水号错误!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
	
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n最后一次写卡流水号校验错误！");
		}			
	}

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM_GPRS + sizeof(Buf),Buf, sizeof(Buf)))
	{
		printfcom0("\r\n读最后一次写卡流水号错误!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
			
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n最后一次写卡流水号校验错误！");
		}			
	}
 	
 	return	FlshRecNum;
}
//
//extern	uint32 ReadLstRedFlshRecNum_Flsh(void);
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshRecNum(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
uint32 GetLstFlshRecNum(void)
{
	uint32		FlshRecNum = 0;
//	stcFlshRec 	sFlshRec;
	
	if( ReadLstRedFlshRecNum() )
	{
		FlshRecNum = ReadLstRedFlshRecNum();
	}
	else
	{
//		if(ReadLstRedFlshRecNum_Flsh())
		{
//			FlshRecNum = ReadLstRedFlshRecNum_Flsh();
		}
	}
	
	return	FlshRecNum;
}

////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshRecNum(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
uint32 GetLstFlshRecNum_gprs(void)
{
	uint32		FlshRecNum = 0;
//	stcFlshRec 	sFlshRec;
	
	if( ReadLstRedFlshRecNum_gprs() )
	{
		FlshRecNum = ReadLstRedFlshRecNum_gprs();
	}
	else
	{
//		if(ReadLstRedFlshRecNum_Flsh())
		{
//			FlshRecNum = ReadLstRedFlshRecNum_Flsh();
		}
	}
	
	return	FlshRecNum;
}

void	StoreSysRunPara(stcSysRunPara  sSysRunPara)
{
	WriteFM24CL64(SYS_RUN_PARA_ADDR,(uint8 *)&sSysRunPara, sizeof(stcSysRunPara));	
}

uint8	GetSysRunPara(stcSysRunPara * sSysRunPara)
{
	uint16	CrcCheck;
  	if(!ReadFM24CL64(SYS_RUN_PARA_ADDR,(uint8 *)sSysRunPara, sizeof(stcSysRunPara)))
	{
		printfcom0("\r\nsSysRunPara错误!");
		return	0;
	}
	else
	{
		CrcCheck = GetCrc16Check((uint8 *)sSysRunPara,sizeof(stcSysRunPara) - 2);
		if((CrcCheck == sSysRunPara->CrcCheck ) && (CrcCheck != 0) )
		{
//			printfcom0("\r\n 参数读取成功！");
			return 1;	
		}

		//printfcom0("\r\n CrcCheck Err ,%d,%d",CrcCheck,sSysRunPara->CrcCheck );
	}
	return	0;
}
//
//
//void	ClearFlshRec(void)
//{
//	uint32	RecNum = 0;
//	
//	printfcom0("\r\n ClearFlshRec!");
//	
//	RecNum = 1;
//	
//	StoreCurFlshRecNum(RecNum);
//	StoreLstRedFlshRecNum(RecNum);
//	ReCalPara(1);												//油尺参数重新计算
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint32 StoreOilBoxModel(stcModel sModel)
////  功  能 ：存油箱模型
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------

uint8	StoreOilBoxModel(uint32 add,uint8	*buf,uint32	bufsize)
{
	WriteFM24CL64(OIL_BOX_MODEL_ADDR+add,buf,bufsize);
	return 1;	
}
//uint8	StoreOilBoxModel(stcModelCard * sModelCard)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	
//	Flg = TRUE;
//	
//	CrcCheck = GetCrc16Check((uint8 *)sModelCard,sizeof(stcModelCard) - 2);
//
//	if(CrcCheck == sModelCard->CrcCheck)
//	{
//		if(! WriteFM24CL64(OIL_BOX_MODEL_ADDR,(uint8 *)sModelCard, sizeof(stcModelCard)))
//		{
//			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
//			Flg = FALSE;
//		}
//	}	
//	else
//	{
//		printfcom0("\r\nCrcCheck == sModelCard->CrcCheck ERR!");
//		Flg = FALSE;
//	}
//
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint32 ReadOilBoxModel(stcModel sModel)
////  功  能 ：存油箱模型
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------
uint8	ReadOilBoxModel(stcModelCard * sModelCard)
{
	uint16	CrcCheck;
	uint16	Flg;
	//uint8	Buf[sizeof(stcModelCard)] = {0};

	Flg = FALSE;

	printfcom0("\r\n ReadOilBoxModel!");
	if( ReadFM24CL64(OIL_BOX_MODEL_ADDR,(uint8 *)sModelCard, sizeof(stcModelCard)))
	{
		printfcom0("\r\n ReadOilBoxModel!22");
		CrcCheck = GetCrc16Check((uint8 *)sModelCard,sizeof(stcModelCard) - 2);
		
		if((CrcCheck == sModelCard->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
			}
//			else if( memcmp( (uint8 *)sModelCard,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//			}
		}
	}
		printfcom0("\r\n ReadOilBoxModel!12");
	return	Flg;
}

uint8	GetOilBoxModelsModel(stcModel * sModel)
{
	  uint32	i;
	  uint32	ModelNumAdd;
	  uint32	ModelAdd;
	  uint8		ModelNum;
	  uint16	CrcCheck;
	  uint8		OilBoxTypCod;

	  OilBoxTypCod	= GetOilBoxCod(); 

	  for(i = 0; i < 18;i++)
	  {
	      ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*i + sizeof(stcModPot)*50 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

//		  printfcom0("\r\n 11 OilBoxTypCod == ModelNum %d ,i = %d",ModelNum,i);

		  if(OilBoxTypCod == ModelNum)
		  {
//		  	  printfcom0("\r\n 2OilBoxTypCod == ModelNum %d,i = %d",ModelNum,i);
			  
			  ModelAdd = OIL_BOX_MODEL_ADDR + sizeof(stcModel)*i;		  		
		      ReadFM24CL64(ModelAdd,(uint8 *)sModel,sizeof(stcModel));
//			  printfcom0("\r\n ModelAdd == ModelNum %d,i = %d",ModelAdd);
//			  for(i = 0;i < sModel->PotNum;i++)
//			  {
//			  	printfcom0("\r\n  gaodu %d,youliang %d",sModel->sModPot[i].HigVal,sModel->sModPot[i].DipVal);
//			  }

			  CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);

			  if(CrcCheck == sModel->CrcCheck)
			  {
			  	 //printfcom0("\r\n 3PotNum %d",sModel->PotNum);	
			  	 return  1;
			  }
		  }
	  }

	  return  0;
}

uint8	GetOilBoxModelsModelSemple(stcModelSemple * sModelSemple)
{
	  uint32	i;
	  uint32	ModelNumAdd;
	  uint32	ModelAdd;
	  uint8		ModelNum;
	  uint16	CrcCheck;
	  uint8		OilBoxTypCod;

	  OilBoxTypCod	= GetOilBoxCod(); 

	  for(i = 0; i < 46;i++)
	  {
		  ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18 
		  				+ sizeof(stcModelSemple)*i + sizeof(stcModPot)*10 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

		  //printfcom0("\r\n 22 OilBoxTypCod == ModelNum %d, %d",ModelNum,OilBoxTypCod);

		  if(OilBoxTypCod == ModelNum)
		  {
			  ModelAdd = OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18  
			  			+ sizeof(stcModelSemple)*i ;
		
		      ReadFM24CL64(ModelAdd,(uint8 *)sModelSemple,sizeof(stcModelSemple));

			  CrcCheck = GetCrc16Check((uint8 *)sModelSemple,sizeof(stcModelSemple) - 2);

//			  printfcom0("\r\n 22 CrcCheck == CrcCheck %d, %d",CrcCheck,sModelSemple->CrcCheck);
			  if(CrcCheck == sModelSemple->CrcCheck)
			  {
			  	 return  1;
			  }
		  }
	  }

	  return  0;
}

//
////------------------------------------------------------------------------
////  名  称 ：uint32 uint8	StoreDensity(stcModel sModel)
////  功  能 ：存油箱模型
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------
uint8	StoreDensity(stcDensity * sDensity)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(stcDensity) - 2);

	if(CrcCheck == sDensity->CrcCheck)
	{
		if(! WriteFM24CL64(OIL_DENSITY_ADDR,(uint8 *)sDensity, sizeof(stcDensity)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
			Flg = FALSE;
		}
		
		if(! WriteFM24CL64(OIL_DENSITY_ADDR + sizeof(stcDensity),(uint8 *)sDensity, sizeof(stcDensity)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}		
	}	
	else
	{
		#pragma diag_suppress 870, 223
		printfcom0("\r\n 设置燃油密度的校验和错误！");
		Flg = FALSE;
	}

	return	Flg;
}

//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadDensity(stcDensity * sDensity)
////  功  能 ：读燃油密度错误
//// 入口参数：燃油密度指针
//// 出口参数：操作成功：返回1；否则，返回0
////------------------------------------------------------------------------
uint8	ReadDensity(stcDensity * sDensity)
{
	uint16	CrcCheck;
	uint16	Flg;


	Flg = FALSE;

	if( ReadFM24CL64(OIL_DENSITY_ADDR,(uint8 *)sDensity, sizeof(stcDensity)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(stcDensity) - 2);
		
		if((CrcCheck == sDensity->CrcCheck))
		{		
			if(CrcCheck )
			{
				Flg = TRUE;
				return	Flg;
			}
			else if(sDensity->Density)
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				printfcom0("\r\n读燃油密度校验错误！");
			}
		}
		else
		{
			printfcom0("\r\n读燃油密度校验错误！");
		}
	}
	else
	{
		printfcom0("\r\n读燃油箱密度错误！");
	}
	
	if( ReadFM24CL64(OIL_DENSITY_ADDR + sizeof(stcDensity),(uint8 *)sDensity, sizeof(stcDensity)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(sDensity) - 2);
		
		if((CrcCheck == sDensity->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if(sDensity->Density)
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				printfcom0("\r\n读燃油密度校验错误！");
			}
		}
		else
		{
			printfcom0("\r\n读燃油密度校验错误！");
		}
	}
	else
	{
		printfcom0("\r\n读燃油箱密度错误！");
	}
		
	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	StoreReviseHight(stcReviseHight sReviseHight)
////  功  能 ：存油箱修正高度
//// 入口参数：修正高度变量指针
//// 出口参数：成功，返回1；否则，返回0
////------------------------------------------------------------------------
uint8	StoreReviseHight(stcReviseHight * sReviseHight)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);

	if(CrcCheck == sReviseHight->CrcCheck)
	{
		if(! WriteFM24CL64(OIL_REVISE_HIGHT_ADDR,(uint8 *)sReviseHight, sizeof(stcReviseHight)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}
		
		if(! WriteFM24CL64(OIL_REVISE_HIGHT_ADDR + sizeof(stcReviseHight),(uint8 *)sReviseHight, sizeof(stcReviseHight)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}		
	}	
	else
	{
		printfcom0("\r\n存修正高度校验和错误！");
		Flg = FALSE;
	}

	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  功  能 ：读修正高度值
//// 入口参数：修正高度结构体指针
//// 出口参数：成功：返回1，否则，返回0
////------------------------------------------------------------------------
uint8	ReadReviseHight(stcReviseHight * sReviseHight)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8	Buf[sizeof(stcReviseHight)] = {0};	

	Flg = FALSE;

	if( ReadFM24CL64(OIL_REVISE_HIGHT_ADDR,(uint8 *)sReviseHight, sizeof(stcReviseHight)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
		
		if((CrcCheck == sReviseHight->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sReviseHight,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n读修正高度检验和 %d",CrcCheck);
				return	Flg;
			}
		}
		else
		{
			printfcom0("\r\n读修正高度检验和错误！");
		}
	}
	else
	{
		printfcom0("\r\n读取修正高度错误！");
	}
	
	if( ReadFM24CL64(OIL_REVISE_HIGHT_ADDR + sizeof(stcReviseHight),
									(uint8 *)sReviseHight, sizeof(stcReviseHight)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
		
		if((CrcCheck == sReviseHight->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sReviseHight,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n读修正高度检验和 %d",CrcCheck);
				return	Flg;			
			}					
		}
		else
		{
			printfcom0("\r\n读修正高度检验和错误！");
		}		
	}
	else
	{
		printfcom0("\r\n读取修正高度错误！");
	}	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	StoreReviseHight(stcReviseHight sReviseHight)
////  功  能 ：存油箱修正高度
//// 入口参数：修正高度变量指针
//// 出口参数：成功，返回1；否则，返回0
////------------------------------------------------------------------------
uint8	StoreAddDipVal(stcAddDipVal * sAddDipVal)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);

	if(CrcCheck == sAddDipVal->CrcCheck)
	{
		if(! WriteFM24CL64(ADD_DIP_VAL_ADDR,(uint8 *)sAddDipVal, sizeof(stcReviseHight)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}
		
		if(! WriteFM24CL64(ADD_DIP_VAL_ADDR + sizeof(stcAddDipVal),(uint8 *)sAddDipVal, sizeof(stcAddDipVal)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}		
	}	
	else
	{
		printfcom0("\r\n存油量加校验和错误！");
		Flg = FALSE;
	}

	return	Flg;
}
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  功  能 ：读修正高度值
//// 入口参数：修正高度结构体指针
//// 出口参数：成功：返回1，否则，返回0
////------------------------------------------------------------------------
uint8	ReadAddDipVal(stcAddDipVal * sAddDipVal)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8	Buf[sizeof(stcAddDipVal)] = {0};	

	Flg = FALSE;

	if( ReadFM24CL64(ADD_DIP_VAL_ADDR,(uint8 *)sAddDipVal, sizeof(stcAddDipVal)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
		
		if((CrcCheck == sAddDipVal->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n读增加油量检验和 %d",CrcCheck);
				return	Flg;
			}
		}
		else
		{
			printfcom0("\r\n读读增加油量检验和错误！");
		}
	}
	else
	{
		printfcom0("\r\n读读增加油量错误！");
	}
	
	if( ReadFM24CL64(ADD_DIP_VAL_ADDR + sizeof(stcAddDipVal),
									(uint8 *)sAddDipVal, sizeof(stcAddDipVal)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
		
		if((CrcCheck == sAddDipVal->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n读增加油量检验和 %d",CrcCheck);
				return	Flg;			
			}					
		}
		else
		{
			printfcom0("\r\n读增加油量检验和检验和错误！");
		}		
	}
	else
	{
		printfcom0("\r\n读增加油量检验和错误！");
	}	
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	StoreSelectModel(uint8	ModelNum)
////  功  能 ：存油箱模型选择
//// 入口参数：无
//// 出口参数：无
////------------------------------------------------------------------------
uint8	StoreSelectModel(uint8	ModelNum)
{
	uint16	CrcCheck;
	uint8	Buf[4];
	uint8	Flg;
	
	Flg = TRUE;
	
	Buf[0] = ModelNum;
	Buf[1] = ModelNum;
	
	CrcCheck = GetCrc16Check(Buf,2);

	memcpy(&Buf[2],(uint8	*)&CrcCheck,2);
	
	if(! WriteFM24CL64(SELECT_MODEL_ADDR,Buf, sizeof(Buf)))
	{
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}
	
	if(! WriteFM24CL64(SELECT_MODEL_ADDR + sizeof(Buf),Buf, sizeof(Buf)))
	{
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}		


	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadSelectModel(uint8	ModelNum)
////  功  能 ：存油箱模型选择
//// 入口参数：无
//// 出口参数：无
////------------------------------------------------------------------------
uint8	ReadSelectModel(uint8	*ModelNum)
{
	uint16	CrcCheck;
	uint16	CrcCheckTmp;
	uint8	Buf[4];
	uint8	Flg;
	
	Flg = FALSE;
	
	if( ReadFM24CL64(SELECT_MODEL_ADDR,Buf, sizeof(Buf)))
	{	
		CrcCheckTmp = GetCrc16Check(Buf,2);
		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
		
		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
		{
			*ModelNum = Buf[0];
			
			if(Buf[0])					//不为零
			{
				Flg = TRUE;
				
				return	Flg;
			}
		}
	}

	if( ReadFM24CL64(SELECT_MODEL_ADDR + sizeof(Buf),Buf, sizeof(Buf)))
	{	
		CrcCheckTmp = GetCrc16Check(Buf,2);
		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
		
		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
		{
			*ModelNum = Buf[0];
			
			if(Buf[0])					//不为零
			{
				Flg = TRUE;
				
				return	Flg;
			}
		}
	}
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8 StoreHostStation(stcHostStation  sHostSta)
////  功  能 ：存能耗统计装置出厂信息
//// 入口参数：无
//// 出口参数：存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
uint8 StoreHostInfo(stcDeviceInfo * sDevice)
{
	if(!WriteFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDevice, sizeof(stcDeviceInfo)))
	{
		//printfcom0("\r\n存出厂信息错误!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		return	FALSE;
	}
	return	TRUE;
}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo)
////  功  能 ：	读记录装置出厂信息
//// 入口参数：	无
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8 	Buf[sizeof(stcDeviceInfo)];
	
	Flg = FALSE;
	
	if( ReadFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDeviceInfo, sizeof(stcDeviceInfo)))
	{		
		//PrintfDebug("\r\nReadFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDeviceInfo, sizeof(stcDeviceInfo))");

		CrcCheck = GetCrc16Check((uint8 *)sDeviceInfo,sizeof(stcDeviceInfo) - 2);
		
		//PrintfDebug("\r\nCrcCheck %d,sDeviceInfo->CrcCheck %d",CrcCheck,sDeviceInfo->CrcCheck);

		if((CrcCheck == sDeviceInfo->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
			}
			else if( memcmp( (uint8 *)sDeviceInfo,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
			}
			else
			{
				//printfcom0("\r\n读出厂信息校验错误!");
			}				
		}		
		else
		{
			//printfcom0("\r\n读出厂信息校验错误!");
		}	
	}
	else
	{
		//printfcom0("\r\n读出厂信息错误!");
	}
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8 StoreFixInfo(stcHostStation  sHostSta)
////  功  能 ：存能耗统计装置初装车信息
//// 入口参数：无
//// 出口参数：存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
uint8 StoreFixInfo(stcFixInfo * sFix)
{
	if(!WriteFM24CL64(FIX_INFO_ADDR, (uint8 *)sFix, sizeof(stcFixInfo)))
	{
		printfcom0("\r\nWrite StoreFixInfo Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		return	FALSE;
	}
	 
	return	TRUE;
}
//
////------------------------------------------------------------------------
////  名  称 ：uint8 StoreHostStation(stcHostStation  sHostSta)
////  功  能 ：存能耗统计装置初装车信息
//// 入口参数：无
//// 出口参数：存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
uint8 ReadFixInfo(stcFixInfo * sFix)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8 	Buf[sizeof(stcFixInfo)] = {0};	
	
	Flg = FALSE;
	 
	if( ReadFM24CL64(FIX_INFO_ADDR, (uint8 *)sFix, sizeof(stcFixInfo)))
	{		
		CrcCheck = GetCrc16Check((uint8 *)sFix,sizeof(stcFixInfo) - 2);
		
		if(CrcCheck == (sFix->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
			}
			else if( memcmp( (uint8 *)sFix,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
			}
		}	
		else
		{
			printfcom0("\r\n读装车信息检验错误!");
		}			
	}
	else
	{
		printfcom0("\r\n读装车信息错误!");
	}
	
	return	Flg;
}
//
//uint8	GetFramWriteErrEvtFlg(void)
//{
//	return	l_FramWriteErrEvtFlg;
//}
//
//uint8	GetFramReadErrEvtFlg(void)
//{
//	return	l_FramReadErrEvtFlg;
//}
//
//
//
////-------------------------------------------------------------------------------
////函数名称:        	uint8	JudgeFramEvt(void)
////函数功能:       	判断Flsh事件
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
uint8	JudgeFramEvt(void)
{
//	uint8	EvtType;
//	
//	if((GetFramWriteErrEvtFlg() == RIGHT_DATA) && (GetFramReadErrEvtFlg() == RIGHT_DATA) )
//	{
//		EvtType = RIGHT_DATA;
//	}
//	else if(GetFramWriteErrEvtFlg() == RIGHT_DATA)
//	{
//		EvtType = GetFramReadErrEvtFlg();
//	}
//	else
//	{
//		EvtType = GetFramWriteErrEvtFlg();
//	}
//	
//	return	EvtType;
	return 1;
}
//
#define		FRAM_WRITE_TEST		0xaa55
uint8		mFramWordTestErrFlg;
////-------------------------------------------------------------------------------
////函数名称:        	uint8	JudgeFramWordEvt(void)
////函数功能:       	判断Flsh事件
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
void	TestFramOneWord(void)
{
	uint16	Temp16;
	uint16	TestTmp = FRAM_WRITE_TEST;
	uint16	ReadTmp;

	ReadFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&Temp16, sizeof(Temp16));  	//取数暂存
	
	WriteFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&TestTmp, sizeof(TestTmp));	//写入数年
	
	ReadFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&ReadTmp, sizeof(ReadTmp));  	//取数暂存
	
	WriteFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&Temp16, sizeof(Temp16));		//写入数年
	
	if(ReadTmp == TestTmp)						
	{
		mFramWordTestErrFlg = NO_ERROR;
	}
	else
	{
		mFramWordTestErrFlg = ERROR;
	}
}
//
//-------------------------------------------------------------------------------
//函数名称:        	uint8	GetFramWordTestErrFlg(void)
//函数功能:       	判断Flsh事件
//入口参数:        	无
//出口参数:      	无
//-------------------------------------------------------------------------------
uint8	GetFramWordTestErrFlg(void)
{
	return	mFramWordTestErrFlg;	
}


#define		FRAM_WORD_ERR	37
////-------------------------------------------------------------------------------
////函数名称:        	uint8	JudgeFramWordEvt(void)
////函数功能:       	判断Flsh事件
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
uint8	JudgeFramWordEvt(void)
{
	
	if(GetSysTime() % 60*100 ==1  || GetSysTime() < 60*100)
	{
		TestFramOneWord();
	}

	if(GetFramWordTestErrFlg() == ERROR)
	{
		return	FRAM_WORD_ERR;
	}

	return	RIGHT_DATA;

}

////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreCurFlshRec(uint32  RecNum)
////  功  能 ：	存能耗统计装置记录流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//uint8 StoreCurFlshRec(stcFlshRec * sFlshRec)
//{
//	uint8	Flg;
//	
//	Flg = TRUE;
//
//	if(!WriteFM24CL64(CUR_REC_ADDR, (uint8 *)sFlshRec, sizeof(stcFlshRec)))	//存信息
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\n最新数据记录错误!");
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8 ReadCurFlshRec(stcFlshRec * sFlshRec)
////  功  能 ：读存能耗统计装置记录流水号
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------
//uint8 ReadCurFlshRec(stcFlshRec * sFlshRec)
//{
//	uint8	Flg;
//	uint16	CrcCheck;
//
//	
//	Flg = TRUE;
//
//	if(!ReadFM24CL64(CUR_REC_ADDR, (uint8 *)sFlshRec, sizeof(stcFlshRec)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nRead ReadCurFlshRec Error!");
//	}
//	else
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sFlshRec,sizeof(stcFlshRec) - 2);
//		
//		if(CrcCheck != (sFlshRec->CrcCheck) || CrcCheck == 0 )
//		{
//			//sFlshRec = 0;
//			Flg = 	FALSE;
//			printfcom0("\r\n最后一次存的FLASE的CRC错误！");
//		}	
//	}
//	
// 	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreCurFlshRec(uint32  RecNum)
////  功  能 ：	存能耗统计装置记录流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//uint8 StoreLogZone(stcLogZone * sLogZone)
//{
//
//	uint8	Flg;
///*	
//	Flg = TRUE;
//
//	if(!WriteFM24CL64(LOG_INFO_ADDR, (uint8 *)sLogZone, sizeof(stcLogZone)))	//存信息
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nStoreLogZone Error!");
//	}
//*/	
//	return	Flg;
//
//}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreCurFlshRec(uint32  RecNum)
////  功  能 ：	存能耗统计装置记录流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//uint8 ReadLogZone(stcLogZone * sLogZone)
//{
//	uint8	Flg;
//	
//	Flg = TRUE;
//
//	if(!ReadFM24CL64(LOG_INFO_ADDR, (uint8 *)sLogZone, sizeof(stcLogZone)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nReadLogZone Error!");
//	}
//	
// 	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadDebugCardInfo(stcDebugCard *sDebugCard)
////  功  能 ：读出铁电调试信息
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------
//uint8	StoreDebugCardInfo(stcDebugCard *sDebugCard)
//{
//	uint8	Flg = 	TRUE;
//
//	if(!WriteFM24CL64(DEBUG_INFO_ADDR, (uint8 *)sDebugCard, sizeof(stcDebugCard)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nGetDebugCardInfo");
//	}	
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadDebugCardInfo(stcDebugCard *sDebugCard)
////  功  能 ：读出铁电调试信息
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------
//uint8	ReadDebugCardInfo(stcDebugCard *sDebugCard)
//{
//	uint8	Flg = 	TRUE;
//	uint16	CrcCheck;
//
//	if(!ReadFM24CL64(DEBUG_INFO_ADDR, (uint8 *)sDebugCard, sizeof(stcDebugCard)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nGetDebugCardInfo ERR!");
//	}	
//	else
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sDebugCard,sizeof(stcDebugCard) - 2);
//		
//		if(CrcCheck != sDebugCard->CrcCheck)
//		{
//			Flg = 	FALSE;
//		
//			printfcom0("\r\n读调试卡信息校验失败！");		
//		}
//	}
//	
//	return	Flg;
//}
//
//
//extern	uint32 ReadCurFlshRecNum_Flsh(void);
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshRecNum(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
uint32 GetCurFlshRecNum(void)
{
	uint32		CurFlshRecNum = 0;
	 
	CurFlshRecNum = ReadCurFlshRecNum();

	return 	CurFlshRecNum;
}
//
