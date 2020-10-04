// 本文件只支持STM32F10X






#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "stm32f10x.h"

// 通道选择定义
// 暂时不支持反向通道输出
typedef enum{
	CH1	=0x01,
	CH2	=0x02,
	CH3	=0x03,
	CH4	=0x04,
//	CH1N=0x10,
//	CH2N=0x20,
//	CH3N=0x30,

}TIM_CH_TypeDef;






void bsp_pwm_init(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx);

void bsp_pwm_set_duty(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx,float duty);
void bsp_pwm_set_data(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx,uint16_t data);
void bsp_pwm_set_HighTime(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx,float time_us);




#endif
