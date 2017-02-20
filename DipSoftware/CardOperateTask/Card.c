//#include 	"config.h"
//#include 	"string.h"
//#include 	"CpuDrive.h"
//#include 	"HardDrive.h"

#include    "includes.h"  
#include    "card.h"  


#define		SCK_IC	120//P004  
#define		MISO_IC	123//P005  
#define		MOSI_IC	124//P006 
#define     SSEL0	7//P007

#define		CS_IC	127//P228	
#define		SOFT_SPI_CS_IC	CS_IC//P228	
#define		POW_IC	211//P028

#define		IC_SWT	200//P029
#define		IC_RST	212//P230
#define		FINISH		1
#define		UNFINISH	0

uint32		l_Spi0Len 	= 0;
uint32		l_Spi0Point = 0;
//uint8		Spi0SendBuf[256*1];
//uint8		Spi0RevBuf[256*1];
uint8		Spi0FinishFlg = FINISH;

//------------------------------------------------------------------------
//  名  称 ：void WriteSCK_IC( uint8 temp )
//  功  能 ：设置 SCK_IC
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSCK_IC(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SCK_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCK_IC,0);		
	}	
	nop();	
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCK_IC(void)
//  功  能 ：读取 SCK_IC 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadSCK_IC(void)
{
	uint8 temp;

	temp = 	GPIO_ReadIoVal(SCK_IC);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI_IC( uint8 temp )
//  功  能 ：设置 MOSI_IC
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteMOSI_IC(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(MOSI_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(MOSI_IC,0);		
	}	
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadMOSI_IC(void)
//  功  能 ：读取 MOSI_IC 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadMOSI_IC(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(MOSI_IC);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI_IC( uint8 temp )
//  功  能 ：设置 MOSI_IC
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteMISO_IC(uint8 temp)
{
	
	if(temp)		
	{
		GPIO_SetOrClearValue(MISO_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(MISO_IC,0);		
	}
		
	nop();		
}

//void  SSP0_Init(void)
//{
// //   LPC_SC->PCONP |= (1 << 21);                                         /* 打开SSP0电源                 */
//  
////    LPC_PINCON->PINSEL3 |= (0x03ul << 8);                              /* 设置管脚功能                 */
////    LPC_PINCON->PINSEL3 |= (0x03ul << 14)|(0x03 << 16);
//   /* 
//    * 设置数据长度为8位，帧格式SPI，SCK高有效，第一个时钟沿采样，位速率为默认值 
//    */
//    LPC_SSP0->CR0 = (0x01 << 8)                                         /* SCR  设置SPI时钟分频         */
//                  | (0x01 << 7)                                         /* CPHA 时钟输出相位            */
//                  | (0x01 << 6)                                         /* CPOL 时钟输出极性            */
//                  | (0x00 << 4)                                         /* FRF  帧格式 00=SPI           */
//                  | (0x07 << 0);                                        /* DSS  数据长度,0111=8位       */
//
//    LPC_SSP0->CR1 = (0x00 << 3)                                         /* SOD  从机输出禁能,0=允许     */
//                  | (0x00 << 2)                                         /* MS   主从选择,0=主机,1=从机  */
//                  | (0x01 << 1)                                         /* SSE  SSP使能                 */
//                  | (0x00 << 0);                                        /* LBM  回写模式                */
//    LPC_SSP0->CPSR = 0x52;                                              /* 设置SSP从PCLK获得的分频值,   */
//                                                                        /* 主模式下有效, 最小值为0x02   */
//}		

void SSP0_Init(void)
{
	SSP_CFG_Type SSP_ConfigStruct;

	SSP_ConfigStructInit(&SSP_ConfigStruct);
	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP0, ENABLE);
}		 
void InitCardIO( void )
{
	GPIO_PinselConfig(SCK_IC,3);
	GPIO_PinselConfig(MOSI_IC,3);
	GPIO_PinselConfig(MISO_IC,3);
	GPIO_PinselConfig(SOFT_SPI_CS_IC,0);
	GPIO_PinselConfig(IC_SWT,0);

	SSP0_Init();
}
		       
//void	InitCardIO(void)
//{
//	GPIO_PinselConfig(SCK_IC,0);
//	GPIO_PinselConfig(SCK_IC,0);
//	GPIO_PinselConfig(MOSI_IC,0);
//	GPIO_PinselConfig(MOSI_IC,0);	
//	GPIO_PinselConfig(MISO_IC,0);
//	GPIO_PinselConfig(MISO_IC,0);	
//	GPIO_PinselConfig(SOFT_SPI_CS_IC,0);			
//	GPIO_PinselConfig(POW_IC,0);
//	GPIO_PinselConfig(IC_SWT,0);
//	GPIO_PinselConfig(IC_SWT,0);
//
//	SSP0_Init();
//}




//------------------------------------------------------------------------
//  名  称 ：uint8 ReadMOSI_IC(void)
//  功  能 ：读取 MOSI_IC 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadMISO_IC(void)
{
	uint8 temp;

	temp = 	GPIO_ReadIoVal(MISO_IC);

	nop();
	return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteMOSI_IC( uint8 temp )
//  功  能 ：设置 MOSI_IC
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSoftSpiCSIC(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS_IC,0);		
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
//uint8 SendOrRecByte_SPI_IC(uint8 ch)
//{
//	uint8 i,temp;   
//	
////	WriteSCK_IC ( 0 );
//	printfcom0("\r\n temp1 %x,%x",ch);
//    for (i=0;i<8;i++)
//    {
//		temp=ch&0x80;
//    	ch=ch<<1;
//      if(temp)
//      {
//      	WriteMOSI_IC( 1 );	
//
//      	WriteSCK_IC ( 0 );
//
//      	WriteSCK_IC ( 1 );	        	
//      }
//      else
//      {
//      	WriteMOSI_IC( 0 );	
//
//        WriteSCK_IC ( 0 );
//          
//      	WriteSCK_IC ( 1 );
//      }
//      
//      ch |= ReadMISO_IC();
//	  //nop();
//    }
//        
//   // WriteSCK_IC ( 0 );
//    printfcom0("\r\n temp2 %x,%x",ch);
//    return	ch;
//}


uint8 SendOrRecByte_SPI_IC(uint8 data)
{
	uint8	tmp;

    while((LPC_SSP0->SR & 0x04) == 0x04)
	{
		tmp	= LPC_SSP0->DR; 
	}
	while ((LPC_SSP0->SR & 0x02) == 0);                                 /* 等待发送FIFO留出空间         */   
    LPC_SSP0->DR = data;
    while ((LPC_SSP0->SR & 0x10) == 0x10);                              /* 等待数据帧发送完毕           */ 
	
	while((LPC_SSP0->SR & 0x04) == 0x04)
	{
		tmp	= LPC_SSP0->DR; 
	}
    return tmp;
}



void	SendByte_SPI_IC(uint8	ch)
{
	SendOrRecByte_SPI_IC(ch);
}

uint8	RecByte_SPI_IC(void)
{
	uint8		ch =0;
	return	SendOrRecByte_SPI_IC(ch);
}



//------------------------------------------------------------------------
// 名    称：   uint8 SentByte_SPI(uint8  Dat8)
// 功    能：   SPI口0串口发送1个数据
// 入口参数：   Dat8:数据缓
// 出口参数：	(主机)
//------------------------------------------------------------------------
uint8 SentByte_SPI(uint8  Dat8)
{
	SendByte_SPI_IC(Dat8);
	return 1;
}

//------------------------------------------------------------------------
// 名    称：   uint8 RevByte_SPI(void)
// 功    能：   SPI0查询方式接收数据                  	
// 入口参数：  
// 出口参数：	接收到的数据
//------------------------------------------------------------------------
uint8 RevByte_SPI(void)
{
    uint8	Tmp;
    
	Tmp = RecByte_SPI_IC();
        
    return  Tmp;                  			//清发送完成标识
}

//------------------------------------------------------------------------
//  名  称 ：void WritePOW_IC( uint8 temp )
//  功  能 ：设置 POW_IC
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WritePOW_IC(uint8 temp)
{
	nop();		
	
	if(temp)		
	{
		GPIO_SetOrClearValue(POW_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(POW_IC,0);		
	}	

	nop();		
}

//------------------------------------------------------------------------------------------
//  名  称 ：void WriteCS_IC( uint8 temp )
//  功  能 ：设置 CS_IC
// 入口参数：无
// 出口参数：无
//-----------------------------------------------------------------------------------------
void WriteCS_IC(uint8 temp)
{
	GPIO_PinselConfig(CS_IC,0);
	
	nop();
	if(temp)		
	{
		GPIO_SetOrClearValue(CS_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(CS_IC,0);		
	}
	nop();	
}

//--------------------------------------------------------------------------------------------
//  名  称 ：void WriteIC_RST( uint8 temp )
//  功  能 ：设置 IC_RST
// 入口参数：无
// 出口参数：无
//----------------------------------------------------------------------------------------------
void WriteIC_RST(uint8 temp)
{
	GPIO_PinselConfig(IC_RST,0);
	
	if(temp)		
	{
		GPIO_SetOrClearValue(IC_RST,1);
	}
	else
	{
		GPIO_SetOrClearValue(IC_RST,0);		
	}		
}
//--------------------------------------------------------------------------------------------
//  名  称 ：void WriteIC_SWT( uint8 temp )
//  功  能 ：设置 IC_SWT
// 入口参数：无
// 出口参数：无
//---------------------------------------------------------------------------------------------
void WriteIC_SWT(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(IC_SWT,1);
	}
	else
	{
		GPIO_SetOrClearValue(IC_SWT,0);		
	}	
}

//-----------------------------------------------------------------------------------------------
//  名  称 ：uint8 ReadIC_SWT(void)
//  功  能 ：读取 IC_SWT 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------------------------------
uint8 ReadIC_SWT(void)
{
	uint8	Tmp;

	nop();	
	Tmp = 	GPIO_ReadIoVal(IC_SWT);

	return Tmp;	
}



//定义AT45DB041D命令    命令针对于PAGESIZE=l_CardPageSize-------------------------------------- 
#define    	READ_STU               0x57            //读状态字命令
#define    	CON_ARR_READ           0xe8            //continuous array read code
#define    	BUFF1_WRITE            0x84            //write buffer1
#define    	BUFF2_WRITE            0x87            //write buffer2
#define    	BUFF1_TO_MEM           0x83            //BUFFER1 to Main Memory Page Program with Built-in Erase
#define    	BUFF2_TO_MEM           0x86            //BUFFER1 to Main Memory Page Program with Built-in Erase

//#define    BUFF1_READ             0xD4            //read Buff1
//#define    BUFF2_READ             0xD6            //read Buff2
#define    	BUFF1_READ             0x54            //read Buff1
#define   	BUFF2_READ             0x56            //read Buff2
#define    	MEM_TO_BUFF1           0x53            //
#define    	MEM_TO_BUFF2           0x55            //
//IC卡参数
uint32		l_CardPageSize;	
uint32		l_CardStartAddr;	
uint32		l_CardPageNum;
uint8		l_CardTypeFlg;

//-------------------------------------------------------------------------------
//Status Register Format:
//   -----------------------------------------------------------------------
//  |  bit7  |  bit6   |  bit5  |  bit4  |  bit3  |  bit2  |  bit1  |  bit0  |
//  |--------|---------|---------|--------|---------|---------|---------|--------|
//  |RDY/BUSY|  COMP  |   0    |   1    |   1    |   1    |   X    |   X    | */
//
//bit7 - 忙标记，0为忙1为不忙
//当Status Register的位0移出之后，接下来的时钟脉冲序列将使SPI器件继续将最新的状态字节送出。
//bit6 - 标记最近一次Main Memory Page和Buffer的比较结果，0相同，1不同。
//bit5
//bit4
//bit3
//bit2 - 这4位用来标记器件密度，对于AT45DB041B，这4位应该是0111，一共能标记16种不同密度的器件
//bit1
//bit0 - 这2位暂时无效
//函数实现对AT45DB041D芯片状态字读出功能
//-------------------------------------------------------------------------------
uint8   StatusRegisterRead_Card(void)
{
    uint8 Statues;

    WriteCS_IC(1);
    
	WriteCS_IC(0);
    WriteCS_IC(0);
    
    SentByte_SPI(READ_STU);                          	//发送读状态存储器命令
    Statues = RevByte_SPI();                       		//读取状态寄存器命令

    WriteCS_IC(1);

    return Statues;
}

//------------------------------------------------------------------------
// 名    称：   void   InitCardInfo(void)				
// 功    能：   初始化IC卡参数     	
// 入口参数：  	无
// 出口参数：	无
//------------------------------------------------------------------------
void   InitCardInfo(void)								
{
	uint8	CardState;
	CardState = StatusRegisterRead_Card();
	
	if((CardState & 0x3c) == AT45DB041)
	{
		l_CardPageSize	= 256;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 2048;
		l_CardTypeFlg	= AT45DB041;
	}
	else if((CardState & 0x3c) == AT45DB161)
	{
		l_CardPageSize	= 512;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 4096;
		l_CardTypeFlg	= AT45DB161;		
	}	
	else if((CardState & 0x3c) == AT45DB321)
	{
		l_CardPageSize	= 512;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 8192;
		l_CardTypeFlg	= AT45DB321;		
	}	
	else if((CardState & 0x3c) == AT45DB642)
	{
		l_CardPageSize	= 1024;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 8192;
		l_CardTypeFlg	= AT45DB642;		
	}		
	
	//printfcom0("\r\n l_CardPageSize %d l_CardStartAddr %d l_CardPageNum %d l_CardTypeFlg %d ",l_CardPageSize,l_CardStartAddr,l_CardPageNum,l_CardTypeFlg);	
}

//------------------------------------------------------------------------
// 名    称：   uint32   GetCardPageSize(void)			//取IC卡页大小
// 功    能：   初始化IC卡参数     	
// 入口参数：  
// 出口参数：	
//------------------------------------------------------------------------
uint32   GetCardPageSize(void)							//取IC卡页大小
{
	return	l_CardPageSize;
}

//-------------------------------------------------------------------------------
//描述：
//    When the Flsh bit in the main memory array has been read,the device will
//    continue reading back at the beginning of the first page of memory.As w-
//    ith crossing over page boundaries,no Delays will be incurred when wrapp-
//    ing around from the end of the array to the beginning of the array.
//参数：
//    PA      - 页地址，0~2047
//    BFA     - 指定BUFFER中的起始写入地址
//    pHeader - 指定数据的首地址
//    len     - 指定数据的长度
//函数现象连续读取AT45DB041D存储空间功能
//------------------------------------------------------------------------------
void    ContinuousArrayRead_Card(uint16 PA,uint16 BFA,uint8 *pHeader,uint16 Len)
{
    uint16 i = 0;
/**/
    while(i++ < 255)                                  		//确认AT45DB041D准备,确认256次后退出等待
    {
        if(StatusRegisterRead_Card() & 0x80)              	//准备完成,进行后续操作
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);
    
    SentByte_SPI(CON_ARR_READ);                             //送连续读命令
    
    if(l_CardTypeFlg == AT45DB041)
    {
			SentByte_SPI((uint8)(PA>>7));            		//送页地址
			SentByte_SPI((uint8)((PA<<1)|(BFA>>8)));   		//
			SentByte_SPI((uint8)BFA);                   	//送Buffer地址
		}
		else if(l_CardTypeFlg == AT45DB161)
		{
			SentByte_SPI((uint8)(PA>>6));            		//送页地址
			SentByte_SPI((uint8)((PA<<2)|(BFA>>8)));     	//
			SentByte_SPI((uint8)BFA);   
		}
		else if(l_CardTypeFlg == AT45DB321)
		{
			SentByte_SPI((uint8)(PA>>6));              		//送页地址
			SentByte_SPI((uint8)((PA<<2)|(BFA>>8)));     	//
			SentByte_SPI((uint8)BFA);   
		}	
		else if(l_CardTypeFlg == AT45DB642)
		{
			SentByte_SPI((uint8)(PA>>5));                	//送页地址
			SentByte_SPI((uint8)((PA<<3)|(BFA>>8)));      	//
			SentByte_SPI((uint8)BFA);   
		}		

    SentByte_SPI(0x00);                                     //时续要求
    SentByte_SPI(0x00);
    SentByte_SPI(0x00);
    SentByte_SPI(0x00);

    for(i=0;i<Len;i++)                                    	//读数
    {
        pHeader[i] = RevByte_SPI();
    }
    
    WriteCS_IC(1);
}

//-----------------------------------------------------------------------------
//描述：
//    将指定数据写入从某个地址（0~263）开始的页中：包含2个动作，首先将指定数据
//    写入到BUFFER 1或者BUFFER 2中，其中可以指定BUFFER中的起始写入地址，此写入
//    动作不影响BUFFER中其它地址中的数据，然后再将BUFFER中的整个数据写入到某指
//    定页中(带预擦除)。
//参数：
//    buffer  - 选择BUFFER，01H选择BUFFER 1，02H选择BUFFER 2
//    PA      - 页地址，0~2047
//    BFA     - 指定BUFFER中的起始写入地址
//    pHeader - 指定数据的首地址
//    len     - 指定数据的长度
//--------------------------------------------------------------------------------
void    MainMemoryToBuff(uint8 Buffer,uint16 PA)
{
    uint16 i = 0;

    while(i++<3000)                                         //确认AT45DB041D为不忙,确认1000次后退出等待
    {
        if(StatusRegisterRead_Card()&0x80)
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);
    
    switch(Buffer)                                          //选Buffer
    {
        case 1:SentByte_SPI(MEM_TO_BUFF1);break;
        case 2:SentByte_SPI(MEM_TO_BUFF2);break;
    }
    if(l_CardTypeFlg == AT45DB041)
    {
	    SentByte_SPI((uint8)(PA>>7));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<1));
	}
	else if(l_CardTypeFlg == AT45DB161)
	{
		SentByte_SPI((uint8)(PA>>6));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<2));
	}
	else if(l_CardTypeFlg == AT45DB321)
	{
		SentByte_SPI((uint8)(PA>>6));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<2));
	}	
	else if(l_CardTypeFlg == AT45DB642)
	{
		SentByte_SPI((uint8)(PA>>5));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<3));
	}		
		
    SentByte_SPI(0x00);

    WriteCS_IC(1);
}


