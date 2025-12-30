#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

void serial_init(void);
void serial_tx_byte(uint8_t Byte);
void serial_tx_array(uint8_t *array, uint16_t length);
void serial_tx_string(char string[]);
void serial_printf(char *format, ...);
	
#endif
