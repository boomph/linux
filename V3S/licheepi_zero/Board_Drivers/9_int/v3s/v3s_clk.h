#ifndef __V3S_CLK_H
#define __V3S_CLK_H



typedef struct{
    volatile unsigned int   PLL_CPU_CTRL_REG;       //0X0000
    volatile unsigned int   RESV1;                  //0X0004
    volatile unsigned int   PLL_AUDIO_CTRL_REG;     //0x0008 
    volatile unsigned int   RESV2;                  //0X000C
    volatile unsigned int   PLL_VIDEO_CTRL_REG; 	//0x0010
    volatile unsigned int   RESV3;                  //0X0014 
    volatile unsigned int   PLL_VE_CTRL_REG; 	    //0x0018
    volatile unsigned int   RESV4;                  //0X001C
    volatile unsigned int   PLL_DDR0_CTRL_REG; 	    //0x0020 
    volatile unsigned int   RESV5;                  //0X0024
    volatile unsigned int   PLL_PERIPH0_CTRL_REG; 	//0x0028 
    volatile unsigned int   PLL_ISP_CTRL_REG; 	    //0x002C
    volatile unsigned int   RESV6[5];               //
    volatile unsigned int   PLL_PERIPH1_CTRL_REG;   //0x0044 
    volatile unsigned int   RESV7;                  //0X0048
    volatile unsigned int   PLL_DDR1_CTRL_REG; 	    //0x004C 
    volatile unsigned int   CPU_AXI_CFG_REG; 	    //0x0050 
    volatile unsigned int   AHB1_APB1_CFG_REG; 	    //0x0054 
    volatile unsigned int   APB2_CFG_REG; 	        //0x0058 
    volatile unsigned int   AHB2_CFG_REG; 	        //0x005C 
    volatile unsigned int   BUS_CLK_GATING_REG0; 	//0x0060 
    volatile unsigned int   BUS_CLK_GATING_REG1; 	//0x0064 
    volatile unsigned int   BUS_CLK_GATING_REG2; 	//0x0068 
    volatile unsigned int   BUS_CLK_GATING_REG3; 	//0x006C 
    volatile unsigned int   BUS_CLK_GATING_REG4; 	//0x0070
    volatile unsigned int   RESV8[5];               //
    volatile unsigned int   SDMMC0_CLK_REG; 	    //0x0088 
    volatile unsigned int   SDMMC1_CLK_REG; 	    //0x008C 
    volatile unsigned int   SDMMC2_CLK_REG; 	    //0x0090
    volatile unsigned int   RESV9[2];               //
    volatile unsigned int   CE_CLK_REG; 	        //0x009C 
    volatile unsigned int   SPI0_CLK_REG; 	        //0x00A0
    volatile unsigned int   RESV10[10];             // 
    volatile unsigned int   USBPHY_CFG_REG; 	    //0x00CC 
    volatile unsigned int   RESV11[9];              //
    volatile unsigned int   DRAM_CFG_REG; 	        //0x00F4 
    volatile unsigned int   PLL_DDR1_CFG_REG; 	    //0x00F8 
    volatile unsigned int   MBUS_RST_REG; 	        //0x00FC 
    volatile unsigned int   DRAM_CLK_GATING_REG; 	//0x0100 
    volatile unsigned int   DE_CLK_REG;        	    //0x0104
    volatile unsigned int   RESV12[4];              //
    volatile unsigned int   TCON_CLK_REG; 	        //0x0118
    volatile unsigned int   RESV13[5];              //
    volatile unsigned int   CSI_MISC_CLK_REG;  	    //0x0130 
    volatile unsigned int   CSI_CLK_REG;       	    //0x0134
    volatile unsigned int   RESV14;                 //0X0138 
    volatile unsigned int   VE_CLK_REG; 	        //0x013C 
    volatile unsigned int   AC_DIG_CLK_REG;    	    //0x0140 
    volatile unsigned int   AVS_CLK_REG;       	    //0x0144 
    volatile unsigned int   RESV15[5];              //
    volatile unsigned int   MBUS_CLK_REG;      	    //0x015C
    volatile unsigned int   RESV16[3];              //
    volatile unsigned int   MIPI_CSI_REG;        	//0x016C
    volatile unsigned int   RESV17[36];             //
    volatile unsigned int   PLL_STABLE_TIME_REG0; 	//0x0200 
    volatile unsigned int   PLL_STABLE_TIME_REG1; 	//0x0204
    volatile unsigned int   RESV18[6];              // 
    volatile unsigned int   PLL_CPU_BIAS_REG;  	    //0x0220 
    volatile unsigned int   PLL_AUDIO_BIAS_REG; 	//0x0224 
    volatile unsigned int   PLL_VIDEO_BIAS_REG; 	//0x0228 
    volatile unsigned int   PLL_VE_BIAS_REG;   	    //0x022C 
    volatile unsigned int   PLL_DDR0_BIAS_REG; 	    //0x0230 
    volatile unsigned int   PLL_PERIPH0_BIAS_REG; 	//0x0234 
    volatile unsigned int   PLL_ISP_BIAS_REG;  	    //0x0238 
    volatile unsigned int   RESV19[2];              //
    volatile unsigned int   PLL_PERIPH1_BIAS_REG; 	//0x0244
    volatile unsigned int   RESV20;                 //0X0248 
    volatile unsigned int   PLL_DDR1_BIAS_REG; 	    //0x024C 
    volatile unsigned int   PLL_CPU_TUN_REG;     	//0x0250
    volatile unsigned int   RESV21[3];              //
    volatile unsigned int   PLL_DDR0_TUN_REG; 	    //0x0260
    volatile unsigned int   RESV22[7];                  //
    volatile unsigned int   PLL_CPU_PAT_CTRL_REG; 	    //0x0280 
    volatile unsigned int   PLL_AUDIO_PAT_CTRL_REG; 	//0x0284 
    volatile unsigned int   PLL_VIDEO_PAT_CTRL_REG; 	//0x0288 
    volatile unsigned int   PLL_VE_PAT_CTRL_REG; 	    //0x028C 
    volatile unsigned int   PLL_DDR0_PAT_CTRL_REG; 	    //0x0290
    volatile unsigned int   RESV23;                     //0X0294 
    volatile unsigned int   PLL_ISP_PAT_CTRL_REG; 	    //0x0298
    volatile unsigned int   RESV24[2];                  //
    volatile unsigned int   PLL_PERIPH1_PAT_CTRL_REG; 	//0x02A4
    volatile unsigned int   RESV25;                     //0X02A8 
    volatile unsigned int   PLL_DDR1_PAT_CTRL_REG0; 	//0x02AC 
    volatile unsigned int   PLL_DDR1_PAT_CTRL_REG1; 	//0x02B0
    volatile unsigned int   RESV26[3];                  // 
    volatile unsigned int   BUS_SOFT_RST_REG0; 	        //0x02C0 
    volatile unsigned int   BUS_SOFT_RST_REG1; 	        //0x02C4 
    volatile unsigned int   BUS_SOFT_RST_REG2; 	        //0x02C8 
    volatile unsigned int   RESV27;                     //0X02CC
    volatile unsigned int   BUS_SOFT_RST_REG3; 	        //0x02D0
    volatile unsigned int   RESV28;                     //0X02D4 
    volatile unsigned int   BUS_SOFT_RST_REG4; 	        //0x02D8
    volatile unsigned int   RESV29[9];                  //
    volatile unsigned int   PS_CTRL_REG;       	        //0x0300 
    volatile unsigned int   PS_CNT_REG; 	            //0x0304 
}PLL_STRUCT;


//CPU_CLK_SRC_PLL_CPU == CPU_CLK_SRC_PLL1
typedef enum{
    CPU_CLK_SRC_LOSC        = 0,
    CPU_CLK_SRC_OSC24M      = 1,
    CPU_CLK_SRC_PLL_CPU     = 2,
    CPU_CLK_SRC_PLL1        = 3
}CPU_CLK_SRC_SEL;

#endif //__V3S_CLK_H
