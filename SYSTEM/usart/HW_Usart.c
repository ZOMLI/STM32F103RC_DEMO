/**
	*		USART����IO������
	*	
	*		ע������:
	*	
	*		��ע:
	*	
	*		�汾: 2.0.0	
	*
	*		����ʱ��: 2019/09/10
	*
	*/



#include "HW_Usart.h"
#include "stdio.h"



//#if 1		/*	printf �ض���	*/
//#pragma import(__use_no_semihosting)          	//����C��

//struct __FILE 																	//֧�ֱ�׼����Ҫ�ĺ���   
//{ 
//	int handle; 
//}; 

//FILE __stdout;       
//    
//void _sys_exit(int x) 													//���庯���Ա���ʹ�ð�����ģʽ
//{ 
//	x = x; 
//} 

//int fputc(int ch, FILE *f)											//�ض���fputc���� 
//{      
//	while((USART1->SR&0X40)==0)__NOP;							//ѭ������,ֱ���������   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 


void HW_Usart_Init(void)
{
	
	
}




