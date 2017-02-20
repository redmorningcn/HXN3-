#include <includes.h>
#include "GUI.h"

void delay_us(uint16 nUs) 
{ 
uint8 time=12; 
for(;nUs>0;nUs--) 
{ 
time=12; 
while(time>0) 
time--; 
} 
} 

void page5()                                                           
{
//设置视图背景色
SetBcolor(65504);
GUI_CleanScreen();

//画实心椭圆 
SetFcolor(0);
GUI_EllipseFill(32, 47, 182, 121);

//画实心矩形 
SetFcolor(40544);
GUI_RectangleFill(14, 27, 46, 49);

//画空心椭圆 
SetFcolor(13945);
GUI_Ellipse(79, 11, 144, 99);

//画实心椭圆 
SetFcolor(65535);
GUI_CircleFill(174, 102, 17);

//画实心椭圆 
SetFcolor(40147);
GUI_CircleFill(174, 102, 8);

//画空心圆 
SetFcolor(40147);
GUI_Circle(174, 101, 27);

//画线
SetFcolor(51225);
GUI_Line(7, 134, 209, 19);

//文本显示
SetFcolor(0);
SetFont_Region(1, 169,59);
SetTextSpace(0,0);
DisText(132, 200, 0, 6, "１２３");

}

//void ocmLcdTask()
//{
//// delay_us(5000);
////// UartInit();     //串口初始化
//// page5(); 
//// while(1);     
//}
extern	 void Draw8Point(int x0,int y0, int xoff, int yoff);
extern   void SendChar(uint8	Data);
void LcdTask()
{
	uint32	i;
	delay_us(5000);
	  
	GUI_Init(); 

	while(1)
	{	   
		//GUI_Line(7, 134, 209, 19);
		//page5();


         //GUI_SetBkColor(GUI_BLUE);  
         //GUI_SetColor(GUI_RED); 
        GUI_Clear();  

		 //GUI_DispString("Hello world!");
         //GUI_DrawCircle(100,100,50);//画圆

		Draw8Point(100,100,10,10);
		OSTimeDlyHMSM(0,0,0,500);
	}	
}


