#include 	"string.h"
#include <includes.h>

#define		SCK1			7	
#define		MISO1			8	
#define		MOSI1			9
#define		CS_DIS			213		
#define		SOFT_SPI_CS1	CS_DIS


//定义端口及功能引脚---------------------------------------------------------------
//#define     DDR_7219    DDRB 
//#define     PINT_7219   PINB
//#define     PORT_7219   PORTB  
//#define     CS_7219     4                       //数据锁存

//max7219寄存器地址定义-------------------------------------------------------------
#define     NoOp        0x00                    // 空操作寄存器
#define     Digit0      0x01                    // 数码管1寄存器
#define     Digit1      0x02                    // 数码管2寄存器
#define     Digit2      0x03                    // 数码管3寄存器
#define     Digit3      0x04                    // 数码管4寄存器
#define     Digit4      0x05                    // 数码管5寄存器
#define     Digit5      0x06                    // 数码管6寄存器
#define     Digit6      0x07                    // 数码管7寄存器
#define     Digit7      0x08                    // 数码管8寄存器
/**/
#define     DecodeMode  0x09                    // 译码模式寄存器
#define     Intensity   0x0a                    // 亮度寄存器
#define     ScanLimit   0x0b                    // 扫描位数寄存器
#define     ShutDown    0x0c                    // 低功耗模式寄存器
#define     DisplayTest 0x0f                    // 显示测试寄存器
//max7219控制寄存器命令
#define     ShutdownMode    0x00                // 低功耗方式
#define     NormalOperation 0x01                // 正常操作方式
//#define     DecodeDigit     0xff                // 译码设置，8位均为BCD码;对8个数都编码   
#define     NoDecodeDigit   0x00                // 译码设置，对8个数都不编码   
#define     ScanDigit       0x07                // 扫描位数设置，显示8位数码管
//#define   ScanDigit 0x03                      // 扫描位数设置，显示8位数码管
#define   	IntensityGrade  0x0f                // 亮度级别设置
//#define     IntensityGrade  0x03              // 亮度级别设置
#define     TestMode    0x01                    // 显示测试模式 
#define     TextEnd     0x00                    // 显示测试结束，恢复正常工作模式

////---------------------------------------------------------------------------------
////函数名称:             void InitIOForSPI1( void )
////功    能:             将相应端口初始化为SPI口
////入口参数:             
////出口参数:             
////----------------------------------------------------------------------------------
void InitIOForSPI1( void )
{
	GPIO_PinselConfig(SCK1,0);
	GPIO_PinselConfig(MOSI1,0);
	GPIO_PinselConfig(MISO1,0);
	GPIO_PinselConfig(SOFT_SPI_CS1,0);
}
//void SPI1_Init(void)
//{
//	SSP_CFG_Type SSP_ConfigStruct;
//
//	SSP_ConfigStructInit(&SSP_ConfigStruct);
//	// Initialize SSP peripheral with parameter given in structure above
//	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
//
//	// Enable SSP peripheral
//	SSP_Cmd(LPC_SSP1, ENABLE);
//}
//
//
//void InitIOForSPI1( void )
//{
//	GPIO_PinselConfig(SCK1,2);
//	GPIO_PinselConfig(MOSI1,2);
//	GPIO_PinselConfig(MISO1,2);
//	GPIO_PinselConfig(SOFT_SPI_CS1,0);
//
//	SPI1_Init();
//}

//------------------------------------------------------------------------
//  名  称 ：void WriteSCK1( uint8 temp )
//  功  能 ：设置 SCK1
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSCK1(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SCK1,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCK1,0);		
	}	
	nop();	
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCK1(void)
//  功  能 ：读取 SCK1 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadSCK1(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(SCK1);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI1( uint8 temp )
//  功  能 ：设置 MOSI1
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteMOSI1(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(MOSI1,1);
	}
	else
	{
		GPIO_SetOrClearValue(MOSI1,0);		
	}	
	nop();		
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadMOSI1(void)
//  功  能 ：读取 MOSI1 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadMOSI1(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(MOSI1);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI1( uint8 temp )
//  功  能 ：设置 MOSI1
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteMISO1(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(MISO1,1);
	}
	else
	{
		GPIO_SetOrClearValue(MISO1,0);		
	}
		
	nop();		
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadMOSI1(void)
//  功  能 ：读取 MOSI1 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadMISO1(void)
{
	uint8 temp;

	temp = 	GPIO_ReadIoVal(MISO1);

	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI1( uint8 temp )
//  功  能 ：设置 MOSI1
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSoftSpiCS1(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS1,1);
	}
	else
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS1,0);		
	}	

	nop();		
}

