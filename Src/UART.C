/**
	@filename UART.h
	@brief    UART config module, send and read data module
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/
#include "UART.H"
#include "TIME.h"
/*******************************************************************************
* Function Name  : CH559UART0Alter()
* Description    : CH559串口0引脚映射,串口映射到P0.2和P0.3
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH559UART0Alter()
{
   PORT_CFG |= bP0_OC;
   P0_DIR |= bTXD_;
   P0_PU |= bTXD_ | bRXD_;
   PIN_FUNC |= bUART0_PIN_X;                                                  //串口映射到P0.2和P0.3
}

/*******************************************************************************
* Function Name  : mInitSTDIO()
* Description    : CH559串口0初始化,默认使用T1作UART0的波特率发生器,也可以使用T2
                   作为波特率发生器
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void	mInitSTDIO( )
{
    UINT32 x;
    UINT8 x2; 

    SM0 = 0;                                                                   //选择 8 位数据异步通信
    SM1 = 1;                                                                   //设置可变波特率
    SM2 = 0;                                                                   //串口0使用模式1
                                                                               //使用Timer1作为波特率发生器
    RCLK = 0;                                                                  //UART0接收时钟
    TCLK = 0;                                                                  //UART0发送时钟

    PCON |= SMOD;
    x = 10 * FREQ_SYS / BOUND / 16;                             
    x2 = x % 10;
    x /= 10;
    if ( x2 >= 5 ) x ++;                                                       //四舍五入

    TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1;              //0X20，Timer1作为8位自动重载定时器
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;                                        //Timer1时钟选择
    TH1 = 0-x;                                                                 //12MHz晶振,bound/12为实际需设置波特率
    TR1 = 1;                                                                   //启动定时器1
    TI = 1;
    REN = 1;                                                                   //串口0接收使能
}

/*******************************************************************************
* Function Name  : CH559UART0RcvByte()
* Description    : CH559UART0接收一个字节
* Input          : None
* Output         : None
* Return         : SBUF
*******************************************************************************/
UINT8  CH559UART0RcvByte( )
{
   while(RI == 0);                                                            //查询接收，中断方式可不用
   RI = 0;
   return SBUF;
}

/*******************************************************************************
* Function Name  : CH559UART0SendByte(UINT8 SendDat)
* Description    : CH559UART0发送一个字节
* Input          : UINT8 SendDat；要发送的数据
* Output         : None
* Return         : None
*******************************************************************************/
void CH559UART0SendByte(UINT8 SendDat)
{
	SBUF = SendDat;                                                              //查询发送，中断方式可不用下面2条语句,但发送前需TI=0
	while(TI ==0);
	TI = 1;
}

void CH559UART0Interrupt( )  interrupt INT_NO_UART0 using 1                    //看门狗中断服务程序,使用寄存器组1
{
    if(TI)
    {
        TI = 0;                                                                //清空发送中断                        
    }
    if(RI)
    {	
		
    }
}