#ifndef __CAN_SENT_DRV8301_H
#define __CAN_SENT_DRV8301_H

#include "sys.h"



#define CAN_IDE_STD                 0           /**< @brief Standard id.    */
#define CAN_IDE_EXT                 1           /**< @brief Extended id.    */


// CAN commands CAN����
typedef enum {
	CAN_PACKET_SET_DUTY = 0,  							//CAN����ռ�ձ�	����λΪ��32λ(int�ͱ���),��32λ����Ϊ0; ���뱶��Ϊ����ֵ��1e-5��;	
	CAN_PACKET_SET_CURRENT,									//CAN���õ���	ͬ��	����1e-3		
	CAN_PACKET_SET_CURRENT_BRAKE,						//CAN����ɲ������		
	CAN_PACKET_SET_RPM,											//CAN����ת��
	CAN_PACKET_SET_POS,											//CAN���û��û�(�޸�)
	CAN_PACKET_FILL_RX_BUFFER,							//CAN���� ���RX������
	CAN_PACKET_FILL_RX_BUFFER_LONG,					//CAN����  ���RX������LONG
	CAN_PACKET_PROCESS_RX_BUFFER,						//CAN���� ����RX������	
	CAN_PACKET_PROCESS_SHORT_BUFFER,				//CAN���� ����RX������SHORT
	CAN_PACKET_STATUS,				
	CAN_PACKET_SET_CURRENT_REL,							//CAN���� ��������
	CAN_PACKET_SET_CURRENT_BRAKE_REL,				//CAN���� �������� 0.0~1.0
	CAN_PACKET_SET_CURRENT_HANDBRAKE,				//CAN����  ��ɲ����
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL		//CAN����  ��ɲ��������
} CAN_PACKET_ID;


#pragma anon_unions //���֧����������
/**
 * @brief   CAN transmission frame.
 * @note    Accessing the frame data as word16 or word32 is not portable because
 *          machine data endianness, it can be still useful for a quick filling.
 */
typedef struct {  //CAN ����֡���
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
void comm_can_set_rpm(uint8_t controller_id, float rpm);//��Ƕ� = ת��ת��*������
void comm_can_set_pos(uint8_t controller_id, float pos);
void comm_can_set_current_rel(uint8_t controller_id, float current_rel);
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel);
void comm_can_set_handbrake(uint8_t controller_id, float current);
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel);


#endif
