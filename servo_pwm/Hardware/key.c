#include "stm32f10x.h"                  // Device header
#include "Delay.h" 


void key_init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能时钟
	
	// 按键初始化
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
}


// 读取按键 1 值
uint8_t key1_get_num(void){
	
	uint8_t key1_num = 0;  // 默认返回 0 
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)  // 若按下
	{
		Delay_ms(20); // 按下时消抖, 抖动完再判定
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)  // 确认稳定按下, 而不是单跳变
		{
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0){}  // 等待松开
			Delay_ms(20);  // 松开时消抖
			key1_num = 1;
		}
	}
	return key1_num;
}


// 读取按键 2 值
uint8_t key2_get_num(void){
	
	uint8_t key2_num = 0;  // 默认返回 0 
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		Delay_ms(20); // 按下时消抖
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)  // 确认稳定按下, 而不是单跳变
		{
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0){}  // 等待松开
			Delay_ms(20);  // 松开时消抖
			key2_num = 1;
		}
	}
	return key2_num;
}


