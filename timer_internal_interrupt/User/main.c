#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"

uint16_t num;

int main(void)
{
	OLED_Init();
	timer_init();

	// OLED_ShowChar(1, 1, 'O');
	OLED_ShowString(1, 1, "I like jerking");
	OLED_ShowString(2, 1, "off");
	OLED_ShowString(3, 1, "count:");
	//	OLED_ShowSignedNum(2, 1, 12345, 5);
	//	OLED_ShowHexNum(3, 1, 0xFF, 2);
	//	OLED_ShowBinNum(4, 1, 0xFF, 8);
	// OLED_ShowBMP(0, 0, 128, 64, pingu);	
	// OLED_Clear();
	
	while (1)
	{
		OLED_ShowNum(3, 7, num, 5);
		OLED_ShowNum(4, 7, TIM_GetCounter(TIM2), 5);
	}

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
	

}

