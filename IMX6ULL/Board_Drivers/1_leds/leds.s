.global _start  @全局标号

_start:
    /*
        1、使用GPIO1_IO03时钟：CCM_CCGR1，为方便全为1    
    */
    ldr r0,=0x020C406c
    ldr r1,=0xffffffff
    str r1,[r0]

    /*
        2、复用GPIO1_IO03为GPIO1_03:
        IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03    MUX_MODE    5(0X0101)
     */
    ldr r0,=0x020E0068
    ldr r1,=0xffffffff
    str r1,[r0]


    /*
        3、设置电气特性:
        IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03    20E_02F4h
            bit 16:0 HYS 关闭
            bit [15:14]: 00 默认下拉
            bit [13]: 0 kepper 功能
            bit [12]: 1 pull/keeper 使能
            bit [11]: 0 关闭开路输出
            bit [7:6]: 10 速度 100Mhz
            bit [5:3]: 110 R0/6 驱动能力
            bit [0]: 0 低转换率
     */
    ldr r0,=0x020E02F4
    ldr r1,=0x0X10B0
    str r1,[r0]


    /*
        4、设置GPIO输出方向
        GPIOx_GDIR  GPIO1_GDIR  209_C004
     */
    ldr r0,=0x0209C004
    ldr r1,=0x00000008
    str r1,[r0]


    /*
        5、驱动GPIO1_IO03:
        209_C000 GPIO data register (GPIO1_DR)
     */
    ldr r0,=0X0209C000
    ldr r1,=0x00000000
    str r1,[r0]

loop:
    b loop