////#include    "config.h" 
////#include    "stdlib.h"
////#include    "string.h"
////#include    "Globe.h"
////#include    "CpuDrive.h"
////#include    "HardDrive.h"
////#include    "OperateCard.h"
////#include    "FramStore.h"
//
#include <includes.h>
#include "FRAM.h"


#define     MODEL_SEL0          10//P010
#define     MODEL_SEL1          11//P011
#define     MODEL_SEL2          12//P012
#define     MODEL_SEL3          13//P013
#define     MODEL_SEL4          15//P015
#define     MODEL_SEL5          20//P020


// 
////定义油箱和车型对照关系   20120110
//
///////////////////////////////////////
//
//
////定义油箱和车型对照关系
//static	stcLocoModNum sLocoModNumBuf[64];
//#define LOCO_MOD_TYP_NUM	64
////------------------------------------------------------------------------
////名    称：    void IniLocoModTab(void)
////功    能：    初始化机车车型与油箱模型对照表
////入口参数：    无
////出口参数：    无
////------------------------------------------------------------------------
//void IniLocoModTab(void)
//{
//	uint8	i;
//	for(i = 0; i < LOCO_MOD_TYP_NUM;i++)					//初始化油箱模型编号
//	{
//		//SysFastHoldTast();
//
//		sLocoModNumBuf[i].ModeNum = i;
//		
//		switch (sLocoModNumBuf[i].ModeNum)
//		{
//			case 1:	sLocoModNumBuf[i].LocoType = 141;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF4D"); break;
//			case 2:	sLocoModNumBuf[i].LocoType = 104;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF4B"); break;
//			case 3:	sLocoModNumBuf[i].LocoType = 142;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF8B"); break;
//			case 4:	sLocoModNumBuf[i].LocoType = 131;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF7C"); break;
//			case 5:	sLocoModNumBuf[i].LocoType = 107;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF5"); break;
//			case 6:	sLocoModNumBuf[i].LocoType = 138;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF11"); break;
//			case 7:	sLocoModNumBuf[i].LocoType = 111;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF8"); break;
//		  //case 8:	sLocoModNumBuf[i].LocoType = 141;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"DF4D"); break;
//			
//			case 30:sLocoModNumBuf[i].LocoType = 161;strcpy((int8 *)sLocoModNumBuf[i].LocoStr,"HXN5"); break;
//			
//		}
//	}
//}
//
//
////------------------------------------------------------------------------
////名    称：    uin8 GetLocoModInfo(uint32	LocoTyp,uint32 ModeNum;stcLocoModNum *sLocoModNum)
////功    能：    根据输入的车型或机车油箱模型编号查找对应的信息
////入口参数：    车型代码，模型模型代码，反回车型数据
////出口参数：    操作是否成功
////------------------------------------------------------------------------
//uint8 GetLocoModInfo(uint32	LocoTyp,uint32 ModeNum,stcLocoModNum *sLocoModNum)
//{
//	uint8 	i;
//	uint8	Flg = FALSE;
//	
//	if( LocoTyp != 0)
//	{
//		for(i = 0; i < LOCO_MOD_TYP_NUM;i++)
//		{
//			//SysFastHoldTast();
//
//			if(sLocoModNumBuf[i].LocoType == LocoTyp)
//			{
//				printfcom0("\r\nLocoTyp %d,%d",LocoTyp,i);
//
//				memcpy((uint8 *)sLocoModNum,(uint8 *)&sLocoModNumBuf[i],sizeof(sLocoModNumBuf[i]));	//8888888
//				Flg = TRUE;
//			}
//		}
//	}
//	else if(ModeNum != 0)
//	{
//		for(i = 0; i < LOCO_MOD_TYP_NUM;i++)
//		{
//			//SysFastHoldTast();
//
//			if(sLocoModNumBuf[i].ModeNum == ModeNum)
//			{
//				printfcom0("\r\nModeNum %d,%d",ModeNum,i);
//
//				memcpy((uint8 *)sLocoModNum,(uint8 *)&sLocoModNumBuf[i],sizeof(sLocoModNumBuf[i]));	//8888888
//				Flg = TRUE;
//			}
//		}	
//	}
//	else
//	{
//		;
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////名    称：    uint8 ReadOilBoxCod(void)
////功    能：    取油箱模型设置代码
////入口参数：    无
////出口参数：    油尺的油箱模型代码
////------------------------------------------------------------------------
//uint8 ReadOilBoxCod(void)
//{
//    uint8 BoxModelCode = 0;
//    
//    IO0DIR_IN(MODEL_SEL0);    
//    IO0DIR_IN(MODEL_SEL1);    
//    IO0DIR_IN(MODEL_SEL2);    
//    IO0DIR_IN(MODEL_SEL3);    
//    IO0DIR_IN(MODEL_SEL4);    
//    //IO0DIR_IN(MODEL_SEL5);    
//    
//    BoxModelCode =  (IO0PIN_R(MODEL_SEL0) << 0)     |
//                    (IO0PIN_R(MODEL_SEL1) << 1)     |
//                    (IO0PIN_R(MODEL_SEL2) << 2)     |
//                    (IO0PIN_R(MODEL_SEL3) << 3)     |
//                    (IO0PIN_R(MODEL_SEL4) << 4)     ;
//                    //(IO0PIN_R(MODEL_SEL5) << 5);
//            		
//    //BoxModelCode = 0x3f -  BoxModelCode;    
//    BoxModelCode = 0x1f -  BoxModelCode;    
//        
//    return  BoxModelCode;
//}
//
#define     DF4D    1
#define     DF4B    2
#define     DF8B    3
#define     DF7C    4
#define     DF5     5
#define     DF11    6
#define     DF8     7
#define     DF7X    8
#define     DF7G60 	9
#define     DF7G80  10
#define     DF7G20  11
#define     DF7G50  12
#define     DF12G40 13
#define     DF12G50 14
#define     DF12G17 15
#define     DF5G20 	16
#define     DF57G5675 	17
//
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf4bOilBoxModel(void)
////功    能：    DF4b油箱模型
////入口参数：    无
////出口参数：    DF4b的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf4bOilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 2500;   
//    
//    sModel->sModPot[1].HigVal = 622;
//    sModel->sModPot[1].DipVal = 3400;   
//    
//    sModel->sModPot[2].HigVal = 6239;
//    sModel->sModPot[2].DipVal = 8700;   
//    
//    sModel->PotNum  = 3;
//
//    sModel->ModelNum    = DF4B;
//    
//    sModel->StartHight= 35;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf7xOilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 800;   
//    
//    sModel->sModPot[1].HigVal = 630;
//    sModel->sModPot[1].DipVal = 1500;   
//    
//    sModel->sModPot[2].HigVal = 1430;
//    sModel->sModPot[2].DipVal = 2500;   
//    
//    sModel->sModPot[3].HigVal = 1570;
//    sModel->sModPot[3].DipVal = 2600;       
//    
//    sModel->sModPot[4].HigVal = 2250;
//    sModel->sModPot[4].DipVal = 3000;       
//    
//    sModel->sModPot[5].HigVal = 7850;
//    sModel->sModPot[5].DipVal = 6400;       
//        
//    sModel->PotNum  = 6;
//
//    sModel->ModelNum    = DF7X;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf7G80OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 80;
//    sModel->sModPot[0].DipVal = 2000;   
//    
//    sModel->sModPot[1].HigVal = 1180;
//    sModel->sModPot[1].DipVal = 3100;   
//    
//    sModel->sModPot[2].HigVal = 1310;
//    sModel->sModPot[2].DipVal = 3200;   
//    
//    sModel->sModPot[3].HigVal = 1511;
//    sModel->sModPot[3].DipVal = 3300;       
//    
//    sModel->sModPot[4].HigVal = 7209;
//    sModel->sModPot[4].DipVal = 6000;       
//        
//    sModel->PotNum  = 5;
//
//    sModel->ModelNum    = DF7G80;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf7G60OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 2500;   
//    
//    sModel->sModPot[1].HigVal = 7400;
//    sModel->sModPot[1].DipVal = 6200;
//    
////    sModel->sModPot[2].HigVal = 1310;
////    sModel->sModPot[2].DipVal = 3200;   
//    
////    sModel->sModPot[3].HigVal = 1511;
////    sModel->sModPot[3].DipVal = 3300;       
//    
////    sModel->sModPot[4].HigVal = 7209;
////    sModel->sModPot[4].DipVal = 6000;       
//        
//    sModel->PotNum  = 2;
//
//    sModel->ModelNum    = DF7G60;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf7G20OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 800;   
//    
//    sModel->sModPot[1].HigVal = 720;
//    sModel->sModPot[1].DipVal = 1600; 
//    
//    sModel->sModPot[2].HigVal = 1440;
//    sModel->sModPot[2].DipVal = 2500;   
//    
//    sModel->sModPot[3].HigVal = 1580;
//    sModel->sModPot[3].DipVal = 2600;       
//    
//    sModel->sModPot[4].HigVal = 6365;
//    sModel->sModPot[4].DipVal = 5500;       
//    
//    sModel->sModPot[5].HigVal = 7709;
//    sModel->sModPot[5].DipVal = 6300;       
//        
//    sModel->PotNum  = 6;
//
//    sModel->ModelNum    = DF7G20;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf7G50OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 700;   
//    
//    sModel->sModPot[1].HigVal = 1150;
//    sModel->sModPot[1].DipVal = 1700; 
//    
//    sModel->sModPot[2].HigVal = 2690;
//    sModel->sModPot[2].DipVal = 3100;   
//    
//    sModel->sModPot[3].HigVal = 7650;
//    sModel->sModPot[3].DipVal = 6200;       
//    
//    sModel->PotNum  = 4;
//
//    sModel->ModelNum    = DF7G50;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf12G50OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 2200;   
//    
//    sModel->sModPot[1].HigVal = 330;
//    sModel->sModPot[1].DipVal = 2400; 
//    
//    sModel->sModPot[2].HigVal = 550;
//    sModel->sModPot[2].DipVal = 2600;   
//    
//    sModel->sModPot[3].HigVal = 2000;
//    sModel->sModPot[3].DipVal = 3600;             
//    
//    sModel->sModPot[4].HigVal = 2220;
//    sModel->sModPot[4].DipVal = 3800;   
//    
//    sModel->sModPot[5].HigVal = 2520;
//    sModel->sModPot[5].DipVal = 4000; 
//    
//    sModel->sModPot[6].HigVal = 2840;
//    sModel->sModPot[6].DipVal = 4200;   
//    
//    sModel->sModPot[7].HigVal = 4580;
//    sModel->sModPot[7].DipVal = 5400;  
//    
//    sModel->sModPot[8].HigVal = 4850;
//    sModel->sModPot[8].DipVal = 5600;   
//    
//    sModel->sModPot[9].HigVal = 5450;
//    sModel->sModPot[9].DipVal = 6000;  
//              
//    sModel->PotNum  = 10;
//
//    sModel->ModelNum    = DF12G50;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf12G40OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 1600;   
//    
//    sModel->sModPot[1].HigVal = 440;
//    sModel->sModPot[1].DipVal = 2000; 
//    
//    sModel->sModPot[2].HigVal = 1030;
//    sModel->sModPot[2].DipVal = 2500;   
//    
//    sModel->sModPot[3].HigVal = 5830;
//    sModel->sModPot[3].DipVal = 6500;             
//        
//    sModel->PotNum  = 4;
//
//    sModel->ModelNum    = DF12G40;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf12G17OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 2300-500;  //20121210  
//    
//    sModel->sModPot[1].HigVal = 5434;
//    sModel->sModPot[1].DipVal = 6100-500;          
//        
//    sModel->PotNum  = 2;
//
//    sModel->ModelNum    = DF12G17;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf5G20OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 1100;   
//    
//    sModel->sModPot[1].HigVal = 2806;
//    sModel->sModPot[1].DipVal = 3400;          
//
//    sModel->sModPot[2].HigVal = 6656;
//    sModel->sModPot[2].DipVal = 5600;
//            
//    sModel->PotNum  = 3;
//
//    sModel->ModelNum    = DF5G20;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
//
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf7xOilBoxModel(void)
////功    能：    DF7x油箱模型
////入口参数：    无
////出口参数：    DF7x的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf7C5675OilBoxModel(stcModel * sModel)
{
//    uint16      CrcCheck;
//    
//    sModel->sModPot[0].HigVal = 0;
//    sModel->sModPot[0].DipVal = 700;   
//    
//    sModel->sModPot[1].HigVal = 736;
//    sModel->sModPot[1].DipVal = 1500;          
//
//    sModel->sModPot[2].HigVal = 1556;
//    sModel->sModPot[2].DipVal = 2500;
//            
//    sModel->sModPot[3].HigVal = 7952;
//    sModel->sModPot[3].DipVal = 6400;
//    
//    sModel->PotNum  = 4;
//
//    sModel->ModelNum    = DF57G5675;
//    
//    sModel->StartHight= 0;
//        
//    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
//    
//    sModel->CrcCheck= CrcCheck;
//    
    return  1;
}
////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf11OilBoxModel(void)
////功    能：    DF11油箱模型
////入口参数：    无
////出口参数：    DF11的油箱模型
////------------------------------------------------------------------------------
//uint8    GetDf11OilBoxModel(stcModel * sModel)
//{
////    uint16      CrcCheck;
////    
////    sModel->sModPot[0].HigVal = 0;
////    sModel->sModPot[0].DipVal = 2200;   
////    
////    sModel->sModPot[1].HigVal = 100;
////    sModel->sModPot[1].DipVal = 2300;   
////    
////    sModel->sModPot[2].HigVal = 195;
////    sModel->sModPot[2].DipVal = 2400;         
////    
////    sModel->sModPot[3].HigVal = 310;
////    sModel->sModPot[3].DipVal = 2500;
////    
////    sModel->sModPot[4].HigVal = 5590;
////    sModel->sModPot[4].DipVal = 6500;    
////               
////    sModel->PotNum      = 5;
////
////    sModel->ModelNum    = DF11;
////    
////    sModel->StartHight= 35;
////        
////    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
////    
////    sModel->CrcCheck= CrcCheck;
////    
////    return  1;
//}