void WriteCS_DIS(uint8 temp)
{
	WriteSoftSpiCS1(temp);
}

//---------------------------------------------------------------------------------
//函数名称:             void SentByte_SPI1(uint8 ch)
//功    能:             SPI发送一字节数据
//入口参数:             Data8
//出口参数:             无
//说    明:				以模拟SPI总线方式发送数据
//----------------------------------------------------------------------------------
void SentByte_SPI1(uint8 ch)
{
	uint8 i,temp;   
	
	WriteSCK1 ( 0 );

    for (i=0;i<8;i++)
    {
		temp=ch&0x80;
    	ch=ch<<1;
        if(temp)
        {
        	WriteMOSI1( 1 );	

        	WriteSCK1 ( 0 );

        	WriteSCK1 ( 1 );	        	
        }
        else
        {
        	WriteMOSI1( 0 );	

            WriteSCK1 ( 0 );
            
        	WriteSCK1 ( 1 );
        }
		NOP();
    }
        
    WriteSCK1 ( 0 );
}
//void SentByte_SPI1(uint8 ch)
//{
//	uint32	time;
//	time = GetSysTime();
//
//	SSP_SendData(LPC_SSP1,ch);
//	while(SSP_GetStatus(LPC_SSP1,SSP_STAT_TXFIFO_EMPTY)!=SET)
//	{	
//		printfcom0("\r\n test");
//		if(GetSysTime()-time>100)
//		{
//			
//			return;	
//		}	
//	}
//}

//----------------------------------------------------------------------------
//函数名称:   void SentByteTo7219(uint8 Addr,uint8 Num) 
//功    能:   向7219发送1Byte数据或命令
//入口参数:   addr:   数据接收地址
//            num:    要存的数据
//出口参数:   无
//-----------------------------------------------------------------------------
void SentByteTo7219(uint8 Addr,uint8 Num) 
{ 
	 WriteCS_DIS( 0 );	
	 		   					   		
  	 SentByte_SPI1( Addr );		
             										
  	 SentByte_SPI1( Num );   
	                  	
  	 WriteCS_DIS( 1 );			  									
}


typedef	struct  _stcDisplay
{
	char	Buf[12];
	uint32	Time;			//显示的时间
	uint32	Degree;			//显示的次数
//	uint8	Enable;			
}stcDisplay;

#define		DIS_BUF_NUM		10
stcDisplay	sDisplay[DIS_BUF_NUM];
stcDisplay	sDisplayBak[DIS_BUF_NUM];

//----------------------------------------------------------------------------
// 名    称：   uint32 Displayf(char *fmt, va_list param) 
// 功    能：   
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
void InitDisplayBuf(void)
{
	uint8	i;
	
	for(i = 0; i < DIS_BUF_NUM;i++)
	{
		sDisplay[i].Degree = 0;
	}
}

//----------------------------------------------------------------------------
// 名    称：   void ClaerDisplaySet(void)
// 功    能：   
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
void ClaerDisplaySet(void)
{
	uint8	i;
	
	memcpy((uint8 *)sDisplayBak,(uint8 *)sDisplay,sizeof(sDisplay));  //888888
	
	for(i = 0; i < DIS_BUF_NUM;i++)			//清显示
	{
		sDisplay[i].Degree = 0;			
	}
}

//----------------------------------------------------------------------------
// 名    称：   void ClaerDisplaySetWithoutStore(void)
// 功    能：   
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
void ClaerDisplaySetWithoutStore(void)
{
	uint8	i;
		
	for(i = 0; i < DIS_BUF_NUM;i++)			//清显示
	{
		sDisplay[i].Degree = 0;			
	}
}

