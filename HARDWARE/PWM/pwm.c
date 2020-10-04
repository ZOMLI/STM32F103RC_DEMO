/**
	*	PWM模板
	*	
	*	注意事项:
	*		1.使能顺序未测试,可能有问题
	*		2.仅支持单通道,多通道copy吧
	*		3.未加入复用支持
	*		4.自动调ARR,PSC功能仅适用于整倍数频率,若要标准PWM频率得手动调节
	*
	*	备注:
	*
	*	版本:	1.0.0
	*
	*
	*/



#include "pwm.h"




void PWM_Init(void)		//输出PWM波
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	PWM_tim_rcc();						//使能TIM时钟
 	PWM_gpio_rcc(); 					//使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM3 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = PWM_PIN; 													//TIM_CH
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  								//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIOx, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = PWM_ARR-1; 									//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =PWM_PSC-1; 								//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 										//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  		//TIM向上计数模式
	TIM_TimeBaseInit(PWM_TIMx, &TIM_TimeBaseStructure); 						//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 							//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; 															//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
	
#if		 (PWM_TIM_CHx==1)		//通道选择
	TIM_OC1Init(PWM_TIMx, &TIM_OCInitStructure);  									//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC1PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);  					//CH预装载使能
	TIM_SetCompare1(PWM_TIMx,PWM_DEF_DATA);													//CCR初值设定
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
  TIM_CtrlPWMOutputs(PWM_TIMx,ENABLE);														//仅高级定时器要用的 MOE主输出使能	
#endif
	 
	TIM_ARRPreloadConfig(PWM_TIMx, ENABLE); 												//使能TIMx在ARR上的预装载寄存器
	TIM_Cmd(PWM_TIMx, ENABLE);  																		//使能TIM
 
}




