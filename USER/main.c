/**
	*	STM32F10x�հ�ģ��
	*
	*	ע������:
	*
	*	��ע:
	*
	*	�汾: 1.0.1.1
	*
	*	����:
	*		ͨѶ��:
	*			1.SPI
	*			2.IIC
	*		�㷨��:
	*			1.�����
	*			2.PID
	*		������:
	*			1.DMA
	*			2.������
	*			3.LCD��������
	*			4.USMART
	*		ϵͳ*
	*
	*
	*	����: 2019_08_31
	*
	*/
#include "zhead.h"














int main(void)
 {	
	//��������
	int x=1;
	//�����ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ�����2

	uart_init();																		//���ڳ�ʼ��
	delay_init();	    															//��ʱ��ʼ��	  
//	LED_Init();		  																//LED��ʼ��
	 
	 
//	Timer_Init();																		//��ʱ����ʼ��
//	Adc_Init();																			//ADC��ʼ��
//	PWM_Init();																			//PWM��ʼ��
//	Key_Exit_Init();																//�����ⲿ�жϳ�ʼ��
//	can_void();																			//CAN��ʼ��
	
	//�����ֵԤ��
	delay_ms(300);
//	Flash_data_Load();
//	Set_LED_Case(LED_MODE_NONE);
	
	 printf("hi!");
	
	GPIO_Init_Pins(GPIOA,GPIO_Pin_0,GPIO_Mode_AF_PP);
	bsp_timer_init(TIM2,3999,359,2,2);
	bsp_pwm_init(TIM2,CH1);
	bsp_pwm_set_duty(TIM2,CH1,0.5);
	bsp_pwm_set_data(TIM2,CH1,500);
	bsp_pwm_set_HighTime(TIM2,CH1,1000);
	 while(1)
	 {
		 
		 
//	usart_CMD();													//���������,����ʹ�ܴ�����ִ�п����
	delay_ms(1000);
	}
 }

 
 
 
 
 
 

