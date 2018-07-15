#ifndef USBCOM_H
#define USBCOM_H

#define THIS_ENDP0_SIZE         DEFAULT_ENDP0_SIZE
#define UsbSetupBuf     ((PUSB_SETUP_REQ)Ep0Buffer)

void USBDeviceCfg();
void USBDeviceIntCfg();
void USBDeviceEndPointCfg();
void SendData( PUINT8 SendBuf );
void RecieveData();
void USB_SEND_TEST();

#endif 