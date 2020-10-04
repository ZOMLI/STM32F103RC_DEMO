#include "stm32f10x.h"
#include "iic.h"
 
#define write 0
#define read  1
//IIC���ߵ�ַ�ӿڶ���
#define SCL PAout(4)
#define SDA_OUT PAout(5)
#define SDA_IN PAin(5)
#define IIC_INPUT_MODE_SET()  {GPIOA->CRL&=0xFF0FFFFF;GPIOA->CRL|=0x00800000;}
#define IIC_OUTPUT_MODE_SET() {GPIOA->CRL&=0xFF0FFFFF;GPIOA->CRL|=0x00300000;}
 
void IIC_Init(void)
{
  /*1.��ʱ��*/
  RCC->APB2ENR |= 1<<2;
  /*2.����GPIOģʽ*/
  GPIOA->CRL &= 0xFF00FFFF;
  GPIOA->CRL |= 0x00330000;
  /*3.����GPIO���е�ƽ*/
  GPIOA->ODR |= 0x3<<4;	
  printf("IIC_Init OK��\n");
}	
 
/*******************************************************************
����:����I2C����,������I2C��ʼ����. SCLΪ�ߵ�ƽ�ڼ� SDA�����½���
********************************************************************/
void IIC_Start(void)
{
  IIC_OUTPUT_MODE_SET();
  SDA_OUT=1;
  SCL=1;
  SDA_OUT=0;
	SCL=0;
}
 
/*******************************************************************
����:����I2C����,������I2C��������. SCLΪ�ߵ�ƽ�ڼ� SDA���������� 
********************************************************************/
void IIC_Stop(void)
{
	IIC_OUTPUT_MODE_SET();
	SDA_OUT=0;  	
	SCL=1;
	SDA_OUT=1; 
}
 
/*��������ACK*/
void IIC_ACK(void)
{
  IIC_OUTPUT_MODE_SET();
  SCL=0; 
  SDA_OUT=0;   
  SCL=1;                
  SCL=0;                        
}
 
/*����������ACK*/
void IIC_NACK(void)
{
  IIC_OUTPUT_MODE_SET();
  SCL=0;
  SDA_OUT=1;     
  SCL=1;                  
  SCL=0;                        
}
 
/*�����ȴ��ӻ���ACK*/
u8 IIC_wait_ACK(void)
{
	u8 t = 200;
	IIC_OUTPUT_MODE_SET();
	SDA_OUT=1;//8λ��������ͷ������ߣ�׼������Ӧ��λ 
	SCL=0;
	IIC_INPUT_MODE_SET();
	while(SDA_IN)//�ȴ�Ӧ��
	{
		t--;
		delay_us(1); 
		if(t==0)
		{
			SCL=0;
			return 1;
		}
	}     
	SCL=1;
	SCL=0;                
	return 0;	
}
 
/*******************************************************************
�ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
********************************************************************/
void  IIC_SendByte(u8 byte)
{
	u8  BitCnt;
	IIC_OUTPUT_MODE_SET();
	SCL=0;
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ
	{
		if(byte&0x80) SDA_OUT=1;//�жϷ���λ
		else SDA_OUT=0; 
		byte<<=1;
		SCL=1;
		SCL=0;
	}
}
/*******************************************************************
 �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����: �������մ���������������  
********************************************************************/    
u8 IIC_RcvByte(void)
{
  u8 retc;
  u8 BitCnt;
  retc=0; 
  IIC_INPUT_MODE_SET();//��������Ϊ���뷽ʽ                   
  for(BitCnt=0;BitCnt<8;BitCnt++)
  {  
		SCL=0;	//��ʱ����Ϊ�ͣ�׼����������λ
		delay_us(1);               
		SCL=1;	//��ʱ����Ϊ��ʹ��������������Ч                
		retc=retc<<1;
		if(SDA_IN) retc |=1;//������λ,���յ�����λ����retc�� 
  }
  SCL=0;    
  return(retc);
}



