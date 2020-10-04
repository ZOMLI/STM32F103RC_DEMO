/**
	*	STM32F10x pwm配置
	*
	*	注意事项:
	*
	*	备注:
	*
	*	版本: 1.0.0
	*
	*	更新: 2020_10_05
	*
	*/



#include "bsp_pwm.h"




//将某个定时器的通道 配置成 PWM模式 不涉及定时器基本设置与GPIO口设置
void bsp_pwm_init(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM2; 						//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse 			= 0; 													//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low; 				//输出极性:TIM输出比较极性高
	
	switch(CHx)
	{
		case CH1:
			TIM_OC1Init(TIMx, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		
		case CH2:
			TIM_OC2Init(TIMx, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);			
			break;
		
		case CH3:
			TIM_OC3Init(TIMx, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case CH4:
			TIM_OC4Init(TIMx, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		
		default: while(1){} break;				//这都对不上就堵塞卡死吧
	}
	
	if((uint32_t)TIMx==TIM1_BASE || (uint32_t)TIMx==TIM8_BASE)
		TIM_CtrlPWMOutputs(TIMx,ENABLE);														//仅高级定时器要用的 MOE主输出使能	
	
}


// 设置通道口的占空比(有小数舍弃)
void bsp_pwm_set_duty(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx,float duty)
{
	switch(CHx)
	{
		case CH1:		TIMx->CCR1 = (int)(duty*TIMx->ARR);		break;
		case CH2:		TIMx->CCR2 = (int)(duty*TIMx->ARR);		break;
		case CH3:		TIMx->CCR3 = (int)(duty*TIMx->ARR);		break;
		case CH4:		TIMx->CCR4 = (int)(duty*TIMx->ARR);		break;
		
		default: break;
	}
}


// 设置通道口的CCR值
void bsp_pwm_set_data(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx,uint16_t data)
{
		switch(CHx)
	{
		case CH1:		TIMx->CCR1 = data;		break;
		case CH2:		TIMx->CCR2 = data;		break;
		case CH3:		TIMx->CCR3 = data;		break;
		case CH4:		TIMx->CCR4 = data;		break;
		
		default: break;
	}
}


// 设置高电平持续时间
// 更改PCLK1时钟了要注意,此函数将因为2倍频率失效而多一倍时间
void bsp_pwm_set_HighTime(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx,float time_us)
{
	static RCC_ClocksTypeDef rcc_clock={0}; 
	uint32_t freq;
	
	if(rcc_clock.PCLK1_Frequency==0) RCC_GetClocksFreq(&rcc_clock);  
	if(rcc_clock.PCLK2_Frequency==0) RCC_GetClocksFreq(&rcc_clock);  

	
	
	if((uint32_t)TIMx==TIM1_BASE || (uint32_t)TIMx==TIM8_BASE)
		freq = rcc_clock.PCLK2_Frequency/(TIMx->PSC+1);
	else 
		freq = rcc_clock.PCLK1_Frequency*2/(TIMx->PSC+1);
	
	bsp_pwm_set_data(TIMx,CHx,(int)(freq*time_us)/1000000);
}



