#include "bsp_timer.h"





//��ʱ��������ʼ��(�������ж�) 50HZ�Ƽ� arr=3999 psr=359
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
	
	//��ʱ��TIMx��ʼ��
	TIMx_TimeBaseStructure.TIM_Period 					= arr;					 					//�����Զ���ת�ؼĴ������ڵ�ֵ
	TIMx_TimeBaseStructure.TIM_Prescaler 				= psr;					 					//����ʱ�ӷ�Ƶ������Ԥ��Ƶֵ
	TIMx_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;	 					//����ʱ�ӷָ�
	TIMx_TimeBaseStructure.TIM_CounterMode			= TIM_CounterMode_Up; 		//TIM���ϼ���
	TIM_TimeBaseInit(TIMx, &TIMx_TimeBaseStructure);									//��ʼ��TIMx
	
	TIM_ClearITPendingBit(TIMx, TIM_IT_Update);					 									//��ʼ��ʱ���뽫����ж���0,�����ڿ�����ж�֮ǰ
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);					 									//��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= prepri; 			//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= subpri;		   	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;				//ʹ��IRQͨ��
	NVIC_Init(&NVIC_InitStructure);								  		 							//��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIMx, ENABLE); //ʹ��TIMx
}






