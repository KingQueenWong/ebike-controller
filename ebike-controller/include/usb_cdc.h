/*
 * usb_cdc.h
 *
 *  Created on: Feb 20, 2017
 *      Author: David
 */

#ifndef USB_CDC_H_
#define USB_CDC_H_

#define DATA_OUT_EP		1
#define DATA_IN_EP		1
#define CMD_IN_EP		2

#define DATA_ENDPOINT_FIFO_SIZE		64
#define CMD_ENDPOINT_FIFO_SIZE		8

#define         DEVICE_ID1          (0x1FFF7A10)
#define         DEVICE_ID2          (0x1FFF7A14)
#define         DEVICE_ID3          (0x1FFF7A18)

#define  USB_SIZ_STRING_SERIAL       0x1A

#define USB_VID                      0x0483
#define USB_PID                      0x5740
#define USB_LANGID_STRING            0x409
#define USB_MANUFACTURER_STRING      "STMicroelectronics"
#define USB_PRODUCT_HS_STRING        "STM32 Virtual ComPort in HS Mode"
#define USB_PRODUCT_FS_STRING        "STM32 Virtual ComPort in FS Mode"
#define USB_CONFIGURATION_HS_STRING  "VCP Config"
#define USB_INTERFACE_HS_STRING      "VCP Interface"
#define USB_CONFIGURATION_FS_STRING  "VCP Config"
#define USB_INTERFACE_FS_STRING      "VCP Interface"
#define USB_MAX_NUM_INTERFACES			1
#define USB_MAX_NUM_CONFIGURATION 		1
#define USB_MAX_STR_DESC_SIZ			0x100

#define CDC_SEND_ENCAPSULATED_COMMAND               0x00
#define CDC_GET_ENCAPSULATED_RESPONSE               0x01
#define CDC_SET_COMM_FEATURE                        0x02
#define CDC_GET_COMM_FEATURE                        0x03
#define CDC_CLEAR_COMM_FEATURE                      0x04
#define CDC_SET_LINE_CODING                         0x20
#define CDC_GET_LINE_CODING                         0x21
#define CDC_SET_CONTROL_LINE_STATE                  0x22
#define CDC_SEND_BREAK                              0x23

typedef struct
{
  uint32_t data[CDC_DATA_HS_MAX_PACKET_SIZE/4];      // Buffer for control transfers
  uint8_t  CmdOpCode;
  uint8_t  CmdLength;
  uint8_t  *RxBuffer;
  uint8_t  *TxBuffer;
  uint32_t RxLength;
  uint32_t TxLength;

  __IO uint32_t TxState;
  __IO uint32_t RxState;
}
USBD_CDC_HandleTypeDef;

typedef struct
{
  uint32_t bitrate;
  uint8_t  format;
  uint8_t  paritytype;
  uint8_t  datatype;
}USBD_CDC_LineCodingTypeDef;

typedef struct
{
    uint8_t Buffer[DATA_ENDPOINT_FIFO_SIZE];
    int Position, Size;
    char ReadDone;
} USB_CDC_RxBufferTypedef;

extern USB_ClassDescTypedef  USB_CDC_ClassDesc;
extern USB_ClassCallbackTypedef USB_CDC_ClassCallbacks;

uint8_t* CDC_DeviceDescriptor(uint16_t* len);
uint8_t* CDC_ConfigDescriptor(uint16_t* len);
uint8_t* CDC_LangIDStrDescriptor(uint16_t* len);
uint8_t* CDC_ManufacturerStrDescriptor(uint16_t* len);
uint8_t* CDC_ProductStrDescriptor(uint16_t* len);
uint8_t* CDC_SerialStrDescriptor(uint16_t* len);
uint8_t* CDC_ConfigurationStrDescriptor(uint16_t* len);
uint8_t* CDC_InterfaceStrDescriptor(uint16_t* len);

void CDC_Init(uint8_t configNum);
void CDC_DeInit(void);
void CDC_Connect(void);
void CDC_Disconnect(void);
void CDC_Reset(void);
void CDC_Setup(USB_SetupReqTypedef* stp);
void CDC_EP0_RxReady(void);
void CDC_DataIn(uint8_t epnum);
void CDC_DataOut(uint8_t epnum);
void CDC_Itf_Control(uint8_t cmd, uint8_t* pbuf, uint16_t length);

int32_t VCP_Read(void* data, int32_t len);
int32_t VCP_Write(const void* data, int32_t len);


#endif /* USB_CDC_H_ */
