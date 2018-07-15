#ifndef ADS1299_H
#define ADS1299_H

#define NO_XSFR_DEFINE
#include "CH559.h"

sbit DOUT=P1^1;
sbit DRDY=P1^0;
sbit CS=P1^3;
sbit ASCLK=P1^2;
sbit START=P1^4;
sbit REST=P1^5;
sbit DIN=P1^7;

void init_ADS();
void readADS();
void readEEG();
UINT8 RREG(UINT8 x,UINT8 y);
void WREG(UINT8 x,UINT8 y,UINT8 d);

#endif