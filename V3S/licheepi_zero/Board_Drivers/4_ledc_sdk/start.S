.global _start


_start:

    cpsid i						/* 关闭全局中断 */

	/* 关闭I,DCache和MMU 
	 * 采取读-改-写的方式。
	 */
	mrc     p15, 0, r0, c1, c0, 0     /* 读取CP15的C1寄存器到R0中       		        	*/
    bic     r0,  r0, #(0x1 << 12)     /* 清除C1寄存器的bit12位(I位)，关闭I Cache            	*/
    bic     r0,  r0, #(0x1 <<  2)     /* 清除C1寄存器的bit2(C位)，关闭D Cache    				*/
    bic     r0,  r0, #0x2             /* 清除C1寄存器的bit1(A位)，关闭对齐						*/
    bic     r0,  r0, #(0x1 << 11)     /* 清除C1寄存器的bit11(Z位)，关闭分支预测					*/
    bic     r0,  r0, #0x1             /* 清除C1寄存器的bit0(M位)，关闭MMU				       	*/
    mcr     p15, 0, r0, c1, c0, 0     /* 将r0寄存器中的值写入到CP15的C1寄存器中	 				*/


    //SVR MODE
    mrs r0,cpsr
    bic r0,r0,#0x1f
    orr r0,r0,#0x13
    msr cpsr,r0

.global _bss_start
.global _bss_end

_bss_start:
    .word __bss_start

_bss_end:
    .word __bss_end

    // CLEAN BSS SECTION
    ldr r0,_bss_start
    ldr r1,_bss_end
    ldr r2,=#0
bss_loop:
    stmia r0!,{r2}
    cmp r0,r1
    ble bss_loop



    //SET SP
    ldr sp,=0x20000


    cpsie i

    //GOTO C
    b main