extern	void InitDisplay (void);

//----------------------------------------------------------------------------
// 名    称：   void ResumeDisplaySet(void)
// 功    能：   
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
void ResumeDisplaySet(void)
{	
	InitDisplay();

	memcpy((uint8 *)sDisplay,(uint8 *)sDisplayBak,sizeof(sDisplay)); 	//888888
}

//-------------------------------------------------------------------
//函数名称:     void InitDisplay (void)
//功    能:     7219初始化
//入口参数:     无
//出口参数:     无
//-------------------------------------------------------------------
void InitDisplay (void)
{
	InitIOForSPI1();								//SPI端口初始化IO口
	
	InitDisplayBuf();								//初始化显示缓冲区
	
    SentByteTo7219 (DisplayTest,TextEnd);         	// 设置工作模式
	SentByteTo7219 (ScanLimit,ScanDigit);         	// 设置扫描界限
    SentByteTo7219 (DecodeMode,NoDecodeDigit);      // 设置不译码模式
    SentByteTo7219 (Intensity,IntensityGrade);    	// 设置亮度
    SentByteTo7219 (ShutDown,NormalOperation);    	// 设置为正常工作模式
}
		  
uint8 LedNumCode[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,
                   // 0    1    2    3    4    5    6    7    8    9    A 
                     0x1F,0x4E,0x3D,0x4F,0x47};  
                   // b   C    d     E    F      

uint8 LedCharCode[] = {0x00,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0x80,0x01,0x80,0xE5,
					//       !    "    #    $    %    &    '    (     )    *    +    ,    -    .   /
					  0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B, 
					// 0    1    2		3   4    5    6    7    8    9	
					  0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,
					// :    ;    <    =     >   ?    @
					  0x77,0x1F,0x4E,0x3d,0x4F,0x47,0x5F,0x37,0x30,0x3c,0x87,0x0e,0xE5,
                    //  A    B   C    D     E    F    G    H   I    J    K    L    M    
                      0x76,0x7E,0x67,0xFE,0x66,0x5B,0x0F,0x3E,0x3E,0xE5,0x37,0x33,0x6D,
                    //  N    O    P   Q    R     S    T    U    V   W    X    Y    Z     
                      0xE5,0xE5,0xE5,0xE5,0x08,0xE5,
                     // [    \    ]    ^    _    `
                      0x77,0x1F,0x0D,0x3D,0x4F,0x47,0x7B,0x17,0x30,0x3c,0x87,0x0e,0xE5,
                     // a    b   c    d     e    f    g    h    i    j     k    l    m
					  0x15,0x1D,0x67,0x73,0x05,0x5B,0x0F,0x1C,0x1C,0xD3,0x37,0x33,0x6D,
                     // n    o   p    q     r    s    t    u    v   w    x    y    z     
                      0xE5,0xE5,0xE5,0xE5,0xE5,0x00//
                      // {    |    }    ~       灭
					   };     
           
#define     LED_CHAR_NNM    	16                  //数码管显示编码个数 


#define     DISPLAY_LED_NUM 	8                   //数码管个数   

        
//--------------------------------------------------------------------
//void          DisplayNum (uint32 Unmber)
//功    能:     用数码管将整型数据显示出来
//入口参数:     number
//出口参数:     无
//-------------------------------------------------------------------
void    DisplayNum (uint32 Unmber)
{
    unsigned char i  = DISPLAY_LED_NUM;
	unsigned char digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
	
	InitDisplay();                                //显示初始化
	
	do
	{ 		
		i--;
		SentByteTo7219(digit[i],LedNumCode[Unmber % 10] );       //从低位到高位显示
		Unmber /= 10;                       
	}while(i && Unmber);
		
	while(i)
	{
        i--;
        SentByteTo7219(digit[i],0x00);            //将没有用位的显示清除        
    }	  
}

