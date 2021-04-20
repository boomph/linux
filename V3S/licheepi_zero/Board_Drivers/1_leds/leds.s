.global _start /*全局标号 */

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
    //bic     r0,  r0, #0x1             /* 清除C1寄存器的bit0(M位)，关闭MMU				       	*/
    mcr     p15, 0, r0, c1, c0, 0     /* 将r0寄存器中的值写入到CP15的C1寄存器中	 				*/


    /*使能所有外设时钟  */
    /*V3S忽略 */

    /*V3S 配置GPIO PG0复用为GPIO输出,
    PG_CFG0_REG(0x01C208D8) 位0-2 = 001B(Output)  
    */
    LDR R0,=0x01C20824  @PG_CFG0_REG PB3
    LDR R1,=0X1000         @即设置0-2位为001   14:12 --- 001
    STR R1,[R0]

    /*
    V3S配置PG0的电气属性：
    PG_DRV0_REG(0x01C208EC) 位0-1= 01B(LEVEL1驱动等级), 5:4 -- 01
    PG_PULL0_REG(0x01C208F4) 位0-1= 00B(禁止上下拉)
     */
    LDR R0,=0x01C20838  @PG_DRV0_REG
    LDR R1,=0X10         @即设置0-1位为01
    STR R1,[R0]

    LDR R0,=0x01C20840  @PG_PULL0_REG
    LDR R1,=0X0         @即设置0-1位为00
    STR R1,[R0]

    /*
        V3S打开LED
        LICHEEPI_ZERO:  PG0输出0
            PG_DATA_REG(0x01C208E8) 位0 = 0B(输出低电平)
     */

    LDR R0,=0x01C20834  @PG_DATA_REG
    LDR R1,=0X3FFF        @即设置0位为0
    STR R1,[R0]

    cpsie i				/* 打开全局中断 */

loop:
    b loop
    