//------------------------------------------------------------------------------
//描述：
//    将指定数据写入从某个地址（0~263）开始的BUFFER中。
//参数：
//    buffer  - 选择BUFFER，01H选择BUFFER 1，02H选择BUFFER 2
//              在该指令序列中，操作码84H选择BUFFER 1，87H选择BUFFER 2
//    BFA     - BUFFER中的起始地址，0~263
//    pHeader - 待存数据的头指针
//    len     - 待存数据的长度1~l_CardPageSize
//----------------------------------------------------------------------------
void    BufferRead_Card(uint8 Buffer,uint16 PA,uint16 BFA,uint8 *pHeader,uint16 Len)
{
    uint16 i;

	MainMemoryToBuff(Buffer,PA);							//读取指定的页内容

    while(i++<5000)                                       	//确认AT45DB041D为不忙,确认500次后退出等待
    {
        if(StatusRegisterRead_Card() & 0x80)
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);

    switch(Buffer)                                       	//选择buffer
    {
        case 1:SentByte_SPI(BUFF1_READ);break;             	//送buffer1 写命令
        case 2:SentByte_SPI(BUFF2_READ);break;             	//送buffer2 写命令
    }
    
    SentByte_SPI(0x00);
    SentByte_SPI((uint8)(BFA>>8));                          //A8地址
    SentByte_SPI((uint8)BFA);                               //A7~A0
    SentByte_SPI(0x00);

    for(i=0;i<Len;i++)                                 		//写Buffer
    {
        pHeader[i] = RevByte_SPI();
    }

    WriteCS_IC(1);
}

