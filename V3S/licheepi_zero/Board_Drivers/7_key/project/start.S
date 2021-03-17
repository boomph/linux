.global _start
.global _bss_start
.global _bss_end

_bss_start：
    .word __bss_start

_bss_end:
    .word __bss_end

    
_start:
    //svc mode
    mrs r0,cpsr
    bic r0,r0,#0x1f
    orr r0,r0,#0x13
    msr cpsr,r0


    //clean bss
    ldr r0,_bss_start
    ldr r1,_bss_end
    ldr r2,=0x0
bss_loop:
    stmia r0!,{r2}
    cmp r0,r1
    ble bss_loop

    //set sp pointer
    ldr sp,=0x40020000

    //go to main
    b mmain
