#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "led.h"
#include "pwm.h"
#include "servo.h"
#include "key.h"

uint16_t angle = 90;  // 默认初始角度

int main(void)
{ 
	OLED_Init();
	led_init();
	pwm_init();
	servo_init();
	key_init();

	OLED_ShowString(1, 1, "angle:");
	
	while (1)
	{
		if (key1_get_num() == 1)
		{
			if (angle >= 45) angle = angle - 45;
			else angle = 0;
		}
		if (key2_get_num() == 1)
		{
			if (angle <= 135) angle = angle + 45;
			else angle = 180;
		}
		
		servo_set_angle(angle);
		OLED_ShowNum(1, 8, angle, 3);
	}
}

