/**
	*	usartͨѶЭ�麯��
	*
	*	ע������:
	*		1.��ʹ�� USART_TEXT
	*		2.������115200
	*		3.��֡ͷ,֡β��ʽΪ 0x0A 0x0D
	*		4.��Ե��Ե���ʹ��(���и�ʽ��Ϊ�ַ���)
	*		5.�ַ���󳤶� 15  ������󳤶� 16(����.)
	*		6.����ֱ�ӵ���printf()��ӡ;
	*		7.�����ʽΪ :(����) (����) 
	*		8.���н��պ����Խ�
	*
	*	������־:
	*		1.�ĳ��ýṹ���б�.
	*			.2 �����ӡ��װ�ɺ���.
	*
	*	��֪BUG:
	*
	*	�汾:1.1.2
	*
	* ����ʱ��: 2019_09_28
	*
	*/
	
#include "zhead.h"
#include "comm_usart.h"
#include "string.h"
#include "stdlib.h"
#include "stmflash.h"

uint8_t usart_disp=USART_DISP_DEFAULT;

//��������
uint16_t text1=0;
uint16_t text2=0;
uint16_t text3=0;
uint16_t text4=0;


struct _usart_cmdtab
{
	USART_RE_MODE MODE;			//����ѡ��
	const char* name;				//��������
											//��ִ�к���
};
//�����б�
static const struct _usart_cmdtab usart_cmdtab[]={
	USART_RE_MODE_,												"",
//flash����� ���
	USART_RE_MODE_GET_SPEED_KP,						"speedkp",
	USART_RE_MODE_GET_SPEED_KI,						"speedki",
	USART_RE_MODE_GET_SPEED_KD,						"speedkd",
	USART_RE_MODE_GET_SPEED_PID,					"speedpid",
	USART_RE_MODE_GET_POSITOIN_KP,				"poskp",
	USART_RE_MODE_GET_POSITOIN_KI,				"poski",
	USART_RE_MODE_GET_POSITOIN_KD,				"poskd",
	USART_RE_MODE_GET_POSITOIN_PID,				"pospid",
	
	USART_RE_MODE_SET_SPEED_KP,						"setspeedkp",
	USART_RE_MODE_SET_SPEED_KI,						"setspeedki",
	USART_RE_MODE_SET_SPEED_KD,						"setspeedkd",
	USART_RE_MODE_SET_POSITOIN_KP,				"setposkp",
	USART_RE_MODE_SET_POSITOIN_KI,				"setposki",
	USART_RE_MODE_SET_POSITOIN_KD,				"setposkd",
	
	USART_RE_MODE_GET_FLASH_DATA,					"flashdata",
	USART_RE_MODE_LAOD_FLASH_DATA,				"flashload",
	USART_RE_MODE_SAVE_FLASH_DATA,				"flashsave",
	
//��ӡ��ʾ
	USART_RE_MODE_DISP,										"disp",
	USART_RE_MODE_DISP_ALL,								"dispall",
	USART_RE_MODE_DISP_NONE,							"dispnone",
	USART_RE_MODE_DISP_1,									"disp1",
	USART_RE_MODE_DISP_2,									"disp2",
	USART_RE_MODE_DISP_3,									"disp3",
	USART_RE_MODE_DISP_4,									"disp4",

//�����ʹ���
	USART_RE_MODE_HELP,										"?",
	USART_RE_MODE_HELP1,									"help",
	USART_RE_MODE_GET_CLOCK,							"clock",
	USART_RE_MODE_TEXT_FLOAT,							"text",
	USART_RE_MODE_TEXT_HEX,								"textfloat",
	USART_RE_MODE_FAULT,									"texthex",
	USART_RE_MODE_END,										""
};


//˽�б���
static	uint8_t ind=0;
static	uint8_t ind_stage1=0;
static	uint8_t ind_stage2=0;
static	uint8_t compare_data1[16]={'\0'};
static	uint8_t compare_data2[16]={'\0'};
static 	RCC_ClocksTypeDef rccclock;

//˽�к���
static _Bool AlpJudge(const uint8_t *data,const uint8_t len,const char a[]);
static USART_RE_MODE comm_usart_process_judge(const uint8_t *data,const uint8_t len);
static float AlpJudge_float(const uint8_t *data,const uint8_t len);
static void Clipping_Hex(const uint8_t *data,const uint8_t len);
static int AlpJudge_Hex(const uint8_t *data,const uint8_t len);


