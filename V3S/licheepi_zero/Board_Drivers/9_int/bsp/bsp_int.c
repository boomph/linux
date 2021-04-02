#include "bsp_int.h"

//记录当前中断嵌套
static unsigned int irqNesting=0;

/* 中断处理结构表 */
static system_irq_handle_t             irqTable[NUMBER_OF_INT_VECTORS];

/* 初始化中断处理结构表*/
void system_irqtable_init(void)
{
    unsigned int i=0;

    //清0中断嵌套数
    irqNesting = 0;

    for(i=0;i<NUMBER_OF_INT_VECTORS;i++)
    {
        irqTable[i].irqHandler  = default_irqHandler;
        irqTable[i].userParam   = NULL;
    }
}

/* 注册中断处理函数 */
void system_register_irqHandler(IRQn_Type irq,
                system_irq_handler_t handler,
                void* userParam)
{
    irqTable[irq].irqHandler    = handler;
    irqTable[irq].userParam     = userParam;
}


/* 默认中断处理函数 */
void default_irqHandler(unsigned int gicc_iar,void* userParam)
{
    while(1)
    {
        //nothing...
    }
}

/* 
中断初始化 
一定要放在代码最前面
*/
void v3s_int_init(void)
{
    //GIC中断控制器初始化
    GIC_Init();

    //设置中断偏移，也可以在start.S-->reset_handler中设置
    //我选择在reset_handler中设置
    //__set_VBAR(0x41000000);

    //中断处理结构表初始化
    system_irqtable_init();

    //注册中断处理函数
    
}

/* 具体的中断处理函数，IRQ_Handler会调用此函数 */
void system_irqhandler(unsigned int gicc_iar)
{
    unsigned int intNum = gicc_iar & 0x03ff;

    /* 
        检查中断ID 
        1023 = BIT 9--0 全为1，非法
    */
    if((intNum == 1023) || (intNum >= NUMBER_OF_INT_VECTORS))
    {
        return;
    }

    //中断嵌套计数+1
    irqNesting++;

    /* 根据中断ID号，读取中断处理函数，然后执行 */
    irqTable[intNum].irqHandler(gicc_iar,irqTable[intNum].userParam);

    //中断嵌套计数-1
    irqNesting--;
}

