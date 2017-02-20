#include <includes.h>

#define		FIRE_DIS_ADDR	0x75
#define		DIP_DIS_ADDR	0x87

//
//unsigned char reverse8( unsigned char c )
//{
//     c = ( c & 0x55 ) << 1 | ( c & 0xAA ) >> 1;
//     c = ( c & 0x33 ) << 2 | ( c & 0xCC ) >> 2;
//     c = ( c & 0x0F ) << 4 | ( c & 0xF0 ) >> 4;
//     return c;
//}
//
//void	HdlcSend(uint8	desaddr,void *buf,uint8	contrl,uint32	buflen)
//{
//	uint8	buftmp[64];
//	uint16	crc16;
//	uint32  len=0;
//
//	len=0;
//	
//	if(buflen>(sizeof(buftmp)+4)) 	//数据过长，不发送
//	return;
//
//	buftmp[len] = desaddr;
//	len += sizeof(desaddr);
//
//	buftmp[len] = contrl;
//	len += sizeof(contrl);
//
//	memcpy(&buftmp[len],buf,buflen);
//	len += buflen;
//
//	crc16 = GetCRCR16_8408_FFFF_FFFF_Table(buftmp,len);
//	memcpy(&buftmp[len],(uint8 *)&crc16,sizeof(crc16));
//	len += sizeof(crc16);
//
//	SendSoftCOM(buftmp,len);
//}
//
//uint8   l_hdlcrecaddr = 0;
//uint8	l_hdlccontrl  = 0;
//uint8	l_hdlcsendnum = 0;
//uint8	l_hdlcrecnum  = 0;
//uint8	l_hdlcpfflg = 0;
//uint8	l_hdlcunumcode = 0;
//uint8	l_hdlcsframcode = 0;
//
//void	GetHdlc(uint8 *buf,uint32 buflen,void *databuf,uint32 *datalen)
//{
//	uint32	i;
//	uint32	len;
//	uint8	tmp;
//	uint16 	crc16,crcrec;
//
//	if(buflen < 4)
//	return;
//
//
// 	printfcom0("\r\n");
//	for(i = 0;i<buflen;i++)
//	{
//		printfcom0("%02x ",buf[i]);		
//	}
//	printfcom0("\r\n");
//	crc16 =  GetCRCR16_8408_FFFF_FFFF_Table(buf,buflen-2);
//	memcpy((uint8 *)&crcrec,&buf[buflen-2],buflen-2);
//	if(crc16 != crcrec)
//	return;
//
//	printfcom0("\r\n");
//	for(i = 0;i<buflen;i++)
//	{
//		printfcom0("%02x ",buf[i]);		
//	}
//
//
//	len = 0;
////	if(buf[len] != DIP_DIS_ADDR)
////	{return;}
//
//	
//
//	l_hdlcrecaddr = buf[len];
//	len++; buflen--;
//	printfcom0(" caddr %02x,",l_hdlcrecaddr);
//
//	tmp = reverse8(buf[len]);
//	printfcom0("contrl rev %x,",tmp);
//	l_hdlccontrl = (tmp>>6)&0x03;
//	printfcom0(" contrl %02x,",l_hdlccontrl);
//
//
//	switch(l_hdlccontrl)
//	{
//
//		case 0x02:	
//					l_hdlcsframcode = (tmp>>4)&0x03;
//					l_hdlcpfflg   = (tmp>>3)&0x01;
//					l_hdlcrecnum  =  (tmp&0x07);
//					printfcom0("framcode %x, cp %02x,l_recnum %02x,",l_hdlcsframcode,l_hdlcpfflg,l_hdlcrecnum);
//					break;
//		case 0x03:
//					l_hdlcunumcode =  (tmp&0x07) + (tmp&(0x03<<4));
//					printfcom0(" numcode %02x,",l_hdlcunumcode);
//					break;
//		default:
//					l_hdlcsendnum = (tmp>>4)&0x07;
//					l_hdlcpfflg   = (tmp>>3)&0x01;
//					l_hdlcrecnum  =  tmp&0x07;
//					printfcom0(" cp %02x,recnum %02x,sennum %02x,",l_hdlcpfflg,l_hdlcrecnum,l_hdlcsendnum);
//					break;					
//	}
//	len++;buflen--;
//	
//	if(buflen>2)
//	{
//		memcpy(databuf,&buf[len],buflen-2);
//		*datalen = buflen-2;
//		printfcom0(" datalen %d",*datalen);
//	}
//}
//
//
//uint8	hdlcreccombuf[256];
//void	hdlctes(void)
//{
//	 uint8 	sendbuf[256];
////	 uint8	hdlcrecdatabuf[256];
//	 uint8	hdlcdatalen;
//	 uint8	len,i;
//
//	 while(1)
//	 {
//	   	if(Gett0HdlcFramEndFlg())
//		{
//			Cleart0HdlcFramEndFlg();
//			len = ReadSoftCOM(sendbuf,sizeof(sendbuf));
//			DataSend_CSNR(0xa1,0x80,sendbuf,len);
//		}
//
//		 CSNR_RecDealHostDip();
//
//		 len = GetHdlcReccomDataNum();
//		 if(len)
//		 {
//		 	 ClearHdlcReccomDataNum();
//		 	 SendSoftCOM(hdlcreccombuf,len);
//		 }
//	 }
//}


