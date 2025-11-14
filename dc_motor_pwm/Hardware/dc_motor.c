#include "stm32f10x.h"                  // Device header


void dc_motor_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 只需要使能一次时钟
	GPIO_InitTypeDef GPIO_InitStructure;  // 只需要定义一次结构体
	
	// --- 配置 PA2 ---
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // 初始化 PA2
	
	// --- 配置 PA6 和 PA7 ---
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // 初始化 PA6 和 PA7 
}


void dc_motor_set_speed(int8_t speed){
	if (speed >= 0)
	{
		// 顺时针
		GPIO_SetBits(GPIOA, GPIO_Pin_6); 
		GPIO_ResetBits(GPIOA, GPIO_Pin_7); 
		TIM_SetCompare3(TIM2, speed);
	}
	else
	{
		// 逆时针
		GPIO_SetBits(GPIOA, GPIO_Pin_7); 
		GPIO_ResetBits(GPIOA, GPIO_Pin_6); 
		TIM_SetCompare3(TIM2, -speed);  // 注意负号
	}
}

