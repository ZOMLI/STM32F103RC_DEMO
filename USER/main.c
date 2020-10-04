/**
	*	STM32F10x空白模板
	*
	*	注意事项:
	*
	*	备注:
	*
	*	版本: 1.0.1.1
	*
	*	设想:
	*		通讯类:
	*			1.SPI
	*			2.IIC
	*		算法类:
	*			1.过零点
	*			2.PID
	*		功能类:
	*			1.DMA
	*			2.陀螺仪
	*			3.LCD屏功能类
	*			4.USMART
	*		系统*
	*
	*
	*	更新: 2019_08_31
	*
	*/
#include "zhead.h"














int main(void)
 {	
	//给定变量
	int x=1;
	//各项初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断优先级分组2

	uart_init();																		//串口初始化
	delay_init();	    															//延时初始化	  
//	LED_Init();		  																//LED初始化
	 
	 
//	Timer_Init();																		//定时器初始化
//	Adc_Init();																			//ADC初始化
//	PWM_Init();																			//PWM初始化
//	Key_Exit_Init();																//键盘外部中断初始化
//	can_void();																			//CAN初始化
	
	//各项初值预设
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
		 
		 
//	usart_CMD();													//串口命令函数,若不使能串口则执行空语句
	delay_ms(1000);
	}
 }

 
 
 
 
 
 

