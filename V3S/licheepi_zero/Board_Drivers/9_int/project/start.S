.global _start
.global _bss_start
.global _bss_end

_bss_start:
    .word __bss_start

_bss_end:
    .word __bss_end

    
_start:
    /* ********************************************************************
        中断向量表 
        pc寄存器保存要执行的代码
    */
    ldr pc,=Reset_Handler //复位中断服务函数
    ldr pc,=Undefined_Handler       //未定义指令中断服务函数
    ldr pc,=SVC_Handler             //SVC
    ldr pc,=PreAbort_Handler        //预取终止
    ldr pc,=DataAbort_Handler       //数据终止
    ldr pc,=NotUsed_Handler         //未使用
    ldr pc,=IRQ_Handler             //IRQ中断
    ldr pc,=FIQ_Handler             //FIQ中断


    /* *******************************************************************
        中断服务函数 位置可以随意     
    */

    /* 复位中断服务函数 */
Reset_Handler:

#if 0
    /* -------------------------------------------------------------------
        关IRQ中断，防止干扰
     */
    cpsid i

    /*--------------------------------------------------------------------
        关闭I、D Cache和MMU
        修改SCTLR寄存器，采用读-改-写的方式
    */
    MRC p15,0,r0,c1,c0,0        //读取SCTLR寄存数据到r0
    //bic指令用于清空指定位
    bic r0,r0,#(1<<12)          //关闭 I Cache
    bic r0,r0,#(1<<11)          //关闭分支预测
    bic r0,r0,#(1<<2)           //关闭 D Cache
    bic r0,r0,#(1<<1)           //关闭对齐
    bic r0,r0,#(1<<0)           //关闭MMU
    MCR p15,0,r0,c1,c0,0        //r0的数据写入到SCTLR寄存器



    /* -------------------------------------------------------------------
        设置中断向量偏移 ，可以在C语言中设置，只要在中断发生前设置
    */
    ldr r0,=0x41000000          //新的中断向量首地址
    dsb                         //数据同步，当前面存储操作完毕，才执行后面的指令
    isb                         //指令同步，当前面指令执行完毕，才执行后面的指令
    MCR p15,0,r0,c12,c0,0       //设置VBAR寄存器
    dsb
    isb
#endif

    /* -------------------------------------------------------------------
        清 bss 段 
    */
    ldr r0,_bss_start
    ldr r1,_bss_end
    ldr r2,=0x0
bss_loop:
    stmia r0!,{r2}
    cmp r0,r1
    ble bss_loop

    /* --------------------------------------------------------------------
        设置处理器在不同模式下的SP指针，重点：SVC,IRQ,SYS
        其他模式按程序功能添加
     */
    /* 
        设置处理器进入SYS模式 !!!
    */
    mrs r0,cpsr                 //读取CPSR到R0
    bic r0,r0,#0x1f             //清除CPSR的bit4-0
    orr r0,r0,#0x1F             //进入SYS模式
    msr cpsr,r0                 //将R0写入CPSR
    ldr sp,=0x40060000          //设置SYS模式下SP

    /* 
        设置处理器进入IRQ模式 !!!
    */
    mrs r0,cpsr                 //读取CPSR到R0
    bic r0,r0,#0x1f             //清除CPSR的bit4-0
    orr r0,r0,#0x12             //进入IRQ模式
    msr cpsr,r0                 //将R0写入CPSR
    ldr sp,=0x40040000          //设置IRQ模式下SP

    /* 
        设置处理器进入SVC模式 !!!
    */
    mrs r0,cpsr                 //读取CPSR到R0
    bic r0,r0,#0x1f             //清除CPSR的bit4-0
    orr r0,r0,#0x13             //进入SVC模式
    msr cpsr,r0                 //将R0写入CPSR
    ldr sp,=0x40020000          //设置SVC模式下SP

#if 0
    /* -------------------------------------------------------------------
        打开IRQ中断
     */
    cpsie i
#endif

    /* ---------------------------------------------------------------------
       跳转C语言main函数
    */
    b main
    

    /* 未定义指令中断服务函数 */
Undefined_Handler:
    ldr r0,=Undefined_Handler
    bx r0

    /* SVC中断服务函数 */
SVC_Handler:
    ldr r0,=SVC_Handler
    bx r0

    /* 预取终止中断服务函数 */
PreAbort_Handler:
    ldr r0,=PreAbort_Handler
    bx r0

    /* 数据终止中断服务函数 */
DataAbort_Handler:
    ldr r0,=DataAbort_Handler
    bx r0

    /* 未使用中断服务函数 */
NotUsed_Handler:
    ldr r0,=NotUsed_Handler
    bx r0

    /* IRQ中断服务函数 */
IRQ_Handler:
    ldr r0,=IRQ_Handler
    bx r0

    /* FIQ中断服务函数 */
FIQ_Handler:
    ldr r0,=FIQ_Handler
    bx r0




   
