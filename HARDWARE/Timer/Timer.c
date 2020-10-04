/**
	*	��ʱ����ʱ����
	*
	*	ע������:
	*	
	*	��ע:
	*
	*	�汾: 1.0.0 
	*
	* ��������: 2019_08_06
	*
	*/
	
#include "Timer.h"

#include "usart.h"
#include "led.h"




uint32_t 	TIM_Global_ms;		//ȫ��ms��ʱ
uint32_t 	TIM_ms=0;					//ms����ʱ	

volatile _Bool  	TIM_MPU_10ms;		//10msһ��
volatile _Bool  	TIM_10ms;				//10msһ����
volatile _Bool  	TIM_200ms;			//200msһ����
volatile _Bool  	TIM_500ms;			//500msһ����
volatile _Bool	 	TIM_1000ms;			//1000msһ����

void Timer_Init(void)
{
	Timer6_Init();																			//��ʼ��10ms���ж϶�ʱ��
	Timer7_Init();																			//��ʼ��1ms���ж϶�ʱ��
}

void Timer6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);					//ʹ��TIM6ʱ��
	
	//��ʼ����ʱ��6 TIM6
	TIM_TimeBaseStructure.TIM_Period 				= TIM6_ARR-1 ; 				//�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler 		=	TIM6_PSC-1 ; 				//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 							//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  							//TIM6�����ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  		//��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  					//�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  															//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);											//��������ж�
	
  TIM_Cmd(TIM6,ENABLE ); 																				//ʹ�ܶ�ʱ��6
}

//void TIM6_IRQHandler(void) 
//{ 
//if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
//	{
//	
//	}
//    TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 								//����жϱ�־λ
// 
//}


void Timer7_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);					//ʹ��TIM7ʱ��
	
	//��ʼ����ʱ��7 TIM7
	TIM_TimeBaseStructure.TIM_Period 				= TIM7_ARR-1; 				//�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler 		=	TIM7_PSC-1; 				//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 							//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  							//TIM7�����ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  					//�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  															//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);											//��������ж�
	
  TIM_Cmd(TIM7,ENABLE ); 																				//ʹ�ܶ�ʱ��7
}

//void TIM7_IRQHandler(void) 
//{ 
//if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
//	{
//		TIM_Global_ms++;
//		if(TIM_ms>0) TIM_ms--;
//		if((TIM_Global_ms%10)==0)				TIM_10ms			=!	TIM_10ms;
//		if((TIM_Global_ms%200)==0)		{	TIM_200ms			=!	TIM_200ms;  LED_Case();	}		//��
//		if((TIM_Global_ms%500)==0)			TIM_500ms			=!	TIM_500ms;
//		if((TIM_Global_ms%1000)==0)			TIM_1000ms		=!	TIM_1000ms;
//		if( TIM_Global_ms>0x7fffffff)		TIM_Global_ms	=		0;													//��ʱ�ֶ����
//		
//    TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 																		//����жϱ�־λ
//	}
//}

