#include "v3s_sys.h"
#include "bsp_gpio.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_int.h"

char led = 0;

void MyPB2_IRQHandler(unsigned int gicc_iar,void* param)
{
    if(led)
    {
        led=0;
    }
    else
    {
        led=1;
    }
    /* //检测PB0中断状态
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
    } */
}

int main(void){

    //V3S中断初始化
    v3s_int_init();
    //注册中断处理函数
    system_register_irqHandler(PB_EINT_IRQn,MyPB2_IRQHandler,NULL);


    //配置主频
    v3s_clk_init();
    
    //init pb3 输出，HIGH点亮LED
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
    
    //INIT PB2 中断模式,上拉
    GPIO_Init(PIO_PORT_B,2,PIO_MODE_INT,PIO_DRV_LEVEL1,PIO_PULL_UP);

    
    //GPIO外部中断初始化
    GPIO_EINT_Init(PIO_PORT_B,2,PIO_EINT_MODE_NEGATIVE_EDGE,PIO_EINT_DEB_LOSC_32KHZ,7);
    GPIO_EINT_CMD(PIO_PORT_B,2,1);
    GPIO_EINT_Clean(PIO_PORT_B,2);
    
    

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
