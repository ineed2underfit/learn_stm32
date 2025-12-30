#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "serial.h"
#include <string.h>


int main(void)
{
	OLED_Init();
	serial_init(); 
	LED_Init();
	

	//OLED_ShowString(1, 1, "tx_data: ");
	OLED_ShowString(1, 1, "rx_data: ");
	OLED_ShowString(3, 1, "led_state: ");
	
	
	uint8_t sys_mode = 0; // 0:灭, 1:亮, 2:闪烁 (全局变量或静态变量)

	while (1)
	{
		// 1. 串口指令解析处理
		if (serial_rx_flag == 1)
		{
			OLED_ShowString(2, 1, "                "); // 清屏
			OLED_ShowString(2, 1, serial_rx_packet);
			
			if (strcmp(serial_rx_packet, "ledon") == 0)
			{
				sys_mode = 1; // 切换到模式1
				OLED_ShowString(4, 1, "led_on");
			}
			else if (strcmp(serial_rx_packet, "ledoff") == 0)
			{
				sys_mode = 0; // 切换到模式0
				OLED_ShowString(4, 1, "led_off");
			}
			else
			{
				sys_mode = 2; // 切换到闪烁模式
				OLED_ShowString(4, 1, "error command");
			}
	
			serial_rx_flag = 0;
			// 注意：这里需要确保 serial_rx_flag 被清零，通常在 get 函数内部或此处手动处理
		}

		// 2. 根据当前模式控制硬件执行
		if (sys_mode == 1)
		{
			LED1_ON();
		}
		else if (sys_mode == 0)
		{
			LED1_OFF();
		}
		else if (sys_mode == 2)
		{
			// 持续闪烁逻辑
			LED1_ON();
			Delay_ms(200); // 延时要用毫秒级(ms)，肉眼才能看到闪烁
			LED1_OFF();
			Delay_ms(200);
		}
		
		
	}
}

