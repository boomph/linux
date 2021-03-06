#include "v3s_sys.h"
#include "bsp_gpio.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_int.h"



void MyPB2_IRQHandler(unsigned int gicc_iar,void* param)
{
    //检测PB0中断状态
    if(GPIO_EINT_GetStatus(PIO_PORT_B,2))
    {
        if(led)
        {
            led=0;
        }
        else
        {
            led=1;
        }
        //清PB0中断状态
        GPIO_EINT_Clean(PIO_PORT_B,2);
    } 
}

int main(void){
    //PLL_STRUCT* PLL2 = (PLL_STRUCT*)CCU_BASE_ADDRESS;

    // //V3S中断初始化
    // v3s_int_init();
    // //注册中断处理函数
    // system_register_irqHandler(PB_EINT_IRQn,(system_irq_handler_t)MyPB2_IRQHandler,NULL);


    //配置主频
    v3s_clk_init();
    
    //init pb3 输出，HIGH点亮LED
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
    
    //INIT PB2 中断模式,上拉
    // GPIO_Init(PIO_PORT_B,2,PIO_MODE_INT,PIO_DRV_LEVEL0,PIO_PULL_UP);

    
    
    // //GPIO外部中断初始化
    // GPIO_EINT_Init(PIO_PORT_B,2,PIO_EINT_MODE_NEGATIVE_EDGE,PIO_EINT_DEB_LOSC_32KHZ,5);

    // GIC_EnableIRQ(PB_EINT_IRQn);
    // //PLL2->BUS_CLK_GATING_REG2 |= (0x01<<5);//使能 PIO 时钟
    // GPIO_EINT_CMD(PIO_PORT_B,2,1);
    // //GPIO_EINT_Clean(PIO_PORT_B,2);
    
    
    led=1;

    while(1)
    {

        if(led){
            
            GPIO_SetPin(PIO_PORT_B,3);
        }
        else
        {
        
            GPIO_ResetPin(PIO_PORT_B,3);
        }

    }

    return 0;
}
