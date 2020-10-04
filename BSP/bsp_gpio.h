#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f10x.h"





void GPIO_Init_Pins(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode);


#endif

