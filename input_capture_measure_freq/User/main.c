#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "pwm.h"
#include "OLED.h"
#include "input_capture.h"


int main(void)
{
	OLED_Init();
	pwm_init();
	ic_init();
	
	// 单独设置 预分频值
	pwm_set_prescaler(720 - 1);  // Freq = 72MHz / (PSC + 1) / 100
	
	// 单独设置 CCR	
	TIM_SetCompare1(TIM2, 60);  // Duty = CCR / (ARR + 1) = CCR / 100 
	
	OLED_ShowString(1, 1, "freq: ");
	
	while(1)
	{
		OLED_ShowNum(1, 7, get_pwm_freq(), 6);
	}
}


