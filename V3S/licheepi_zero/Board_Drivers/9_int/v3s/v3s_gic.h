#ifndef __V3S_GIC_H
#define __V3S_GIC_H


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 157                /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */

  /* SGI 16个 */
  Software0_IRQn               = 0,                /**< Cortex-A7 Software Generated Interrupt 0 */
  Software1_IRQn               = 1,                /**< Cortex-A7 Software Generated Interrupt 1 */
  Software2_IRQn               = 2,                /**< Cortex-A7 Software Generated Interrupt 2 */
  Software3_IRQn               = 3,                /**< Cortex-A7 Software Generated Interrupt 3 */
  Software4_IRQn               = 4,                /**< Cortex-A7 Software Generated Interrupt 4 */
  Software5_IRQn               = 5,                /**< Cortex-A7 Software Generated Interrupt 5 */
  Software6_IRQn               = 6,                /**< Cortex-A7 Software Generated Interrupt 6 */
  Software7_IRQn               = 7,                /**< Cortex-A7 Software Generated Interrupt 7 */
  Software8_IRQn               = 8,                /**< Cortex-A7 Software Generated Interrupt 8 */
  Software9_IRQn               = 9,                /**< Cortex-A7 Software Generated Interrupt 9 */
  Software10_IRQn              = 10,               /**< Cortex-A7 Software Generated Interrupt 10 */
  Software11_IRQn              = 11,               /**< Cortex-A7 Software Generated Interrupt 11 */
  Software12_IRQn              = 12,               /**< Cortex-A7 Software Generated Interrupt 12 */
  Software13_IRQn              = 13,               /**< Cortex-A7 Software Generated Interrupt 13 */
  Software14_IRQn              = 14,               /**< Cortex-A7 Software Generated Interrupt 14 */
  Software15_IRQn              = 15,               /**< Cortex-A7 Software Generated Interrupt 15 */

  /* PPI 16个*/
  PrivatePeriph0_IRQn           = 16,               /**< Cortex-A7 Private Peripheral Interrupt 0 */
  PrivatePeriph1_IRQn           = 17,               /**< Cortex-A7 Private Peripheral Interrupt 1 */
  PrivatePeriph2_IRQn           = 18,               /**< Cortex-A7 Private Peripheral Interrupt 2 */
  PrivatePeriph3_IRQn           = 19,               /**< Cortex-A7 Private Peripheral Interrupt 3 */
  PrivatePeriph4_IRQn           = 20,               /**< Cortex-A7 Private Peripheral Interrupt 4 */
  PrivatePeriph5_IRQn           = 21,               /**< Cortex-A7 Private Peripheral Interrupt 5 */
  PrivatePeriph6_IRQn           = 22,               /**< Cortex-A7 Private Peripheral Interrupt 6 */
  PrivatePeriph7_IRQn           = 23,               /**< Cortex-A7 Private Peripheral Interrupt 7 */
  PrivatePeriph8_IRQn           = 24,               /**< Cortex-A7 Private Peripheral Interrupt 8 */
  PrivatePeriph9_IRQn           = 25,               /**< Cortex-A7 Private Peripheral Interrupt 9 */
  PrivatePeriph10_IRQn          = 26,               /**< Cortex-A7 Private Peripheral Interrupt 10 */
  PrivatePeriph11_IRQn          = 27,               /**< Cortex-A7 Private Peripheral Interrupt 11 */
  PrivatePeriph12_IRQn          = 28,               /**< Cortex-A7 Private Peripheral Interrupt 12 */
  PrivatePeriph13_IRQn          = 29,               /**< Cortex-A7 Private Peripheral Interrupt 13 */
  PrivatePeriph14_IRQn          = 30,               /**< Cortex-A7 Private Peripheral Interrupt 14 */
  PrivatePeriph15_IRQn          = 31,               /**< Cortex-A7 Private Peripheral Interrupt 15 */


  /* Device specific interrupts */
  /* SPI Shared Peripheral Interrupt 32---156 */
  UART0_IRQn                   = 32,               /**< UART0 interrupt request. */
  UART1_IRQn                   = 33,               /**< UART1 interrupt request. */
  UART2_IRQn                   = 34,               /**< UART2 interrupt request. */

  /**35-37保留 */

  TWI0_IRQn                   = 38,               /**< TWI0 interrupt request. */
  TWI1_IRQn                   = 39,               /**< TWI1 interrupt request. */

  /**40--46保留 */

  PB_EINT_IRQn                = 47,               /**< PB_EINT interrupt request. */

  /**48保留 */

  PG_EINT_IRQn                = 49,               /**< PG_EINT interrupt request. */

  Timer0_IRQn                 = 50,               /**< Timer0 interrupt request. */
  Timer1_IRQn                 = 51,               /**< Timer1 interrupt request. */
  Timer2_IRQn                 = 52,               /**< Timer2 interrupt request. */

  /**53---56保留 */

  Watchdog_IRQn               = 57,               /**< Watchdog interrupt request. */

  /**58---60保留 */

  AudioCodec_IRQn             = 61,               /**< Watchdog interrupt request. */
  LRADC_IRQn                  = 62,               /**< LRADC interrupt request. */

  /**63保留 */

  ExternalNMI_IRQn            = 64,               /**< External Non-Mask interrupt request. */

  /**65-71保留*/

  Alarm0_IRQn                 = 72,               /**< Alarm0 interrupt request. */
  Alarm1_IRQn                 = 73,               /**< Alarm1 interrupt request. */

  /**74---81保留*/

  DMA_IRQn                    = 82,               /**< DMA Channel interrupt request. */
  HSTimer0_IRQn               = 83,               /**< HS Timer0 interrupt request. */
  HSTimer1_IRQn               = 84,               /**< HS Timer1 interrupt request. */

  /**85--89保留*/

  VE_IRQn                     = 90,               /**< VE interrupt request. */

  /**91保留*/

  SDMMC0_IRQn                 = 92,               /**< SD/MMC Host Controller 0 interrupt request. */
  SDMMC1_IRQn                 = 93,               /**< SD/MMC Host Controller 1 interrupt request. */
  SDMMC2_IRQn                 = 94,               /**< SD/MMC Host Controller 2 interrupt request. */

  /**95--96保留*/

  SPI0_IRQn                   = 97,               /**< SPI0 interrupt request. */

  /**98--102保留*/

  USB_OTG_Device_IRQn         = 103,               /**< USB OTG_Device interrupt request. */
  USB_OTG_EHCI_IRQn           = 104,               /**< USB OTG_EHCI interrupt request. */
  USB_OTG_OHCI_IRQn           = 105,               /**< USB OTG_OHCI interrupt request. */

  /**106--111保留*/

  CE_IRQn                     = 112,               /**< CE interrupt request. */

  /**113保留*/

  EMAC_IRQn                   = 114,               /**< EMAC interrupt request. */
  CSI0_IRQn                   = 115,               /**< CSI0 interrupt request. */
  CSI1_IRQn                   = 116,               /**< CSI1 interrupt request. */
  CSI_CCI_IRQn                = 117,               /**< CSI_CCI interrupt request. */
  TCON_IRQn                   = 118,               /**< TCON interrupt request. */

  /**119-121保留*/

  MIPI_CSI_IRQn               = 122,               /**< MIPI CSI interrupt request. */

  /**123---126保留*/

  DE_IRQn                     = 127,               /**< DE interrupt request. */

  /**128--139保留*/

  CTI0_IRQn                   = 140,               /**< CTI0 interrupt request. */
  CTI1_IRQn                   = 141,               /**< CTI1 interrupt request. */
  CTI2_IRQn                   = 142,               /**< CTI2 interrupt request. */
  CTI3_IRQn                   = 143,               /**< CTI3 interrupt request. */

  COMMTX0_IRQn                = 144,               /**< COMMTX0 interrupt request. */
  COMMTX1_IRQn                = 145,               /**< COMMTX1 interrupt request. */
  COMMTX2_IRQn                = 146,               /**< COMMTX2 interrupt request. */
  COMMTX3_IRQn                = 147,               /**< COMMTX3 interrupt request. */

  COMMRX0_IRQn                = 148,               /**< COMMRX0 interrupt request. */
  COMMRX1_IRQn                = 149,               /**< COMMRX1 interrupt request. */
  COMMRX2_IRQn                = 150,               /**< COMMRX2 interrupt request. */
  COMMRX3_IRQn                = 151,               /**< COMMRX3 interrupt request. */

  PMU0_IRQn                   = 152,               /**< PMU0 interrupt request. */
  PMU1_IRQn                   = 153,               /**< PMU1 interrupt request. */
  PMU2_IRQn                   = 154,               /**< PMU2 interrupt request. */
  PMU3_IRQn                   = 155,               /**< PMU3 interrupt request. */

  AXI_ERROR_IRQn              = 156,               /**< AXI ERROR interrupt request. */
  
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Configuration of the Cortex-A7 Processor and Core Peripherals
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Configuration of the Cortex-A7 Processor and Core Peripherals
 * @{
 */

#define __CA7_REV                      0x0005    /**< Core revision r0p5 */
#define __GIC_PRIO_BITS                5         /**< Number of Bits used for Priority Levels */
#define __FPU_PRESENT                  1         /**< FPU present or not */


/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */

 
#endif //__V3S_GIC_H
