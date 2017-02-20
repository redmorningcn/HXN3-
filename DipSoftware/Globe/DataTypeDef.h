#ifndef  _DataTypeDef_h_
#define  _DataTypeDef_h_

#include "IdDataTypeDef.h"
#include "CardDataTypeDef.h"
#include "RecDataTypeDef.h"
#include "LocoModTypeDef.h"
#include "GlobePara.h"


//计算模型卡参数
typedef struct _stcSysRunPara_ 					//IC 卡cd参数 352
{
	uint8			StoreTime;					//存储时间间隔  //默认为
	uint8			PrintfFlg;					//打印开关
	uint8			DisHigFlg;					//打印开关
	uint8			NoAvgFlg;
	uint16			CrcCheck;					//CRC检验
}stcSysRunPara;


#define			RIGHT_DATA		0xff

#endif