//---------------------------------------------------------------------------
//描述：
//    将指定数据写入从某个地址（0~263）开始的BUFFER中。
//参数：
//    buffer  - 选择BUFFER，01H选择BUFFER 1，02H选择BUFFER 2
//              在该指令序列中，操作码84H选择BUFFER 1，87H选择BUFFER 2
//    BFA     - BUFFER中的起始地址，0~263
//    pHeader - 待存数据的头指针
//    len     - 待存数据的长度1~l_CardPageSize
//----------------------------------------------------------------------------
void    BufferWrite_Card(uint8 Buffer,uint16 BFA,uint8 *pHeader,uint16 Len)
{
    uint16 i;
/*
    while(i++<500)                                      	//确认AT45DB041D为不忙,确认500次后退出等待
    {
        if(StatusRegisterRead_Card() & 0x80)
        {
            break;
        }
    }
*/
    WriteCS_IC(0);

    switch(Buffer)                                        	//选择buffer
    {
        case 1:SentByte_SPI(BUFF1_WRITE);break;             //送buffer1 写命令
        case 2:SentByte_SPI(BUFF2_WRITE);break;             //送buffer2 写命令
    }
    
    SentByte_SPI(0x00);
    SentByte_SPI((uint8)(BFA>>8));                          //A8地址
    SentByte_SPI((uint8)BFA);                               //A7~A0

    for(i=0;i<Len;i++)                                   	//写Buffer
    {
        SentByte_SPI(pHeader[i]);
    }

    WriteCS_IC(1);
}

