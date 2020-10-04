/**
	*	建议配合 bsp_timer_up_it.c 配合使用,防止使能了更新中断找不到中断服务函数
	*
	*	注意事项:
	*
	*	更新: 2020_10_05
	*
	*/



#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H



#include "stm32f10x.h"








void bsp_timer_init(TIM_TypeDef *TIMx, uint16_t arr, uint16_t psr, uint16_t prepri, uint16_t subpri);


#endif
