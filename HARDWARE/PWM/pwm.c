/**
	*	PWMģ��
	*	
	*	ע������:
	*		1.ʹ��˳��δ����,����������
	*		2.��֧�ֵ�ͨ��,��ͨ��copy��
	*		3.δ���븴��֧��
	*		4.�Զ���ARR,PSC���ܽ�������������Ƶ��,��Ҫ��׼PWMƵ�ʵ��ֶ�����
	*
	*	��ע:
	*
	*	�汾:	1.0.0
	*
	*
	*/



#include "pwm.h"




void PWM_Init(void)		//���PWM��
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	PWM_tim_rcc();						//ʹ��TIMʱ��
 	PWM_gpio_rcc(); 					//ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM3 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = PWM_PIN; 													//TIM_CH
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  								//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIOx, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = PWM_ARR-1; 									//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =PWM_PSC-1; 								//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 										//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  		//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(PWM_TIMx, &TIM_TimeBaseStructure); 						//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 							//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; 															//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//�������:TIM����Ƚϼ��Ը�
	
#if		 (PWM_TIM_CHx==1)		//ͨ��ѡ��
	TIM_OC1Init(PWM_TIMx, &TIM_OCInitStructure);  									//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC1PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);  					//CHԤװ��ʹ��
	TIM_SetCompare1(PWM_TIMx,PWM_DEF_DATA);													//CCR��ֵ�趨
#elif 	(PWM_TIM_CHx==2)
	TIM_OC2Init(PWM_TIMx, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
	TIM_SetCompare2(PWM_TIMx,PWM_DEF_DATA);
#elif		(PWM_TIM_CHx==3)
	TIM_OC3Init(PWM_TIMx, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
	TIM_SetCompare3(PWM_TIMx,PWM_DEF_DATA);
#elif		(PWM_TIM_CHx==4)
	TIM_OC4Init(PWM_TIMx, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
	TIM_SetCompare4(PWM_TIMx,PWM_DEF_DATA);
#endif

#if PWM_IF_TIMx_ADVANCED
  TIM_CtrlPWMOutputs(PWM_TIMx,ENABLE);														//���߼���ʱ��Ҫ�õ� MOE�����ʹ��	
#endif
	 
	TIM_ARRPreloadConfig(PWM_TIMx, ENABLE); 												//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(PWM_TIMx, ENABLE);  																		//ʹ��TIM
 
}




