/**
	* USART����IO������
	*
	*	ע������:
	*		1.ֱ�ӹ���printf
	*		2.�ݲ�֧�ָ���
	*	
	*	��ע:
	*
	*	�汾: 1.0.0	
	*	
	*	����ʱ��: 2019/08/28
	*
	*/




#include "sys.h"
#include "usart.h"	  


#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USARTx->SR&0X40)==0)__NOP;//ѭ������,ֱ���������   
    USARTx->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
#if EN_USARTx_RX   //���ʹ���˽���
u8 USART_RX_BUF[USART_REC_LEN];   //���ջ���,���USART_REC_LEN�ֽ�.bit:15������ɱ�־ bit:14~0���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       				//����״̬���
  
void uart_init(void){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	USARTx_RCC();//ʹ��USARTx��RX,TXʱ��
	RCC_APB2PeriphClockCmd(USARTx_TX_RCC_APB2CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(USARTx_RX_RCC_APB2CLOCK, ENABLE);
  
	//USART1_TX
  GPIO_InitStructure.GPIO_Pin 	= USARTx_TX_PIN; 						//TX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;					//�����������
  GPIO_Init(USARTx_TX_GPIOx, &GPIO_InitStructure);					//��ʼ��GPIOA.9
   
  //USART1_RX
  GPIO_InitStructure.GPIO_Pin 	= USARTx_RX_PIN;						//RX
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;		//��������
  GPIO_Init(USARTx_RX_GPIOx, &GPIO_InitStructure);					//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQN;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);														//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate 		= USARTx_BOUNT;												//���ڲ�����
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;								//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;										//һ��ֹͣλ
	USART_InitStructure.USART_Parity 			= USART_Parity_No;										//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode			 	= USART_Mode_Rx | USART_Mode_Tx;			//˫��ģʽ

  USART_Init(USARTx, &USART_InitStructure); 			//��ʼ������1
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	//�������ڽ����ж�
  USART_Cmd(USARTx, ENABLE);                    	//ʹ�ܴ���1 
}


void USARTx_IRQ_FUN(void)        //����1�жϷ������
{
	static uint8_t mode=0;
	uint8_t Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USARTx);	//��ȡ���յ�������
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
				printf("���ڽ��ճ���!!!\r\n");
				break;
		}
	}
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

