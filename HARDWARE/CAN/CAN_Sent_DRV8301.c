/**
	*	本杰明方案无刷电机驱动板之CAN传输协议(主机发送)
	*	
	*	注意事项(仅对配套驱动板):
	*		1.波特率1M
	*		2.CAN传输函数预先自己填写!!
	*		3.使用拓展ID
	*		4.ID的低8位为 对象;其余位为 命令;
	*		5.全体广播ID为 0XFF 驱动板独立ID为APP内设
	*		6.CAN控制电机须重复发送 指令最大间隔为2秒 超2秒会导致超时启动保护程序(电机会停,但如果重复发送间隔超过2秒会跑得不流畅)
	*		7.添加支持匿名联合(#pragma anon_unions)
	*
	*	版本:V1.0.0
	* 
	*	更新时间:2019.08.04
	*
	* 作者:MEIC战队
	*/


#include "CAN_Sent_DRV8301.h"
#include "string.h"


/**************************自定义一个CAN传输函数********************************/
#define CANTRANSMIT 0 //0:使用默认程序 1:自定义
#ifdef CANTRANSMIT
#if !CANTRANSMIT
// 默认程序为STMF103正点原子的CAN例程测试-已测试 
#include "can.h"
static int canTransmit(const CANTxFrame *ctfp)
{
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
//	TxMessage.StdId		=	ctfp->SID;																									// 标准标识符 
	TxMessage.ExtId		=	ctfp->EID;																									// 设置扩展标示符 
	TxMessage.IDE			=	CAN_Id_Extended; 																						// 扩展帧
	TxMessage.RTR			=	CAN_RTR_Data;																								// 数据帧
	TxMessage.DLC			=	ctfp->DLC;																									// 要发送的数据长度
	
	for(i=0;i<ctfp->DLC;i++)
	TxMessage.Data[i]=ctfp->data8[i];			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;			// 等待发送结束
	if(i>=0XFFF)return 1;
	return 0;	 
}
#else
static void canTransmit(const CANTxFrame *ctfp)
{
	//填在这
}
#endif
#else
#error  undeclared identifier CANTRANSMIT //没有自己创建一个CAN传输函数
#endif




void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) {
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int32(buffer, (int32_t)(number * scale), index);
}


void comm_can_transmit_eid(uint32_t id, uint8_t *data, uint8_t len) {
	CANTxFrame txmsg;

	if (len > 8) {	len = 8;	}
	
	txmsg.IDE = CAN_IDE_EXT;
	txmsg.EID = id;
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = len;
	memcpy(txmsg.data8, data, len);

	canTransmit(&txmsg);

}

void comm_can_transmit_sid(uint32_t id, uint8_t *data, uint8_t len) {
	
	CANTxFrame txmsg;
	
	if (len > 8) {	len = 8;	}
	
	txmsg.IDE = CAN_IDE_STD;
	txmsg.SID = id;
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = len;
	memcpy(txmsg.data8, data, len);

	canTransmit(&txmsg);
}

void comm_can_set_duty(uint8_t controller_id, float duty) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(duty * 100000.0f), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

void comm_can_set_current(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void comm_can_set_current_brake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), buffer, send_index);
}

void comm_can_set_rpm(uint8_t controller_id, float rpm) {
	int32_t send_index = 0; 
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)rpm, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}

void comm_can_set_pos(uint8_t controller_id, float pos) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(pos * 1000000.0f), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}

/** 设置电流相对于最小和最大电流限制。
 * Set current relative to the minimum and maximum current limits.
 *
 * @param controller_id
 * The ID of the VESC to set the current on.
 *
 * @param current_rel
 * The relative current value, range [-1.0f 1.0f]
 */
void comm_can_set_current_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5f, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_REL << 8), buffer, send_index);
}

/** 设置制动电流相对于最小电流限制。
 * Set brake current relative to the minimum current limit.
 *
 * @param controller_id
 * The ID of the VESC to set the current on.
 *
 * @param current_rel
 * The relative current value, range [0.0f 1.0f]
 */
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5f, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE_REL << 8), buffer, send_index);
}

/** 设置手刹电流
 * Set handbrake current.
 *
 * @param controller_id
 * The ID of the VESC to set the handbrake current on.
 *
 * @param current_rel
 * The handbrake current value
 */
void comm_can_set_handbrake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current, 1e3f, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE << 8), buffer, send_index);
}

/**
 * Set handbrake current relative to the minimum current limit.
 *
 * @param controller_id
 * The ID of the VESC to set the handbrake current on.
 *
 * @param current_rel
 * The relative handbrake current value, range [0.0f 1.0f]
 */
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_float32(buffer, current_rel, 1e5f, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE_REL << 8), buffer, send_index);
}

