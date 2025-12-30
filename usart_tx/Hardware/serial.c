#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

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


// 串口 -> USB 发送字符串
void serial_tx_string(char string[])
{
	uint16_t i;
	for(i = 0; string[i]!=0x00; i++)
	{
		serial_tx_byte(string[i]);
	}
}


// 封装 sprintf 函数
void serial_printf(char *format, ...)
{
	char string[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(string, format, arg);
	va_end(arg);
	serial_tx_string(string);	
}


int fputc(int ch, FILE *f)
{
	serial_tx_byte(ch);
	return ch;
}