extern	unsigned char GetSendHdlcAddr(void);
extern	uint8	GetSetHdlcDataBuf(uint8 *buf) ;
extern	uint16 	GetCRCR16_8408_FFFF_FFFF_Table(unsigned char *crcBuff, unsigned char crcLen) ;
extern	uint8	GetHdlcFrameEndFlg(void);
extern	void	ClearHdlcFrameEndFlg(void);
extern	uint8	ReadHdlcFrame(uint8	*buf);
//extern	uint16	g_dipval;

#define	HDLC_UI_FRAM		0x03
#define	HDLC_SNRM_FRAM		0x83
#define	HDLC_DISC_FRAM		0x43
#define	HDLC_UP_FRAM		0x23
#define	HDLC_UA_FRAM		0x63
#define	HDLC_TEST_FRAM		0xe3
#define	HDLC_SIM_FRAM		0x07
#define	HDLC_FRMR_FRAM		0x87
#define	HDLC_SARM_FRAM		0x0f
#define	HDLC_REST_FRAM		0x8f
#define	HDLC_SARME_FRAM		0x4f
#define	HDLC_SNRME_FRAM		0xcf
#define	HDLC_SABM_FRAM		0x2f
#define	HDLC_XID_FRAM		0x5f
#define	HDLC_SABME_FRAM		0x3f



typedef struct	_stcHdlcPara_
{
	uint8		type;	
	uint8		sendconter;
	uint8		recconter;
	uint8		flg;	
	uint8		code;
	
	uint8		newframeflg;
	uint8		tmp[2];
	
}stcHdlcPara;
static	stcHdlcPara	s_hdlcpara;

uint8	GetUframAnswer(uint8 type)
{
	uint8	code;
	
	
	code =  HDLC_UA_FRAM;
	switch(type)
	{
		case HDLC_UI_FRAM:
			break;
		case HDLC_SNRM_FRAM:
			break;
		case HDLC_DISC_FRAM:
			break;
		case HDLC_UP_FRAM:
			break;
		case HDLC_UA_FRAM:
			break;
		case HDLC_TEST_FRAM:
			break;
		case HDLC_SIM_FRAM:
			break;
		case HDLC_FRMR_FRAM:
			break;
		case HDLC_SARM_FRAM:
			break;
		case HDLC_REST_FRAM:
			break;
		case HDLC_SARME_FRAM:
			break;
		case HDLC_SNRME_FRAM:
			break;
		case HDLC_SABM_FRAM:
			break;
		case HDLC_XID_FRAM:
			break;
		case HDLC_SABME_FRAM:
			break;

		default:;
			
	}
	return code;
}

extern	void	PrintfHdlcBufInfo(uint8 *buf,uint32	buflen) ;
//返回接收参数，数据
uint8	HdlcRecDeal(uint8* databuf,uint32	*datalen)
{
		uint32		len;
		uint16		crc16,crcrec;
		uint8		addr;
		uint8		type;
		uint8		buf[256];
		uint8		movesendbit = 1,moverecbit = 5,moveflgbit = 4,movecodebit=2;
		uint8		i;
		
		*datalen = 0; 		
		len 	= ReadHdlcFrame(buf);
		

//		printfcom0("\r\n接收%d：",len);		
//		
//		for(i = 0;i< len;i++)
//		printfcom0("%02x ",buf[i]);
	
					
		if(len<3)
		return 0;

		SetLedFlg(HDLC_RXD_LED,GetSysTime());	  	//led

		crc16 =  GetCRCR16_8408_FFFF_FFFF_Table(buf,len-2);	
		memcpy((uint8 *)&crcrec,&buf[len-2],2);	
		if(crc16 != crcrec)
		return 0;
		
		addr = buf[0];
		
//		if(addr != )
//		return;
		
		type = buf[1];
		
		switch( type &0x03 )
		{
				case  	0x01: 
							s_hdlcpara.type			= 0x01;
							s_hdlcpara.code 		= (type>>movecodebit)&0x03;
							s_hdlcpara.sendconter	= (((type>>moverecbit)&0x07)+1)%8;		//发送帧++
	
							break;			
				case  	0x03: 
							s_hdlcpara.type			= 0x03;
							s_hdlcpara.code 		= type;
							s_hdlcpara.flg     		= (type>>moveflgbit)&0x01;
							s_hdlcpara.sendconter	= 0;																		//清零
							s_hdlcpara.recconter	= 0;
							break;	
				default	:	
							s_hdlcpara.type			= 0x00;
							s_hdlcpara.recconter	= (type>>movesendbit)&0x07;							//接收帧赋值
							s_hdlcpara.flg     		= (type>>moveflgbit)&0x01;
							*datalen							= len - 2;	
							memcpy(databuf,&buf[2],len-2);
							
						
							if(databuf[0] == 0xc5 &&
							   databuf[1] == 0x68 &&
							   databuf[2] == 0x01 &&
							   (len-2)>4
							   )
							{
//								memcpy((uint8 *)&g_dipval,&databuf[3],2);
//								//printftextbox(" 油量：%d",g_dipval);
							}
		}
		
		s_hdlcpara.newframeflg = 1;

		return 1;			 	
}



