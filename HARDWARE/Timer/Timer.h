#ifndef __BASE_TIMER_H
#define __BASE_TIMER_H	 
#include "sys.h"


#define TIM6_HZ 	100
#define TIM6_ms		10
#define TIM6_ARR 	1000
#define TIM6_PSC	720

#define TIM7_HZ		1000
#define TIM7_ms		1
#define TIM7_ARR 	100
#define TIM7_PSC	720

#if (TIM7_ms != 1)
#warning  TIM_ms ȫ�岻׼!
#endif


extern uint32_t 	TIM_Global_ms;	//ȫ��ms��ʱ
extern uint32_t 	TIM_ms;					//ms����ʱ

extern volatile _Bool  	TIM_MPU_10ms;		//10msһ��
extern volatile _Bool  	TIM_10ms;				//10msһ����
extern volatile _Bool  	TIM_200ms;			//200msһ����
extern volatile _Bool  	TIM_500ms;			//500msһ����
extern volatile _Bool	 	TIM_1000ms;			//1000msһ����

void Timer_Init(void);		//�ܳ�ʼ��
void Timer6_Init(void);
void Timer7_Init(void);

void TIM6_IRQHandler(void);
void TIM7_IRQHandler(void); 
								
#endif
