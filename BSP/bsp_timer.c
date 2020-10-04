#include "bsp_timer.h"





//定时器基础初始化(带更新中断) 50HZ推荐 arr=3999 psr=359
void bsp_timer_init(TIM_TypeDef *TIMx, uint16_t arr, uint16_t psr, uint16_t prepri, uint16_t subpri)
{
	TIM_TimeBaseInitTypeDef TIMx_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
	
	switch ((uint32_t)TIMx)
	{
		case TIM1_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
			break;
		
		case TIM8_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
			break;
		
		case TIM2_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
			break;
		
		case TIM3_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
			break;
			
		case TIM4_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
			break;
	
		case TIM5_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
			break;
		
		case TIM6_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
			break;
		
		case TIM7_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
			break;
	}
	
	//定时器TIMx初始化
	TIMx_TimeBaseStructure.TIM_Period 					= arr;					 					//设置自动重转载寄存器周期的值
	TIMx_TimeBaseStructure.TIM_Prescaler 				= psr;					 					//设置时钟分频除数的预分频值
	TIMx_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;	 					//设置时钟分割
	TIMx_TimeBaseStructure.TIM_CounterMode			= TIM_CounterMode_Up; 		//TIM向上计数
	TIM_TimeBaseInit(TIMx, &TIMx_TimeBaseStructure);									//初始化TIMx
	
	TIM_ClearITPendingBit(TIMx, TIM_IT_Update);					 									//初始化时必须将溢出中断清0,必须在开溢出中断之前
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);					 									//允许溢出中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= prepri; 			//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= subpri;		   	//从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;				//使能IRQ通道
	NVIC_Init(&NVIC_InitStructure);								  		 							//初始化NVIC寄存器

	TIM_Cmd(TIMx, ENABLE); //使能TIMx
}






