#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "v3s_sys.h"


void GPIO_Init(PIO_PORT port, unsigned int pin, PIO_MODE mode, PIO_DRV drv, PIO_PULL pul);
void GPIO_SetPin(PIO_PORT port, unsigned int pin);
void GPIO_ResetPin(PIO_PORT port, unsigned int pin);
unsigned int GPIO_GetPinData(PIO_PORT port, unsigned int pin);

void GPIO_EINT_Init(PIO_PORT port,
                    unsigned int pin,
                    PIO_EINT_MODE mode,
                    PIO_EINT_DEB_CLK_SELECT Deb_Clk_Select,
                    unsigned int Deb_Clk_Pre_Scale);

void GPIO_EINT_CMD(PIO_PORT port,unsigned int pin,unsigned int cmd);
unsigned int GPIO_EINT_GetStatus(PIO_PORT port,unsigned int pin);
void GPIO_EINT_Clean(PIO_PORT port,unsigned int pin);

#endif //__BSP_GPIO_H
