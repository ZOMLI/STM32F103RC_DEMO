#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  

//����������ݽṹ
typedef struct _FLASH_PID_SAVE
	{
		float Kp;
		float Ki;
		float Kd;
		float I_max;
		float O_max;
	}falsh_pid;

typedef struct _FALSH_SAVE_STRUCT
{
	falsh_pid speed;
	falsh_pid position;
}_flash_save_data;


extern _flash_save_data flash_save_data;



#define STM32_FLASH_SIZE 256 	 												//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1       			 								//ʹ��FLASHд��(0��������;1��ʹ��)

#define STM32_FLASH_BASE 0x08000000 									//STM32 FLASH����ʼ��ַ
#define FLASH_SAVE_ADDR  0X08020000 									//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
#define STM32_SAVE_SIZE  (sizeof(_flash_save_data))	 		//flash�������ݵĳ���
 
 
 
 
 
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  													//��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);											//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);			//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   			//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);			

void Flash_data_Save(void);	//flash����ȫ����
void Flash_data_Load(void);	//flash����ȫװ��
void Flash_data_Read(void);	//flash����ȫ��ȡ(��ӡ)

#endif

