//-----------------------------------------------------------------------------
//描述：
//    将指定数据写入从某个地址（0~263）开始的页中：包含2个动作，首先将指定数据
//    写入到BUFFER 1或者BUFFER 2中，其中可以指定BUFFER中的起始写入地址，此写入
//    动作不影响BUFFER中其它地址中的数据，然后再将BUFFER中的整个数据写入到某指
//    定页中(带预擦除)。
//参数：
//    buffer  - 选择BUFFER，01H选择BUFFER 1，02H选择BUFFER 2
//    PA      - 页地址，0~2047
//    BFA     - 指定BUFFER中的起始写入地址
//    pHeader - 指定数据的首地址
//    len     - 指定数据的长度
//--------------------------------------------------------------------------------
void    BufferToMainMemoryPageProgramWithBuilt_inErase_Card(uint8 Buffer,uint16 PA,uint16 BFA,uint8 *pHeader,uint16 Len)
{
    uint16 i = 0;

    BufferWrite_Card(Buffer,BFA,pHeader,Len);         		//写buffer操作

    while(i++<3000)                                         //确认AT45DB041D为不忙,确认1000次后退出等待
    {
        if(StatusRegisterRead_Card()&0x80)
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);
    
    switch(Buffer)                                          //选Buffer
    {
        case 1:SentByte_SPI(BUFF1_TO_MEM);break;
        case 2:SentByte_SPI(BUFF2_TO_MEM);break;
    }
    if(l_CardTypeFlg == AT45DB041)
    {
	    SentByte_SPI((uint8)(PA>>7));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<1));
	}
	else if(l_CardTypeFlg == AT45DB161)
	{
		SentByte_SPI((uint8)(PA>>6));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<2));
	}
	else if(l_CardTypeFlg == AT45DB321)
	{
		SentByte_SPI((uint8)(PA>>6));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<2));
	}	
	else if(l_CardTypeFlg == AT45DB642)
	{
		SentByte_SPI((uint8)(PA>>5));                       //确定页地址
	    SentByte_SPI((uint8)(PA<<3));
	}		
	
    SentByte_SPI(0x00);

    WriteCS_IC(1);
}

