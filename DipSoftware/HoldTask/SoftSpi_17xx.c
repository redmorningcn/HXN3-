#include <includes.h>

#define			SCK0					15    	//p1.20  
#define			MISO0					17			//p1.23  
#define			MOSI0					18			//p1.24 
#define   		SOFT_SPI_CS0			16			//p1.22

//#define		Hard_SPI0   //硬SPI开关
void	nop(void)
{
	uint8 i;
    i =20;
	NOP();
	while(i--);
}

void	InitFlshIO(void)
{
	GPIO_PinselConfig(SCK0,0);
	GPIO_PinselConfig(MOSI0,0);	
	GPIO_PinselConfig(MISO0,0);	
}

//------------------------------------------------------------------------
//  名  称 ：void WriteSCK0( uint8 temp )
//  功  能 ：设置 SCK0
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSCK0(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(SCK0,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCK0,0);		
	}	
	//nop();	
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCK0(void)
//  功  能 ：读取 SCK0 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadSCK0(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(SCK0);
	//nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI0( uint8 temp )
//  功  能 ：设置 MOSI0
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteMOSI0(uint8 temp)
{
	
	if(temp)		
	{
		GPIO_SetOrClearValue(MOSI0,1);
	}
	else
	{
		GPIO_SetOrClearValue(MOSI0,0);		
	}	
	//nop();		
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadMOSI0(void)
//  功  能 ：读取 MOSI0 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadMOSI0(void)
{
	uint8 temp;

	temp = 	GPIO_ReadIoVal(MOSI0);
	//nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI0( uint8 temp )
//  功  能 ：设置 MOSI0
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteMISO0(uint8 temp)
{
	GPIO_PinselConfig(MISO0,0);
	
	if(temp)		
	{
		GPIO_SetOrClearValue(MISO0,1);
	}
	else
	{
		GPIO_SetOrClearValue(MISO0,0);		
	}
		
	//nop();		
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadMOSI0(void)
//  功  能 ：读取 MOSI0 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadMISO0(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(MISO0);

	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI0( uint8 temp )
//  功  能 ：设置 MOSI0
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSoftSpiCS0(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS0,1);
	}
	else
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS0,0);		
	}	

	nop();		
}

//---------------------------------------------------------------------------------
//函数名称:             SentByte_SPI()
//功    能:             SPI发送一字节数据
//入口参数:             Data8
//出口参数:             无
//说    明:				以模拟SPI总线方式发送数据
//----------------------------------------------------------------------------------
uint8 SendOrRecByte_SPI0(uint8 ch)
{
	uint8 i,temp;   
	
    for (i=0;i<8;i++)
    {
	  temp=ch&0x80;
      ch=ch<<1;

      if(temp)
      {
      	WriteMOSI0( 1 );	

      	WriteSCK0 ( 0 );

      	WriteSCK0 ( 1 );	        	
      }
      else
      {
      	WriteMOSI0( 0 );	

        WriteSCK0 ( 0 );
          
      	WriteSCK0 ( 1 );
      }
      
      ch |= ReadMISO0();
    }
    
    return	ch;
}

void	SendByte_SPI0(uint8	ch)
{
	SendOrRecByte_SPI0(ch);
}

uint8	RecByte_SPI0(void)
{
	uint8	ch =0;
	return	SendOrRecByte_SPI0(ch);
}

