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

	// USART 对 USB 发送字节
	serial_tx_byte(0x41);
	serial_tx_byte('A');
	
	
	// USART 对 USB 发送数组
	uint8_t my_array[] = {0x41, 0x42, 0x43};
	serial_tx_array(my_array, 3);
	
	
	// USART 对 USB 发送字符串
	char my_string[] = "\r\nI like eatting shit\r\n";
	serial_tx_string(my_string);
	
	
	// 打印到 OLED
	// 1. printf 方法 要重定向
	printf("I like eatting shit\r\n");
	printf("114514\r\n");
	
	// 2. sprintf 方法
	char string[100];
	sprintf(string, "I am going to Shantou\r\n");
	serial_tx_string(string);
	
	// 3. 封装 sprintf 方法
	serial_printf("I am going to Nanjing\r\n");
	
	
	// 发送汉字到串口软件
	serial_printf("想撸管\r\n");
	
	while (1)
	{
		
	}
}