//--------------------------------------------------------------------
//void          DisplayNumWithDoit (uint32 Unmber)
//功    能:     用数码管将整型数据显示出来
//入口参数:     number
//出口参数:     无
//-------------------------------------------------------------------
void    DisplayNumWithDot (uint32 Unmber)
{
    unsigned char i  = DISPLAY_LED_NUM;
	unsigned char digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};

	do
	{ 		
		i--;
		SentByteTo7219(digit[i],LedNumCode[Unmber % 10] + 0x80);	//从低位到高位显示
		Unmber /= 10;                       
	}while(i && Unmber);
		
	while(i)
	{
        i--;
        SentByteTo7219(digit[i],0x00);            					//将没有用位的显示清除        
    }	  
}

//------------------------------------------------------
//函数名称:     DisplayString ()
//功    能:     用数码管显示字符串代码
//入口参数:     String: 字符代码
//出口参数:     无
//显示内容:     String
//内容代码:	    调用格式  DisplayString("ABCD");
//-------------------------------------------------------
void DisplayString(char * String)
{
	uint8   i = 0;
	uint8   digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
	uint8   CharTemp;
	uint8	DotNum = 0;
	
	while( i < DISPLAY_LED_NUM)
	{
        SentByteTo7219(digit[i],0x00);                      						//将没有用位的显示清除  
          
        i++;    
    }	
	
	i = 0;
	while(i < DISPLAY_LED_NUM + DotNum  && strlen((char *)String) - i > 0)
	{ 		
		i++;
		if(String[strlen((char *)String) - i - DotNum] >= ' '  )					//
		{
			if(String[strlen((char *)String) - i - DotNum] != '.' )					//对'.'进行处理
			{
				CharTemp = String[strlen((char *)String)- i - DotNum] - ' ' ; 		//求显示字符位置,LedCharCode位置
				SentByteTo7219(digit[DISPLAY_LED_NUM - i],LedCharCode[CharTemp] );	//从低位到高位显示      
			}
			else
			{	
				if(String[strlen((char *)String)- i - DotNum - 1] != '.')
				{
					CharTemp = String[strlen((char *)String)- i - DotNum - 1] - ' ';  
					SentByteTo7219(digit[DISPLAY_LED_NUM - i],LedCharCode[CharTemp] + 0x80);
					DotNum++;
				}  
				else
				{
					CharTemp = String[strlen((char *)String)- i - DotNum ] - ' ' ; 
					SentByteTo7219(digit[DISPLAY_LED_NUM - i],LedCharCode[CharTemp]); 
				}
			}
		}      
	}
}

//------------------------------------------------------
//函数名称:MovDisplayChar ()
//功    能:用数码管显示字符即已定字符
//入口参数:character: 字符代码
//出口参数:无
//显示内容:   -   E   H   L   P   Black
//内容代码:	  A	  B	  C	  D	  E	  F	  
//-------------------------------------------------------
void MovDisplayChar (uint8 character)
{
	uint8 i = DISPLAY_LED_NUM ,j;
	uint8 digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
		
	for(j = 0;j < 12; j++)
	{
	 	 i = DISPLAY_LED_NUM;
		 while(i)
		 {
            i--;
            SentByteTo7219(digit[i],0x00);            						//将没有用位的显示清除
         }	
		 
		SentByteTo7219(digit[j%4],LedNumCode[character%LED_CHAR_NNM]);       //从低位到高位显示   
		DelayX10ms(20);                 
	}
}

//----------------------------------------------------------------------------
// 名    称：   uint32 Displayf(char *fmt, va_list param) 
// 功    能：   
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
uint32 Displayf(char *fmt, ...) 
{ 
   va_list  argptr;
   uint32   cnt;
   char     a[255];
   
   strlen(fmt);
   if(strlen(fmt) > (sizeof(a) - 55))
   {
        return FALSE;
   }
   va_start(argptr, fmt);
   
   cnt = vsprintf(a, fmt, argptr);
   
   va_end(argptr);
   
   DisplayString(a); 

   return(cnt);
}

