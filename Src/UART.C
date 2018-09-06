#define NO_XSFR_DEFINE
#include "CH559.h"

                                        
UINT8 uart0_flag;

void CH559UART0Interrupt( )  interrupt INT_NO_UART0 using 1                    //看门狗中断服务程序,使用寄存器组1
{
    if(TI)
    {
        TI = 0;                                                                //清空发送中断                        
    }
    if(RI)
    {	
		uart0_flag=1;
    }
}