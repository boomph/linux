#ifndef __V3S_LED_H
#define __V3S_LED_H

#define PIO_BASE_ADDRESS 0x01C20800

//unsigned int 4字节 一个PIO_Struct占36字节,对应十六进制就是0x24，正好是一个offset值。
typedef struct{
    unsigned int CFG[4];
    unsigned int DAT;
    unsigned int DRV[2];
    unsigned int PUL[2];
}PIO_Struct;


typedef struct {
    PIO_Struct Pn[7];
}PIO_Map;


typedef enum{
    PORT_A=0,
    PORT_B=1,
    PORT_C=2,
    PORT_D=3,
    PORT_E=4,
    PORT_F=5,
    PORT_G=6
}GPIO_PORT;


typedef enum {
    MODE_IN = 0x00,
    MODE_OUT = 0x01,
    MODE_AUX = 0x02,
    MODE_INT = 0x06,
    MODE_DISABLE = 0x07,
}PIN_MODE;

typedef enum{
    DRV_LEVEL0=0x00,
    DRV_LEVEL1=0x01,
    DRV_LEVEL2=0x02,
    DRV_LEVEL3=0x03,
}PIN_DRV;

typedef enum{
    PUL_DISABLE = 0X00,
    PULL_UP = 0X01,
    PULL_DOWN = 0X02,
}PIN_PUL;



void GPIO_Init(GPIO_PORT port, unsigned int pin, PIN_MODE mode, PIN_DRV drv, PIN_PUL pul);
void GPIO_SetPin(GPIO_PORT port, unsigned int pin);
void GPIO_ResetPin(GPIO_PORT port, unsigned int pin);
unsigned int GPIO_GetPinDat(GPIO_PORT port, unsigned int pin);

#endif //__V3S_LED_H
