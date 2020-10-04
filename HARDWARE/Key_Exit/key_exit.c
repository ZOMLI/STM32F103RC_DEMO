/**
	*	外部中断按键
	*
	* 注意事项:
	*		1.因处理按键抖动问题给了中断延时10ms
	*		2.总是使能AFIO时钟
	*		3.中断服务函数不能一样
	*
	*	备注:
	*
	*	版本:1.0.0
	*
	*	更新时间 2018_08_10
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
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//外部中断，需要使能AFIO时钟
#ifdef KEY_RCC_SPECIAL
		KEY_RCC_SPECIAL();																	//特殊复用
#endif

#if KEY0_ENABLE 
	
		RCC_APB2PeriphClockCmd(KEY0_RCC_APB2CLOCK,ENABLE);	//使能PORTx时钟
		GPIO_InitStructure.GPIO_Pin  = KEY0_GPIO_PIN;	
		if(KEY0_ACT_LEVEL)	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				//低电平有效则设置成下拉输入
		else 								
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//高电平有效则设置成上拉输入
		GPIO_Init(KEY0_GPIO, &GPIO_InitStructure);					//初始化KEY0
	
	  //KEY0中断线以及中断初始化配置
  	GPIO_EXTILineConfig(KEY0_GPIO_SOURCE,KEY0_PIN_SOURCE);

  	EXTI_InitStructure.EXTI_Line		=	KEY0_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//初始化EXTI
		
		 
  	NVIC_InitStructure.NVIC_IRQChannel 	= KEY0_EXTI_IRQN;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
#endif 

#if KEY1_ENABLE
	
		RCC_APB2PeriphClockCmd(KEY1_RCC_APB2CLOCK,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin  = KEY1_GPIO_PIN;	
		if(KEY1_ACT_LEVEL)	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				//低电平有效则设置成下拉输入
		else 								
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//高电平有效则设置成上拉输入		
		GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);					//初始化KEY1
	
		 //KEY1中断线以及中断初始化配置
  	GPIO_EXTILineConfig(KEY1_GPIO_SOURCE,KEY1_PIN_SOURCE);

  	EXTI_InitStructure.EXTI_Line		=	KEY1_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//初始化EXTI
	
		NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQN;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
	
#endif

#if KEY2_ENALBE

		RCC_APB2PeriphClockCmd(KEY2_RCC_APB2CLOCK,ENABLE);

		GPIO_InitStructure.GPIO_Pin  = KEY2_GPIO_PIN;	
		if(KEY2_ACT_LEVEL)	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				//低电平有效则设置成下拉输入
		else 								
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//高电平有效则设置成上拉输入
		GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);					//初始化KEY2

    //KEY2中断线以及中断初始化配置
  	GPIO_EXTILineConfig(KEY2_GPIO_SOURCE,KEY2_PIN_SOURCE);

   	EXTI_InitStructure.EXTI_Line		=	KEY2_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//初始化EXTI
 
   	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQN;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
#endif
 
}

#include "comm_usart.h"
#include "delay.h"
#if KEY0_ENABLE
void KEY0_EXTI_IRQ_FUNC(void)
{
  delay_ms(10);    //消抖
	if(KEY0==KEY0_ACT_LEVEL)
	{	  
		LED0=!LED0;
		LED1=!LED1;	
	}
	EXTI_ClearITPendingBit(KEY0_EXTI_LINE);  //清除EXTI0线路挂起位
}
#endif

#if KEY1_ENABLE
 void KEY1_EXTI_IRQ_FUNC(void)
{			
	delay_ms(10);   //消抖			 
	if(KEY1==KEY1_ACT_LEVEL)	
	{
		LED0=!LED0;
	}
 	 EXTI_ClearITPendingBit(KEY1_EXTI_LINE);    //清除LINE5上的中断标志位  
}
#endif
#if KEY2_ENALBE
void KEY2_EXTI_IRQ_FUNC(void)
{
  delay_ms(10);    //消抖			 
  if(KEY2==KEY2_ACT_LEVEL)
	{
		LED1=!LED1;
	}
	 EXTI_ClearITPendingBit(KEY2_EXTI_LINE);  //清除LINE15线路挂起位
}
#endif




