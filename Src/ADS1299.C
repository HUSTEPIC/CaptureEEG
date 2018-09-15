/**
	@filename ADS1299.C
	@brief    ADS1299 config module and read data module
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/

#include "ADS1299.h"
#include "TIME.h"
#include "UART.h"

/***********SPI Send Function**************
	@param  spidata: Data to send,
	@retval void
******************************************/
void SPI_send(UINT8 spidata)
{
	UINT8 i;
	ASCLK = 0;
	mDelayuS(1);
	for (i=0;i<8;i++)		
   {
  	if(spidata&0x80)
			DIN = 1;
	else
			DIN = 0;
	ASCLK = 1;
	spidata<<= 1;
	mDelayuS(2);
	ASCLK = 0; 
  	mDelayuS(2);
   }
}
/***********SPI Send Function**************
	@param  void
	@retval Data of UINT8 type from register
******************************************/
UINT8 SPI_read(void)
{
    UINT8 j,d;
	for (j=0;j<8;j++)		
	{	 
		d=d<<1;
		ASCLK = 0;
		mDelayuS(2);
		ASCLK=1;
		mDelayuS(2);
		if(DOUT==1)	d=d|0x01;
	}
	ASCLK=0;
	return d;
}

/***********Write A Register**************
	@param  x: Addr of register,
			y: Num of register,
			d: Data to send,
	@retval void
****************************************/
void WREG(UINT8 x, UINT8 y, UINT8 d)
{  
	x=x|0x40;
	y=y&0x1F;
	CS=0;
	SPI_send(x);
	mDelayuS(8);
	SPI_send(y);
	mDelayuS(2);
	SPI_send(d);
	CS=1;
}

/***********Read A Register**************
	@param  x: Addr of register,
			y: Num of register,
	@retval Data of UINT8 type from register
****************************************/
UINT8 RREG(UINT8 x, UINT8 y)		
{
	x=x|0x20;
	y=y&0x1F;
	CS=0;
	ASCLK = 0;
	mDelaymS(1);
	SPI_send(x);
	mDelaymS(8);
	SPI_send(y);
	mDelaymS(2);
	CS=1;
	return SPI_read();
}

/***********Read Data from ADC channel**************
	@param  ch,the buffer to store the data from channel
	@retval Return status to read,0 is successful.
***************************************************/
UINT8 RDATAC(UINT32 *ch)
{	
	UINT8 i,j;
	UINT32 temp=0;
	ASCLK=0;
	CS=0; 
	for(i=0;i<9;i++){
		for(j=0;j<24;j++){
			temp=temp<<1;
			ASCLK=0;
			mDelayuS(2);
			ASCLK=1;
			mDelayuS(2);
			if(DOUT==1)	temp=temp|0x01;
		}
		*(ch+i)=temp;
		temp=0;
		j=0;
	}
	CS=1;
	ASCLK=0;
	return 0;
}

/***********Read Data from ADC channel**************
	@param  void
	@retval Data of UINT8 type from channel
***************************************************/
void Read_ADS1299()
{
	UINT32 ch[9]={0};
	UINT8 EEG_Data[3]={0};
	if(DRDY==0){
		RDATAC(ch);
		EEG_Data[0]=(ch[1]&0xff0000)>>16;
		EEG_Data[1]=(ch[1]&0x00ff00)>>8;
		EEG_Data[2]= ch[1]&0x0000ff;
		Send_ADS1299(EEG_Data);
	}
}

/***********Init ADS1299 IC**************
	@param  void
	@retval void
****************************************/
void Init_ADS1299()
{
	PWDN=1;
	START=0;
	ASCLK=0;
	CS=1;
	RESET=1;
	mDelaymS(200);
	RESET=0;
	mDelayuS(2);
	RESET=1;
	mDelayuS(20);
	CS=0;
	SPI_send(0x11);
	CS=1;
	mDelayuS(2);
	WREG(0x03,0x00,0xEC);  //Configures either an internal or exteral reference and BIAS operation
	WREG(0x01,0x00,0x96);  //This register configures the DAISY_EN bit, clock, and data rate
	WREG(0x02,0x00,0xD4);  //This register configures the test signal generation
	WREG(0x05,0x00,0x00);  //Configures the power mode, PGA gain, and multiplexer settings channels
	WREG(0x0D,0x00,0x01);  //Route channel 1 positive signal into BIAS channel
	WREG(0x0E,0x00,0x01);  //Route channel 1 negative signal into BIAS derivation
	START=0;
	mDelaymS(1);
	START=1;
	CS=0;
	SPI_send(0x10);
	CS=1;
	mDelaymS(1);
}

/***********Init ADS1299 IC**************
	@param  Point of data to send 
	@retval Error value
****************************************/
UINT8 Send_ADS1299(UINT8 *Txdata)
{
	UINT8 i=0;
	CH559UART0SendByte('s');
	CH559UART0SendByte('t');
	for(i = 0; i<3; i++)
	CH559UART0SendByte(*(Txdata+i));
	return 0;
}
