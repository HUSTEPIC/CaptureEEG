/**
	@filename ADS1299.h
	@brief    ADS1299 config module and read data module
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/

#ifndef SRC_ADS1299_H_
#define SRC_ADS1299_H_

#define NO_XSFR_DEFINE
#include "CH559.h"

// #define PCB2_0
// Map pin function
#ifdef PCB2_0
sbit CS = P1^4;
sbit DIN = P1^5;
sbit DOUT = P1^6;
sbit ASCLK = P1^7;
sbit DRDY = P2^5;
sbit START = P1^2;
sbit PWDN = P3^4;
sbit RESET = P3^2;
#else
sbit CS = P1^3;
sbit DIN = P1^7;
sbit DOUT = P1^1;
sbit ASCLK = P1^2;
sbit DRDY = P1^0;
sbit START = P1^4;
sbit PWDN = P1^6;
sbit RESET = P1^5;
#endif

void Init_ADS1299();
UINT8 RDATAC(UINT32 *ch);
void Read_ADS1299();
UINT8 Send_ADS1299(UINT8 *Txdata);
void Read_EEG();

void SPI_send(UINT8 spidata);
UINT8 SPI_read(void);
void WREG(UINT8 x, UINT8 y, UINT8 d);
UINT8 RREG(UINT8 x, UINT8 y);
#endif  // SRC_ADS1299_H_
