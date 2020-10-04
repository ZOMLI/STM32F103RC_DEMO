#ifndef __PWM_H
#define __PWM_H

#include "sys.h"

//端口配置
#define PWM_IF_TIMx_ADVANCED 	0
#define PWM_TIMx							TIM2
#define PWM_GPIOx							GPIOA
#define PWM_PIN								GPIO_Pin_1
#define PWM_TIM_CHx						2
#define PWM_tim_rcc() 				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE)
#define PWM_gpio_rcc()				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)



//波形配置
//不能给10000HZ,因为给完后ARR刚好是1
#define PWM_HZ				50
#define PWM_A_P				(72000000/PWM_HZ)
#if 	(PWM_A_P<7200)
#define PWM_PSC				72
#else 
#define PWM_PSC				7200
#endif
#define PWM_ARR				(PWM_A_P/PWM_PSC)
#define PWM_DEF_DUTY	(1-0.075)
#define PWM_DEF_DATA	(PWM_DEF_DUTY*PWM_ARR) 




void PWM_Init(void);



#endif 


