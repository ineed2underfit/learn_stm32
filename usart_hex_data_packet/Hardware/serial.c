#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t serial_tx_packet[4];
uint8_t serial_rx_packet[4];
volatile uint8_t serial_rx_flag;  // 中断共享变量必须 volatile

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



// 串口 -> USB 发送字节
void serial_tx_byte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == 0);
}


// 串口 -> USB 发送数组
void serial_tx_array(uint8_t array[], uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length; i++)
	{
		serial_tx_byte(array[i]);
	}
}


// 发送单个数据包
void serial_tx_single_packet(void)
{
	serial_tx_byte(0xFF);                  // 包头
	serial_tx_array(serial_tx_packet, 4);  // 载荷
	serial_tx_byte(0xFE);                  // 包尾
}



/**
  * @brief  USART1 中断服务函数
  * @param  无
  * @retval 无
  * @note   逻辑：
  * 1. 采用状态机接收固定格式数据包：包头(0xFF) + 数据(4字节) + 包尾(0xFE)
  * 2. 接收成功后，serial_rx_flag 置 1，数据存储在全局数组 serial_rx_packet[] 中
  */
void USART1_IRQHandler(void)
{
	static uint8_t rx_state = 0;
	static uint8_t p_rx_state = 0;  // 记录数组的第 p 个成员
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == 1)
	{
		uint8_t serial_rx_data = USART_ReceiveData(USART1);  // 获取数据
		if (rx_state == 0)
		{
			if (serial_rx_data == 0xFF)  // 收到包头
			{
				rx_state = 1;
				p_rx_state = 0;
			}
			
		}			 
		else if (rx_state == 1)
		{
			serial_rx_packet[p_rx_state] = serial_rx_data;
			p_rx_state++;
			if (p_rx_state >= 4)
			{
				rx_state = 2;
			}
			
		}
		else if (rx_state == 2)
		{
			if (serial_rx_data == 0xFE)  // 收到包尾
			{
				rx_state = 0;
				serial_rx_flag = 1;  // "数据包接收完成" 标志位, 获取成功则置 1
			}
		}
	}
}



// 获取 "数据包接收完成" 标志位
uint8_t serial_get_rx_flag(void)
{
	if (serial_rx_flag == 1)
	{
		serial_rx_flag = 0;
		return 1;
	}
	return 0;
}

