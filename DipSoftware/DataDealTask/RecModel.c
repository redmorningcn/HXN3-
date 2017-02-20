//#include    "config.h" 
//#include	"Globe.h"
//#include    "stdio.h" 
//#include    "stdarg.h" 
//#include    "string.h"
//#include    "math.h"
//#include    "stdlib.h"
//#include    "DipMath.h"
//#include    "FramStore.h"
//#include    "HardDrive.h"
//#include    "CpuDrive.h"
//#include    "Tax2.h"
//#include    "OperateCard.h"


#include <includes.h>

//--------------------------------------------------------------------------------
// 名    称：  	stcModPot     StringToWord(char   *String,char FlgChar,int  WordNum)
// 功    能:    主函数
// 入口参数：
// 出口参数：
//-------------------------------------------------------------------------------
stcModPot     StringToWord(char   *String,char FlgChar,int  WordNum)
{
    char    StringTmp[128];
    char    *WordPos;
    char    WordStr[128];
    char    StrTmpBuf[128];
    int     WordLen,OtherLen;
    int     i;
    stcModPot	sModPot;

    strcpy(StringTmp,String);

    for(i = 0; i < WordNum-1;i++)
    {
//		SysFastHoldTast();
//201400		    
        WordPos =  (char *)strchr(StringTmp, FlgChar);
            
        WordLen =  (WordPos - StringTmp);

        OtherLen = strlen(StringTmp) - WordLen;

        memcpy(WordStr,StringTmp,WordLen);

        WordStr[WordLen] = '\0';
        
        memcpy(StrTmpBuf,&StringTmp[WordLen+1],OtherLen);

        memcpy(StringTmp,StrTmpBuf,OtherLen);

        StringTmp[OtherLen] = '\0';
        
        sModPot.HigVal = atoi(WordStr);
    }
    
    sModPot.DipVal = atoi(StringTmp);

    return   sModPot;
}

//--------------------------------------------------------------------------------
// 名    称：  	void	GetOilModel(uint8 *Buf,uint16	Len)
// 功    能:    取油箱模型
// 入口参数：
// 出口参数：
//-------------------------------------------------------------------------------
uint8	GetCOM0ModelComplex(stcModelComplex *sModelComplex,uint8 *Buf,uint16	Len)
{
	char 		ModelFlgString[] = {"通过串口通信设置油箱模型"};
	char		LineString[128];

	uint32		CharNum = 0,LineCharNum = 0,Line = 0;		
	uint8		ModelFlg = 0;
		
	////printfcom0("\r\nGetCOM0ModelComplex(stcModelComplex *sModelComplex,uint8 *Buf,uint16	Len)" );
	
	while(CharNum < Len)
	{
		//SysHoldTast();
		
		if(Buf[CharNum] != 0x0d && Buf[CharNum] != 0x0a)
		{
			LineString[LineCharNum++] = Buf[CharNum];
		}
		else if(Buf[CharNum] == 0x0a)
		{
			LineString[LineCharNum] = '\0';
				
			if(ModelFlg == 1)
			{
				if(Line == 1)
				{
					sModelComplex->ModelNum = atoi(LineString);
				}
					
				if(Line == 2)
				{
			    	sModelComplex->PotNum = atoi(LineString);
				}
						
				if(Line == 3)
				{
					sModelComplex->StartHight = atoi(LineString);
				}
					  
				if(Line > 3)
				{
					uint8	LineTmp;
					
					LineTmp = Line - 4;
					
		  			sModelComplex->sModPot[LineTmp] = StringToWord(LineString,',',2);
		  			
		  		}
		  		
		  		Line++;
			}
		
			if(!strcmp(LineString,ModelFlgString))
	      	{
	      	    ModelFlg = 1;
	      	    
	      	    Line = 1;
	      	}
	      	
	      	LineCharNum = 0;
      	}
      	
      	CharNum++;	
	}
	
	return	Line;
}


