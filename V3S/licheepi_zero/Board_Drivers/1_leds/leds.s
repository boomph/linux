.global _start /*全局标号 */

_start:
    /*使能所有外设时钟  */
    /*V3S忽略 */

    /*V3S 配置GPIO PG0复用为GPIO输出,
    PG_CFG0_REG(0x01C208D8) 位0-2 = 001B(Output)  
    */
    LDR R0,=0x01C208D8  @PG_CFG0_REG
    LDR R1,=0X1         @即设置0-2位为001
    STR R1,[R0]

    /*
    V3S配置PG0的电气属性：
    PG_DRV0_REG(0x01C208EC) 位0-1= 01B(LEVEL1驱动等级),
    PG_PULL0_REG(0x01C208F4) 位0-1= 00B(禁止上下拉)
     */
    LDR R0,=0x01C208EC  @PG_DRV0_REG
    LDR R1,=0X1         @即设置0-1位为01
    STR R1,[R0]

    LDR R0,=0x01C208F4  @PG_PULL0_REG
    LDR R1,=0X0         @即设置0-1位为00
    STR R1,[R0]

    /*
        V3S打开LED
        LICHEEPI_ZERO:  PG0输出0
            PG_DATA_REG(0x01C208E8) 位0 = 0B(输出低电平)
     */

    LDR R0,=0x01C208E8  @PG_DATA_REG
    LDR R1,=0X0         @即设置0位为0
    STR R1,[R0]

loop:
    b loop
    