////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf8OilBoxModel(void)
////功    能：    DF8油箱模型
////入口参数：    无
////出口参数：    DF8的油箱模型
////------------------------------------------------------------------------------
//uint8    GetDf8OilBoxModel(stcModel * sModel)
//{
////    uint16      CrcCheck;
////    
////    sModel->sModPot[0].HigVal = 0;
////    sModel->sModPot[0].DipVal = 2500;   
////    
////    sModel->sModPot[1].HigVal = 350;
////    sModel->sModPot[1].DipVal = 2900;   
////    
////    sModel->sModPot[2].HigVal = 5654;
////    sModel->sModPot[2].DipVal = 8000;         
////        
////    sModel->PotNum      = 3;
////
////    sModel->ModelNum    = DF8;
////    
////    sModel->StartHight= 35;
////        
////    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
////    
////    sModel->CrcCheck= CrcCheck;
////    
////    return  1;
//}

////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf8bOilBoxModel(void)
////功    能：    DF8b油箱模型
////入口参数：    无
////出口参数：    DF8b的油箱模型
////------------------------------------------------------------------------------
//uint8    GetDf8bOilBoxModel(stcModel * sModel)
//{
////    uint16      CrcCheck;
////    
////    sModel->sModPot[0].HigVal = 0;
////    sModel->sModPot[0].DipVal = 2500;   
////    
////    sModel->sModPot[1].HigVal = 487;
////    sModel->sModPot[1].DipVal = 3100;   
////    
////    sModel->sModPot[2].HigVal = 6201;
////    sModel->sModPot[2].DipVal = 9000;   
////    
////    sModel->PotNum  	= 3;
////
////    sModel->ModelNum    = DF8B;
////    
////    sModel->StartHight= 35;
////        
////    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
////    
////    sModel->CrcCheck= CrcCheck;
////    
////    return  1;
//}

