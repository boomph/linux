
.global _start

_start:
    /*设置CONTEX-A7处理器进入SVC模式 */
     mrs r0,cpsr            /*读取CPSR到R0 */
     bic r0,r0,#0x1f        /*清除CPSR的BIT4-0位 */
     orr r0,r0,#0x13        /*设置为SVC模式 */
     msr cpsr,r0            /*R0写入CPSR */

     /*设置SP指针 ，
     V3S内存映射DDR2起始地址为0X40000000,
     堆栈大小0X20000,所以SP指向0X40020000 
     */
     ldr sp,=0x40020000
     b main                 /*跳至MAIN函数 */
