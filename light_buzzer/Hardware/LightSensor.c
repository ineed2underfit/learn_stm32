#include "stm32f10x.h"                  // Device header



void LightSensor_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能时钟
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  // GPIO 初始化
}


uint8_t LightSensor_GetNum(void){
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}