//////------------------------------------------------------------------------------
//////名    称：    stcModel    GetDf7cOilBoxModel(void)
//////功    能：    Df7c油箱模型
//////入口参数：    无
//////出口参数：    Df7c的油箱模型
//////------------------------------------------------------------------------------
//uint8    GetDf7cOilBoxModel(stcModel * sModel)
//{
////    uint16      CrcCheck;
////    
////    sModel->sModPot[0].HigVal = 0;
////    sModel->sModPot[0].DipVal = 600;    
////    
////    sModel->sModPot[1].HigVal = 2330;
////    sModel->sModPot[1].DipVal = 2500;   
////    
////    sModel->sModPot[2].HigVal = 6030;
////    sModel->sModPot[2].DipVal = 5000;   
////    
////    sModel->PotNum  = 3;
////
////    sModel->ModelNum    = DF7C; 
////    
////    sModel->StartHight= 170;
////        
////    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
////    
////    sModel->CrcCheck= CrcCheck;
////    
////    return  1;
//}

////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf4dOilBoxModel(void)
////功    能：    Df4d油箱模型
////入口参数：    无
////出口参数：    Df4d的油箱模型
////------------------------------------------------------------------------------
uint8    GetDf4dOilBoxModel(stcModel * sModel)
{
    uint16      CrcCheck;
    
    sModel->sModPot[0].HigVal = 0;
    sModel->sModPot[0].DipVal = 1200;   
    
    sModel->sModPot[1].HigVal = 1558;
    sModel->sModPot[1].DipVal = 3400;   
    
    sModel->sModPot[2].HigVal = 7529;
    sModel->sModPot[2].DipVal = 9000;   
    
    sModel->PotNum      = 3;
    
    sModel->ModelNum    = DF4D; 
    
    sModel->StartHight  = 0;
        
    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
    
    sModel->CrcCheck    = CrcCheck;
    
    return  1;
}

