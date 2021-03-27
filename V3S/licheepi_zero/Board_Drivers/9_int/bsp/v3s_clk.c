#include "v3s_clk.h"
#include "v3s_sys.h"

PLL_STRUCT* PLL=NULL;
/*
The PLL Output= (24MHz*N*K)/(M*P).
The PLL output is for the CPUX Clock.
Note: The PLL output clock must be in the range of 200MHz~2.6GHz.
Its default is 408MH
*/
void v3s_clk_init(void){
    PLL = (PLL_STRUCT*)CCU_BASE_ADDRESS;

    /*
        检查当前CPU时钟源，确保为OSC24M
    */
    //取CPU_CLK_SRC_SEL(17-16)
    unsigned char clkSrcSel = PLL->CPU_AXI_CFG_REG >> 16;
    clkSrcSel &= 0x03;

    switch (clkSrcSel)
    {
    case CPU_CLK_SRC_LOSC:
    case CPU_CLK_SRC_PLL_CPU:
    case CPU_CLK_SRC_PLL1:
        //如呆不是OSC24M,则切换至OSC24M
        v3s_cpu_clk_src_switch(CPU_CLK_SRC_OSC24M);
        break;
    
    default:
        break;
    }

    /*
        配置PLL_CPU_CTRL_REG,设置PLL_CPU(PLL1)

        测试:
        配置为408MHZ
        PLL_CPU_CTRL_REG = 0X80001000  OK

	配置为1008MHZ
	PLL_CPU_CTRL_REG = 0X80001B21
        28位设为0，检测=1表示稳定
    */
   PLL->PLL_CPU_CTRL_REG=0X80001B21;
   while((PLL->PLL_CPU_CTRL_REG & 0X10000000) == 0){
       //等待 28 = 1: Locked (It indicates that the PLL has been stable.)
   }

   /*
    从OSC24M切换回PLL_CPU(PLL1)
   */ 
   v3s_cpu_clk_src_switch(CPU_CLK_SRC_PLL_CPU);

}

void v3s_cpu_clk_src_switch(CPU_CLK_SRC_SEL sel){
    
    //转为unsigned int
    unsigned int curSel = sel;
    //确保二位
    curSel &= 0x03;

    //清空并设置17-16位，完成切换
    PLL->CPU_AXI_CFG_REG &= ~(((unsigned int)0x03)<<16);
    PLL->CPU_AXI_CFG_REG |= (curSel<<16);

    //If the clock source is changed, at most to wait for 8 present running clock cycles
    //如果时钟源已更改，最多等待8个当前运行时钟周期
    unsigned char n=8;
    while(n--){}
}
