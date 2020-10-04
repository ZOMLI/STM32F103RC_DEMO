/**
	*	�ⲿ�жϰ���
	*
	* ע������:
	*		1.������������������ж���ʱ10ms
	*		2.����ʹ��AFIOʱ��
	*		3.�жϷ���������һ��
	*
	*	��ע:
	*
	*	�汾:1.0.0
	*
	*	����ʱ�� 2018_08_10
	*
	*/


#include "key_exit.h"
#include "delay.h"
#include "led.h"

void Key_Exit_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
#ifdef KEY_RCC_SPECIAL
		KEY_RCC_SPECIAL();																	//���⸴��
#endif

#if KEY0_ENABLE 
	
		RCC_APB2PeriphClockCmd(KEY0_RCC_APB2CLOCK,ENABLE);	//ʹ��PORTxʱ��
		GPIO_InitStructure.GPIO_Pin  = KEY0_GPIO_PIN;	
		if(KEY0_ACT_LEVEL)	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				//�͵�ƽ��Ч�����ó���������
		else 								
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//�ߵ�ƽ��Ч�����ó���������
		GPIO_Init(KEY0_GPIO, &GPIO_InitStructure);					//��ʼ��KEY0
	
	  //KEY0�ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(KEY0_GPIO_SOURCE,KEY0_PIN_SOURCE);

  	EXTI_InitStructure.EXTI_Line		=	KEY0_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//��ʼ��EXTI
		
		 
  	NVIC_InitStructure.NVIC_IRQChannel 	= KEY0_EXTI_IRQN;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
#endif 

#if KEY1_ENABLE
	
		RCC_APB2PeriphClockCmd(KEY1_RCC_APB2CLOCK,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin  = KEY1_GPIO_PIN;	
		if(KEY1_ACT_LEVEL)	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				//�͵�ƽ��Ч�����ó���������
		else 								
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//�ߵ�ƽ��Ч�����ó���������		
		GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);					//��ʼ��KEY1
	
		 //KEY1�ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(KEY1_GPIO_SOURCE,KEY1_PIN_SOURCE);

  	EXTI_InitStructure.EXTI_Line		=	KEY1_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//��ʼ��EXTI
	
		NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQN;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
	
#endif

#if KEY2_ENALBE

		RCC_APB2PeriphClockCmd(KEY2_RCC_APB2CLOCK,ENABLE);

		GPIO_InitStructure.GPIO_Pin  = KEY2_GPIO_PIN;	
		if(KEY2_ACT_LEVEL)	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				//�͵�ƽ��Ч�����ó���������
		else 								
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//�ߵ�ƽ��Ч�����ó���������
		GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);					//��ʼ��KEY2

    //KEY2�ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(KEY2_GPIO_SOURCE,KEY2_PIN_SOURCE);

   	EXTI_InitStructure.EXTI_Line		=	KEY2_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//��ʼ��EXTI
 
   	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQN;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
#endif
 
}

#include "comm_usart.h"
#include "delay.h"
#if KEY0_ENABLE
void KEY0_EXTI_IRQ_FUNC(void)
{
  delay_ms(10);    //����
	if(KEY0==KEY0_ACT_LEVEL)
	{	  
		LED0=!LED0;
		LED1=!LED1;	
	}
	EXTI_ClearITPendingBit(KEY0_EXTI_LINE);  //���EXTI0��·����λ
}
#endif

#if KEY1_ENABLE
 void KEY1_EXTI_IRQ_FUNC(void)
{			
	delay_ms(10);   //����			 
	if(KEY1==KEY1_ACT_LEVEL)	
	{
		LED0=!LED0;
	}
 	 EXTI_ClearITPendingBit(KEY1_EXTI_LINE);    //���LINE5�ϵ��жϱ�־λ  
}
#endif
#if KEY2_ENALBE
void KEY2_EXTI_IRQ_FUNC(void)
{
  delay_ms(10);    //����			 
  if(KEY2==KEY2_ACT_LEVEL)
	{
		LED1=!LED1;
	}
	 EXTI_ClearITPendingBit(KEY2_EXTI_LINE);  //���LINE15��·����λ
}
#endif




