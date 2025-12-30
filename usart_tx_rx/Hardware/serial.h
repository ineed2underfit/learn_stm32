#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

void serial_init(void);
uint8_t serial_get_rx_flag(void);
uint8_t serial_get_rx_data(void);
	
#endif
