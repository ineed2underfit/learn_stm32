#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "serial.h"


int main(void)
{
	OLED_Init();
	serial_init();
    Key_Init(); 
	

	OLED_ShowString(1, 1, "tx_data: ");
	OLED_ShowString(3, 1, "rx_data: ");
	
	// 定义数据包的载荷数据
	serial_tx_packet[0] = 0x01;
	serial_tx_packet[1] = 0x02;
	serial_tx_packet[2] = 0x03;
	serial_tx_packet[3] = 0x04;
	
	
	while (1)
	{
		if (Key_GetNum() == 1)
		{
			// 定义数据包的载荷数据
			serial_tx_packet[0] ++;
			serial_tx_packet[1] ++;
			serial_tx_packet[2] ++;
			serial_tx_packet[3] ++;
			
			serial_tx_single_packet();
			
			OLED_ShowHexNum(2, 1, serial_tx_packet[0], 2);
			OLED_ShowHexNum(2, 4, serial_tx_packet[1], 2);
			OLED_ShowHexNum(2, 7, serial_tx_packet[2], 2);
			OLED_ShowHexNum(2, 10, serial_tx_packet[3], 2);
			
		}
		if (serial_get_rx_flag() == 1)
		{
			OLED_ShowHexNum(4, 1, serial_rx_packet[0], 2);
			OLED_ShowHexNum(4, 4, serial_rx_packet[1], 2);
			OLED_ShowHexNum(4, 7, serial_rx_packet[2], 2);
			OLED_ShowHexNum(4, 10, serial_rx_packet[3], 2);
		}
	}
}

