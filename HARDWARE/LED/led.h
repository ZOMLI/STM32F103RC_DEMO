#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//�����߼�
#define LED_ON 	0
#define LED_OFF	1



//LED������ʱ������
#define LED0 								PAout(8)
#define LED0_GPIO 					GPIOA
#define LED0_GPIO_PIN				GPIO_Pin_8
#define LED0_RCC_APB2CLOCK	RCC_APB2Periph_GPIOA

#define LED1 								PDout(2)
#define LED1_GPIO 					GPIOD
#define LED1_GPIO_PIN				GPIO_Pin_2
#define LED1_RCC_APB2CLOCK	RCC_APB2Periph_GPIOD

#define LED2_ENABLE					0
#define LED2_DEFAULT				1
#define LED2								PCout(10)
#define LED2_GPIO						GPIOC
#define LED2_GPIO_PIN				GPIO_Pin_10
#define LED2_RCC_APB2CLOCK	RCC_APB2Periph_GPIOC

//#define TIM_LED_ms 
#ifdef TIM_LED_ms
extern volatile _Bool TIM_200ms;
extern volatile _Bool TIM_500ms;
extern volatile _Bool TIM_1000ms;
#endif


typedef enum {
	LED_MODE_NONE,
	//LED0����
	LED_MODE_ON_ON,
	LED_MODE_ON_OFF,
	LED_MODE_ON_1HZ,
	LED_MODE_ON_2HZ,
	LED_MODE_ON_5HZ,
	//LED0����
	LED_MODE_OFF_ON,
	LED_MODE_OFF_OFF,
	LED_MODE_OFF_1HZ,
	LED_MODE_OFF_2HZ,
	LED_MODE_OFF_5HZ,
	//LED0 1HZ
	LED_MODE_1HZ_ON,
	LED_MODE_1HZ_OFF,
	LED_MODE_1HZ_1HZ,
	LED_MODE_1HZ_2HZ,
	LED_MODE_1HZ_5HZ,
	LED_MODE_1HZ_1NHZ,
	LED_MODE_1HZ_2NHZ,
	LED_MODE_1HZ_5NHZ,
	//LED0 2HZ
	LED_MODE_2HZ_ON,
	LED_MODE_2HZ_OFF,
	LED_MODE_2HZ_1HZ,
	LED_MODE_2HZ_2HZ,
	LED_MODE_2HZ_5HZ,
	LED_MODE_2HZ_1NHZ,
	LED_MODE_2HZ_2NHZ,
	LED_MODE_2HZ_5NHZ,
	//LED0 5HZ
	LED_MODE_5HZ_ON,
	LED_MODE_5HZ_OFF,
	LED_MODE_5HZ_1HZ,
	LED_MODE_5HZ_2HZ,
	LED_MODE_5HZ_5HZ,
	LED_MODE_5HZ_1NHZ,
	LED_MODE_5HZ_2NHZ,
	LED_MODE_5HZ_5NHZ,
	
	
	

	LED_MODE_FAULT
	
} LED_MODE;


void LED_Init(void);										//��ʼ��
void LED_Case(void);										//LED���� PS:���Ӧ�÷��ڶ�ʱ���ж���
void Set_LED_Case(LED_MODE CaseNum);		//���õ���ģʽ

#endif