////------------------------------------------------------------------------------
////名    称：    stcModel    GetDf5OilBoxModel(void)
////功    能：    Df5油箱模型
////入口参数：    无
////出口参数：    Df5的油箱模型
////------------------------------------------------------------------------------
//uint8   GetDf5OilBoxModel(stcModel * sModel)
//{
////    uint16      CrcCheck;
////    
////    sModel->sModPot[0].HigVal = 0;
////    sModel->sModPot[0].DipVal = 600;    
////    
////    sModel->sModPot[1].HigVal = 3420;
////    sModel->sModPot[1].DipVal = 3400;   
////    
////    sModel->sModPot[2].HigVal = 9220;
////    sModel->sModPot[2].DipVal = 6700;   
////    
////    sModel->PotNum  = 3;
////
////    sModel->ModelNum    = DF5;
////    
////    sModel->StartHight= 260;
////        
////    CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
////    
////    sModel->CrcCheck= CrcCheck;
////    
////    return  1;
//}

uint8		l_SelModelErrFlg 		= NO_ERROR;		//模型设置故障
//extern	uint8 GetLocoModInfo(uint32	LocoTyp,uint32 ModeNum,stcLocoModNum *sLocoModNum);
//extern	uint8 ReadFixInfo_Flsh(stcFixInfo * sFix);
//extern	uint8	ReadSelectModel_Flsh(uint8	*ModelNum);
////------------------------------------------------------------------------------
////名    称：    uint8   GetOilBoxCod(void)
////功    能：    取油箱模型号
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
uint8   GetOilBoxCod(void)
{
    uint8      		OilBoxTypCod = 1;                                   	//装车信息
	
	l_SelModelErrFlg = ERROR;	
	
    if(ReadSelectModel( (uint8 *)&OilBoxTypCod))					//读取设置的油量模型编号
    {                                               				//读卡调试信息    	
        if(OilBoxTypCod > 63 || OilBoxTypCod == 0) 					//设置错误，采用默认的油箱模型1
    	{
            OilBoxTypCod = 1;
    	}
    	else
    	{
    		l_SelModelErrFlg 		= NO_ERROR;
    	}
    }
	else
	{
		OilBoxTypCod = 1;	
	}
   
    return	OilBoxTypCod;
}
//
//uint8	GetSelModelErrFlg(void)
//{
//	return l_SelModelErrFlg;
//}
//
//
#define			DF4_MODLE		2
//
////------------------------------------------------------------------------------
////名    称：    void   stcModelTostcModelComplex(stcModelComplex * sComplexModel,stcModel	* sModel)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
void   stcModelTostcModelComplex(stcModelComplex * sComplexModel,stcModel	* sModel)
{
	uint16		Crc16;
	uint16		StartPointNum;

 	if(sModel->Reserve0 > 5)										//防止Reserve没有赋值
	{		
		sModel->Reserve0 = 0;
	}
	
//	StartPointNum = (sModel->Reserve0)*(sizeof(sModel->sModPot)/sizeof(stcModPot));

//	memcpy((uint8 *)&sComplexModel->sModPot[StartPointNum],(uint8 *)sModel->sModPot,sizeof(sModel->sModPot));
	memcpy((uint8 *)&sComplexModel->sModPot,(uint8 *)sModel->sModPot,sizeof(sModel->sModPot));
//	printfcom0("\r\n sModel->Reserve2220 = %u",sModel->Reserve0);	
///////////////////////////////////////////////////////////////////20120511
//	if(sModel->ModelNum == DF4_MODLE)
//	{
//		if(sComplexModel->sModPot[1].HigVal == 1114 )
//		{
//			sComplexModel->sModPot[1].HigVal = 622;
//		}
//	}
//////////////////////////////////////////////////////////////////	

	sComplexModel->	ModelNum 	= sModel->ModelNum;
	sComplexModel->	PotNum 		= sModel->PotNum;
	sComplexModel->	StartHight 	= sModel->StartHight;
	
	

	Crc16 = GetCrc16Check((uint8 *)sComplexModel,sizeof(stcModelComplex) - 2);
	
	sComplexModel->CrcCheck  	= Crc16;
}	
//
//void   stcModelComplexTostcModel(stcModel	* sModel,stcModelComplex * sComplexModel)
//{
//	uint16		Crc16;
//	uint16		StartPointNum;
//	uint16		pointnum;
//	uint16		i;
//
//// 	if(sModel->Reserve0 > 5)										//防止Reserve没有赋值
////	{		
////		sModel->Reserve0 = 0;
////	}
//	pointnum = sComplexModel-> ModelNum;
//	if(pointnum < 50)	
//	{
//		memcpy((uint8 *)sModel->sModPot,(uint8 *)sComplexModel->sModPot,sizeof(sModel->sModPot));
//	}
//	else
//	{
//		for(i = 0;i<50;i++)	
//		{
//			memcpy((uint8 *)&sModel->sModPot[i],(uint8 *)&sComplexModel->sModPot[],sizeof(sModel->sModPot));
//
//		}
//	}	
//
////	printfcom0("\r\n sModel->Reserve2220 = %u",sModel->Reserve0);	
/////////////////////////////////////////////////////////////////////20120511
////	if(sModel->ModelNum == DF4_MODLE)
////	{
////		if(sComplexModel->sModPot[1].HigVal == 1114 )
////		{
////			sComplexModel->sModPot[1].HigVal = 622;
////		}
////	}
////////////////////////////////////////////////////////////////////	
//
//	sComplexModel->	ModelNum 	= sModel->ModelNum;
//	sComplexModel->	PotNum 		= sModel->PotNum;
//	sComplexModel->	StartHight 	= sModel->StartHight;
//	
//	Crc16 = GetCrc16Check((uint8 *)sComplexModel,sizeof(stcModelComplex) - 2);
//	
//	sComplexModel->CrcCheck  	= Crc16;
//}


