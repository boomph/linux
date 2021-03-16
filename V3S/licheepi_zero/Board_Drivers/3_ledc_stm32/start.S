.global _start
.global _bss_start
.global _bss_end

_bss_start:
    .word __bss_start

_bss_end:
    .word __bss_end


_start:
    /* 设置V3S中contex-a7处理器进入SVC模式 */   
    mrs r0,cpsr         //读取CPSR到R0
    bic r0,r0,#0x1f     //清除CPSR的BIT0-4
    orr r0,r0,#0x13     //设置为SVC模式
    msr cpsr,r0         //R0写入CPSR


    /*
        C语言将定义且未初始化的变量存入BSS段
        因此，需要将BSS段清0
     */
    ldr r0,_bss_start
    ldr r1,_bss_end
    mov r2,#0
bss_loop:
    stmia r0!,{r2}      //将R0中的数据写入R0,R0+1
    cmp r0,r1           //比较R0,R1地址
    ble bss_loop        //如果小于等于，跳至bss_loop
    

    /* 设置SP指针 
        V3S内存DDR2起始地址：0X40000000
        堆栈大小设为0X20000,
        SP=0X40020000
     */
    ldr sp,=0x40020000
    b main              //跳MAIN

