////#include 	"config.h"   
////#include 	"string.h"   
////#include	"Globe.h"
////#include	"CpuDrive.h"
////#include	"HardDrive.h"
//
//#include <includes.h>
//#include "FRAM.h"
////------------------------------------------------------------------------
////  名  称 ：	uint8 StoreCurFlashRecNum(uint32  RecNum)
////  功  能 ：	存能耗统计装置记录流水号
//// 入口参数：	当前记录流水号
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//void StoreFramToFlsh(void)
//{
////	static	uint8	Buf[128];
////	uint32	i;
////	
////	UnProtectFlash();
////	
////	printfcom0("\r\n 刷新FLsh保护区!");
////
////	for(i = 0;i < FRAM_SIZE ;)
////	{
////		//SysFastHoldTast();
////		
////		ReadFM24CL64(i,Buf,128);
////		WriteFlsh(i,(uint16 *)Buf,128);
////		i+=128;
////	}
////	
////	ProtectFlash();
//}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8 	ReadCurFlshRecNum(void)
////  功  能 ：	读当前记录装置记录流水号
//// 入口参数：	无
//// 出口参数：	当前流水号
////------------------------------------------------------------------------
//uint32 ReadCurFlshRecNum_Flsh(void)
//{
//	uint16	CrcCheck;
//	uint8	Buf[6];
//	uint32	FlshRecNum = 0;
//
//	if(!ReadFlsh(CUR_FLSH_REC_NUM, (uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n 取Flsh读当前流水号错误!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//			
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh读当前流水号校验错误！");
//			//l_FramReadErrEvtFlg = FRAM_ERR_EVT;
//		}
//	}
//
//	if(!ReadFlsh(CUR_FLSH_REC_NUM + sizeof(Buf), (uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n 取Flsh读当前流水号备份错误!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh当前流水号备份校验错误！");
//			//l_FramReadErrEvtFlg = FRAM_ERR_EVT;
//		}		
//	}
// 	
// 	return	FlshRecNum;
//}
//
////------------------------------------------------------------------------
////  名  称 ：	uint32 ReadLstRedFlshRecNum(void)
////  功  能 ：	读存能耗统计装置上次写记录流水号
//// 入口参数：	无
//// 出口参数：	最后写卡的记录流水号
////------------------------------------------------------------------------
//uint32 ReadLstRedFlshRecNum_Flsh(void)
//{
//	uint16	CrcCheck;
//	uint8	Buf[6];
//	uint32	FlshRecNum = 0;
//
//	if(!ReadFlsh(LST_RED_FLSH_REC_NUM, (uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n 取Flsh读最后一次写卡流水号错误!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//	
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh最后一次写卡流水号校验错误！");
//		}			
//	}
//
//	if(!ReadFlsh(LST_RED_FLSH_REC_NUM + sizeof(Buf),(uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n 取Flsh读最后一次写卡流水号错误!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//			
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh最后一次写卡流水号校验错误！");
//		}			
//	}
// 	
// 	return	FlshRecNum;
//}
//
//
////------------------------------------------------------------------------
////  名  称 ：uint32 ReadOilBoxModel(stcModel sModel)
////  功  能 ：存油箱模型
//// 入口参数：无
//// 出口参数：当前流水号
////------------------------------------------------------------------------
//uint8	ReadOilBoxModel_Flsh(stcModelCard * sModelCard)
//{
////	uint16	CrcCheck;
////	uint16	Flg;
////	static	uint8	Buf[sizeof(stcModelCard)] = {0};
////
////	Flg = FALSE;
////
////	if( ReadFlsh(OIL_BOX_MODEL_ADDR,(uint16 *)sModelCard, sizeof(stcModelCard)))
////	{
////		CrcCheck = GetCrc16Check((uint8 *)sModelCard,sizeof(stcModelCard) - 2);
////		
////		if((CrcCheck == sModelCard->CrcCheck))
////		{
////			if(CrcCheck)
////			{
////				printfcom0("\r\n 取Flsh中的油尺模型成功！");
////
////				Flg = TRUE;
////			}
////			else if( memcmp( (uint8 *)sModelCard,Buf,sizeof(Buf)))
////			{
////				printfcom0("\r\n 取Flsh中的油尺模型失败！");
////			
////				Flg = TRUE;
////			}
////		}
////	}
////
////	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadDensity(stcDensity * sDensity)
////  功  能 ：读燃油密度错误
//// 入口参数：燃油密度指针
//// 出口参数：操作成功：返回1；否则，返回0
////------------------------------------------------------------------------
//uint8	ReadDensity_Flsh(stcDensity * sDensity)
//{
////	uint16	CrcCheck;
////	uint16	Flg;
////	static	uint8	Buf[sizeof(stcDensity)] = {0};
////
////	Flg = FALSE;
////
////	if( ReadFlsh(OIL_DENSITY_ADDR,(uint16 *)sDensity, sizeof(stcDensity)))
////	{
////		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(stcDensity) - 2);
////		
////		if((CrcCheck == sDensity->CrcCheck))
////		{		
////			if(CrcCheck)
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n 取Flsh中的密度成功！");
////
////				return	Flg;
////			}
////			else if( memcmp( (uint8 *)sDensity,Buf,sizeof(Buf)))
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n 取Flsh中的密度成功！");
////				return	Flg;
////			}
////			else
////			{
////				printfcom0("\r\n 取Flsh读燃油密度校验错误！");
////			}
////		}
////		else
////		{
////			printfcom0("\r\n 取Flsh读燃油密度校验错误！");
////		}
////	}
////	else
////	{
////		printfcom0("\r\n  取Flsh读燃油箱密度错误！");
////	}
////	
////	if( ReadFlsh(OIL_DENSITY_ADDR + sizeof(stcDensity),(uint16 *)sDensity, sizeof(stcDensity)))
////	{
////		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(sDensity) - 2);
////		
////		if((CrcCheck == sDensity->CrcCheck))
////		{
////			if(CrcCheck)
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n 取Flsh中的密度成功！");
////
////				return	Flg;
////			}
////			else if( memcmp( (uint8 *)sDensity,Buf,sizeof(Buf)))
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n 取Flsh中的密度成功！");
////
////				return	Flg;				
////			}
////			else
////			{
////				printfcom0("\r\n 取Flsh读燃油密度校验错误！");
////			}
////		}
////		else
////		{
////			printfcom0("\r\n 取Flsh读燃油密度校验错误！");
////		}
////	}
////	else
////	{
////		printfcom0("\r\n 取Flsh读燃油箱密度错误！");
////	}
////		
////	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  功  能 ：读修正高度值
//// 入口参数：修正高度结构体指针
//// 出口参数：成功：返回1，否则，返回0
////------------------------------------------------------------------------
//uint8	ReadReviseHight_Flsh(stcReviseHight * sReviseHight)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	uint8	Buf[sizeof(stcReviseHight)] = {0};	
//
//	Flg = FALSE;
//
//	if( ReadFlsh(OIL_REVISE_HIGHT_ADDR,(uint16 *)sReviseHight, sizeof(stcReviseHight)))
//	{
//		
//		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
//		
//		if((CrcCheck == sReviseHight->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n 取Flsh中的高度成功！");
//				return	Flg;
//			}
//			else if( memcmp( (uint8 *)sReviseHight,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n 取Flsh中的高度成功！");
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n  取Flsh读修正高度检验和 %d",CrcCheck);
//				return	Flg;
//			}
//		}
//		else
//		{
//			printfcom0("\r\n  取Flsh读修正高度检验和错误！");
//		}
//	}
//	else
//	{
//		printfcom0("\r\n  取Flsh读取修正高度错误！");
//	}
//	
//	if( ReadFlsh(OIL_REVISE_HIGHT_ADDR + sizeof(stcReviseHight),
//									(uint16 *)sReviseHight, sizeof(stcReviseHight)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
//		
//		if((CrcCheck == sReviseHight->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n 取Flsh中的高度成功！");
//
//				return	Flg;
//			}
//			else if( memcmp( (uint16 *)sReviseHight,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n 取Flsh中的高度成功！");
//				
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n 取Flsh读修正高度检验和 %d",CrcCheck);
//				return	Flg;			
//			}					
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh读修正高度检验和错误！");
//		}		
//	}
//	else
//	{
//		printfcom0("\r\n 取Flsh读取修正高度错误！");
//	}	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  功  能 ：读修正高度值
//// 入口参数：修正高度结构体指针
//// 出口参数：成功：返回1，否则，返回0
////------------------------------------------------------------------------
//uint8	ReadAddDipVal_Flsh(stcAddDipVal * sAddDipVal)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	static	uint8	Buf[sizeof(stcAddDipVal)] = {0};	
//
//	Flg = FALSE;
//
//	if( ReadFlsh(ADD_DIP_VAL_ADDR,(uint16 *)sAddDipVal, sizeof(stcAddDipVal)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
//		
//		if((CrcCheck == sAddDipVal->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n 取Flsh读增加油量检验和 %d",CrcCheck);
//				return	Flg;
//			}
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh读读增加油量检验和错误！");
//		}
//	}
//	else
//	{
//		printfcom0("\r\n 取Flsh读读增加油量错误！");
//	}
//	
//	if( ReadFlsh(ADD_DIP_VAL_ADDR + sizeof(stcAddDipVal),
//									(uint16 *)sAddDipVal, sizeof(stcAddDipVal)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
//		
//		if((CrcCheck == sAddDipVal->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n 取Flsh读增加油量检验和 %d",CrcCheck);
//				return	Flg;			
//			}					
//		}
//		else
//		{
//			printfcom0("\r\n 取Flsh读增加油量检验和检验和错误！");
//		}		
//	}
//	else
//	{
//		printfcom0("\r\n 取Flsh读增加油量检验和错误！");
//	}	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8	ReadSelectModel(uint8	ModelNum)
////  功  能 ：存油箱模型选择
//// 入口参数：无
//// 出口参数：无
////------------------------------------------------------------------------
//uint8	ReadSelectModel_Flsh(uint8	*ModelNum)
//{
//	uint16	CrcCheck;
//	uint16	CrcCheckTmp;
//	uint8	Buf[4];
//	uint8	Flg;
//	
//	Flg = FALSE;
//	
//	if( ReadFlsh(SELECT_MODEL_ADDR,(uint16 *)Buf, sizeof(Buf)))
//	{	
//		
//		CrcCheckTmp = GetCrc16Check(Buf,2);
//		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
//		
//		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
//		{
//			*ModelNum = Buf[0];
//			
//			if(Buf[0])					//不为零
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n 取Flsh中的油尺模型编号成功！");
//
//				return	Flg;
//			}
//		}
//	}
//
//	if( ReadFlsh(SELECT_MODEL_ADDR + sizeof(Buf),(uint16 *)Buf, sizeof(Buf)))
//	{	
//		CrcCheckTmp = GetCrc16Check(Buf,2);
//		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
//		
//		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
//		{
//			*ModelNum = Buf[0];
//			
//			if(Buf[0])					//不为零
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n 取Flsh中的油尺模型编号成功！");
//	
//				return	Flg;
//			}
//		}
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：	uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo)
////  功  能 ：	读记录装置出厂信息
//// 入口参数：	无
//// 出口参数：	存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//uint8	ReadHostInfo_Flsh(stcDeviceInfo * sDeviceInfo)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	static	uint8 	Buf[sizeof(stcDeviceInfo)];
//	
//	Flg = FALSE;
//	
//	if( ReadFlsh(HOST_DEVICE_INFO_ADDR, (uint16 *)sDeviceInfo, sizeof(stcDeviceInfo)))
//	{		
//		//PrintfDebug("\r\nReadFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDeviceInfo, sizeof(stcDeviceInfo))");
//
//		CrcCheck = GetCrc16Check((uint8 *)sDeviceInfo,sizeof(stcDeviceInfo) - 2);
//		
//		//PrintfDebug("\r\nCrcCheck %d,sDeviceInfo->CrcCheck %d",CrcCheck,sDeviceInfo->CrcCheck);
//
//		if((CrcCheck == sDeviceInfo->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//			}
//			else if( memcmp( (uint8 *)sDeviceInfo,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//			}
//			else
//			{
//				printfcom0("\r\n 取Flsh读出厂信息校验错误!");
//			}				
//		}		
//		else
//		{
//			printfcom0("\r\n 取Flsh读出厂信息校验错误!");
//		}	
//	}
//	else
//	{
//		printfcom0("\r\n 取Flsh读出厂信息错误!");
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  名  称 ：uint8 StoreHostStation(stcHostStation  sHostSta)
////  功  能 ：存能耗统计装置初装车信息
//// 入口参数：无
//// 出口参数：存成功,返回TRUE,否则,返回FALSE
////------------------------------------------------------------------------
//uint8 ReadFixInfo_Flsh(stcFixInfo * sFix)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	static	uint8 	Buf[sizeof(stcFixInfo)] = {0};	
//	
//	Flg = FALSE;
//	 
//	if( ReadFlsh(FIX_INFO_ADDR, (uint16 *)sFix, sizeof(stcFixInfo)))
//	{		
//		CrcCheck = GetCrc16Check((uint8 *)sFix,sizeof(stcFixInfo) - 2);
//		
//		if(CrcCheck == (sFix->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//			}
//			else if( memcmp( (uint8 *)sFix,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//			}
//		}	
//		else
//		{
//			printfcom0("\r\n 取Flsh读装车信息检验错误!");
//		}			
//	}
//	else
//	{
//		printfcom0("\r\n 取Flsh读装车信息错误!");
//	}
//	
//	return	Flg;
//}
//
