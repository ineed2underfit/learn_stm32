#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "ad.h"

float voltage;
uint16_t ad_value;
uint16_t mv;


int main(void)
{
	OLED_Init();
    ad_init();

	OLED_ShowString(1, 1, "ad_value: ");
	OLED_ShowString(2, 1, "voltage: 0.00V");

	
	while (1)
	{
		// ad_value = ad_get_value_single();
		ad_value = ad_get_value_continuous();  // 连续转换模式
		mv = 3300 * ad_value / 4095;  // 向下截断
		
		// 1. 显示转换值
		OLED_ShowNum(1, 11, ad_value, 4);
		
		
		// 2. 显示电压值
		// 2. 1. 整数位
		OLED_ShowNum(2, 10, mv / 1000, 1);
		// 2. 2. 小数位
		OLED_ShowNum(2, 12, (mv % 1000) / 10, 2);


		Delay_ms(50);
	}
}

