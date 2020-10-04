/**	
	*	LED����
	*	
	*	ע������:
	*		1.��TIM_200ms���ض���,���ӵ�TIM��
	*	
	*	��ע:
	*		1.���ڿ��Ժ����б�
	*
	*	�汾: 1.0.2
	*
	* ��������: 2019_08_10
	*
	*/
#include "led.h"
#include "sys.h"
#include "Timer.h"

#ifdef TIM_LED_ms
volatile _Bool TIM_200ms;
volatile _Bool TIM_500ms;
volatile _Bool TIM_1000ms;
#endif

static LED_MODE SetLED=LED_MODE_OFF_ON;			//�趨LED������ʽ  ע�����tim7ʹ��

void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;

 RCC_APB2PeriphClockCmd(LED0_RCC_APB2CLOCK, ENABLE);	 					//ʹ��LEDʱ��
 RCC_APB2PeriphClockCmd(LED1_RCC_APB2CLOCK, ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;	 									//LED0
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(LED0_GPIO, &GPIO_InitStructure);
	
 GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	 									//LED1
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(LED1_GPIO, &GPIO_InitStructure);								 			//�����趨������ʼ��

 LED0=LED_OFF;					 					 															//LED0��ʼ����
 LED1=LED_ON;							 																			//LED1��ʼ����

#if LED2_ENABLE
	RCC_APB2PeriphClockCmd(LED2_RCC_APB2CLOCK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;	 									//LED0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;	 									//LED1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED2_GPIO, &GPIO_InitStructure);								 			//�����趨������ʼ��
	
	LED2 =LED2_DEFAULT;
#endif
}

void LED_Case(void)
{
	switch(SetLED)
	{
		case LED_MODE_NONE:																							break;
		//LED0����
		case LED_MODE_ON_ON:			LED0=LED_ON;			LED1=LED_ON;				break;
		case LED_MODE_ON_OFF:			LED0=LED_ON;			LED1=LED_OFF;				break;
		case LED_MODE_ON_1HZ:			LED0=LED_ON;			LED1=TIM_1000ms;		break;
		case LED_MODE_ON_2HZ:			LED0=LED_ON;			LED1=TIM_500ms;			break;
		case LED_MODE_ON_5HZ:			LED0=LED_ON;			LED1=TIM_200ms;			break;
		//LED0����
		case LED_MODE_OFF_ON:			LED0=LED_OFF;			LED1=LED_ON;				break;
		case LED_MODE_OFF_OFF:		LED0=LED_OFF;			LED1=LED_OFF;				break;
		case LED_MODE_OFF_1HZ:		LED0=LED_OFF;			LED1=TIM_1000ms;		break;
		case LED_MODE_OFF_2HZ:		LED0=LED_OFF;			LED1=TIM_500ms;			break;
		case LED_MODE_OFF_5HZ:		LED0=LED_OFF;			LED1=TIM_200ms;			break;
		//LED0 1HZ
		case LED_MODE_1HZ_ON:			LED0=TIM_1000ms;	LED1=LED_ON;				break;
		case LED_MODE_1HZ_OFF:		LED0=TIM_1000ms;	LED1=LED_OFF;				break;
		case LED_MODE_1HZ_1HZ:		LED0=TIM_1000ms;	LED1=TIM_1000ms;		break;
		case LED_MODE_1HZ_2HZ:		LED0=TIM_1000ms;	LED1=TIM_500ms;			break;
		case LED_MODE_1HZ_5HZ:		LED0=TIM_1000ms;	LED1=TIM_200ms;			break;
		case LED_MODE_1HZ_1NHZ:		LED0=TIM_1000ms;	LED1=!TIM_1000ms;		break;
		case LED_MODE_1HZ_2NHZ:		LED0=TIM_1000ms;	LED1=!TIM_500ms;		break;
		case LED_MODE_1HZ_5NHZ:		LED0=TIM_1000ms;	LED1=!TIM_200ms;		break;
		//LED0 2HZ
		case LED_MODE_2HZ_ON:			LED0=TIM_500ms;		LED1=LED_ON;				break;
		case LED_MODE_2HZ_OFF:		LED0=TIM_500ms;		LED1=LED_OFF;				break;
		case LED_MODE_2HZ_1HZ:		LED0=TIM_500ms;		LED1=TIM_1000ms;		break;
		case LED_MODE_2HZ_2HZ:		LED0=TIM_500ms;		LED1=TIM_500ms;			break;
		case LED_MODE_2HZ_5HZ:		LED0=TIM_500ms;		LED1=TIM_200ms;			break;
		case LED_MODE_2HZ_1NHZ:		LED0=TIM_500ms;		LED1=!TIM_1000ms;		break;
		case LED_MODE_2HZ_2NHZ:		LED0=TIM_500ms;		LED1=!TIM_500ms;		break;
		case LED_MODE_2HZ_5NHZ:		LED0=TIM_500ms;		LED1=!TIM_200ms;		break;
		//LED0 5HZ
		case LED_MODE_5HZ_ON:			LED0=TIM_200ms;		LED1=LED_ON;				break;
		case LED_MODE_5HZ_OFF:		LED0=TIM_200ms;		LED1=LED_OFF;				break;
		case LED_MODE_5HZ_1HZ:		LED0=TIM_200ms;		LED1=TIM_1000ms;		break;
		case LED_MODE_5HZ_2HZ:		LED0=TIM_200ms;		LED1=TIM_500ms;			break;
		case LED_MODE_5HZ_5HZ:		LED0=TIM_200ms;		LED1=TIM_200ms;			break;
		case LED_MODE_5HZ_1NHZ:		LED0=TIM_200ms;		LED1=!TIM_1000ms;		break;
		case LED_MODE_5HZ_2NHZ:		LED0=TIM_200ms;		LED1=!TIM_500ms;		break;
		case LED_MODE_5HZ_5NHZ:		LED0=TIM_200ms;		LED1=!TIM_200ms;		break;
				
		default: break;
	}
}

void Set_LED_Case(LED_MODE CaseNum)
{
	SetLED = CaseNum;
}
