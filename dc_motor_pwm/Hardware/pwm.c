#include "stm32f10x.h"                  // Device header


void pwm_init(void)
{
	// 1. 初始化 RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  

	
	// 2. 选择时钟源
	TIM_InternalClockConfig(TIM2);	
	
	
	// 3. 时基单元初始化
	TIM_TimeBaseInitTypeDef tim_time_base_init;
	tim_time_base_init.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_time_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_time_base_init.TIM_Period = 100 - 1;  // ARR 自动重装寄存器值
	tim_time_base_init.TIM_Prescaler = 36 - 1;  // PSC
	tim_time_base_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &tim_time_base_init);  
	
	
	// 4. 初始化输出比较单元
	TIM_OCInitTypeDef tim_oc_init;
	TIM_OCStructInit(&tim_oc_init);   // 4.1 给结构体赋初始值
	tim_oc_init.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
	tim_oc_init.TIM_OutputState = TIM_OutputState_Enable;
	tim_oc_init.TIM_Pulse = 0;  // CCR 捕获比较寄存器值
	TIM_OC3Init(TIM2, &tim_oc_init);  // 初始化通道3
	
	
	// 5. 运行控制
	TIM_Cmd(TIM2, ENABLE);  
}

