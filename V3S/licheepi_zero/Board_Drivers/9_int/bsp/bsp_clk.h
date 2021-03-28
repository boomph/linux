#ifndef __BSP_CLK_H
#define __BSP_CLK_H

#include "v3s_sys.h"

void v3s_clk_init(void);
void v3s_cpu_clk_src_switch(CPU_CLK_SRC_SEL sel);

#endif //__BSP_CLK_H
