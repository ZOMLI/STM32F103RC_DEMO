/**
	*	定时器计时程序
	*
	*	注意事项:
	*	
	*	备注:
	*
	*	版本: 1.0.0 
	*
	* 更新日期: 2019_08_06
	*
	*/
	
#include "Timer.h"

#include "usart.h"
#include "led.h"




uint32_t 	TIM_Global_ms;		//全局ms定时
uint32_t 	TIM_ms=0;					//ms倒计时	

volatile _Bool  	TIM_MPU_10ms;		//10ms一开
volatile _Bool  	TIM_10ms;				//10ms一开关
volatile _Bool  	TIM_200ms;			//200ms一开关
volatile _Bool  	TIM_500ms;			//500ms一开关
volatile _Bool	 	TIM_1000ms;			//1000ms一开关

void Timer_Init(void)
{
	Timer6_Init();																			//初始化10ms级中断定时器
	Timer7_Init();																			//初始化1ms级中断定时器
}

void Timer6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);					//使能TIM6时钟
	
	//初始化定时器6 TIM6
	TIM_TimeBaseStructure.TIM_Period 				= TIM6_ARR-1 ; 				//设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler 		=	TIM6_PSC-1 ; 				//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 							//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  							//TIM6更新中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  		//先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  					//从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  															//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);											//允许更新中断
	
  TIM_Cmd(TIM6,ENABLE ); 																				//使能定时器6
}

//void TIM6_IRQHandler(void) 
//{ 
//if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
//	{
//	
//	}
//    TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 								//清除中断标志位
// 
//}


void Timer7_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);					//使能TIM7时钟
	
	//初始化定时器7 TIM7
	TIM_TimeBaseStructure.TIM_Period 				= TIM7_ARR-1; 				//设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler 		=	TIM7_PSC-1; 				//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 							//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  							//TIM7更新中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  					//从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  															//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);											//允许更新中断
	
  TIM_Cmd(TIM7,ENABLE ); 																				//使能定时器7
}

//void TIM7_IRQHandler(void) 
//{ 
//if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
//	{
//		TIM_Global_ms++;
//		if(TIM_ms>0) TIM_ms--;
//		if((TIM_Global_ms%10)==0)				TIM_10ms			=!	TIM_10ms;
//		if((TIM_Global_ms%200)==0)		{	TIM_200ms			=!	TIM_200ms;  LED_Case();	}		//灯
//		if((TIM_Global_ms%500)==0)			TIM_500ms			=!	TIM_500ms;
//		if((TIM_Global_ms%1000)==0)			TIM_1000ms		=!	TIM_1000ms;
//		if( TIM_Global_ms>0x7fffffff)		TIM_Global_ms	=		0;													//超时手动溢出
//		
//    TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 																		//清除中断标志位
//	}
//}

