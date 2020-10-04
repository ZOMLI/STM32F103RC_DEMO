/**
	*		USART串口IO口设置
	*	
	*		注意事项:
	*	
	*		备注:
	*	
	*		版本: 2.0.0	
	*
	*		更新时间: 2019/09/10
	*
	*/



#include "HW_Usart.h"
#include "stdio.h"



//#if 1		/*	printf 重定向	*/
//#pragma import(__use_no_semihosting)          	//调用C库

//struct __FILE 																	//支持标准库需要的函数   
//{ 
//	int handle; 
//}; 

//FILE __stdout;       
//    
//void _sys_exit(int x) 													//定义函数以避免使用半主机模式
//{ 
//	x = x; 
//} 

//int fputc(int ch, FILE *f)											//重定义fputc函数 
//{      
//	while((USART1->SR&0X40)==0)__NOP;							//循环发送,直到发送完毕   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 


void HW_Usart_Init(void)
{
	
	
}




