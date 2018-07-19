#define NO_XSFR_DEFINE
#include "CH559.h"
#include "DEBUG.h"
#include "ADS1299.h"
#include "USBCOM.h"

void main()
{
	mDelaymS(30);                                                                 //上电延时
	
//  CfgFsys( );                                                                   //CH559时钟选择配置  
	
    mInitSTDIO( );                                                                //串口0,可以用于调试
	USBDeviceCfg();                                                               //设备模式配置
    USBDeviceEndPointCfg();														                            //端点配置
    USBDeviceIntCfg();															                              //中断初始化
	
//	USB_SEND_TEST();
    readEEG();
}

