#define NO_XSFR_DEFINE
#include "CH559.h"
#include "DEBUG.h"
#include "ADS1299.h"
#include "USBCOM.h"

void main()
{
	mDelaymS(30);                                                                 //上电延时
	init_ADS();
	
//  CfgFsys( );                                                                   //CH559时钟选择配置  
	
    mInitSTDIO( );                                                                //串口0,可以用于调试
	USBDeviceCfg();                                                               //设备模式配置
    USBDeviceEndPointCfg();														                            //端点配置
    USBDeviceIntCfg();															                              //中断初始化
	
	UEP0_T_LEN = 0;
    UEP1_T_LEN = 0;	                                                              //预使用发送长度一定要清空	
    UEP2_T_LEN = 0;	
	
//	USB_SEND_TEST();
    readEEG();
}

