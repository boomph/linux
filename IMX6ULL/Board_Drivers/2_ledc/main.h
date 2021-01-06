#ifndef __MAIN_H
#define __MAIN_H

/*定义要使用的寄存器*/
/*
    1、使用GPIO1_IO03时钟：CCM_CCGR1，为方便全为1    
*/
#define  CCCM_CCGR0     *((volatile unsigned int *) 0x20c4068)
#define  CCCM_CCGR1     *((volatile unsigned int *) 0x20c406c)
#define  CCCM_CCGR2     *((volatile unsigned int *) 0x20c4070)
#define  CCCM_CCGR3     *((volatile unsigned int *) 0x20c4074)
#define  CCCM_CCGR4     *((volatile unsigned int *) 0x20c4078)
#define  CCCM_CCGR5     *((volatile unsigned int *) 0x20c407c)
#define  CCCM_CCGR6     *((volatile unsigned int *) 0x20c4080)

/*
    2、复用GPIO1_IO03为GPIO1_03:
        IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03    MUX_MODE    5(0X0101)
*/
#define SW_MUX_GPIO1_IO03   *((volatile unsigned int*) 0x020E0068)

/*
    3、设置电气特性:
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03    20E_02F4h
        bit 16:0 HYS 关闭
        bit [15:14]: 00 默认下拉
        bit [13]: 0 kepper 功能
        bit [12]: 1 pull/keeper 使能
        bit [11]: 0 关闭开路输出
        bit [7:6]: 10 速度 100Mhz
        bit [5:3]: 110 R0/6 驱动能力
        bit [0]: 0 低转换率
*/
#define SW_PAD_GPIO1_IO03   *((volatile unsigned int*) 0x020E02F4)

/*
    4、设置GPIO输出方向
    GPIOx_GDIR  GPIO1_GDIR  209_C004
*/
#define GPIO1_DR       *((volatile unsigned int*) 0X0209C000)
#define GPIO1_GDIR     *((volatile unsigned int*) 0x0209C004)

#endif