static	uint8	l_CardBufNum;
//extern	SysFastHoldTast(void);
//---------------------------------------------------------------------
//名    称：   ReadCard(uint32 Addr,uint32 *buf,uint32 Len)
//功    能：   将指定区IC卡值读出。
//入口参数：   Addr    读取数据的地址       地址：0~Sizeof(IC)
//             buf     读取后放置的缓冲区
//             Len     读出的数据长度  以8位的数据为长度单位
//出口参数：   无
//----------------------------------------------------------------------
uint8 ReadCard(uint32 Addr,uint8 *TargetBuf,uint32 Len)
{
    uint16	PageNum;                                                    //页
	uint16	PageOffset;                                                 //页内地址
	uint16  ReadPageTimes;                                              //读页次数       
	uint16  LenTemp;                                                  	//长度         
	uint16  i;
	uint32  BufOffset = 0;
    uint32  AddrTemp; 
	uint32	PageNoReadSize;
	uint32	BufNoReadSize;
	
	AddrTemp =  Addr; 
    AddrTemp += l_CardStartAddr;                                      	//映射到IC卡内部
               
    if(AddrTemp + Len > l_CardStartAddr + l_CardPageNum*l_CardPageSize)    
    {
       //printfcom0("\r\n READ AddrTemp + Len %d > l_CardStartAddr + l_CardPageNum*l_CardPageSize %d  ", 
//       								AddrTemp + Len,l_CardStartAddr + l_CardPageNum*l_CardPageSize);
       return  FALSE;                                                   //地址超阶
    }

    PageNum         = AddrTemp / l_CardPageSize ;                     	//求页
    PageOffset      = AddrTemp % l_CardPageSize ;                     	//求页内地址
    ReadPageTimes   = (Len + PageOffset  + (l_CardPageSize - 1)) / l_CardPageSize;            
    /* 																	//读页次数        
    for(i = 0; i < ReadPageTimes; i++)
    {
        PageNoReadSize = 	l_CardPageSize - (PageOffset + BufOffset)
        					 % l_CardPageSize;							//计算IC卡一页内未写地址
        BufNoReadSize	=	Len - BufOffset;							//缓冲区未读入字节长度
        LenTemp = (PageNoReadSize < BufNoReadSize ? PageNoReadSize:BufNoReadSize);
        																//取将一页写满或将未读入字节长度
	    BufferRead_Card(((l_CardBufNum++%2)+1),PageNum,PageOffset
	    							,(uint8 *)&TargetBuf[BufOffset],LenTemp);	
	    																//取数 
        BufOffset += LenTemp;
        PageNum++; 
    }
    */
    
    for(i = 0; i <= ReadPageTimes; i++)
    {
    	//SysFastHoldTast();

        PageNoReadSize = 	l_CardPageSize - (PageOffset + BufOffset)
        					 % l_CardPageSize;						//计算IC卡一页内未写地址
        BufNoReadSize	=	Len - BufOffset;						//缓冲区未读入字节长度
        LenTemp = (PageNoReadSize < BufNoReadSize ? PageNoReadSize:BufNoReadSize);
        																//取将一页写满或将未读入字节长度  
        ContinuousArrayRead_Card(PageNum,PageOffset,(uint8 *)&TargetBuf[BufOffset],LenTemp);	//取数 
                
        BufOffset += LenTemp;
        PageOffset += LenTemp;
        PageOffset %= l_CardPageSize;
        
        PageNum++; 
    }
    
    //NOP(); 
    return  TRUE;	                                                    //正确                   
}

