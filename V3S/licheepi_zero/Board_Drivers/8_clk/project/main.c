#include "v3s_sys.h"
#include "v3s_gpio.h"
#include "v3s_delay.h"


int main(void){
    char led = 0;

    //init pb2 输出，低点亮LED
    GPIO_Init(PIO_PORT_B,2,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
    


    while(1){

        if(led){
            led=0;

            GPIO_ResetPin(PIO_PORT_B,2);
        }
        else{
            led=1;
        
            GPIO_SetPin(PIO_PORT_B,2);
        }

        delay_ms(1000);

    }

    return 0;
}
