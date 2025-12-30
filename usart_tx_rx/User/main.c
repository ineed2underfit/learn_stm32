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
     
	
	OLED_ShowString(1, 1, "usart 2 usb");
	OLED_ShowString(2, 1, "rx_data: ");
	while (1)
	{
		if (serial_get_rx_flag() == 1)
		{
			OLED_ShowHexNum(2, 10, serial_get_rx_data(), 2);
		}
	}
}