//����
void comm_usart_process(const uint8_t *data,const uint8_t len)
{
	ind=0;
	ind_stage1=0;
	ind_stage2=0;
	memset(compare_data1,'\0',sizeof(compare_data1));
	memset(compare_data2,'\0',sizeof(compare_data2));
	
	if(len == 0 ) return;
	
	//������
		//ģʽ��
		while( (ind<len) && Re_Range_Cmd(data[ind]) )
		{
			compare_data1[ind] = data[ind];
			ind++;
		}
		if(ind==0) printf("��������...\r\n");
		ind_stage1 = ind;
		ind++; //�����ո�
		
		//���ݶ�
		while( (ind<len) && Re_Range_Num(data[ind]) )
		{
			compare_data2[ind-ind_stage1-1] = data[ind];
			ind++;
		}
		ind_stage2 = ind - ind_stage1-1;
			
	switch( comm_usart_process_judge(compare_data1,ind_stage1) )
	{

		case USART_RE_MODE_:
			printf("???");
			break;
		//flash����� ���
		case USART_RE_MODE_GET_SPEED_KP:	ffnprint(Speed_Kp,flash_save_data.speed.Kp);			break;
		case USART_RE_MODE_GET_SPEED_KI:	ffnprint(Speed_Ki,flash_save_data.speed.Ki);			break;
		case USART_RE_MODE_GET_SPEED_KD:	ffnprint(Speed_Kd,flash_save_data.speed.Kd);			break;
		
		case USART_RE_MODE_GET_SPEED_PID:
			ffprint(Speed_Kp,flash_save_data.speed.Kp);
			ffprint(Speed_Ki,flash_save_data.speed.Ki);
			ffnprint(Speed_Kd,flash_save_data.speed.Kd);
		break;
		
		
		case USART_RE_MODE_GET_POSITOIN_KP:	ffnprint(Pos_Kp,flash_save_data.position.Kp);			break;
		case USART_RE_MODE_GET_POSITOIN_KI:	ffnprint(Pos_Kp,flash_save_data.position.Ki);			break;
		case USART_RE_MODE_GET_POSITOIN_KD:	ffnprint(Pos_Kp,flash_save_data.position.Kd);			break;
		
		case USART_RE_MODE_GET_POSITOIN_PID:
			ffprint(Pos_Kp,flash_save_data.position.Kp);
			ffprint(Pos_Kp,flash_save_data.position.Ki);
			ffnprint(Pos_Kp,flash_save_data.position.Kp);
			break;
		
		case USART_RE_MODE_SET_SPEED_KP:
			flash_save_data.speed.Kp=AlpJudge_float(compare_data2,ind_stage2);
			ffnprint(Speed_Kp,flash_save_data.speed.Kp);
			break;
	
		
		case USART_RE_MODE_SET_SPEED_KI:
			flash_save_data.speed.Ki=AlpJudge_float(compare_data2,ind_stage2);
			ffnprint(Speed_Ki,flash_save_data.speed.Ki);
			break;
		
		case USART_RE_MODE_SET_SPEED_KD:
			flash_save_data.speed.Kd=AlpJudge_float(compare_data2,ind_stage2);
			ffnprint(Speed_Kd,flash_save_data.speed.Kd);
			break;
		
		case USART_RE_MODE_SET_POSITOIN_KP:
			flash_save_data.position.Kp=AlpJudge_float(compare_data2,ind_stage2);
			ffnprint(Pos_Kp,flash_save_data.position.Kp);
			break;
		
		case USART_RE_MODE_SET_POSITOIN_KI:
			flash_save_data.position.Ki=AlpJudge_float(compare_data2,ind_stage2);
			ffnprint(Pos_Kp,flash_save_data.position.Ki);
			break;
		
		case USART_RE_MODE_SET_POSITOIN_KD:
			flash_save_data.position.Kd=AlpJudge_float(compare_data2,ind_stage2);
			ffnprint(Pos_Kp,flash_save_data.position.Kd);
			break;
		
		case USART_RE_MODE_GET_FLASH_DATA:
			Flash_data_Read();
			break;
	
		case USART_RE_MODE_LAOD_FLASH_DATA:
			Flash_data_Load();
			printf("Falsh��ȡ�ɹ�...\r\n");
			break;
		
		case USART_RE_MODE_SAVE_FLASH_DATA:
			Flash_data_Save();
			printf("Falsh����ɹ�...\r\n");
			break;
		
		//��ӡ��ʾ
		case  USART_RE_MODE_DISP:
			if 	(usart_disp ==0) usart_disp = 	0xFF;
			else 								 usart_disp = 	0;
		break;
		
		case	USART_RE_MODE_DISP_NONE:	usart_disp = 	0;				break;
		case	USART_RE_MODE_DISP_ALL:		usart_disp = 	0xFF;			break;
		case	USART_RE_MODE_DISP_1:			usart_disp ^= 0x01;			break;
		case	USART_RE_MODE_DISP_2:			usart_disp ^= 0x02;			break;
		case	USART_RE_MODE_DISP_3:			usart_disp ^= 0x04;			break;
		case	USART_RE_MODE_DISP_4:			usart_disp ^= 0x08;			break;
		
		//����
		case 	USART_RE_MODE_HELP:
		case  USART_RE_MODE_HELP1:
			usart_disp = 	0;
			ind=0;
			printf("/*************************************************************************/\r\n");
			printf("������������\r\n");
			while(ind<USART_RE_MODE_END)
			{
				ind++;
				printf("%s\r\n",usart_cmdtab[ind].name);
			}
			printf("/*************************************************************************/\r\n");
			break;
		
		case	USART_RE_MODE_GET_CLOCK:
			RCC_GetClocksFreq(&rccclock);
			ddprint(SYSCLK,rccclock.SYSCLK_Frequency);
			ddprint(HCLK,rccclock.HCLK_Frequency);
			ddprint(PCLK1,rccclock.PCLK1_Frequency);
			ddprint(PCLK2,rccclock.PCLK2_Frequency);
			ddprint(ADCCLK,rccclock.ADCCLK_Frequency);
			nprint();
			break;
		
		case	USART_RE_MODE_TEXT_FLOAT:
			ffnprint(text,AlpJudge_float(compare_data2,ind_stage2));
			break;
		
		case	USART_RE_MODE_TEXT_HEX:
			Clipping_Hex(data,len);
			xxnprint(text,AlpJudge_Hex(compare_data2,ind_stage2));
			break;
		
		default:
			printf("��������,ģʽѡ�����(��ģʽδ����?)...\r\n");
			break;
	}
}


