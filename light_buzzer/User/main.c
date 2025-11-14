#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"



int main(void)
{
	LightSensor_Init();
	Buzzer_Init();

	while (1)
	{
		if (LightSensor_GetNum() == 0)  // 无光
		{
			Buzzer_OFF();
			
		}
		else
		{
			Buzzer_ON();
		}
		
	}
}

