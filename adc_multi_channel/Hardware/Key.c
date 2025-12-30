#include "stm32f10x.h"                  // Device header
#include "Delay.h" 


void Key_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能时钟
	
	// 按键初始化
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
}

// 读取按键值
uint8_t Key_GetNum(void){
	
	uint8_t KeyNum = 0;  // 默认返回 0 
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)  // 若按下
	{
		Delay_ms(20); // 按下时消抖, 抖动完再判定
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0){}  // 消抖后还是按下, 则在此循环
		Delay_ms(20);  // 松开时消抖
		KeyNum = 1;
	}
	
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
	{
		Delay_ms(20); // 按下时消抖
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0){}  // 消抖后还是按下, 则在此循环
		Delay_ms(20);  // 松开时消抖
		KeyNum = 11;
	}
	return KeyNum;
}