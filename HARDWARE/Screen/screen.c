


#include "screen.h"



void screen_init(void)							//屏幕初始化
{
#if  DISP_CHOOSE==0
		//空语句 
#elif DISP_CHOOSE==1				
		LCD_Init();						//LCD屏初始化	 
		LCD_Clear(CYAN); 
		lcd_disp_f_o_meansure_menu(1000,10);		
#elif DISP_CHOOSE==2
		OLED_Init();  //OLED显示屏初始化
		OLED_Clear(); 
#elif DISP_CHOOSE==3
		OLED_Init();  //OLED显示屏初始化
		OLED_Clear(); 
#endif
	
}


void screen_update(void)						//屏幕更新
{
#if  DISP_CHOOSE==0
		//空语句
#elif DISP_CHOOSE==1				
		lcd_disp_adc_menu( Get_Adc_Average(ADC_Channel_1,100) );
#elif DISP_CHOOSE==2
		OLED_Menu_Display();
#elif DISP_CHOOSE==3
		oled_disp_menu(1000,100);
#endif
}













