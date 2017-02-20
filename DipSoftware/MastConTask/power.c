#include    "includes.h"  


typedef	struct	_stcModBusRead_
{
    uint8	DeviceAddr;
    uint8	WorkCode;
    uint16	RegStart;
    uint16	RegLenth;	
    uint16	Crc16;   	
}stcModBusRead;

typedef	struct	_stcModBusPower_
{
	uint8	Voltage[2];
	uint8	Current[2];
	uint8	Power[2];
	uint8	PosEnergy[4];
	uint8	NegEnergy[4];
//	uint8	AddNBound[2];
//	uint8	ModName[4];
}stcModBusPower;

typedef	struct	_stcPower_
{
	int16	Voltage;
	int16	Current;
	int16	Power;
//	int16	AddNBound;	
	int32	PosEnergy;
	int32	NegEnergy;
//	int32	ModName;
}stcPower;
//


#define		MODBUS_HEAD		0x01
#define		MODBUS_READ		0x03
#define		MODBUS_SET		0x10
#define		MODBUS_LEN		0x07

//------------------------------------------------------------------------
// 名称：	void	SendReadPowerCode(void)
// 功能：初始化定时器1，定时时间单位为10ms，并使能中断。
// 入口参数：无
// 出口参数：无
//从设备地址	功能码	起始寄存器地址	寄存器个数	CRC-L	CRC-H
//0x01	0x03	0x00	0x10	0x00	0x07	0x05	0xCD
//------------------------------------------------------------------------
void  SendReadPowerCode(void)
{ 
	stcModBusRead		sModBusRead;
    uint16	Crc16;
    
    sModBusRead.DeviceAddr 		= MODBUS_HEAD;
    sModBusRead.WorkCode		= MODBUS_READ;
   	sModBusRead.RegStart		= 0x1000;
   	sModBusRead.RegLenth		= 0x0700;
   	   	
   	Crc16 = GetModBusCrc16Up((uint8 *)&sModBusRead,sizeof(sModBusRead) - 2);
   	
   	sModBusRead.Crc16 			= Crc16; 
   	
   	SendCOM1((uint8 *)&sModBusRead,sizeof(sModBusRead));

}

//------------------------------------------------------------------------
// 名称：	void  ClearPowerVal(void)
// 功能：初始化定时器1，定时时间单位为10ms，并使能中断。
// 入口参数：无
// 出口参数：无
//从设备地址	功能码	起始寄存器地址	寄存器个数	CRC-L	CRC-H
//0x01	0x10	0x00	0xA7	0x00	0x01	0x02	0x00	0x00	0xBF	0x47
//------------------------------------------------------------------------
void  ClearPowerVal(void)
{ 
//	stcModBusRead	sModBusRead;
//    uint16			Crc16;
//    
//    sModBusRead.DeviceAddr 		= MODBUS_HEAD;
//    sModBusRead.WorkCode		= MODBUS_READ;
//   	sModBusRead.RegStart		= 0x1000;
//   	sModBusRead.RegLenth		= 0x0700;
//   	   	
//   	Crc16 = GetModBusCrc16Up((uint8 *)&sModBusRead,sizeof(sModBusRead) - 2);
//   	
//   	sModBusRead.Crc16 			= Crc16; 
//   	
//   	SendCOM1((uint8 *)&sModBusRead,sizeof(sModBusRead));
}



extern	void  MathPower(stcModBusPower  sModBusPower);
//----------------------------------------------------------------------------
// 名    称：   uint8  GetDipData(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
uint8  GetPowerVal(uint8 *Buf,uint16	Len)
{
	static		uint32		Times = 0;
	int16		i = 0;	
	uint16		RecCheck = 0,Crc16;
	uint16		ModBusLen;
	stcModBusPower	sModBusPower;
	
	ModBusLen = 1 + 1 + 1 + MODBUS_LEN*2 + 2;         		//地址+操作码+数据长度字节+数据+校验

	if(Times > 10)											//长时间没有数据，清零
	{
		uint16		tmp = 0;
		uint16  i;

		for(i = 0;i<sizeof(stcModBusPower)/2;i++)
		{
			memcpy((uint8 *)&sModBusPower,(uint8 *)&tmp,sizeof(tmp));
		}
	}
	
	if(Len < ModBusLen)
	{
		Times++;
		return 0;	
	}

	for(i = 0; i < Len - ModBusLen;i++)
	{
		if(Buf[i] == MODBUS_HEAD && Buf[i+1] == MODBUS_READ 
			&& Buf[i+2] == MODBUS_LEN*2)
		{
			memcpy((uint8 *)&RecCheck,&Buf[i + ModBusLen - 2],sizeof(RecCheck));
			
			Crc16 = GetModBusCrc16Up(&Buf[i],ModBusLen - 2);
				
			if(Crc16 == RecCheck)							//校验正确
			{
				memcpy((uint8 *)&sModBusPower,&Buf[i+3],sizeof(sModBusPower));		
				
				MathPower(sModBusPower);						//转换成功率

				Times = 0;							

				return	1;
			}
			else
			{
				Times++;
			}
		}
	}
	
	return 0;
}

