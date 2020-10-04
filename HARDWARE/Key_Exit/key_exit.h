#ifndef __KEY_EXIT_H
#define __KEY_EXIT_H


#include "sys.h"

	//KEY0配置
#define KEY0_ENABLE					1
#define KEY0_ACT_LEVEL			0
#define KEY0 								PCin(5) 
#define KEY0_GPIO 					GPIOC
#define KEY0_GPIO_PIN				GPIO_Pin_5
#define KEY0_RCC_APB2CLOCK	RCC_APB2Periph_GPIOC
#define KEY0_GPIO_SOURCE		GPIO_PortSourceGPIOC
#define KEY0_PIN_SOURCE			GPIO_PinSource5
#define KEY0_EXTI_LINE			EXTI_Line5
#define KEY0_EXTI_IRQN			EXTI9_5_IRQn
#define KEY0_EXTI_IRQ_FUNC 	EXTI9_5_IRQHandler
	//KEY1配置
#define KEY1_ENABLE					1
#define KEY1_ACT_LEVEL			0
#define KEY1 								PAin(15)
#define KEY1_GPIO 					GPIOA
#define KEY1_GPIO_PIN				GPIO_Pin_15
#define KEY1_RCC_APB2CLOCK	RCC_APB2Periph_GPIOA
#define KEY1_GPIO_SOURCE		GPIO_PortSourceGPIOA
#define KEY1_PIN_SOURCE			GPIO_PinSource15
#define KEY1_EXTI_LINE			EXTI_Line15
#define KEY1_EXTI_IRQN			EXTI15_10_IRQn
#define KEY1_EXTI_IRQ_FUNC 	EXTI15_10_IRQHandler
	//KEY2配置	得用下拉输入
#define KEY2_ENALBE					1
#define KEY2_ACT_LEVEL			1
#define KEY2 								PAin(0)
#define KEY2_GPIO 					GPIOA
#define KEY2_GPIO_PIN				GPIO_Pin_0
#define KEY2_RCC_APB2CLOCK	RCC_APB2Periph_GPIOA
#define KEY2_GPIO_SOURCE		GPIO_PortSourceGPIOA
#define KEY2_PIN_SOURCE			GPIO_PinSource0
#define KEY2_EXTI_LINE			EXTI_Line0
#define KEY2_EXTI_IRQN			EXTI0_IRQn
#define KEY2_EXTI_IRQ_FUNC 	EXTI0_IRQHandler
	//特殊配置 不用直接注释了
#define KEY_RCC_SPECIAL()		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE)


void Key_Exit_Init(void);


#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
 

#endif






