/**
	@filename UART.h
	@brief    UART config module, send and read data module
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/
#ifndef SRC_UART_H_
#define SRC_UART_H_

#define NO_XSFR_DEFINE
#include "CH559.h"

#ifndef BOUND
#define BOUND 9600  // 57600
#endif

void CH559UART0Alter();                  // CH559串口0引脚映射到P0.2/P0.3
void mInitSTDIO();                       // T1作为波特率发生器
UINT8 CH559UART0RcvByte();               // CH559 UART0查询方式接收一个字节
void CH559UART0SendByte(UINT8 SendDat);  // CH559UART0发送一个字节

#endif  // SRC_UART_H_
