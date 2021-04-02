#ifndef __V3S_GPIO_H
#define __V3S_GPIO_H


//unsigned int 4字节 一个PIO_Struct占36字节,对应十六进制就是0x24，正好是一个offset值。
//GPIO 结构体
typedef struct{
    volatile unsigned int CFG[4];
    volatile unsigned int DAT;
    volatile unsigned int DRV[2];
    volatile unsigned int PUL[2];
}PIO_Struct;

//GPIO 映射体
typedef struct {
    volatile PIO_Struct Pn[7];
}PIO_Map;


//GPIO PORT
typedef enum{
    PIO_PORT_A=0,
    PIO_PORT_B=1,
    PIO_PORT_C=2,
    PIO_PORT_D=3,
    PIO_PORT_E=4,
    PIO_PORT_F=5,
    PIO_PORT_G=6
}PIO_PORT;

//GPIO 输入输出模式
typedef enum {
    PIO_MODE_IN = 0x00,
    PIO_MODE_OUT = 0x01,
    PIO_MODE_AUX = 0x02,
    PIO_MODE_RESV1 = 0x03,
    PIO_MODE_RESV2 = 0x04,
    PIO_MODE_RESV3 = 0x05,
    PIO_MODE_INT = 0x06,
    PIO_MODE_DISABLE = 0x07,
}PIO_MODE;

//GPIO 驱动等级
typedef enum{
    PIO_DRV_LEVEL0=0x00,
    PIO_DRV_LEVEL1=0x01,
    PIO_DRV_LEVEL2=0x02,
    PIO_DRV_LEVEL3=0x03,
}PIO_DRV;

//GPIO 上下拉
typedef enum{
    PIO_PULL_DISABLE = 0X00,
    PIO_PULL_UP = 0X01,
    PIO_PULL_DOWN = 0X02,
}PIO_PULL;



/*----------------------------------------------------------
     gpio 外部中断 
*/
/*
    GPIO 中断结构体 
    大小 = 0x20
    地址 = 基址 + 0x200 + 0x20*n
*/
typedef struct{
    volatile unsigned int EINT_CFG[4];
    volatile unsigned int EINT_CTL;
    volatile unsigned int EINT_STA;
    volatile unsigned int EINT_DEB;
    volatile unsigned int EINT_RESV;//保留
}PIO_EINT_Struct;

//GPIO 中断映射体
typedef struct {
    volatile PIO_EINT_Struct Pn[7];
}PIO_EINT_Map;

/*
    GPIO 中断触发方式
    External INTn Mode 
*/
typedef enum{
    PIO_EINT_MODE_POSITIVE_EDGE   = 0X0,
    PIO_EINT_MODE_NEGATIVE_EDGE   = 0X1,
    PIO_EINT_MODE_HIGH_LEVEL      = 0X2,
    PIO_EINT_MODE_LOW_LEVEL       = 0X3,
    PIO_EINT_MODE_DOUBLE_EDGE     = 0X4,    
}PIO_EINT_MODE;

/*
    GPIO 中断使能
    External INTn Enable (n = 0~9)
*/
typedef enum{
    PIO_EINT_CMD_Disable         = 0,
    PIO_EINT_CMD_Enable          = 1,
}PIO_EINT_CMD;

/**
    GPIO 中断状态标志
    External INTn Pending Bit (n = 0~9)
*/
typedef enum{
    PIO_EINT_STATUS_No_IRQ_Pending      = 0,
    PIO_EINT_STATUS_IRQ_Pending         = 1,
}PIO_EINT_STATUS;

/* 
    GPIO PIO_INT_CLK_SELECT 中断时钟源选择
    PIO Interrupt Clock Select
    
    注：
        中断消抖时钟源     BIT 6-4 : DEB_CLK_PRE_SCALE
        Debounce Clock Pre-scale n
        The selected clock source is prescaled by 2^n

        推测--------------------------------------------------------
        以32.768khz晶振为例：
            1/32768 ≈ 0.03052ms
            DEB_CLK_PRE_SCALE n = 7 => 2^7 * 0.03052ms = 3.90656ms消抖
*/
typedef enum{
    PIO_EINT_DEB_LOSC_32KHZ      = 0,
    PIO_EINT_DEB_HOSC_24MHZ      = 1,
}PIO_EINT_DEB_CLK_SELECT;


#endif //__V3S_GPIO_H
