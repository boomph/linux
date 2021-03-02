#include "v3s_sys.h"
#include "v3s_gpio.h"

int main(void){

    /* PG1 配置为 输出 */
    GPIO_Init(PORT_G,1,MODE_OUT,DRV_LEVEL1,PUL_DISABLE);

    /* PG1 置 0*/
    GPIO_ResetPin(PORT_G,1);

    while(1);
    
    return 0;
}
