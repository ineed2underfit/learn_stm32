#include "stm32f10x.h"                  // Device header

uint16_t sensor_irq_count;  // 中断触发次数  


// 初始化
void sensor_count_init(void)  
{
	// 使能 RCC 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
	// 配置 GPIO
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // EXTI 推荐浮空/上拉/下拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  // GPIO 初始化

	
	// 配置 AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);  // 配置 AFIO 的数据选择器

	
	// 配置 EXTI
	EXTI_InitTypeDef EXTI_InitStructure;  // 定义结构体
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;  // 开启中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  // 中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  // 下降沿触发
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发
	EXTI_Init(&EXTI_InitStructure);  // 注意取地址符 &
	
	
	// 配置 NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 选择第二个分组
	
	// 配置中断通道 EXTI15_10_IRQn
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  // 响应优先级
	NVIC_Init(&NVIC_InitStructure);  // 注意取地址符 &
	
}




// 返回计次
uint16_t get_irq_count(void)
{
	return sensor_irq_count;
}


// 中断函数
//void EXTI15_10_IRQHandler(void)
//{
//	if (EXTI_GetITStatus(EXTI_Line14) == SET)
//	{
//		sensor_irq_count ++;  // 若中断, 次数 + 1
//		
//		EXTI_ClearITPendingBit(EXTI_Line14);
//	}
//	
//}
