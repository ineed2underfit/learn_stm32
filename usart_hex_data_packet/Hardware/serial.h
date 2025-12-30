#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

extern uint8_t serial_tx_packet[];
extern uint8_t serial_rx_packet[];

void serial_init(void);
void serial_tx_byte(uint8_t Byte);
void serial_tx_array(uint8_t array[], uint16_t length);
uint8_t serial_get_rx_flag(void);

void serial_tx_single_packet(void);  // 发送数据包
	
#endif