////------------------------------------------------------------------------------
////名    称：    void   stcModelTostcModelComplex(stcModelComplex * sComplexModel,stcModel	* sModel)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
void   stcModelSempleTostcModelComplex(stcModelComplex * sComplexModel,stcModelSemple	* sModelSemple)
{
	uint16		Crc16;
	uint16		StartPointNum;
	
	if(sModelSemple->Reserve0 > 25)									//防止Reserve没有赋值	
	{		
		sModelSemple->Reserve0 = 0;
	}
		
	StartPointNum = (sModelSemple->Reserve0)*(sizeof(sModelSemple->sModPot)/sizeof(stcModPot));
	
	memcpy((uint8 *)&sComplexModel->sModPot[StartPointNum],(uint8 *)sModelSemple->sModPot,sizeof(sModelSemple->sModPot));

///////////////////////////////////////////////////////////////////20120511
//if(sModelSemple->PotNum == DF4_MODLE)
//{
//	if(sComplexModel->sModPot[1].HigVal == 1114 )
//	{
//		sComplexModel->sModPot[1].HigVal = 622;
//	}
//}
//////////////////////////////////////////////////////////////////	
	
	sComplexModel->	ModelNum 	= sModelSemple->ModelNum;
	sComplexModel->	PotNum 		= sModelSemple->PotNum;
	sComplexModel->	StartHight 	= sModelSemple->StartHight;
	
	Crc16 = GetCrc16Check((uint8 *)sComplexModel,sizeof(stcModelComplex) - 2);
	
	sComplexModel->CrcCheck  	= Crc16;
}	

