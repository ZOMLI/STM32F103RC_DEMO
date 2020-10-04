#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  

//所保存的数据结构
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



#define STM32_FLASH_SIZE 256 	 												//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1       			 								//使能FLASH写入(0，不是能;1，使能)

#define STM32_FLASH_BASE 0x08000000 									//STM32 FLASH的起始地址
#define FLASH_SAVE_ADDR  0X08020000 									//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
#define STM32_SAVE_SIZE  (sizeof(_flash_save_data))	 		//flash保存数据的长度
 
 
 
 
 
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  													//读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);											//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);			//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   			//从指定地址开始读出指定长度的数据

//测试写入
void Test_Write(u32 WriteAddr,u16 WriteData);			

void Flash_data_Save(void);	//flash数据全保存
void Flash_data_Load(void);	//flash数据全装载
void Flash_data_Read(void);	//flash数据全读取(打印)

#endif

















