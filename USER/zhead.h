/**
	*	文件头文件总集
	*
	*	注意事项:
	*
	*	备注:
	*		因移植考虑,只有有确认会大规模调用其他文件才会引入"zhead.h"
	*
	*	使用文件预期:
	*		main文件
	*		通讯命令文件
	*		程序运行内容文件
	*
	*	版本: 1.0.0.0
	*
	*	更新: 2019_09_03
	*
	*/

#ifndef __ZHEAD_H
#define __ZHEAD_H


	//全局配置宏
#define 	USART_CMD 		0
#define 	USART_DISP_DEFAULT 		0x00





	//头文件调用
#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "comm_usart.h"
#include "Timer.h"
#include "adc.h"
#include "pwm.h"
#include "stmflash.h"
#include "key_exit.h"
#include "can.h"




// 2020年更新过的程序
//片内外设
#include "bsp_gpio.h"
#include "bsp_timer.h"
#include "bsp_pwm.h"






#endif












