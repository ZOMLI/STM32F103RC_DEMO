#ifndef __CAN_SENT_DRV8301_H
#define __CAN_SENT_DRV8301_H

#include "sys.h"



#define CAN_IDE_STD                 0           /**< @brief Standard id.    */
#define CAN_IDE_EXT                 1           /**< @brief Extended id.    */


// CAN commands CAN命令
typedef enum {
	CAN_PACKET_SET_DUTY = 0,  							//CAN设置占空比	数据位为高32位(int型保存),低32位保留为0; 输入倍率为输入值的1e-5倍;	
	CAN_PACKET_SET_CURRENT,									//CAN设置电流	同上	倍率1e-3		
	CAN_PACKET_SET_CURRENT_BRAKE,						//CAN设置刹车电流		
	CAN_PACKET_SET_RPM,											//CAN设置转速
	CAN_PACKET_SET_POS,											//CAN设置环置环(无感)
	CAN_PACKET_FILL_RX_BUFFER,							//CAN设置 填充RX缓冲区
	CAN_PACKET_FILL_RX_BUFFER_LONG,					//CAN设置  填充RX缓冲区LONG
	CAN_PACKET_PROCESS_RX_BUFFER,						//CAN设置 处理RX缓冲区	
	CAN_PACKET_PROCESS_SHORT_BUFFER,				//CAN设置 处理RX缓冲区SHORT
	CAN_PACKET_STATUS,				
	CAN_PACKET_SET_CURRENT_REL,							//CAN设置 电流上限
	CAN_PACKET_SET_CURRENT_BRAKE_REL,				//CAN设置 电流下限 0.0~1.0
	CAN_PACKET_SET_CURRENT_HANDBRAKE,				//CAN设置  手刹电流
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL		//CAN设置  手刹电流上限
} CAN_PACKET_ID;


#pragma anon_unions //添加支持匿名联合
/**
 * @brief   CAN transmission frame.
 * @note    Accessing the frame data as word16 or word32 is not portable because
 *          machine data endianness, it can be still useful for a quick filling.
 */
typedef struct {  //CAN 传输帧框架
  struct {
    uint8_t                 DLC:4;          /**< @brief Data length.        */
    uint8_t                 RTR:1;          /**< @brief Frame type.         */
    uint8_t                 IDE:1;          /**< @brief Identifier type.    */
  };
  union {
    struct {
      uint32_t              SID:11;         /**< @brief Standard identifier.*/
    };
    struct {
      uint32_t              EID:29;         /**< @brief Extended identifier.*/
    };
  };
  union {
    uint8_t                 data8[8];       /**< @brief Frame data.         */
    uint16_t                data16[4];      /**< @brief Frame data.         */
    uint32_t                data32[2];      /**< @brief Frame data.         */
  };
} CANTxFrame;



void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index);
void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index);
void comm_can_transmit_eid(uint32_t id, uint8_t *data, uint8_t len);
void comm_can_transmit_sid(uint32_t id, uint8_t *data, uint8_t len);
void comm_can_set_duty(uint8_t controller_id, float duty);
void comm_can_set_current(uint8_t controller_id, float current);
void comm_can_set_current_brake(uint8_t controller_id, float current);
void comm_can_set_rpm(uint8_t controller_id, float rpm);//电角度 = 转子转速*极对数
void comm_can_set_pos(uint8_t controller_id, float pos);
void comm_can_set_current_rel(uint8_t controller_id, float current_rel);
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel);
void comm_can_set_handbrake(uint8_t controller_id, float current);
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel);


#endif
