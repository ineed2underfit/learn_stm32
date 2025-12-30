#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "sensor_counter.h"
#include "encoder_interface.h"
#include "Timer.h"


int16_t speed;

int main(void)
{
	OLED_Init();
	timer_init();
	encoder_interface_init();
	
	OLED_ShowString(1, 1, "speed: ");
	
	
	while (1)
	{
		OLED_ShowSignedNum(1, 8, speed, 5);
	}
}


// 中断函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		speed = encoder_get_cnt_speed();  
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

