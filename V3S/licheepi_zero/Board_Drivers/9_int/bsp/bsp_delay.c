#include "bsp_delay.h"

/*
    v3s 延时MS
*/
void delay_ms(volatile unsigned int ms){
    volatile unsigned int n;

    while(ms--){
        //约1MS
        n=0x2155;	//0x63ff;0x18fff;0x9fff;

        while(n--){            
        }
    }
}