//------------------------------------------------------------------------
// 名称：	void  ClearPowerVal(void)
// 功能：初始化定时器1，定时时间单位为10ms，并使能中断。
// 入口参数：无
// 出口参数：无
//从设备地址	功能码	起始寄存器地址	寄存器个数	CRC-L	CRC-H
//0x01	0x10	0x00	0xA7	0x00	0x01	0x02	0x00	0x00	0xBF	0x47
//------------------------------------------------------------------------
void  SetPowerAddAndBound(uint8 Add)
{ 
//	static	stcModBusRead	sModBusRead;
//    uint16			Crc16;
//    static	uint8			Buf[16];
//    
//    sModBusRead.DeviceAddr 		= Add;
//    sModBusRead.WorkCode		= MODBUS_SET;
//   	sModBusRead.RegStart		= 0x2000;
//   	sModBusRead.RegLenth		= 0x0100;
//   	   	
//   	memcpy(Buf,(uint8 *)&sModBusRead,sizeof(sModBusRead)-2);
//   	
//   	Buf[sizeof(sModBusRead)-2] = 0x02;
//   	
//   	Buf[sizeof(sModBusRead)-1] = 0x01;			//Addr
//   	
//   	Buf[sizeof(sModBusRead)] = 0x06;			//Bound
//   	   	
//   	Crc16 = GetModBusCrc16Up(Buf,sizeof(sModBusRead)+1);
//   	
//   	memcpy(&Buf[sizeof(sModBusRead)+1],(uint8 *)&Crc16,sizeof(Crc16)); 
//   	
//   	SendCOM1(Buf,sizeof(sModBusRead)+3);
}

//------------------------------------------------------------------------
// 名称：	void	SendReadPowerCode(void)
// 功能：初始化定时器1，定时时间单位为10ms，并使能中断。
// 入口参数：无
// 出口参数：无
//从设备地址	功能码	起始寄存器地址	寄存器个数	CRC-L	CRC-H
//0x01	0x03	0x00	0x10	0x00	0x07	0x05	0xCD
//------------------------------------------------------------------------
void  ScanPowerAddr(void)
{ 
//	static	stcModBusRead		sModBusRead;
//	uint16	RecBufLen;
//	static	uint8	Buf[128];
//    uint16	Crc16;
//    uint32	i;
//    
//    for(i = 0; i < 16;i++)
//    {
//	    sModBusRead.DeviceAddr 		= i;
//	    sModBusRead.WorkCode		= MODBUS_READ;
//	   	sModBusRead.RegStart		= 0x1000;
//	   	sModBusRead.RegLenth		= 0x0700;
//	   	   	
//   		Crc16 = GetModBusCrc16Up((uint8 *)&sModBusRead,sizeof(sModBusRead) - 2);
//   	
//   		sModBusRead.Crc16 			= Crc16; 
//   		
//   		SendCOM1((uint8 *)&sModBusRead,sizeof(sModBusRead));
//   		
//   		DelayX10ms(1);
//   		
//		RecBufLen = ReadCOM1(Buf,256);	    
//		
//		if( RecBufLen )
//		{				
//			break;
//	    }
//   	}
//   	
//   	SetPowerAddAndBound(i);
}

//----------------------------------------------------------------------------
// 名    称：   uint8  GetDipData(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
uint8  GetModbusPowerVal(void)
{
//	static	uint8			Buf[256];									
//	static	uint32			Time = 0;
//	static	uint32			Times = 0;
//	uint32					RecBufLen;					
//	
//	if(GetSysTime() - Time > 150)						
//	{
//		if(Times++)
//		{
//			RecBufLen = ReadCOM1(Buf,256);	    
//			
//			if( RecBufLen )
//			{				
//				if(!GetPowerVal(Buf,RecBufLen))						
//				{
//					//printfcom0("\r\nGetPowerVal(Buf,RecBufLen)ERR!");
//				}	
//		    }
//	    }
//	    
//	    Time = GetSysTime();
//    }
//    
    return	0;
}

//------------------------------------------------------------------------
// 名    称：   int16     GetRealData16(int16  Data)
// 功    能：   
// 入口参数：   
//              
// 出口参数：   
//------------------------------------------------------------------------
int16     GetRealData16(uint16  Data)
{
	int16	Tmp;
	
	Tmp = Data;
    if(Data >= 0x8000)
    {
         Tmp = -(Data - 0x8000);
    }

    return  Tmp;
}

//------------------------------------------------------------------------
// 名    称：   int16     GetRealData16(int16  Data)
// 功    能：   
// 入口参数：   
//              
// 出口参数：   
//------------------------------------------------------------------------
int32     GetRealData32(uint32  Data)
{
	int32	Tmp;
	
	Tmp = Data;
    if(Data >= 0x80000000)
    {
         Tmp = -(Data - 0x80000000);
    }

    return  Tmp;
}