////------------------------------------------------------------------------------
////名    称：    void   stcModelComplexTostcModel(stcModel* sComplexModel,stcModelComplex * sModel)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
void   stcModelComplexTostcModel(stcModel* sModel,stcModelComplex * sComplexModel)
{
	uint16		Crc16;

	memcpy((uint8 *)sModel->sModPot,(uint8 *)sComplexModel->sModPot,sizeof(sModel->sModPot));
	
	sModel->ModelNum 	= sComplexModel->ModelNum;
	sModel->PotNum 		= sComplexModel->PotNum;
	sModel->StartHight 	= sComplexModel->StartHight;
	sModel->Reserve0 	= sComplexModel->Reserve0;
	
	Crc16 = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
	
	sModel->CrcCheck  	= Crc16;
}	

////------------------------------------------------------------------------------
////名    称：    void   stcModelComplexTostcModel(stcModel* sComplexModel,stcModelComplex * sModel)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
void   stcModelComplexToMulstcModel(stcModel* sModel,stcModelComplex * sComplexModel,uint16	ReserveNum)
{
	uint16		Crc16;

	memcpy((uint8 *)sModel->sModPot,(uint8 *)&sComplexModel->sModPot[ReserveNum*(sizeof(sModel->sModPot) / sizeof(stcModPot))],sizeof(sModel->sModPot));
	
	sModel->ModelNum 	= sComplexModel->ModelNum;
	sModel->PotNum 		= sComplexModel->PotNum;
	sModel->StartHight 	= sComplexModel->StartHight;
	sModel->Reserve0 	= ReserveNum;
	
	Crc16 = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);
	
	sModel->CrcCheck  	= Crc16;
}	

