#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"

uint8_t KeyNum;  // 全局变量 KeyNum, 与函数内的局部变量 KeyNum 不同

int main(void)
{
	LED_Init();
	Key_Init();

	while (1)
	{
		KeyNum = Key_GetNum(); 
		if (KeyNum == 1)
		{
			LED1_Turn();
//			LED1_ON();
//			LED2_OFF();
		}
		if (KeyNum == 11)
		{
			LED2_Turn();
//			LED2_ON();
//			LED1_OFF();
		}		
	}
}