int16	l_Voltage;
int16	l_Current;
int16	l_Power;
//	int16	AddNBound;	
int32	l_PosEnergy;
int32	l_NegEnergy;
//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
void  MathPower(stcModBusPower  sModBusPower)
{
//	static	uint32	Time;
	stcPower	sPower;

//	if(GetSysTime() - Time > 150)
	{
		sPower.Voltage 	= GetRealData16((uint16)sModBusPower.Voltage[0]*256 + (uint16)sModBusPower.Voltage[1]);
		sPower.Current 	= GetRealData16((uint16)sModBusPower.Current[0]*256 + (uint16)sModBusPower.Current[1]);
		sPower.Power   	= GetRealData16((uint16)sModBusPower.Power[0]*256   + (uint16)sModBusPower.Power[1]);
		sPower.PosEnergy= GetRealData32(sModBusPower.PosEnergy[0]*256*256*256  + sModBusPower.PosEnergy[1]*256*256
						+ sModBusPower.PosEnergy[2]*256   + sModBusPower.PosEnergy[3]);
		sPower.NegEnergy= GetRealData32(sModBusPower.NegEnergy[0]*256*256*256  + sModBusPower.NegEnergy[1]*256*256
						+ sModBusPower.NegEnergy[2]*256   + sModBusPower.NegEnergy[3]);		
						
//		printfcom0("\r\n voltage %d,%d,%d,%d,%d",(((int32)sPower.Voltage * 1000)/10000),((int32)sPower.Current*5*1000)/10000
//		,(sPower.Power*5*1000*1000)/10000,(sPower.PosEnergy*5*1000*1000)/(1000*3600),(sPower.NegEnergy*5*1000*1000)/(1000*3600));
		
		
		l_Current = ((int32)sPower.Current ) / 2;	
		l_Voltage = ((int32)sPower.Voltage ) /10;
		l_Power	  =	((int32)sPower.Power*5*100);	
		l_PosEnergy=((int32)sPower.PosEnergy)*5*10/36;
		l_NegEnergy= ((int32)sPower.NegEnergy)*5*10/36;

//		Time = GetSysTime();
	}
}	

//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
int16  GetCur(void)
{
	return 	l_Current;
}


//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
int16  GetVol(void)
{
	return 	l_Voltage;	
}

//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
int32  GetPow(void)
{
	return 	l_Power;
}

//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
int32  GetPosEnergy(void)
{
	return 	l_PosEnergy;
}

//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
int32  GetNegEnergy(void)
{
	return 	l_NegEnergy;
}

//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
//int32  GetInitNegEnergy(void)
//{
////	return 	((int32)sPower.NegEnergy);
//}

//----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
//int32  GetInitEnergy(void)
//{
//	return 	((int32)sPower.PosEnergy);
//}
////----------------------------------------------------------------------------
// 名    称：   uint8  GetPower(void)
// 功    能：   取油量数据
// 入口参数：   无
// 出口参数：   无
//----------------------------------------------------------------------------
void  TestPower(void)
{
//	static	uint32	Time = 0;
//	
//	ScanPowerAddr();
//	
//	GetModbusPowerVal();
//	
//	if(GetSysTime() - Time > 100)
//	{
//		MathPower();
//
//		//printfcom0("\r\n%f,%f,%f,%f,%f",(float)(((int32)sPower.Voltage * 1000)/10000),(float)((int32)sPower.Current*5*1000)/10000
//		,((float)sPower.Power*5*1000*1000)/10000,((float)sPower.PosEnergy*5*1000*1000)/(1000*3600),((float)sPower.NegEnergy*50*380)/(1000*3600));
//				
//		////printfcom0("\r\n%hi",-100);				
//		SendReadPowerCode();
//		
//		DelayX10ms(1);
//				
//		Time = GetSysTime();
//	}
//	DelayX10ms(100);
}

uint8  GetCOM1Data(void)
{
	uint8					Buf[64];									
	static	uint32			ErrTimes = 0;
	uint32					RecBufLen;				
	
	RecBufLen = ReadCOM1(Buf,sizeof(Buf));
	 	 
	if( RecBufLen )
	{
		if(!GetPowerVal(Buf,RecBufLen))	
		{
//			printfcom0("\r\n !GetPowerVal(Buf,RecBufLen)");
			return 1;
		}	
	}
    else
    {
		ErrTimes++;
		
		if(ErrTimes > 2)
		{
//			printfcom0("\r\n 111!GetPowerVal(Buf,RecBufLen)");
			//l_DipComErrFlg = ERROR;		
		}
    }
	    
    return	0;
}
void	COM1Task(void)
{
	static	uint32	Time;

	if(GetSysTime() - Time > 100)
	{
		GetCOM1Data();
		
		SendReadPowerCode();			//取电量信号

		Time = GetSysTime();
	}
}
