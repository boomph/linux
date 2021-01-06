#include "main.h"
/*
    使能外设时钟
*/
void clk_enable(void)
{
    CCCM_CCGR0=0XFFFFFFFF;
    CCCM_CCGR1=0XFFFFFFFF;
    //.....
}

/**
 * 初始化LED
 * 
 */
void led_init(void)
{
    /**
     * 复用为GIIO1-IO03
    */
    SW_MUX_GPIO1_IO03=0X05 ;

    /**
     * 设置GPIO1-IO03电气特性
    */
    SW_PAD_GPIO1_IO03 = 0X10B0;

    /**
     * 设置GPIO1-IO03方向=输出
    */
   GPIO1_GDIR = 0X8;

   /**
    * 驱动GPIO=开灯
   */
  GPIO1_DR=0X0;

}

int main(void)
{
    clk_enable();
    /***/
    led_init();

    /**/
    
    while(1);

    return 0;
}