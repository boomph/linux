#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "v3s_sys.h"


void GPIO_Init(PIO_PORT port, unsigned int pin, PIO_MODE mode, PIO_DRV drv, PIO_PULL pul);
void GPIO_SetPin(PIO_PORT port, unsigned int pin);
void GPIO_ResetPin(PIO_PORT port, unsigned int pin);
unsigned int GPIO_GetPinData(PIO_PORT port, unsigned int pin);

#endif //__BSP_GPIO_H
