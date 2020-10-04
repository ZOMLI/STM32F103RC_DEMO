#include "bsp_gpio.h"




void GPIO_Init_Pins(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
	
	/* Enable GPIOx, clock */
	switch ((uint32_t)GPIOx)
	{
	case GPIOA_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		break;

	case GPIOB_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		break;

	case GPIOC_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		break;

	case GPIOD_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		break;

	case GPIOE_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		break;

	case GPIOF_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		break;

	case GPIOG_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		break;

	default:
		break;
	}

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}