////------------------------------------------------------------------------------
////名    称：    void   stcModelTostcModelComplex(stcModelComplex * sComplexModel,stcModel	* sModel)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
void   stcModelComplexTostcModelSemple(stcModelSemple * sModelSemple,stcModelComplex	* sComplexModel)
{
//	uint16		Crc16;
//	
//	memcpy((uint8 *)sModelSemple->sModPot,(uint8 *)sComplexModel->sModPot,sizeof(sModelSemple->sModPot));
//	
//	sModelSemple->ModelNum 		= sComplexModel->ModelNum;
//	sModelSemple->PotNum 		= sComplexModel->PotNum;
//	sModelSemple->StartHight 	= sComplexModel->StartHight;
//	sModelSemple->Reserve0 		= sComplexModel->Reserve0;
//	
//	Crc16 = GetCrc16Check((uint8 *)sModelSemple,sizeof(stcModelSemple) - 2);
//	
//	sModelSemple->CrcCheck  	= Crc16;
}	
//
////------------------------------------------------------------------------------
////名    称：    void   stcModelTostcModelComplex(stcModelComplex * sComplexModel,stcModel	* sModel)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
void   GetHxn5OilBoxModel(stcModelComplex * sComplexModel)
{
	uint16		Crc16;
	static		stcModPot	sModPot[200]= 
	{
		353,335,
		471,457,
		576,563,
		682,664,
		791,768,
		897,867,
		1000,965,
		1110,1068,
		1216,1167,
		1320,1265,
		1431,1369,
		1541,1472,
		1639,1565,
		1745,1665,
		1844,1761,
		1944,1856,
		2052,1961,
		2155,2060,
		2253,2156,
		2357,2256,
		2459,2355,
		2563,2454,
		2666,2552,
		2771,2652,
		2863,2742,
		2967,2845,
		3068,2945,
		3169,3044,
		3264,3142,
		3365,3242,
		3463,3341,
		3558,3439,
		3658,3538,
		3760,3638,
		3854,3736,
		3951,3834,
		4044,3932,
		4138,4029,
		4243,4134,
		4335,4228,
		4435,4328,
		4526,4425,
		4625,4524,
		4720,4623,
		4810,4720,
		4898,4813,
		4993,4917,
		5084,5015,
		5179,5116,
		5269,5211,
		5358,5308,
		5450,5409,
		5496,5459,
		5540,5509,
		5585,5559,
		5635,5613,
		5676,5657,
		5726,5712,
		5770,5760,
		5812,5808,
		5857,5859,
		5898,5906,
		5949,5961,
		6005,6024,
		6097,6095,
		6185,6150,
		6275,6204,
		6363,6261,
		6447,6316,
		6535,6371,
		6618,6433,
		6694,6495,
		6766,6548,
		6836,6598,
		6908,6651,
		6974,6698,
		7049,6753,
		7115,6801,
		7183,6850,
		7251,6899,
		7382,6994,
		7526,7099,
		7666,7200,
		8351,7698,
		9039,8197,
		9720,8691,
		10511,9266
	};
		
	sComplexModel->ModelNum 	= 30;
	sComplexModel->PotNum 		= 87;
	sComplexModel->StartHight 	= 0;	
		
	memcpy((uint8 *)sComplexModel->sModPot,(uint8 *)sModPot,sizeof(sModPot));
	
	Crc16 = GetCrc16Check((uint8 *)sComplexModel,sizeof(stcModelComplex) - 2);
	
	sComplexModel->CrcCheck  	= Crc16;
}	

