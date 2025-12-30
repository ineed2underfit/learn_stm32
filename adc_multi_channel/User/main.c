#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "ad.h"


uint16_t ad_value, ad_value1, ad_value2, ad_value3;
uint16_t mv;



int main(void)
{
	OLED_Init();
    ad_init();

	OLED_ShowString(1, 1, "voltage: 0.00V");
	OLED_ShowString(2, 1, "ad_value1: ");
	OLED_ShowString(3, 1, "ad_value2: ");
	OLED_ShowString(4, 1, "ad_value3: ");

	
	while (1)
	{
		ad_value = ad_get_value_single(ADC_Channel_0); 
		ad_value1 = ad_get_value_single(ADC_Channel_1);  
		ad_value2 = ad_get_value_single(ADC_Channel_2);
		ad_value3 = ad_get_value_single(ADC_Channel_3);
		mv = 3300 * ad_value / 4095;  // 向下截断
		
		
		// 2. 显示电压值
		// 2. 1. 整数位
		OLED_ShowNum(1, 10, mv / 1000, 1);
		// 2. 2. 小数位
		OLED_ShowNum(1, 12, (mv % 1000) / 100, 1);

		OLED_ShowNum(2, 12, ad_value1, 4);
		OLED_ShowNum(3, 12, ad_value2, 4);
		OLED_ShowNum(4, 12, ad_value3, 4);
		

		Delay_ms(50);
	}
}

