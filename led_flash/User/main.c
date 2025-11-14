#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);// GPIO 初始化
	
	// GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	// GPIO_SetBits(GPIOA, GPIO_Pin_1);
	

	while(1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
		Delay_ms(700);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		Delay_ms(300);
//	
//		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
//		Delay_ms(700);
//		GPIO_SetBits(GPIOA, GPIO_Pin_0);
//		Delay_ms(300);
	}
}
