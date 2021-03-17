#include "v3s_sys.h"
#include "v3s_gpio.h"


int main(void){
    //init pb2 上拉，作为KEY触发口
    GPIO_Init(PIO_PORT_B,2,PIO_MODE_IN,PIO_DRV_LEVEL0,PIO_PULL_UP);

    //init pb3 输出，当KEY触发时，PB3输出高电平，点亮LED
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);

    //PB3初始为低电平
    GPIO_ResetPin(PIO_PORT_B,3);

    while(1){
//        if(GPIO_GetPinData(PIO_PORT_B,2) == 0)
  //          GPIO_SetPin(PIO_PORT_B,3);
//	else
//	    GPIO_ResetPin(PIO_PORT_B,3);
    }

    return 0;
}