//---------------------------------------------------------------------
//名    称：   uint8 WriteCardPartPage(uint16 PageNum,SegmentNum,uint8 *Buf,uint32 Len)

//功    能：   写页中的一部分,要求SegmentNum+Len <= l_CardPageSize
//入口参数：   PageNum  页号        地址：0~Sizeof(IC)
//             Buf:     数据缓冲    
//出口参数：   写成功
//----------------------------------------------------------------------
uint8 WriteCardPage(uint16 PageNum,uint16 SegmentNum,uint8 *Buf,uint32 Len)
{
    uint8   IC_BufTemp[256*4];  

    if(PageNum > l_CardPageNum || (SegmentNum + Len) > l_CardPageSize )
    {
        return  FALSE;
    }     
    if(Len == l_CardPageSize)                                         //写完整页
    {
        BufferToMainMemoryPageProgramWithBuilt_inErase_Card(((l_CardBufNum++%2)+1),PageNum,0,Buf,l_CardPageSize);
    }
    else 
    {
        ContinuousArrayRead_Card(PageNum, 0 , IC_BufTemp, l_CardPageSize); 				//IC卡读第PageNum页
        memcpy((uint8 *)&IC_BufTemp[SegmentNum], Buf ,Len);                            //将数据填充

        BufferToMainMemoryPageProgramWithBuilt_inErase_Card(((l_CardBufNum++%2)+1),PageNum,0,IC_BufTemp,l_CardPageSize);
    }
    
    //NOP();
    return  TRUE;    
}

//---------------------------------------------------------------------
// 名    称：   WriteCard()
// 功    能：   指定缓冲区数据编程。
// 入口参数：   Addr    编程地址(内部地址)
//						地址从00 ~ CARD_SIZE  
//
//              buf     编程数据缓冲区 注意：此为16位字

//              Len     编程数据长度  以8位的写入数据为长度单位，相当于 Len 个字节数目