#define			HXN5_MODLE		30
//
//extern	uint8	ReadOilBoxModel_Flsh(stcModelCard * sModelCard);
////------------------------------------------------------------------------------
////名    称：    stcModel    GetOilBoxModel(void)
////功    能：    取油箱模型
////入口参数：    油箱模型指针
////出口参数：    无
////------------------------------------------------------------------------------
uint8   GetOilBoxModel(stcModelComplex * sComplexModel)
{
    stcModel 		  	sModel;
	stcModelSemple	  	sModelSemple;
    uint8           	OilBoxTypCod = 0;                             	//油箱类型代码
    uint8           	ModelErrFlg;				
//	static		uint32	times = 0;

  	
  	ModelErrFlg 	= ERROR; 

    OilBoxTypCod	= GetOilBoxCod(); 
//    
//	 printfcom0("\r\n 油尺的油箱模型读取 %d",OilBoxTypCod);
//    //20110223      增加HXN5油箱模型
    if(OilBoxTypCod == HXN5_MODLE)  									//先取一个模型，然后再进行读模型判断
    {
    	GetHxn5OilBoxModel(sComplexModel);
  	
    	ModelErrFlg = NO_ERROR;

    	return	ModelErrFlg;
    }
 	else if(OilBoxTypCod < 30)
 	{
		if(GetOilBoxModelsModel((stcModel *)&sModel))
		{
			stcModelTostcModelComplex(sComplexModel,(stcModel *)&sModel);

			ModelErrFlg = NO_ERROR;
			//printfcom0("\r\n GetOilBoxModelsModel ");
			return	ModelErrFlg;
		} 		
		
		if(GetOilBoxModelsModelSemple((stcModelSemple *)&sModelSemple))
		{
			stcModelSempleTostcModelComplex(sComplexModel,(stcModelSemple *)&sModelSemple);			//100829
	        
			ModelErrFlg = NO_ERROR;
			return	ModelErrFlg;    		
		}
	}

	ModelErrFlg = ERROR;
    printfcom0("\r\n\r\n■ 选择模型错误 %u,使用DF4D模型 %u\r\n",OilBoxTypCod,1);
    
	GetDf4dOilBoxModel((stcModel *)&sModel);    
    
	stcModelTostcModelComplex(sComplexModel,(stcModel *)&sModel);						//100829	
	
//	if(times++ == 0)


    return  ModelErrFlg; 
}

