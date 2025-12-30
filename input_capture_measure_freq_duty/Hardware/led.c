#include "stm32f10x.h"                  // Device header


void led_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能时钟
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 推挽复用输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // GPIO 初始化
}

