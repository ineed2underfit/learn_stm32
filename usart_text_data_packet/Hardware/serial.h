#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

extern char serial_rx_packet[];
extern volatile uint8_t serial_rx_flag;  // 中断共享变量必须 volatile


void serial_init(void);
void serial_tx_byte(uint8_t Byte);
void serial_tx_array(uint8_t array[], uint16_t length);

void serial_tx_single_packet(void);  // 发送数据包
	
#endif
