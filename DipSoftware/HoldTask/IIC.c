//#include    "config.h"   
#include <includes.h>

#define     SCL     206		//P0.15
#define     SDA     207		//P0.18

//------------------------------------------------------------------------
//  名  称 ：void void InitI2CIO(void)
//  功  能 ：设置 SDA SCL 为普通IO口 进行模拟总线操作
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void InitI2CIO(void)
{
//    SETFUN_P00_15X( GPIO,SCL );         //将I2C端口设为GPIO口
//    SETFUN_P00_15X( GPIO,SDA ); 
}

void	InitFramIO(void)
{
	GPIO_PinselConfig(SCL,0);
	GPIO_PinselConfig(SCL,0);
	GPIO_PinselConfig(SDA,0);
	GPIO_PinselConfig(SDA,0);
}

//------------------------------------------------------------------------
//  名  称 ：void WriteSCL( uint8 temp )
//  功  能 ：设置 SCL
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSCL(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SCL,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCL,0);		
	}	
	nop();	
	  
//    IO0DIR_OUT(SCL);    
//    IO0PIN_W(temp,SCL);
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSCL(void)
//  功  能 ：读取 SCL 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadSCL(void)
{
    uint8 temp;
//    
//    IO0DIR_IN(SCL);    
//    temp = IO0PIN_R(SCL);
//    

	temp = 	GPIO_ReadIoVal(SCL);
	nop();

    return temp;
}

//------------------------------------------------------------------------
//  名  称 ：void WriteSDA( uint8 temp )
//  功  能 ：设置 SDA
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteSDA(uint8 temp)
{
//    IO0DIR_OUT(SDA);    
//    IO0PIN_W(temp,SDA);

	if(temp)		
	{
		GPIO_SetOrClearValue(SDA,1);
	}
	else
	{
		GPIO_SetOrClearValue(SDA,0);		
	}	
	nop();	
}

//------------------------------------------------------------------------
//  名  称 ：uint8 ReadSDA(void)
//  功  能 ：读取 SDA 的值
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
uint8 ReadSDA(void)
{
    uint8 temp;
    
//    IO0DIR_IN(SDA);    
//    temp = IO0PIN_R(SDA);

	temp = 	GPIO_ReadIoVal(SDA);
	nop();

    return temp;
}

//------------------------------------------------------------
//函数名称:         StartI2C()
//功    能:         I2C总线开始条件
//入口参数:         无
//出口参数:         无
//说明：            I2C总线的开始条件：
//                  SCL高电平时SDA的下降沿
//------------------------------------------------------------
void StartI2C(void)
{
    WriteSCL(0);                                // SCL=0;
    
    WriteSDA(1);                                //SDA=1;
    WriteSCL(1);                                //SCL=1;
    WriteSDA(0);                                //SDA=0;
    WriteSCL(0);                                // SCL=0;
}

//---------------------------------------------------------------
//函数名称:         StopI2C()
//功    能:         I2C总线结束条件
//入口参数:         无
//出口参数:         无
//说明：            I2C总线结束条件：SCL为高电平时SDA的上升沿
//--------------------------------------------------------------------
void StopI2C(void)
{
    WriteSCL(0);                                // SCL=0;
    
    WriteSDA(0);                                //SDA=0;
    WriteSCL(1);                                //SCL=1;
    WriteSDA(1);                                //SDA=1;
    WriteSCL(0);                                //SCL=0;
}

//-------------------------------------------------------------------------------
//函数名称:         MasterAckI2C()
//功    能:         主机接收应答，在接收到1字节数据后，返回应答，告诉从机接收完成
//入口参数:         无
//出口参数:         无
//说明：            I2C总线应答：读完一个字节后将SDA线拉低，即应答0
//---------------------------------------------------------------------------------
void MasterAckI2C(void)
{
    WriteSCL(0);                                // SCL=0;

    WriteSDA(0);                                //SDA=0;
    WriteSCL(1);                                //SCL=1;
    WriteSCL(0);                                  //SCL=0;
    WriteSDA(0);                                //SDA=0;
}

//-----------------------------------------------------------------------------------
//函数名称:         MasterNoAckI2C()
//功    能:         主机接收应答，告诉通信从机接收完成
//入口参数:         无
//出口参数:         无
//说明：            I2C总线应答：
//                  读完所要求的字节数据后将SDA线拉高，为结束IIC总线操作做准备
//-------------------------------------------------------------------------------------
void MasterNoAckI2C(void)
{
    WriteSCL(0);                                    // SCL=0;
    
    WriteSDA(1);                                    //SDA=1;
    WriteSCL(1);                                    //SCL=1;
    WriteSCL(0);                                    //SCL=0;
    WriteSDA(0);                                    //SDA=0;
}

//------------------------------------------------------------------------------------
//函数名称:         CheckSlaveAckI2C()
//功    能:         读I2C从机应答
//入口参数:         无
//出口参数:         ackflag
//                  如果从机产生应答，则返回0，
//                  从机没有产生应答,否则返回1
//说明：            检查I2C器件(从机)应答情况,应答返回1,否则为零
//these waw a bug befor 2008/05/17.
//------------------------------------------------------------------------------------
uint8 CheckSlaveAckI2C(void)
{
    uint8 ackflag;                                  //清除应答标志;
    
    ackflag = ReadSDA();
    WriteSCL(1);                                    //SCL=1;
    WriteSCL(0);                                    //SCL=0;
    
    return ackflag;
}

//------------------------------------------------------------------------------------
//函数名称:         WriteByteWithI2C()
//功    能:         主机对I2C总线写1操作
//入口参数:         Data:要写出的数据
//出口参数:         无
//说明：            写一字节数据Data
//------------------------------------------------------------------------------------
void WriteByteWithI2C(uint8 Data)  
{
    uint8 i;
    for(i=0;i<8;i++)
    {
        if(Data & 0x80)                             //传输位从高位到低位,先传最高位 
        {
            WriteSDA(1);                            //SDA=1;
            WriteSCL(1);                            //SCL=1;
        }
        else
        {  
            WriteSDA(0);                            //SDA=0;
            WriteSCL(1);                            //SCL=1;
        }   
        WriteSCL(0);                                //SCL=0;
        WriteSDA(0);                                //SDA=0;
        Data <<= 1;                                 //数据左移             
    }
}

//-------------------------------------------------------------------------------------------------------
//函数名称:         ReadByteWithI2C()
//功    能:         主机对I2C总线写1操作
//入口参数:         无
//出口参数:         无
//说明：            读一字节数据：返回值即读的数据
//--------------------------------------------------------------------------------------------------------
uint8 ReadByteWithI2C(void)            
{
    uint8 readdata=0;                           // Read_Data为读入的数据，0
    uint8 j;
    
    for (j=0;j<8;j++)
    {
        readdata <<=1;
                                                //数据读出，若是0则移位；若是1则与0x01或
        if(ReadSDA())
        {
            readdata =(readdata | 0x01);               
        }
        WriteSCL(1);                              //SCL=1;
        WriteSCL(0);                              //SCL=0;
    }
    
    return   readdata ;                         //返回读出的字节
}


