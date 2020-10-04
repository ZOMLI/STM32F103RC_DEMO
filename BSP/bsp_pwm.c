/**
	*	STM32F10x pwm����
	*
	*	ע������:
	*
	*	��ע:
	*
	*	�汾: 1.0.0
	*
	*	����: 2020_10_05
	*
	*/



#include "bsp_pwm.h"




//��ĳ����ʱ����ͨ�� ���ó� PWMģʽ ���漰��ʱ������������GPIO������
void bsp_pwm_init(TIM_TypeDef *TIMx,TIM_CH_TypeDef CHx)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM2; 						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 		//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse 			= 0; 													//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low; 				//�������:TIM����Ƚϼ��Ը�
	
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
		
		default: while(1){} break;				//�ⶼ�Բ��ϾͶ���������
	}
	
	if((uint32_t)TIMx==TIM1_BASE || (uint32_t)TIMx==TIM8_BASE)
		TIM_CtrlPWMOutputs(TIMx,ENABLE);														//���߼���ʱ��Ҫ�õ� MOE�����ʹ��	
	
}


// ����ͨ���ڵ�ռ�ձ�(��С������)
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


// ����ͨ���ڵ�CCRֵ
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


// ���øߵ�ƽ����ʱ��
// ����PCLK1ʱ����Ҫע��,�˺�������Ϊ2��Ƶ��ʧЧ����һ��ʱ��
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



