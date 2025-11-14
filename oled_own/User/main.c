#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "OLED.h"
#include "OLED_Font.h"



int main(void)
{
	OLED_Init();

	
	
	OLED_ShowBMP(0, 0, 128, 64, pingu);	
	// OLED_Clear();
	
	while (1)
	{
		
	}
}

