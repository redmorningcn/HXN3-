/*
*********************************************************************************************************
*                                              uC/OS-II
*                                        The Real-Time Kernel
*
*                          (c) Copyright 2004-2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/OS-II is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/OS-II in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/OS-II.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                        IAR Development Kits
*                                               on the
*
*                                            NXP LPC1768
*                                      LPC1766-SK KICKSTART KIT
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_MODULES_PRESENT
#define  INCLUDES_MODULES_PRESENT

/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

//#include  <cpu.h>
//#include  <lib_def.h>
//#include  <lib_ascii.h>
//#include  <lib_math.h>
//#include  <lib_mem.h>
//#include  <lib_str.h>


/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/

#include  <app_cfg.h>
//#include  <bsp.h>
//#include  <csp.h>

/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <ucos_ii.h>
 
extern	void  OS_InitTaskIdle (void);

/*
*********************************************************************************************************
*                                               SERIAL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 TCP-IP
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 APP
*********************************************************************************************************
*/


#include  "lpc17xx_pinsel.h"
#include  "lpc17xx_gpio.h"
#include  "lpc17xx_clkpwr.h"
#include  "lpc17xx_uart.h"
#include  "lpc17xx_systick.h"
#include  "lpc17xx_spi.h"
#include  "lpc17xx_ssp.h"
#include  "lpc17xx_i2s.h"
#include  "lpc17xx_gpdma.h"
#include  "lpc17xx_timer.h"
#include  "lpc17xx_iap.h"
#include  "lpc17xx_wdt.h"

#include  "debug_frmwrk.h"


#include  "mx25l1602drv.h"
/*
*********************************************************************************************************
*                                                 APP_TEST
*********************************************************************************************************
*/
#include  	"string.h"
#include  	"UART_Test.h"
#include  	"GPIO_Test.h"
#include  	"GPIO_APP.h"
#include  	"SPI_Test.h"

#include	"DataTypeDef.h"
#include	"FIFO.h"
#include	"globe.h"



#include	"tmp.h"
extern	void	nop(void);
extern	uint32	GetSysTime(void);
extern	void	DelayX10ms(uint32	Time);
extern	unsigned short GetModBusCrc16Up(unsigned char *puchMsg,unsigned short  usDataLen);
extern	uint16 GetCrc16Check(uint8 *Buf, uint16 Len);
extern	uint8 SendCOM0(void *buf,uint32 len);
extern	uint32 ReadCOM0(uint8 *buf,uint32 len);
extern	uint8 SendCOM1(void *buf,uint32 len);
extern	uint32 ReadCOM1(uint8 *buf,uint32 len);
extern	uint8 SendCOM2(void *buf,uint32 len);
extern	uint32 ReadCOM2(uint8 *buf,uint32 len);
extern	uint8 SendCOM3(void *buf,uint32 len);
extern	uint32 ReadCOM3(uint8 *buf,uint32 len);

extern	uint8   GetOilBoxCod(void);

extern	int16  GetDip1Prs(void);
extern	int16  GetDip2Prs(void);

extern	uint8	ReadDensity(stcDensity * sDensity);
extern	uint8	ReadReviseHight(stcReviseHight * sReviseHight);
extern	uint8	ReadAddDipVal(stcAddDipVal * sAddDipVal);
extern	uint32 	DisplaySet(uint32 Time,uint32 Degree,char *fmt, ... ); 

extern	uint8	ReadCardFlg(void);
extern	uint8	ReadSelectModel(uint8	*ModelNum);
extern	uint8	JudgeOilEvt(void);
extern	void 	OnLed(uint8 num,uint32 times,uint16	LightTime,uint16 unLightTime);
extern	uint8	StoreOilBoxModel(uint32 add,uint8	*buf,uint32	bufsize);
extern	void 	OffLed(uint8 num);
extern	void  	FeedDog(void);
extern	uint8	StoreDensity(stcDensity * sDensity);
extern	void    WriteTime(stcTime  sTime);
extern	uint8	ReadFlshRec(stcFlshRec * sFlshRec,uint32	FlshRecNum);
extern	uint32 	GetCurFlshRecNum(void);
extern	uint8  	JudgeCalcError(void);
extern	uint8	ReadTime(stcTime  *  sTime);
extern	uint8 	StoreFixInfo(stcFixInfo * sFix);
extern	uint8	StoreSelectModel(uint8	ModelNum);
extern	uint8	StoreReviseHight(stcReviseHight * sReviseHight);
extern	void	NOP(void)  ;
extern	uint8	GetOilBoxModelsModel(stcModel * sModel);
extern	void	DataCard(uint8 copyflg);
extern	void	SetReadDataFlgTrue(void);
extern	uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo);
extern	uint8	GetReadDataFlg(void);
extern	uint8	SetParaFlgTrue(void);
extern	uint8	GetSetParaFlg(void);
extern	void 	ClaerDisplaySetWithoutStore(void);
extern	uint32 	ReadLstRedFlshRecNum(void);
extern	void 	ClaerDisplaySet(void);
extern	uint8	FixCard(void);
extern	void 	OffAllLed(void);
extern	uint8	DensityCard(void);
extern	uint8	ModCard(void);
extern	void  	ResetSys(void);
extern	uint8 	HoldTask(void);
extern	uint16 	GetTrainSpeed(void);
extern	uint32 	GetTrainKm(void);


extern	int16		l_Dip1Prs;							
extern	int16		l_Dip2Prs;

extern int8			l_Dip1Tmp;
extern int8			l_Dip2Tmp;
extern uint8		l_Dip1ErrCod;
extern uint8		l_Dip2ErrCod;
extern unsigned short 	l_dip1den;
extern unsigned short 	l_dip2den;




typedef	struct	_stcCalDist_
{
	uint32	ModDPR;					//计算余量
	uint32	Dist;					//里程
}stcCalDist;

typedef struct _stcDist_						//油尺
{
	stcCalDist	A_sDist;						//总里程
	stcCalDist	C_sDist;						//分段里程
	stcCalDist	E_sDist;						//自定义里程
	uint32		Rec32;							//预留4字节
	uint16		Speed;							//速度
	uint16		Crc16;							//CRC检验
}stcDist;




typedef	struct	_stcSpeedPluse
{
	uint32	PluseCnt;									//脉冲
	uint32	TimeCnt;
}stcSpeedPluse;


typedef struct _stcSysPra_						//系统参数
{
	uint32		SysStartTimes;					//预留4字节
	uint32		StoreErrTimes;					//存储错误次数
	uint32		ComErrTimes;					//通信错误次数
	uint32		ErrbckTimes;					//通信错误次数
	uint32		DistPra;						//修正系数
	uint8		DisplayTimes;					//显示次数
	uint8		Bck;							//显示次数
	uint16		Crc16;							//CRC检验
}stcSysPra;

#pragma diag_suppress 870, 223


#define		COM_LED_REC			1
#define		COM_LED_DATA		2

/*
*********************************************************************************************************
*                                                 APP_Distance
*********************************************************************************************************
*/
//#include  "Display.h"
//#include  "Speak.h"
//#include  "FIFO.h"
//
//#include  "WriteDataIAP.h"
/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/

#endif
