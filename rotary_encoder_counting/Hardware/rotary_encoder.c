#include "stm32f10x.h"                  // Device header

int16_t encoder_irq_count;  // 旋转编码器中断触发次数  


// 初始化 GPIOB14 | GPIO_Pin_15
void rotary_encoder_init(void) 
{
	
	// 使能 RCC 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
	// 配置 GPIO14 | GPIO15
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // EXTI 推荐浮空/上拉/下拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  // GPIO 初始化

	
	// 配置 AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);  // 配置 AFIO 的数据选择器
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);  // 将第 15 条线路拨到 GPIOB 上

	
	// 定义 EXTI 结构体
	EXTI_InitTypeDef EXTI_InitStructure;  // 定义结构体, 只需要定义一次
	
	// 配置 EXTI14
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;  // 开启中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  // 中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  // 下降沿触发
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发
	EXTI_Init(&EXTI_InitStructure);  // 注意取地址符 &
	
	// 配置 EXTI15
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;  // 开启中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  // 中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  // 下降沿触发
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发
	EXTI_Init(&EXTI_InitStructure);  // 注意取地址符 &
	
	
	// 配置 NVIC
	NVIC_InitTypeDef NVIC_InitStructure;  // 结构体变量可以重复使用
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 选择第二个分组,  程序中只设置一次

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  // 响应优先级
	
	NVIC_Init(&NVIC_InitStructure);  // 注意取地址符 &
	
}
	
// 中断函数
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		// 反转判断
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)  
		{
			encoder_irq_count++;
		}
//		else
//		{
//			encoder_irq_count++;
//		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
	if (EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		// 正转判断
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)  
		{
			encoder_irq_count--;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	
}


// 返回 encoder_irq_count 的变化值
int16_t get_encoder_irq_count()
{
//	int16_t Temp;
//	Temp = encoder_irq_count;
//	encoder_irq_count = 0;
//	return Temp;
	return encoder_irq_count;
	
}



