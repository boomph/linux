#include "v3s_sys.h"
#include "v3s_gpio.h"

/*
    自定义V3S开发板中，驱动PB2=0,PB3=1点亮两个灯
*/
int main(void){
   

   //初始化PB2,PB3为OUT，驱动LEVEL1,禁止上下拉
   GPIO_Init(PIO_PORT_B,2,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
   
   //pb2低电平点亮
   GPIO_ResetPin(PIO_PORT_B,2);

   //pb3高电平点亮
   GPIO_SetPin(PIO_PORT_B,3);

   while(1){}

   return 0;

}
