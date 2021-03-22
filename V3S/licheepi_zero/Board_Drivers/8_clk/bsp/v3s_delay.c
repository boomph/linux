#include "v3s_delay.h"

/*
    v3s 延时MS
*/
void delay_ms(volatile unsigned int ms){
    volatile unsigned int n;

    while(ms--){
        //约1MS
        n=0x9fff;

        while(n--){            
        }
    }
}