//��ӡ��
uint16_t Usart_Switch_Print(void)
{
	return usart_disp;
}


//��������
static USART_RE_MODE comm_usart_process_judge(const uint8_t *data,const uint8_t len)
{
	uint16_t i=0;
	while(i<USART_RE_MODE_END)
	{
	if( AlpJudge(data,len,usart_cmdtab[i].name) ) 	return usart_cmdtab[i].MODE;				//��������ģʽ
	else i++;
	}
	return USART_RE_MODE_END;
}


//�ַ��Ƚ�
static _Bool AlpJudge(const uint8_t *data,const uint8_t len,const char a[])	
{
	int i=0;
	int i_len=strlen(a);
	
	if(len != i_len) return 0;
	
	while(i<i_len)
	{
		if(data[i]==a[i]) i++;
		else return 0;
	}
	return 1;
}


//�ַ�תfloat
static float AlpJudge_float(const uint8_t *data,const uint8_t len)		
{
	int i=0;
	char c[15];	
	while(i<len)										
		{ 
			c[i]=data[i];
			i++;
		} 
	return (float)(atof(c));
}


//��������,�������ݶ�
static void Clipping_Hex(const uint8_t *data,const uint8_t len) 
{
	ind=ind_stage1 +1; 
	while( (ind<len) && Re_Range_Hex(data[ind]) )
	{
		compare_data2[ind-ind_stage1-1] = data[ind];
		ind++;
	}
	ind_stage2 = ind - ind_stage1-1;
}


//�ַ�תHex
static int AlpJudge_Hex(const uint8_t *data,const uint8_t len) 		
{
	int i=0;
	int hex=0;	
	while(i<len)										
		{ 
			hex *= 16;
					 if(data[i]>='0' && data[i]<='9') hex	+= (data[i]-'0');
			else if(data[i]>='a' && data[i]<='f') hex += (data[i]-'a'+10);
			else if(data[i]>='A' && data[i]<='F') hex	+= (data[i]-'A'+10);
			i++;	
		} 
	return hex;
}


void usart_CMD(void)
{
	#if USART_CMD
	if(USART_RX_STA&0x8000)
	{
		comm_usart_process(USART_RX_BUF,USART_RX_STA&0x7FFF);
		USART_RX_STA=0;
	}	
	if(usart_disp)  //���ڿ��ƵĴ�ӡ���
	{
		if(usart_disp&0x01)	dprint(text1);
		if(usart_disp&0x02)	dprint(text2);
		if(usart_disp&0x04)	dprint(text3);
		if(usart_disp&0x08)	dprint(text4);
		nprint();
	}	
#endif
}



