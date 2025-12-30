#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint16_t serial_rx_data;
uint16_t serial_rx_flag;

void serial_init(void)
{
	// 1. 开启 RCC 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	// 2. 初始化 GPIOA
	// 初始化 PA9 -> USART1_TX
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;  // 推挽复用输出 模式
	gpio_init.GPIO_Pin = GPIO_Pin_9;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init);  
	
	// 初始化 PA910 -> USART1_RX
	gpio_init.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入 模式
	gpio_init.GPIO_Pin = GPIO_Pin_10;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init);  // GPIO 初始化
	
	
	// 3. 初始化 USART1
	USART_InitTypeDef usart_init;
	USART_StructInit(&usart_init);  // 给结构体赋初值
	usart_init.USART_BaudRate = 9600;
	usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_init.USART_Parity = USART_Parity_No;
	usart_init.USART_StopBits = USART_StopBits_1;
	usart_init.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &usart_init);
	
	
	// 4. 使能 USART 外设
	USART_Cmd(USART1, ENABLE);
	
	
	// 5. 使能 USART 中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	
	// 5. 配置 NVIC 
	// 5.1 优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// 5.2 初始化 NVIC
	NVIC_InitTypeDef nvic_init;
	nvic_init.NVIC_IRQChannel = USART1_IRQn;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvic_init);  // 5.2. 初始化 NVIC
}


// 中断函数
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == 1)
	{
		serial_rx_data = USART_ReceiveData(USART1);  // 获取数据
		serial_rx_flag = 1;  // "获取数据成功" 标志位, 获取成功则置 1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


// 获取 "获取数据成功" 标志位
uint8_t serial_get_rx_flag(void)
{
	if (serial_rx_flag == 1)
	{
		serial_rx_flag = 0;
		return 1;
	}
	return 0;
}


// 获取数据
uint8_t serial_get_rx_data(void)
{
	return serial_rx_data;
}

