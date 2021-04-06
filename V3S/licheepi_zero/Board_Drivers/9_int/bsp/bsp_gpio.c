#include "bsp_gpio.h"

PIO_Map         *PIO = NULL;
PIO_EINT_Map     *PIO_Int = NULL;

void GPIO_Init(PIO_PORT port, unsigned int pin, PIO_MODE mode, PIO_DRV drv, PIO_PULL pul)
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
    PIO->Pn[port].CFG[cfgIndex] &= ~( ((unsigned int) 0x07) << ((pin % 8) * 4));
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
   PIO->Pn[port].DRV[drvIndex] &= ~(((unsigned int)0x03) << ((pin % 16) * 2));
   PIO->Pn[port].DRV[drvIndex] |= (((unsigned int)drv) << ((pin % 16) * 2));


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
   PIO->Pn[port].PUL[pulIndex] &= ~(((unsigned int)0x03) << ((pin % 16) * 2));
   PIO->Pn[port].PUL[pulIndex] |= (((unsigned int)pul) << ((pin % 16) * 2));
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

unsigned int GPIO_GetPinData(PIO_PORT port, unsigned int pin){
    if(PIO == NULL)
        return 0;
    
    if(PIO->Pn[port].DAT & (1<<pin))
        return 1;
    else
        return 0;
}



/**
 *  GPIO 外部中断 初始化
port: port
pin:pin
mode:触发方式
Deb_Clk_Select:消抖时钟源
Deb_Clk_Pre_Scale:Deb_Clk_Pre_Scale */
void GPIO_EINT_Init(PIO_PORT port,
                    unsigned int pin,
                    PIO_EINT_MODE mode,
                    PIO_EINT_DEB_CLK_SELECT Deb_Clk_Select,
                    unsigned int Deb_Clk_Pre_Scale)
{
    //地址映射= 基地址+偏移
    PIO_Int = (PIO_EINT_Map*)(PIO_BASE_ADDRESS + 0x200 );

    /* 
        配置GPIO复用功能 :
        确定 CFG索引号
        以PIN7为例，7/8 = 0，即CFG[索引]=0 
    */
    int cfgIndex = pin / 8 ;      


    /* 
        PIO_EINT_MODE:配置触发模式--------------------------------------------------------------------------
        4i+3 ---- 4i
        以PIN7为例，4*(7%8)+3----4*(7%8) = 31-28 位 ,即左移28位，清除4位，再置位
    */
    PIO_Int->Pn[port].EINT_CFG[cfgIndex] &= ~(((unsigned int)0x0f) << ((pin % 8) * 4));
    PIO_Int->Pn[port].EINT_CFG[cfgIndex] |= (((unsigned int)mode) << ((pin % 8) * 4));

    /*
        设置中断时钟源选择，设置消抖pre_scale = 2^n---------------------------------------------------------
    */
    //6:4 R/W 0 DEB_CLK_PRE_SCALE 设置 2^(0-7)消抖周期
    PIO_Int->Pn[port].EINT_DEB &= ~(((unsigned int)0x07) << 4);
    PIO_Int->Pn[port].EINT_DEB |= ((Deb_Clk_Pre_Scale & 0x07) << 4);

    //PIO Interrupt Clock Select 设置 消抖时钟源
    PIO_Int->Pn[port].EINT_DEB &= ~(((unsigned int)0x01) << 0);
    PIO_Int->Pn[port].EINT_DEB |= (((unsigned int)Deb_Clk_Select) << 0);


    /* PB_EINT_STATUS_REG pin对应的状态位 置0-----------------------------------------------------------------
    */
    //PIO_Int->Pn[port].EINT_STA &= ~(((unsigned int)0x01) << pin);

    /*PB_EINT_CTL_REG 开pin对应的使能位---------------------------------------------------------------------
    */
    PIO_Int->Pn[port].EINT_CTL |= (((unsigned int)0x01) << pin);
}


/* GPIO外部中断全能 */
void GPIO_EINT_CMD(PIO_PORT port,unsigned int pin,unsigned int cmd)
{
    if(PIO_Int == NULL)
        return;

    if(cmd)
    {
        PIO_Int->Pn[port].EINT_CTL |= (((unsigned int)0x01) << pin);
    }
    else
    {
        PIO_Int->Pn[port].EINT_CTL &= ~(((unsigned int)0x01) << pin);
    }
}


/* GPIO 读取指定pin中断状态 */
unsigned int GPIO_EINT_GetStatus(PIO_PORT port,unsigned int pin)
{
    if(PIO_Int == NULL)
        return 0;

    if(PIO_Int->Pn[port].EINT_STA & (((unsigned int)0x01) << pin))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* GPIO 清除中断位 */
void GPIO_EINT_Clean(PIO_PORT port,unsigned int pin)
{
    if(PIO_Int == NULL)
        return;

    /* EINT_STATUS
    External INTn Pending Bit (n = 0~9)
    0: No IRQ pending
    1: IRQ pending
    Write ‘1’ to clear it */
    if(PIO_Int->Pn[port].EINT_STA & (((unsigned int)0x01) << pin))
    {
        PIO_Int->Pn[port].EINT_STA |= (((unsigned int)0x01) << pin);
    }
}
