#ifndef __SCREEN_H
#define __SCREEN_H

#include "sys.h"

#include "oled_spi.h"




#define DISP_CHOOSE 	0		//ѡ����LCD(1)����OLED_IIC(2)����OLED_SPI(3)

void screen_init(void);							//��Ļ��ʼ��
void screen_update(void);						//��Ļ����




#endif

