#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "sensor_counter.h"
#include "rotary_encoder.h"

int16_t Num;

int main(void)
{
	// 初始化外设及中断
	OLED_Init();
	rotary_encoder_init();
	
	OLED_ShowString(1, 1, "Volume: ");

	
	while (1)
	{
//		Num = Num + get_encoder_irq_count();
//		OLED_ShowSignedNum(1, 8, Num, 4);
		OLED_ShowSignedNum(1, 9, get_encoder_irq_count(), 4);  // 显示带符号数值

	}
}