// 出口参数：   返回TRUE表示操作成功，返回FALSE表示操作失败
//---------------------------------------------------------------------
uint8 WriteCard(uint32 Addr,uint8 *SourceBuf,uint16 Len)
{
    uint16	PageNum;                                                    //页
	uint16	PageOffset;                                                 //页内地址
	uint32  AddrTemp; 
	uint16  WritePageTimes;                                             //写页次数       
	uint16  LenTemp;                                                  	//长度         
	uint16  i;
	uint16  BufOffset = 0;
	uint32	PageNoWriteSize;
	uint32	BufNoWriteSize;
	
	AddrTemp =  Addr; 
    AddrTemp += l_CardStartAddr;                                      	//映射到IC卡内部
              
    if(AddrTemp + Len > l_CardStartAddr + l_CardPageNum*l_CardPageSize)    
    {
       return  FALSE;                                                   //地址超阶
    }

    PageNum         = AddrTemp / l_CardPageSize ;                     	//求页
    PageOffset      = AddrTemp % l_CardPageSize ;                     	//求页内地址
    WritePageTimes  = (Len + PageOffset + (l_CardPageSize - 1)) / l_CardPageSize;            	//读页次数
    
    for(i = 0; i < WritePageTimes; i++)
    {
    	//SysFastHoldTast();

        PageNoWriteSize = 	l_CardPageSize - (PageOffset + BufOffset)
        					 % l_CardPageSize;							//计算IC卡一页内未写地址
        BufNoWriteSize	=	Len - BufOffset;							//缓冲区未写字节长度
        LenTemp = (PageNoWriteSize < BufNoWriteSize ? PageNoWriteSize:BufNoWriteSize);
        																//取将一页写满或将缓冲共写完字节长度
        WriteCardPage(PageNum,PageOffset,(uint8 *)&SourceBuf[BufOffset],LenTemp);     //取数 

        BufOffset += LenTemp;
        PageOffset += LenTemp;
        PageOffset %= l_CardPageSize;
        
        PageNum++; 
    }

    return  TRUE;	                                                    //正确  
}

//---------------------------------------------------------------------
// 名    称：   uint32 GetToEndLen(uint32 Addr)
// 功    能：   指定到指定地址到卡的结束的长度
// 入口参数：   Addr    指定地址
// 出口参数：   返回长度
//---------------------------------------------------------------------
uint32 GetToEndLen(uint32 Addr)
{
	return	(l_CardStartAddr + l_CardPageNum*l_CardPageSize - Addr);
}

static	uint8   mPlugInFlg = NO_PLUG_IN_CARD;                     		//卡片插入标识

static uint32   mPlugTime  = 0;											//没有插卡次数
static uint32   mNoPlugTime= 0;

uint8		l_CardErrorFlg = NO_ERROR;
uint8		l_LongTimePlugCardErrFlg = NO_ERROR;

//---------------------------------------------------------------------
// 名    称：   void   PlugCard( void )
// 功    能：   判断是否有卡片插入
// 入口参数：   无
// 出口参数：   无
//---------------------------------------------------------------------
void   PlugCard( void )
{
    if(ReadIC_SWT() == 1)                               //判断是否插入卡片
    {
        mPlugTime++;                                   	//判卡次数

        if( mPlugTime > 20)                          	//去抖动,是否插入卡片
        {
            mPlugInFlg = PLUG_IN_CARD;              	//有卡
            
            mNoPlugTime = 0;
        }
    }
    else
    {            
        mNoPlugTime++;                                   //判卡次数

        if( mNoPlugTime > 20)                            //去抖动,是否插入卡片
        {
            mPlugInFlg = NO_PLUG_IN_CARD;             	//无卡

          	l_LongTimePlugCardErrFlg = NO_ERROR;

            mPlugTime = 0;
            
      	//	ReStartPluse();							//开柴速测量
        }
    }
    
    ////printfcom0("\r\n mPlugInFlg %d",mPlugInFlg);
}


//---------------------------------------------------------------------
// 名    称：   void   HoldCard( void )
// 功    能：   IC卡插入维护
// 入口参数：   无
// 出口参数：   无
//---------------------------------------------------------------------
void   HoldCard( void )
{
	PlugCard();
}

//---------------------------------------------------------------------
// 名    称：   uint8   GetPlugFlg()
// 功    能：   返回插卡标志
// 入口参数：   无
// 出口参数：   TRUE:有卡插入,FALSE:无卡插入 
//---------------------------------------------------------------------
uint32   GetPlugTime(void)
{
    return  mPlugTime;
}

//extern	void ClosePluseInput(void);
//---------------------------------------------------------------------
// 名    称：   uint8   GetPlugFlg()
// 功    能：   返回插卡标志
// 入口参数：   无
// 出口参数：   TRUE:有卡插入,FALSE:无卡插入 
//---------------------------------------------------------------------
uint8   GetPlugFlg(void)
{
	if(mPlugInFlg == NO_PLUG_IN_CARD)
	{
		WritePOW_IC( 1 );								//关电源
	}
	else
	{
		WritePOW_IC( 0 );								//开电源
	}
		
    return  mPlugInFlg;
}

