#ifndef OLED_IIC_H
#define OLED_IIC_H
#include "stm32f10x.h"
 
#define OLED_ON  0xFF	//��
#define OLED_OFF 0x00	//��
#define high 1
#define low 0
#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
 
/*OLED IICͨѶ��غ궨��*/
#define OLED_CMD 				0		//д����
#define OLED_DATA 				1		//д����
#define IIC_ADD_WC 				0x78	//IICͨѶд����ʱ�ĵ�ַ
#define IIC_ADD_WD 				0x78	//IICͨѶд����ʱ�ĵ�ַ
#define IIC_CONC 				0x00	//�����ֽ�ָ����һ���ֽ�Ϊ����
#define IIC_COND 				0x40	//�����ֽ�ָ����һ���ֽ�Ϊ����SS
 
/*SSD1306 ���������*/
#define SET_CONTRAST_CONTROL		        0x7F	//�Աȶ��������ȡֵ��Χ1-255����λֵ��0x7F		81
#define SET_DISPLAY_ON				0xAF	//����ʾ����
#define SET_DISPLAY_OFF				0xAE	//����ʾ����
#define ENTIRE_DISPLAY_ON_A4		        0xA4	//ȫ����ʾ�ر�
#define ENTIRE_DISPLAY_ON_A5		        0xA5	//ȫ����ʾ����
#define NORMAL_DISPLAY				0xA6	//��GDDRAMֵΪ0��Ϩ�����أ���GDDRAMֵΪ1����������
#define INVERSE_DISPLAY				0xA7	//��GDDRAMֵΪ0���������أ���GDDRAMֵΪ1��Ϩ������
 
/*SSD1306 ������ʾ�����*/
#define HORIZONTAL_SCROLL_SETUP_RIGHT	        0x26	//����ˮƽ�ƶ�
#define HORIZONTAL_SCROLL_SETUP_LEFT	        0x27	//����ˮƽ�ƶ�
#define HORIZONTAL_SCROLL_SETUP_AE		0x00	//����ˮƽ�ƶ�ʱ����Ҫ�������ֽ�
#define HORIZONTAL_SCROLL_SETUP_F		0xFF	//����ˮƽ�ƶ�ʱ����Ҫ�������ֽ�
#define ACTIVATE_SCROLL				0x2F	//����������ʾ����	
#define DEACTIVATE_SCROLL			0x2E	//�رչ�����ʾ����
#define SET_VERTICAL_SCROLL_AREA		0xA3	//���ô�ֱ������Χ����	
#define HV_SCROLL_SRTEP_RIGHT			0x29	//����ˮƽ�ƶ�
#define HV_SCROLL_SRTEP_LEFT			0x2A	//����ˮƽ�ƶ�
 
/*SSD1306 ��ַ���������*/
#define SET_MEMORY_ADDR_MODE			0x20	//���õ�ַģʽ��0x00,�е�ַģʽ��0x01,�е�ַģʽ��0x10��ҳ��ַģʽ
 
/*SSD1306 Ӳ�����������*/
#define SET_SEGMENT_REMAP_A0			0xA0	//�е�ַ0ӳ�䵽SEG0
#define SET_SEGMENT_REMAP_A1			0xA1	//�е�ַ0ӳ�䵽SEG127
#define SET_MULTIPLEX_RATIO			0xA8	//��������·��
#define SET_COM_SCAN_DIRECTION_C0		0xC0	//ɨ�跽���COM0-->COM[N-1]
#define SET_COM_SCAN_DIRECTION_C8		0xC8	//ɨ�跽���COM[N-1]-->COM0
#define SET_DISPLAY_OFFSET			0xD3	//��������ʾƫ��
#define SET_COM_PINS_CONFIG			0xDA	//����COMӲ��������������
 
/*SSD1306 ��ʾʱ�Ӻ�������������*/
#define SET_DISPLAY_CLOCK			0xD5	//����ʱ�ӷ�Ƶ���ӡ���Ƶ��
#define SET_PRECHARGE_PERIOD			0xD9	//����Ԥ�������
#define SET_VCOMH_DESELECT_L			0xDB	//����VCOMH��Դ����
#define CHARGE_PUMP_SET				0x8D	//��ɱ�����
 
/*��ʾ�ַ����Ͷ���*/
#define TYPE_12X06			        0x01	//��ʾ12*06�ַ�
#define TYPE_16X08			        0x02	//��ʾ16*08�ַ�
#define TYPE_16X16			        0x03	//��ʾ16*16�ַ�
 
extern u8 Old_Menu_Page;
extern u8 Display_Fleg;
extern u8 OLED_GRAM[8][128];
extern u8 Menu_Page;
extern u8 Display_Fleg;
extern u8 Data_buff[25];
 
 
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void); 
void OLED_Init(void);
void OLED_Draw_Point(u8 x,u8 y,u8 c);
void OLED_Refresh_Screen(void);
void LCD_ShowFont(u32 x,u32 y,u32 w,u32 h,u8 *p);
void OLED_SetCursorAddrese(u8 x,u8 y);
void OLED_PageClear(u8 page);
void OLED_DisplayString(u8 x,u8 y,u8 width,u8 height,u8 *str);
u8 Oled_Display(u8 x ,u8 y ,u8 width , u8 height);
void OLED_Menu_Display(void);
 
#endif

