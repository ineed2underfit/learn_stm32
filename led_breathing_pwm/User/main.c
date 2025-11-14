#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "pwm.h"

uint16_t i;

int main(void)
{
	led_init();
	pwm_init();

	
	while (1)
	{
		for (i = 0; i <= 80; i++)
		{
			TIM_SetCompare1(TIM2, i);
			Delay_ms(20);
		}
		for (i = 80; i > 0; i--)
		{
			TIM_SetCompare1(TIM2, i);
			Delay_ms(20);
		}	
	}

}


