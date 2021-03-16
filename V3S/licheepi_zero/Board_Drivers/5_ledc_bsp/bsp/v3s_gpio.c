#include "v3s_gpio.h"
#include "v3s_sys.h"

PIO_Map *PIO = NULL;

void GPIO_Init(PIO_PORT port, unsigned int pin, PIN_MODE mode, PIN_DRV drv, PIN_PUL pul)
{    
    PIO = (PIO_Map*)PIO_BASE_ADDRESS;             //结构指向基地址

    /* 
        配置GPIO复用功能 :
        确定 CFG索引号
        以PIN7为例，7/8 = 0，即CFG[索引]=0 
    */
    int cfgIndex = pin / 8 ;               


    /* 
        以PIN7为例，28-30位即 7 % 8 * 4 = 28，清除3位，再置位
    */
    PIO->Pn[port].CFG[cfgIndex] &= ~( ((unsigned int) 0x07) << ((pin % 8) * 4) );
    PIO->Pn[port].CFG[cfgIndex] |= (((unsigned int)mode) << ((pin % 8) * 4));



    /* 
        配置GPIO的电气属性：
        设置驱动等级
        确定 DRV索引号
        以PIN15为例，15 / 16 =0；即DRV[索引]=0
    */
   int drvIndex = pin / 16;

   /* 
        以PIN15为例，2*i+1 : 2*i 位即 2*15+1 : 2*15 = 31 : 30 ，清除2位，再置位
    */
   PIO->Pn[port].DRV[drvIndex] &= ~((unsigned int)0x03) << ((pin % 16) * 2);
   PIO->Pn[port].DRV[drvIndex] |= ((unsigned int)drv) << ((pin % 16) * 2);


   /* 
        配置GPIO的电气属性：
        设置上下拉
        确定 PUL索引号
        以PIN15为例，15 / 16 =0；即PUL[索引]=0
    */
   int pulIndex = pin / 16;

   /* 
        以PIN15为例，2*i+1 : 2*i 位即 2*15+1 : 2*15 = 31 : 30 ，清除2位，再置位
    */
   PIO->Pn[port].PUL[pulIndex] &= ~((unsigned int)0x03) << ((pin % 16) * 2);
   PIO->Pn[port].PUL[pulIndex] |= ((unsigned int)pul) << ((pin % 16) * 2);
}

void GPIO_SetPin(PIO_PORT port, unsigned int pin){
    if(PIO == NULL)
        return;

    PIO->Pn[port].DAT |= (1 << pin);
}

void GPIO_ResetPin(PIO_PORT port, unsigned int pin){
    if(PIO == NULL)
        return;

    PIO->Pn[port].DAT &= ~(1 << pin);
}

unsigned int GPIO_GetPinDat(PIO_PORT port, unsigned int pin){
    if(PIO == NULL)
        return 0;
    
    if(PIO->Pn[port].DAT & (1<<pin))
        return 1;
    else
        return 0;
}
