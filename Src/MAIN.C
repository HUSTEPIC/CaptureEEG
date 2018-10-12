/**
	@filename Main.C
	@brief    Main Function
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/
#define NO_XSFR_DEFINE
#include "CH559.h"
#include "TIME.h"
#include "ADS1299.h"
#include "UART.h"

void main()  {	
	mDelaymS(30);                     // 上电延时

	mInitSTDIO( );                    // 串口0,可以用于调试
	ES = 1;                           // 开启UART0中断
	EA = 1;                           // 总中断开启,中断初始化
	
	PORT_CFG &= ~bP1_OC;
	P1_DIR |= 0xfC;  		
	P1_IE |= 0x03;   				  // DOUT

	Init_ADS1299();
	mDelayuS(1);	
	START=1;
	mDelayuS(15);

	while(1)  {
		Read_ADS1299();
	}
}