//--------------------------------------------------------------------------------
// 名    称：  	void	GetOilModel(uint8 *Buf,uint16	Len)
// 功    能:    取油箱模型
// 入口参数：
// 出口参数：
//-------------------------------------------------------------------------------
//uint8	StoreCOM0Model(stcModelComplex	sModelComplex)
//{
//	static	stcModelCard		sModelCard;
//	uint16	CrcCheck;
//	uint16	RecerveNum = 0;
//	
//	//ReadOilBoxModel((stcModelCard * )&sModelCard);
//				
//	//CrcCheck = GetCrc16Check((uint8 *)&sModelCard,sizeof(stcModelCard) - 2);
//		
//	//if(CrcCheck == sModelCard.CrcCheck)				//校验和相等,有原来的模型		
//	{			
//
//	}
//	//else
//	{
//		if(sModelComplex.PotNum < sizeof(sModelCard.sModelSemple[0].sModPot) / sizeof(stcModPot))
//		{
//			stcModelComplexTostcModelSemple((stcModelSemple *)&sModelCard.sModelSemple[0],
//					(stcModelComplex *)&sModelComplex);
//		}
//		else if(sModelComplex.PotNum < sizeof(sModelCard.sModel[0].sModPot) / sizeof(stcModPot))
//		{
//			stcModelComplexTostcModel((stcModel * )&sModelCard.sModel[0],(stcModelComplex	*)&sModelComplex);
//		}
//		else
//		{
//			while(sModelComplex.PotNum > RecerveNum*(sizeof(sModelCard.sModel[0].sModPot) / sizeof(stcModPot)))
//			{
//				stcModelComplexToMulstcModel((stcModel * )&sModelCard.sModel[RecerveNum],
//					(stcModelComplex	*)&sModelComplex,RecerveNum);
//	
//				RecerveNum++;
//				//SysHoldTast();
//			}
//		}
//	}
//	
//	CrcCheck = GetCrc16Check((uint8 *)&sModelCard,sizeof(stcModelCard) - 2);
//
//	sModelCard.CrcCheck = CrcCheck;
//	
//	StoreOilBoxModel((stcModelCard * )&sModelCard);
//
//	return	0;
//}

extern	 stcCardFlg		l_sCardFlg;
stcModelCard			l_sModelCard={0};


#define		CARD_DATA_ADDR		5120			//IC卡 数据起始地址
#define		CARD_FLG_ADDR		0				//IC卡 标识起始地址

//--------------------------------------------------------------------------------
// 名    称：  	void	COM0SendCardFlg(void)
// 功    能:    取油箱模型
// 入口参数：
// 出口参数：
//-------------------------------------------------------------------------------
void	COM0SendCardFlg(void)
{
/*
	static	stcCardFlg		sCardFlg;
	
	while(1)
	{
		DelayX10ms(200);
		while(GetPlugFlg() == PLUG_IN_CARD)
		{
			while(!PlugICCard())
			{;}	

			ReadCard(CARD_FLG_ADDR,(uint8 *)&sCardFlg,sizeof(stcCardFlg));	
			
			ReadCard(CARD_DATA_ADDR,(uint8 *)&l_sModelCard,sizeof(l_sModelCard));	
			
			SendCOM0((uint8 *)&sCardFlg,sizeof(stcCardFlg));
			
			SendCOM0((uint8 *)&l_sModelCard,sizeof(l_sModelCard));
			
			DelayX10ms(500);
		}
	}
*/
}	

