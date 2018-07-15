#include "ADS1299.h"
#include "DEBUG.h"
#include "USBCOM.h"

UINT32 ch0,ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8;

//***********************************ADS1299********************
void WREG(UINT8 x,UINT8 y,UINT8 d)	   //只写一个字节
{  
   UINT8 i;
   x=x|0x40;  
   y=y&0x1F;
   ASCLK = 0;
   CS=0;
   mDelaymS(1);
      for (i=0;i<8;i++)	   //写地址
   {
    	if(x&0x80)
 			DIN = 1;
    	else
			DIN = 0;
      	ASCLK = 1;
	    x<<= 1;
	    mDelaymS(2)  ;
	    ASCLK = 0; 
     	mDelaymS(2);
   }
  mDelaymS(8);
	 for (i=0;i<8;i++)	    //写寄存器数
	{
		if(y&0x80)
			DIN = 1;
		else
			DIN = 0;
		ASCLK = 1;
		y<<= 1;
		mDelaymS(2)  ;
		ASCLK = 0; 
		mDelaymS(2);
	 }
  mDelaymS(2);
     for (i=0;i<8;i++)		//写数据
  {
  	if(d&0x80)
			DIN = 1;
	else
			DIN = 0;
	ASCLK = 1;
	d<<= 1;
	mDelaymS(2)  ;
	ASCLK = 0; 
  	mDelaymS(2);
  }
  CS=1;
  ASCLK=0;
}
//************************************************************************
//UINT8 RREG(UINT8 x,UINT8 y)		//读一个寄存器
//{
//   UINT8 i,d;
//   x=x|0x20;
//   y=y&0x1F;
//   ASCLK = 0;
//   CS=0;
//   mDelaymS(1);
//      for (i=0;i<8;i++)		//写寄存器地址
//   {
//    	if(x&0x80)
// 			DIN = 1;
//    	else
//			DIN = 0;
//      	ASCLK = 1;
//	    x<<= 1;
//		mDelaymS(2)  ;
//	    ASCLK = 0; 
//	    mDelaymS(2)  ;
//    }
//  mDelaymS(8);
//     for (i=0;i<8;i++)	   //写寄存器数
//    {
//    	if(y&0x80)
//			DIN = 1;
//    	else
//			DIN = 0;
//	    ASCLK = 1;
//		  mDelaymS(2)  ;
//	    y<<= 1;
//    	ASCLK = 0; 
//		mDelaymS(2)  ;
//   }
//	 mDelaymS(2);
//    for (i=0;i<8;i++)		//读数据
//  {	 d=d<<1;
//    ASCLK = 0;
//    mDelaymS(2);
//	ASCLK=1;
//	mDelaymS(2);
//  	if(DOUT==1)	d=d|0x01;
//	DIN=0;  
//  }
//  CS=1;
//  ASCLK=0;
//  return d;
//}
//**************************************************************************
void send_C(UINT8 C)
{
  UINT8 i;
  ASCLK = 0;
  CS=0;
  mDelaymS(1);
  for (i=0;i<8;i++)
  {
  	if(C&0x80)
			DIN = 1;
	else
			DIN = 0;
	ASCLK = 1;
	C<<= 1;
	mDelaymS(2)  ;
	ASCLK = 0; 
  	mDelaymS(1);
  }
   CS=1;
}

// ******************************************
unsigned long readA()
{	 
	 UINT8 i;
     unsigned long ch=0; 
   	for(i=0;i<24;i++)
	{   ch=ch<<1;
	   ASCLK=0;
	   mDelaymS(2);
	   ASCLK=1;
	  	mDelaymS(2);
		 if(DOUT==1)	ch=ch|0x01; 
	   DIN=0; 
	}
	return ch;
}
//***************************************
void readADS()
{
	ASCLK=0;
    CS=0; 
	ch0=readA();
	ch1=readA();
    ch2=readA();
	ch3=readA();
	ch4=readA();
	ch5=readA();
    ch6=readA();
	ch7=readA();
	ch8=readA(); 
	CS=1;
	ASCLK=0;
} 
//*****************************
 void init_ADS()
 {
 	START=0;
	ASCLK=0;
	CS=1;
	REST=1;
 	mDelaymS(200);
 	REST=0;
	mDelaymS(2);
	REST=1;
 	mDelaymS(20);	
	send_C(0x11);
    mDelaymS(1);
    WREG(0x03,0x00,0xEC);  //config3设置内部电压参考,偏置基准、测量等
	WREG(0x01,0x00,0x96);  
	WREG(0x02,0x00,0xD4);  //config2设置内部测试信号,校准信号幅值、引线检测方式
	WREG(0x05,0x00,0x00);  //ch1set 设置通道1电源模式，增益，SRB2，输入多路选择；
	WREG(0x0D,0x00,0x01);  //BIAS_SENSP 设置通道1的P端为偏置驱动
	WREG(0x0E,0x00,0x01);  //BIAS_SENSN 设置通道1的N端为偏置驱动   
	START=0;
    mDelaymS(1);
    START=1;
	send_C(0x10);
	mDelaymS(1);
 }

 
 /*************************************************************/
void readEEG()
{ 	 
	 UINT8 q,x,y,z; 
	 UINT8 i=0;
	 CS=1;
	 START=0;
	 mDelaymS(1);	
     START=1;
     mDelaymS(15);
     while(1)
     {   
	  if(DRDY==0){ 
	    readADS(); 
	    if(ch1&0x800000){ 
		  q=0x81;
		  ch1=~ch1+1;
		  x=(ch1&0xff0000)>>16;
		  y=(ch1&0x00ff00)>>8;
		  z= ch1&0x0000ff;  
		 }
		else{
		  q=0x80; 
		  x=(ch1&0xff0000)>>16;
		  y=(ch1&0x00ff00)>>8;
		  z= ch1&0x0000ff;  
		}
		SendData(&q);
		SendData(&x);
		SendData(&y);
		SendData(&z);		
      }
     }
}