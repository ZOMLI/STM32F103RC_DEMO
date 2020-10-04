/**
	* USART串口IO口设置
	*
	*	注意事项:
	*		1.直接关联printf
	*		2.暂不支持复用
	*	
	*	备注:
	*
	*	版本: 1.0.0	
	*	
	*	更新时间: 2019/08/28
	*
	*/




#include "sys.h"
#include "usart.h"	  


#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USARTx->SR&0X40)==0)__NOP;//循环发送,直到发送完毕   
    USARTx->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
#if EN_USARTx_RX   //如果使能了接收
u8 USART_RX_BUF[USART_REC_LEN];   //接收缓冲,最大USART_REC_LEN字节.bit:15接收完成标志 bit:14~0接收到的有效字节数目
u16 USART_RX_STA=0;       				//接收状态标记
  
void uart_init(void){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	USARTx_RCC();//使能USARTx，RX,TX时钟
	RCC_APB2PeriphClockCmd(USARTx_TX_RCC_APB2CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(USARTx_RX_RCC_APB2CLOCK, ENABLE);
  
	//USART1_TX
  GPIO_InitStructure.GPIO_Pin 	= USARTx_TX_PIN; 						//TX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;					//复用推挽输出
  GPIO_Init(USARTx_TX_GPIOx, &GPIO_InitStructure);					//初始化GPIOA.9
   
  //USART1_RX
  GPIO_InitStructure.GPIO_Pin 	= USARTx_RX_PIN;						//RX
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;		//浮空输入
  GPIO_Init(USARTx_RX_GPIOx, &GPIO_InitStructure);					//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQN;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;	//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);														//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate 		= USARTx_BOUNT;												//串口波特率
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;								//字长为8位数据格式
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;										//一个停止位
	USART_InitStructure.USART_Parity 			= USART_Parity_No;										//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode			 	= USART_Mode_Rx | USART_Mode_Tx;			//双工模式

  USART_Init(USARTx, &USART_InitStructure); 			//初始化串口1
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	//开启串口接受中断
  USART_Cmd(USARTx, ENABLE);                    	//使能串口1 
}


void USARTx_IRQ_FUN(void)        //串口1中断服务程序
{
	static uint8_t mode=0;
	uint8_t Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USARTx);	//读取接收到的数据
		switch(mode)
		{
			case 0:
				if(Res==0x0D) 
					mode++;
				else 
				{
					USART_RX_BUF[USART_RX_STA&0x7FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))	USART_RX_STA=0;
				}
				break;
				
			case 1:
				if(Res==0x0A) USART_RX_STA	|= 0x8000;
				else					USART_RX_STA=0;
				mode=0;
				break;
			
			default :
				printf("串口接收出错!!!\r\n");
				break;
		}
	}
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	

