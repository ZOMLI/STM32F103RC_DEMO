#ifndef __COMM_USART_H
#define __COMM_USART_H

#include "sys.h"
#include "usart.h"


//打印改版
#define ddnprint(expr1,expr2) 		printf(#expr1"=%d\r\n",expr2)
#define ffnprint(expr1,expr2) 		printf(#expr1"=%.3f\r\n",expr2)
#define xxnprint(expr1,expr2) 		printf(#expr1"=0x%0x\r\n",expr2)
#define ddprint(expr1,expr2) 			printf(#expr1"=%d\r\t",expr2)
#define ffprint(expr1,expr2) 			printf(#expr1"=%.3f\r\t",expr2)
#define xxprint(expr1,expr2) 			printf(#expr1"=0x%0x\r\t",expr2)
#define dprint(expr) 							printf(#expr"=%d\r\t",expr)
#define fprint(expr) 							printf(#expr"=%.3f\r\t",expr)
#define xprint(expr) 							printf(#expr"=0x%0x\r\t",expr)
#define sprint(expr)							printf(#expr"\r\t")
#define tprint()									printf("\r\t")
#define nprint() 									printf("\r\n")

//接收范围判断
#define Re_Range_dot(expr)			(	expr=='.')
#define Re_Range_neg(expr)			( expr=='-')
#define Re_Range_que(expr)			(	expr=='?')
#define Re_Range_num(expr)			((expr>='0') && (expr<='9'))
#define Re_Range_alp(expr)			((expr>='a') && (expr<='z'))
#define Re_Range_ALP(expr)			((expr>='A') && (expr<='Z'))

#define Re_Range_hex(expr)			(((expr>='0') && (expr<='9'))||((expr>='a') && (expr<='f')))		//0~f
#define Re_Range_HEX(expr)			(((expr>='0') && (expr<='9'))||((expr>='A') && (expr<='F')))		//0~F
#define Re_Range_Hex(expr)			( Re_Range_hex(expr) || ((expr>='A') && (expr<='F')) )					//0~f(F)

#define Re_Range_NUM(expr)			( Re_Range_num(expr) || Re_Range_neg(expr) )										// 数字 + '-'
#define Re_Range_Alp(expr)			( Re_Range_alp(expr) || Re_Range_ALP(expr) )										// 字母
#define Re_Range_Num(expr)			( Re_Range_NUM(expr) || Re_Range_dot(expr) )										// 数字 + '-' + '.'

#define Re_Range_Alp_Num(expr)	( Re_Range_Alp(expr) || Re_Range_Num(expr) )										// 数字 + 字母 + '-' + '.'

#define Re_Range_Cmd(expr)			( Re_Range_que(expr) || Re_Range_Alp_Num(expr) )								// 全命令作用域

#ifndef		USART_CMD
#define 	USART_CMD 		0
#endif
#ifndef USART_DISP_DEFAULT
#define USART_DISP_DEFAULT 0x00
#endif

typedef enum {
	USART_RE_MODE_=0,
//flash与参数 相关
	USART_RE_MODE_GET_SPEED_KP,
	USART_RE_MODE_GET_SPEED_KI,
	USART_RE_MODE_GET_SPEED_KD,
	USART_RE_MODE_GET_SPEED_PID,
	USART_RE_MODE_GET_POSITOIN_KP,
	USART_RE_MODE_GET_POSITOIN_KI,
	USART_RE_MODE_GET_POSITOIN_KD,
	USART_RE_MODE_GET_POSITOIN_PID,
	
	USART_RE_MODE_SET_SPEED_KP,
	USART_RE_MODE_SET_SPEED_KI,
	USART_RE_MODE_SET_SPEED_KD,
	USART_RE_MODE_SET_POSITOIN_KP,
	USART_RE_MODE_SET_POSITOIN_KI,
	USART_RE_MODE_SET_POSITOIN_KD,
	
	USART_RE_MODE_GET_FLASH_DATA,
	USART_RE_MODE_LAOD_FLASH_DATA,
	USART_RE_MODE_SAVE_FLASH_DATA,
	
//打印显示
	USART_RE_MODE_DISP,
	USART_RE_MODE_DISP_ALL,
	USART_RE_MODE_DISP_NONE,
	USART_RE_MODE_DISP_1,
	USART_RE_MODE_DISP_2,
	USART_RE_MODE_DISP_3,
	USART_RE_MODE_DISP_4,

//其他和错误
	USART_RE_MODE_HELP,
	USART_RE_MODE_HELP1,
	USART_RE_MODE_GET_CLOCK,
	USART_RE_MODE_TEXT_FLOAT,
	USART_RE_MODE_TEXT_HEX,
	USART_RE_MODE_FAULT,
	USART_RE_MODE_END
	
} USART_RE_MODE;


void usart_CMD(void);										//命令控制函数,应该放在主循环里
extern uint16_t text1;
extern uint16_t text2;
extern uint16_t text3;
extern uint16_t text4;
extern uint8_t usart_disp;

void comm_usart_process(const uint8_t *data,const uint8_t len);
uint16_t Usart_Switch_Print(void);
void Usart_Swtich_Timeout(void);




#endif
	
	
	
	


