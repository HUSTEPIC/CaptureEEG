#ifndef ADS1299_H
#define ADS1299_H

#define NO_XSFR_DEFINE
#include "CH559.h"

sbit ASCLK=P1^2;
sbit CS=P1^3;
sbit DIN=P1^7;

sbit START=P1^4;
sbit RESET=P1^5;
sbit PWDN=P1^6;

sbit DOUT=P1^1;
sbit DRDY=P1^0;

void init_ADS();
void readADS();
void readEEG();
UINT8 RREG(UINT8 x,UINT8 y);
void WREG(UINT8 x,UINT8 y,UINT8 d);

#endif