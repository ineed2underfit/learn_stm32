#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "pwm.h"
#include "key.h"
#include "dc_motor.h"

int8_t speed = 0;  // 默认初始速度

int main(void)
{ 
	OLED_Init();
	pwm_init();
	key_init();
	dc_motor_init();

	OLED_ShowString(1, 1, "speed:");

	while (1)
	{
		if (key1_get_num() == 1)
		{
			if (speed >= -50) speed = speed - 50;
			else speed = -100;
		}
		if (key2_get_num() == 1)
		{
			if (speed <= 50) speed = speed + 50;
			else speed = 100;
		}
		dc_motor_set_speed(speed);
		OLED_ShowSignedNum(1, 8, speed, 3);
	}

}


