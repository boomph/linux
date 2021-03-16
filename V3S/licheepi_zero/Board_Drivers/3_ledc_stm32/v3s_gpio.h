#ifndef __V3S_LED_H
#define __V3S_LED_H

#define PIO_BASE_ADDRESS 0x01C20800

//unsigned int 4字节 一个PIO_Struct占36字节,对应十六进制就是0x24，正好是一个offset值。
typedef struct{
    volatile unsigned int CFG[4];
    volatile unsigned int DAT;
    volatile unsigned int DRV[2];
    volatile unsigned int PUL[2];
}PIO_Struct;


typedef struct {
    volatile PIO_Struct Pn[7];
}PIO_Map;


typedef enum{
    PIO_PORT_A=0,
    PIO_PORT_B=1,
    PIO_PORT_C=2,
    PIO_PORT_D=3,
    PIO_PORT_E=4,
    PIO_PORT_F=5,
    PIO_PORT_G=6
}PIO_PORT;


typedef enum {
    PIO_MODE_IN = 0x00,
    PIO_MODE_OUT = 0x01,
    PIO_MODE_AUX = 0x02,
    PIO_MODE_INT = 0x06,
    PIO_MODE_DISABLE = 0x07,
}PIN_MODE;

typedef enum{
    PIO_DRV_LEVEL0=0x00,
    PIO_DRV_LEVEL1=0x01,
    PIO_DRV_LEVEL2=0x02,
    PIO_DRV_LEVEL3=0x03,
}PIN_DRV;

typedef enum{
    PIO_PULL_DISABLE = 0X00,
    PIO_PULL_UP = 0X01,
    PIO_PULL_DOWN = 0X02,
}PIN_PUL;



void GPIO_Init(PIO_PORT port, unsigned int pin, PIN_MODE mode, PIN_DRV drv, PIN_PUL pul);
void GPIO_SetPin(PIO_PORT port, unsigned int pin);
void GPIO_ResetPin(PIO_PORT port, unsigned int pin);
unsigned int GPIO_GetPinDat(PIO_PORT port, unsigned int pin);

#endif //__V3S_LED_H
