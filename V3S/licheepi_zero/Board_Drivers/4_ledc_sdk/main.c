#include "v3s_sys.h"
#include "v3s_gpio.h"


int main(void){

    //gpio pb2,pb3 mode = out
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);

   
    //PB3 = HIGH
    GPIO_SetPin(PIO_PORT_B,3);

    while(1){

    }

    return 0;

}