//---------------------------------------------------------------------
// 名    称：   uint8   GetPlugFlg()
// 功    能：   返回插卡标志
// 入口参数：   无
// 出口参数：   TRUE:有卡插入,FALSE:无卡插入 
//---------------------------------------------------------------------
void   ResetPlugFlgEvt(void)
{
    //mPlugInFlg = NO_PLUG_IN_CARD;						//卡拔表示自动判断
}

//---------------------------------------------------------------------
// 名    称：   void   LongTimePlugCard( void )
// 功    能：   长时间插入IC卡错误
// 入口参数：   无
// 出口参数：   无
//---------------------------------------------------------------------
uint8   LongTimePlugCard( void )
{
	l_LongTimePlugCardErrFlg = NO_ERROR;
	
	if(GetPlugTime() > 10*60*100)
	{
		l_LongTimePlugCardErrFlg = ERROR;
	}
	
	return	l_LongTimePlugCardErrFlg;
}

//---------------------------------------------------------------------
// 名    称：   void   GetLongTimePlugCardErrFlg( void )
// 功    能：   长时间插入IC卡错误
// 入口参数：   无
// 出口参数：   无
//---------------------------------------------------------------------
uint8   GetLongTimePlugCardErrFlg( void )
{
	return	l_LongTimePlugCardErrFlg;
}


//void	ReStartPluse(void);										//关柴速测量
//---------------------------------------------------------------------
// 名    称：   uint8   PlugICCard(void)
// 功    能：   判断是否插入IC卡
// 入口参数：   无
// 出口参数：   TRUE:有卡插入,FALSE:无卡插入 
//---------------------------------------------------------------------
uint8 PlugICCard(void)
{
	uint8	CardSta;
	uint8	Flg;
	uint8	Times;

    Times 	= 3; 
    Flg 	= FALSE;
              
    while(Times-- && Flg == FALSE) 							//判断3次
    {        
	    NOP();
		if(GetPlugFlg() == PLUG_IN_CARD)					//有卡插入
	    {
	    	WritePOW_IC( 0 );								//开电源

			DelayX10ms(20);
							
			CardSta = StatusRegisterRead_Card();			//读IC卡状态
			
			if(	(	((CardSta & AT45DB041) == AT45DB041) 
				|| 	((CardSta & AT45DB161) == AT45DB161)
		 		|| 	((CardSta & AT45DB321) == AT45DB321)
		 		|| 	((CardSta & AT45DB642) == AT45DB642))
				&& 	( CardSta != 0xff) )
			{
				l_CardErrorFlg = NO_ERROR;					//清卡类型错误
				
				InitCardInfo();								//初始化卡信息

				Flg = TRUE; 								//返回1	
				break;		
			}	
			else
			{		 
				l_CardErrorFlg = ERROR;						//置卡错误
				
				Flg = FALSE;
			}	

		}
		else
		{
			l_CardErrorFlg = NO_ERROR;							//卡类
			
			Flg = FALSE;

			break;	
		}
	}
	
	if(Flg == FALSE)
	{
		WritePOW_IC( 1 );										//非卡，关电源
	}
	
	return 	Flg;
}

//---------------------------------------------------------------------
// 名    称：   uint8   GetCardErrorFlg()
// 功    能：   返回插卡错误标志
// 入口参数：   无
// 出口参数：   TRUE:插入卡类型正确,FALSE:插入卡类型错误 
//---------------------------------------------------------------------
uint8   GetCardErrorFlg(void)
{
    return  l_CardErrorFlg;
}

#define		RIGHT_DATA					0xff
#define		CARD_TYPE_ERR				62
#define		CARD_PLUG_LONG_TIME_ERR		61
#define		USB_TYPE_ERR				66

extern	uint8	l_UsbErrFlg;
#define		ERR_USB_UNKNOWN 			0xFA

//extern	UINT8	TestCH376Host( void );
//-------------------------------------------------------------------------------------------------
//函数名称:            	uint8  JudgeCardError(void) 
//函数功能:             对IC卡的卡类型进行判断
//入口参数:            
//出口参数:             
//--------------------------------------------------------------------------------------------------
uint8  JudgeCardError(void) 
{
	uint8		ErrorType;
	
	#ifdef	HARD_VER_111122	
	static		uint32	Times = 0;
	#endif
	
	ErrorType = RIGHT_DATA;
	
	if(GetCardErrorFlg() == ERROR)
	{
//		ErrorType = CARD_TYPE_ERR;
	}
	
	if(GetLongTimePlugCardErrFlg() == ERROR)
	{
		ErrorType = CARD_PLUG_LONG_TIME_ERR;
	}
	
	#ifdef	HARD_VER_111122	
	if(TestCH376Host() == ERR_USB_UNKNOWN)
	{
		if(Times++ < 10)
		{
			mInitCH376Host();
		}

		ErrorType = USB_TYPE_ERR;
	}
	else
	{
		Times = 0;
	}
	#endif
	
	return	ErrorType;
}

