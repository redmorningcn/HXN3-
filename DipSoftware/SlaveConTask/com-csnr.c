#include <includes.h>


uint8	GetHdlcFrameEndFlg(void)
{
	return	Gett0HdlcFramEndFlg();	
}

void	ClearHdlcFrameEndFlg(void)
{
	Cleart0HdlcFramEndFlg();   
}

uint8		ReadHdlcFrame(uint8	*buf)  
{
	uint32	reclen;
	reclen 	= ReadSoftCOM(buf);
	return	reclen;	
}
//
//
//uint8	l_hdlcreccomdata = 0;
//uint8	GetHdlcReccomDataNum(void)
//{
//	return l_hdlcreccomdata;
//}

uint8	GetSendHdlcAddr(void)
{
	return	0x75;
}

//void	ClearHdlcReccomDataNum(void)
//{
//	l_hdlcreccomdata = 0;
//}

uint16	g_higval = 500;
uint8	GetSetHdlcDataBuf(uint8 *buf)  
{
	uint8	len;

	len = 0;
	buf[len++] = 0xc5;
	buf[len++] = 0x67;
	buf[len++] = 0x01;

	memcpy(&buf[len],(uint8 *)&g_higval,sizeof(g_higval));
	len += sizeof(g_higval);
	return len;
}
//
//extern	uint8	hdlcreccombuf[256];
void  CSNR_RecDealHostDip(void)     									//主机
{
	uint8	RecBuf[256] = {0};								//接收缓冲区
	uint8	DataBuf[256] = {0};								//
	uint8	souraddr;
	uint32	RecLen,DataLen;
	uint16	dip,hig = 0;
	static	uint16 	lsthig = 0;
	static	uint32	time;
			
	if( GetFramRecEndFlgDip() == 1)						//有新的帧尾，进行数据处理	  ////////////////////////
	{
		ClearFramRecEndFlg();									//清标志，可重新取数

		RecLen 	= ReadRs485DataDip(RecBuf);
		
		souraddr = CSNR_GetData(RecBuf,RecLen,DataBuf,(unsigned char*)&DataLen); 

	 	if(souraddr == 	0x80)
		{ 
			SetLedFlg(DIP_COM_LED,GetSysTime());//led指示		

//			if((GetRecAddr() & 0xa0) == 0xa0)
//			{
//				dip = DataBuf[3]+ DataBuf[2]*256;	
//			}
//			
			if((GetRecAddr() == 0xc1) || (GetRecAddr() == 0xc2))
			{
				memcpy((uint8 *)&dip,&DataBuf[2],sizeof(dip));
			}
			
			printfcom0("\r\n油量：%d",dip);
	
			g_DipVal = dip;
			
			hig = DipConvertHig(dip);
			
			if(GetSysTime()-time > 500)	 		//刷新速度变慢
			{
				time = GetSysTime();
				if(lsthig)	  					
				{
					if(abs(hig - lsthig) < 2)	//波动幅值变小
					{
						g_higval = hig;
					}
					else
					{
						g_higval = (lsthig + hig )/2;
					}
				}
				lsthig = hig;
			}

//			l_hdlcreccomdata = DataLen;
//			memcpy(hdlcreccombuf,DataBuf,l_hdlcreccomdata);
		 }
	}
}
