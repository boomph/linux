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


    /* -------------------------------------------------------------------
        关全局中断，防止干扰
     */
    cpsid i


    /*--------------------------------------------------------------------
        关闭I、D Cache和MMU
        修改SCTLR寄存器，采用读-改-写的方式
    */
    mrc p15,0,r0,c1,c0,0        //读取SCTLR寄存数据到r0
    //bic指令用于清空指定位
    bic r0,r0,#0x1000		//(0x1 << 12)   关闭 I Cache
    bic r0,r0,#0x800		//(0x1 << 11)   关闭分支预测
    bic r0,r0,#0x4		//(0x1 << 2)    关闭 D Cache
    bic r0,r0,#0x2		//(0x1 << 1)    关闭对齐
//    bic r0,r0,#0x1		//(0x1 << 0)	关闭MMU
    mcr p15,0,r0,c1,c0,0        //r0的数据写入到SCTLR寄存器


    /* -------------------------------------------------------------------
        设置中断向量偏移 ，可以在C语言中设置，只要在中断发生前设置
    */
    ldr r0,=0x41000000          //新的中断向量首地址
    dsb                         //数据同步，当前面存储操作完毕，才执行后面的指令
    isb                         //指令同步，当前面指令执行完毕，才执行后面的指令
    mcr p15,0,r0,c12,c0,0       //设置VBAR寄存器
    dsb
    isb


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


    /* -------------------------------------------------------------------
        打开全局中断，
        之后发生中断都会进入
        外部中断处理函数：IRQ_Handler
     */
    cpsie i


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
    //保护现场--------------------------------------------------------------------------
    push {lr}           //保存lr
    push {r0-r3,r12}    //保存r0-r3,r12

    mrs r0,spsr         //保存spsr
    push {r0}     
    
    //配置基地址寄存器 CBAR/-------------------------------------------------------------
    //取得GIC控制器组的基址 
    //通过GIC基址+0x2000取得cpu interface基址，存入R1=CPU Interface基址
    //通过cpu interface基址+0x0c取得GICC_IAR的值,存入R0=GICC_IAR的值
    mrc p15,4,r1,c15,c0,0    //读取CP15的CBAR

    add r1,r1,#0x2000   //GIC基址+偏移，得到CPU interface基址
    ldr r0,[r1,#0x0c]   //CPU interface基址+偏移，得到GICC_IAR的值

    //GICC_IAR中保存有中断ID，与CPU内核ID
    push {r0,r1}        //保存CPU interface基址、GICC_IAR的值



    //当程序IRQ中断服务函数时，CPU即工作在IRQ运行模式下-----------------------------------
    //切换工作模式至SVC
    //调用C语言函数：system_irqhandler，R0=GICC_IAR的值传参
    cps #0x13           //切换SVC模式，允许其他中断

    push {lr}           //保存lr寄存器
    ldr r2, = system_irqhandler //加载C语言IRQ中断处理函数
    blx r2              //跳转到C语言IRQ中断处理函数
                        //并带有一个参数：GICC_IAR的值
                        //r0传参，此时r0=GICC_IAR的值

    //system_irqhandler执行完毕---------------------------------------------------------
    //反向还原，遇PUSH就pop
    pop {lr}            //还原LR
    cps #0x12           //切回IRQ运行模式

    //还原r0,r1
    pop {r0,r1}         //R0=GICC_IAR的值，R1=CPU interface基址
    str r0,[r1,0x10]    //将R0的值写入GICC_EOIR（中断结束寄存器）
                        //GICC_EOIR中的EOINTID对应INTID
    

    pop {r0}            //还原spsr
    msr spsr_cxsf,r0    //不明白为什么是spsr_cxsf??

    pop {r0-r3,r12}
    pop {lr}            //ARM三级流水线：取指、译指、执行
                        //pc=当前指令地址+8
                        //lr------>执行
    subs pc,lr,#4       //lr-4赋值给pc
                        //pc------>译指，正确的下条指令

    /* FIQ中断服务函数 */
FIQ_Handler:
    ldr r0,=FIQ_Handler
    bx r0




   
