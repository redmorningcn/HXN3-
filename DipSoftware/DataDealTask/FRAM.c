//#include    "config.h"   
//#include    "CpuDrive.h"

#include <includes.h>
#include "IIC.h"
					  
//铁电参数
#define		FRAM_SIZE               8192						         	//1024*8空间容量
#define		FRAM_START_ADDR	        0x0000	                                //铁电的起始地址
#define		FRAM_DIVICE_ADDR        0xa0	                                //铁电的设备地址
#define		FRAM_END_ADDR	      	(FRAM_START_ADDR + FRAM_SIZE)	

#define		FRMA_PROTECT			121//P121

//------------------------------------------------------------------------
//  名  称 ：void WriteSCL( uint8 temp )
//  功  能 ：设置 SCL
// 入口参数：无
// 出口参数：无
//------------------------------------------------------------------------
void WriteFRAM_PROTECT(uint8 temp)
{
//    IO1DIR_OUT(FRMA_PROTECT);    
//    IO1PIN_W(temp,FRMA_PROTECT);
}

//-------------------------------------------------------------------------------------------------------
//函数名称:         WriteFM24CL16()
//功    能:         对FM24CL16指定地址进行写数据
//入口参数:         ADDR:       操作地址    地址：0 ~ sizeof(FM24CL16)
//                  *DataBuf:   数据缓冲
//                  Len:        数据长度
//出口参数:         无
//说明：            
//--------------------------------------------------------------------------------------------------------
uint8 WriteFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen)            
{
    uint32  i = 0;
    uint8   SlaveAddr;                                      //从机地址
    uint16  AddrTemp = 0;                                   //地址缓存
    
    WriteFRAM_PROTECT(0);									//关写保护
    
    AddrTemp = Addr;
    AddrTemp += FRAM_START_ADDR;                            //计算地址

    if( (uint16)AddrTemp + DataBufLen > FRAM_END_ADDR ) 
    {
        return  FALSE;                                      //地址未超阶
    }
        
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //求FM24CL64设备写地址
    
    StartI2C();                                             //启动IIC总线
    
    WriteByteWithI2C(SlaveAddr);                            //写FM24CL64地址
    CheckSlaveAckI2C();
 
    WriteByteWithI2C(Addr >> 8);                            //写FM24CL64高位地址
    CheckSlaveAckI2C();
    
    WriteByteWithI2C( Addr );                               //写FM24CL64低位地址
    CheckSlaveAckI2C();     
  
    for(i = 0; i < DataBufLen; i++)                         //发送数据
    {
        WriteByteWithI2C(DataBuf[i]);                       //写数据
        CheckSlaveAckI2C();                                 //读从机应答信号
    }
    
    StopI2C();                                              //停止IIC操作   
    
    return  TRUE;                                           //正确
}

//-------------------------------------------------------------------------------------------------------
//函数名称:         ReadFM24CL16()
//功    能:         读取FM24CL16指定地址进行数据
//入口参数:         ADDR:       操作地址   地址：0 ~ sizeof(FM24CL16)
//                  *DataBuf:   数据缓冲 
//                  Len:        数据长度
//出口参数:         无
//说明：            
//--------------------------------------------------------------------------------------------------------
uint8 ReadFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen)            
{
    uint32  i = 0;
    uint8   SlaveAddr;                                      //从机地址
    uint16  AddrTemp;                                       //地址缓存
    
	WriteFRAM_PROTECT(0);									//关写保护

    AddrTemp = Addr;
    
    AddrTemp += FRAM_START_ADDR;                            //计算地址
    
    if( (uint16)AddrTemp + DataBufLen > FRAM_END_ADDR ) 
    {
        return  FALSE;                                      //地址未超阶
    }
    
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //求FM24CL64设备写地址
    
    StartI2C();                                             //启动IIC总线
    
    WriteByteWithI2C(SlaveAddr);                            //写FM24CL64设备写地址
    CheckSlaveAckI2C();                                     //读从机应答信号
    
    WriteByteWithI2C(Addr >> 8 );                           //写数据高位地址
    CheckSlaveAckI2C();                                     //读从机应答信号
    
    WriteByteWithI2C( Addr );                               //写数据低位地址
    CheckSlaveAckI2C();                                     //读从机应答信号
        
    SlaveAddr = (FRAM_DIVICE_ADDR)|(0x01);                  //求FM24CL64设备读地址
    
    StartI2C();                                             //启动IIC总线
    
    WriteByteWithI2C(SlaveAddr);                            //写FM24CL16地址
    CheckSlaveAckI2C();                                     //读从机应答信号
   
    for(i = 0; i < (DataBufLen -1); i++)                    //发送数据
    {
        DataBuf[i] = ReadByteWithI2C();                     //写数据
        MasterAckI2C();                                     //主机应答从机
    }
    DataBuf[i] = ReadByteWithI2C();                         //写数据
    
    MasterNoAckI2C();                                       //主机应答从机
    
    StopI2C();
    
    return  TRUE;                                           //正确
}

//#endif
    
