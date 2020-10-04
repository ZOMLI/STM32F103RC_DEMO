#ifndef __SCREEN_H
#define __SCREEN_H

#include "sys.h"

#include "oled_spi.h"




#define DISP_CHOOSE 	0		//选择用LCD(1)还是OLED_IIC(2)还是OLED_SPI(3)

void screen_init(void);							//屏幕初始化
void screen_update(void);						//屏幕更新




#endif