//--------------------------------------------------------------------------------
// 名    称：  	void	COM0GetModelCard(void)
// 功    能:    取油箱模型
// 入口参数：
// 出口参数：
//-------------------------------------------------------------------------------
void	COM0GetModelCard(void)
{

/*	static	uint32	Time;
	static	uint8	Buf[16*1024];
	static	stcCardFlg		sCardFlg;
	uint16	Crc16;

	uint16	Reclen;
	uint32	StoreDataLen = 0;
*/	
/*
	DelayX10ms(200);
	while(GetPlugFlg() == PLUG_IN_CARD)
	{
		while(!PlugICCard())
		{;}	

		ReadCard(CARD_FLG_ADDR,(uint8 *)&sCardFlg,sizeof(stcCardFlg));	
		
		ReadCard(CARD_DATA_ADDR,(uint8 *)&l_sModelCard,sizeof(l_sModelCard));	
		
		//SendCOM0((uint8 *)&sCardFlg,sizeof(stcCardFlg));
		
		//SendCOM0((uint8 *)&sCardFlg,sizeof(l_sModelCard));
		
		DelayX10ms(500);
	}
*/	
/*
	CloseTax2();
	OpenCOM0Tax(19200);
	
	DelayX10ms(10);											//等30S

	Reclen 	= ReadCOM0(Buf,16*1024);
	
	DisplaySet(60,1,"SEND");
	DisplaySet(60,1,"    ");

	//printfcom0("\r\nstcCardFlg = %d",sizeof(stcCardFlg));
	//printfcom0("\r\nl_sModelCard = %d",sizeof(l_sModelCard));
	
	while(1)																
	{
		ClaerDisplaySet();												//清显示缓冲区

		DisplaySet(100,1,"SEND");
		
		Reclen = GetCOM0DataLen();
		
		StoreDataLen = 0;

		while(!Reclen)												//串口是否有数据接受,无数据等待
		{
			Reclen = GetCOM0DataLen();
		}

		Time  	= GetSysTime();			
		
		DisplaySet(100,1,"RECD");
		
		//while(1)
		{
			while( Reclen )												//没有数据就退出
			{
				if(GetSysTime() - Time > 10)							//1秒取一次数据
				{
					Time = GetSysTime();

					Reclen 	= ReadCOM0(&Buf[StoreDataLen],16*1024 - StoreDataLen);
			
					StoreDataLen += Reclen;
					
					//printfcom0("\r\nReclen = %d,StoreDataLen = %d",Reclen,StoreDataLen);
				}
				
				DelayX10ms(10);											//等30S
				////printfcom0("\r\nGetSysTime() = %d",GetSysTime());
			}
		}
					
		memcpy((uint8 *)&sCardFlg,Buf,sizeof(sCardFlg));			//取IC卡标志页
		
		memcpy((uint8 *)&l_sModelCard,&Buf[sizeof(sCardFlg)],sizeof(l_sModelCard));	
																	//取模型卡		
		Crc16	= GetCrc16Check((uint8 *)&sCardFlg,sizeof(sCardFlg) - 2);

		//printfcom0("\r\nCrc16 = %d",Crc16);

		if(Crc16 == sCardFlg.CrcCheck)								//校验接受校验是否正确
		{
			//printfcom0("\r\nCrc16 == sCardFlg.CrcCheck");

			memcpy((uint8 *)&l_sCardFlg,(uint8 *)&sCardFlg,sizeof(sCardFlg));
			
			OperationCOM0ModelCard();
			
			DelayX10ms(1000);

		}
		else
		{
			DisplaySet(100,1,"COME");
		}
	
		DelayX10ms(200);

				
	}
		*/
}
 			

//--------------------------------------------------------------------------------
// 名    称：  	void	COM0SetModel(void)
// 功    能:    取油箱模型
// 入口参数：
// 出口参数：
//-------------------------------------------------------------------------------
void	COM0SetModel(void)
{
/*
	static	uint8		Buf[256*10];
	static	stcModelComplex	sModelComplex;
	uint16			Reclen;
	
	Reclen = ReadCOM0(Buf,256*10);
	
	if(Reclen)
	{
		////printfcom0("\r\nReclen = %d",Reclen );
		if(GetCOM0ModelComplex((stcModelComplex *)&sModelComplex,Buf,Reclen))
		{
			////printfcom0("\r\nStoreCOM0Model(sModelComplex);" );

			StoreCOM0Model(sModelComplex);					//存数据
			
			//printfcom0("\r\n油箱模型输入完成！;" );
		}
	}
	
	DelayX10ms(500);										//等30S
*/
}
