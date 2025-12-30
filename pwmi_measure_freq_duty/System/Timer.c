#include "stm32f10x.h"                  // Device header

void timer_init(void)
{
	
	// 1. 初始化 RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  
	
	
	// 2. 选择时钟源
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);  
	
	
	// 3. 时基单元初始化
	TIM_TimeBaseInitTypeDef tim_time_base_init;
	tim_time_base_init.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_time_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_time_base_init.TIM_Period = 10 - 1;
	tim_time_base_init.TIM_Prescaler = 1 - 1;
	tim_time_base_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &tim_time_base_init);  
	
	
	// 4. 使能中断输出控制
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  
	
	
	// 5. 初始化 NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 5.1. 设置优先级分组
	
	NVIC_InitTypeDef nvic_init;
	nvic_init.NVIC_IRQChannel = TIM2_IRQn;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvic_init);  // 5.2. 初始化 NVIC
	
	
	TIM_Cmd(TIM2, ENABLE);  // 6. 运行控制
}	


//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}

