#include "v3s_sys.h"
#include "v3s_gpio.h"
#include "v3s_delay.h"
#include "v3s_clk.h"


int main(void){
    char led = 0;

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

        delay_ms(1000);

    }

    return 0;
}