extern	void   FeedDog(void);
//----------------------------------------------------------------------------
// 名    称：   uint32 DisplaySet(uint32 Time,uint32 Degree,char *fmt, ... )
// 功    能：   设置要显示的值
// 入口参数：   Time：显示时间，Degree：显示次数，*fmt：显示内容
// 出口参数：   
//----------------------------------------------------------------------------  
uint32 DisplaySet(uint32 Time,uint32 Degree,char *fmt, ... ) 
{ 
   va_list  argptr;
   uint32   cnt;
   char     a[255];
   //char     b[10] = {' ',' ',' ',' '};
   uint32	i,j;
   
   strlen(fmt);
   if(strlen(fmt) > (sizeof(a) - 55))
   {
        return FALSE;
   }
   va_start(argptr, fmt);
   
   cnt = vsprintf(a, fmt, argptr);
   
   va_end(argptr);

   FeedDog();							//喂狗

   for(i= 0 ;i < DIS_BUF_NUM; i++)
   {
       if(sDisplay[i].Degree == 0)
       {	
       		for(j = 0; j< sizeof(sDisplay[i].Buf); j++)
       		{
       			sDisplay[i].Buf[j] = '\0';
       		}
       			
       	   	sDisplay[i].Time 	= Time;
       	   	sDisplay[i].Degree 	= Degree;
       	   	memcpy(sDisplay[i].Buf,a,cnt);
			
       	   /*
       	   /////////////////////////////////////
       	   if(cnt > 4)
       	   {
       	   		if(cnt-4<4)
       	   		{
       	   			memcpy(sDisplay[i].Buf,&a[4],cnt-4);
       	   			memcpy(&sDisplay[i].Buf[cnt-4],b,4-(cnt-4));
       	   			memcpy(&sDisplay[i].Buf[4],a,4);
       	   		}
       	   		else
       	   		{
       	   			memcpy(sDisplay[i].Buf,&a[4],4);
       	   			memcpy(&sDisplay[i].Buf[4],a,4);	
       	   		}
       	   }
       	   else
       	   {/ *
				memcpy(sDisplay[i].Buf,&a[4],cnt-4);
				memcpy(&sDisplay[i].Buf[cnt-4],b,4-(cnt-4));
				memcpy(&sDisplay[i].Buf[4],a,4);
			* /	
       	   		memcpy(sDisplay[i].Buf,b,4);
       	   		memcpy(&sDisplay[i].Buf[4],a,cnt);
       	   		memcpy(&sDisplay[i].Buf[4+ cnt],b,(4-cnt));
       	   }
       	   */    	  	
		   return 1;
       }
   }
   
   return(cnt);
}	

//----------------------------------------------------------------------------
// 名    称：   void DisplayContrl(void) 
// 功    能：   
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
void DisplayContrl(void) 
{
	static	uint8	i = 0;
	static  uint32	Time = 0;
	static	uint32	DisplayTimes = 0;
	static  uint32	LastTime = 0;
//	static	uint32	DisResTimes = 0;	
		
	while(i < DIS_BUF_NUM)
	{
	   if(sDisplay[i].Degree != 0)
       {	
       	   if(DisplayTimes == 0)
       	   {
       	   	    Time = sDisplay[i].Time;
       	   }

       	   if(Time != 0)
       	   {
				//Time--;
				DisplayString(sDisplay[i].Buf);

				if(Time > GetSysTime() - LastTime)
				{
					Time -= (GetSysTime() - LastTime);
				}
				else
				{
					Time = 0;
				}
				
				DisplayTimes++;
       	   }
       	   else
       	   {
       	   		sDisplay[i].Degree = sDisplay[i].Degree - 1;  
       	   		DisplayTimes = 0;
       	   		i++;
       	   }
       	   
       	   LastTime = GetSysTime();
       	   return ;
       }
	   
	   DisplayTimes = 0;
	   i++;
   	}
   	
   	LastTime = GetSysTime();
   	i = 0;
}

//----------------------------------------------------------------------------
// 名    称：   void HoldDisplay(void) 
// 功    能：   显示维护	
// 入口参数：  

// 出口参数：   
//----------------------------------------------------------------------------  
void HoldDisplay(void) 
{
	DisplayContrl();			
}