extern	void	ClearSoftStart(void);
extern	uint8	GetSoftStart(void);



uint8	HdlcSendDeal(void)
{
	uint8		buf[256];
	uint8		len;
	uint8		movesendbit = 1,moverecbit = 5,moveflgbit = 4,movecodebit=2;	
	uint16		crc16;
	uint32		i;
	
	static	uint32	time = 0;	

	static	uint32	recsframtime;

	if(
			(s_hdlcpara.newframeflg == 1)		|| 
			(GetSysTime() - time > 400)		 	
//			||
//			GetSoftStart()
		)
		{
			
//			ClearSoftStart() ;
			len = 0;
			buf[len++] = GetSendHdlcAddr();
			
			if(s_hdlcpara.newframeflg == 1)																	//刚接收到数据
			{
								
				switch(s_hdlcpara.type)
				{
					case 0x01:
						//s_hdlcpara.type = 03;									//改变
						recsframtime = GetSysTime();							//应答监控帧时间						
						return	0;					
						break;
					case 0x03:
						buf[len++] = GetUframAnswer(s_hdlcpara.type);   		//返回相同,具体后续考虑
						break;
					case 0x00:
						buf[len++] = (s_hdlcpara.recconter << moverecbit) + (s_hdlcpara.flg<< moveflgbit) + 0x01;	//应答RR帧
						break;
					default:;
				}
				
				s_hdlcpara.newframeflg = 0; 
			}
			else
			{
				time = GetSysTime();
				
				len = 0;
				buf[len++] = GetSendHdlcAddr();

				buf[len++] =((s_hdlcpara.sendconter<<movesendbit)) + (s_hdlcpara.flg<< moveflgbit);  
				
//				if(GetSysTime() - recsframtime > 100*30)  		//长时间未应答，跳过此帧
//					s_hdlcpara.sendconter++;	
				
				len += GetSetHdlcDataBuf(&buf[len]); 			//赋值		
			}
			
			crc16 =  GetCRCR16_8408_FFFF_FFFF_Table(buf,len); 
			memcpy(&buf[len],(uint8 *)&crc16,sizeof(crc16));
			len += sizeof(crc16) ;		
			
			//DataSend_CSNR(0x80,0xA1,(unsigned char *)&buf,len);	
			SendSoftCOM((unsigned char *)&buf,len);
			
			
			SetLedFlg(HDLC_TXD_LED,GetSysTime());		//led	
			printfcom0("\r\n发送%d：",len);
			for(i=0;i<len;i++)
			{
				printfcom0("%02x. ",buf[i]);	
			}
			printfcom0("\r\n");
//			PrintfHdlcBufInfo(buf,len); 
	}
	
	return 1;
}


void HdlcDeal(void)
{
	uint8			buf[256];
	uint32		len;
	uint8			flg;
	static		uint32	systime = 0; 
	
	if(GetHdlcFrameEndFlg())		//hdlc 从串口接收  
	{
		ClearHdlcFrameEndFlg(); 
		
		HdlcRecDeal(buf,(uint32 *)&len);
	}
	
  CSNR_RecDealHostDip();			//com 接收统计装置数据

	HdlcSendDeal();							//hdlc 发送到串口
	
	if(GetSysTime() - systime > 150)
	{
		SetCOM1Bout(9600);

		HostScanDip();
		systime = GetSysTime();
//		
		SetCOM1Bout(57600);
	}

}
