#include "v3s_sys.h"
#include "bsp_gpio.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_int.h"


int main(void){
    char led = 1;

    v3s_int_init();

    //配置主频
    v3s_clk_init();
    
    //init pb3 输出，HIGH点亮LED
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
    


    while(1){

        if(led){
            led=0;

            GPIO_SetPin(PIO_PORT_B,3);
        }
        else{
            led=1;
        
            GPIO_ResetPin(PIO_PORT_B,3);
        }

        delay_ms(3000);

    }

    return 0;
}
