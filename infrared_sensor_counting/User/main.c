#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "sensor_counter.h"



int main(void)
{
	OLED_Init();
	sensor_count_init();
	
	OLED_ShowString(1, 1, "Count: ");

	
	
	
	while (1)
	{
		OLED_ShowNum(1, 8, get_irq_count(), 5);
//		OLED_ShowNum(1, 8, sensor_irq_count, 5);
	}
}

