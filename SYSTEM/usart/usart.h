#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USARTx										USART1
#define USARTx_BOUNT 							115200
#define USARTx_RCC()							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

#define USARTx_TX_GPIOx						GPIOA
#define USARTx_TX_PIN							GPIO_Pin_9
#define USARTx_TX_RCC_APB2CLOCK		RCC_APB2Periph_GPIOA

#define USARTx_RX_GPIOx						GPIOA
#define USARTx_RX_PIN							GPIO_Pin_10
#define USARTx_RX_RCC_APB2CLOCK		RCC_APB2Periph_GPIOA		

#define USARTx_IRQN								USART1_IRQn
#define USARTx_IRQ_FUN						USART1_IRQHandler





#define USART_REC_LEN  						200  	//定义最大接收字节数 200
#define EN_USARTx_RX 							1			//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         					//接收状态标记	
void uart_init(void);


#endif


