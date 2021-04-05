#ifndef __BSP_INT_H
#define __BSP_INT_H

#include "v3s_sys.h"


extern char led;
/* 中断处理函数 原型*/
typedef void (*system_irq_handler_t)(unsigned int gicc_iar,void* param);

/* 中断处理结构 */
typedef struct _system_irq_handle
{
    system_irq_handler_t irqHandler;        //中断处理函数
    void* userParam;                        //中断处理函数参数
}system_irq_handle_t;


void v3s_int_init(void);    //中断初始化函数，必须放在代码最前面

/* 注册中断处理函数 */
void system_register_irqHandler(IRQn_Type irq,
                system_irq_handler_t handler,
                void* userParam);


void system_irqhandler(unsigned int gicc_iar);

void system_irqtable_init(void);

/* 默认中断处理函数 */
void default_irqHandler(unsigned int gicc_iar,void* userParam);

#endif //__BSP_INT_H
