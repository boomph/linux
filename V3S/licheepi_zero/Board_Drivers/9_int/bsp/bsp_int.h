#ifndef __BSP_INIT_H
#define __BSP_INIT_H

#include "v3s_sys.h"


/* 注册中断处理函数 */
void system_register_irqHandler(IRQn_Type irq,
                system_irq_handler_t handler,
                void* userParam);

/* 默认中断处理函数 */
void default_irqHandler(unsigned int gicc_iar,void* userParam);

void v3s_int_init(void);    //中断初始化函数，必须放在代码最前面

void system_irqhandler(unsigned int gicc_iar);

#endif //__BSP_INIT_H
