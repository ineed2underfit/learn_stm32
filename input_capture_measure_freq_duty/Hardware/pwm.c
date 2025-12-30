#include "stm32f10x.h"                  // Device header

void pwm_init(void)
{
	// 1. 初始化 RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	
	// 2. 初始化 GPIO 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 推挽复用输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // GPIO 初始化
	
	
	// 3. 选择时钟源
	TIM_InternalClockConfig(TIM2);	
	
	
	// 4. 时基单元初始化
	TIM_TimeBaseInitTypeDef tim_time_base_init;
	tim_time_base_init.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_time_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_time_base_init.TIM_Period = 100 - 1;  // ARR 自动重装寄存器值
	tim_time_base_init.TIM_Prescaler = 720 - 1;  // PSC 预分频
	tim_time_base_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &tim_time_base_init);  
	
	
	// 5. 初始化输出比较单元
	// 频率为1KHz, 占空比为50%, 分辨率为1%的PWM
	TIM_OCInitTypeDef tim_oc_init;
	TIM_OCStructInit(&tim_oc_init);   // 4.1 给结构体赋初始值
	tim_oc_init.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
	tim_oc_init.TIM_OutputState = TIM_OutputState_Enable;
	tim_oc_init.TIM_Pulse = 0;  // CCR 捕获比较寄存器值
	TIM_OC1Init(TIM2, &tim_oc_init);
	
	
	// 6. 运行控制
	TIM_Cmd(TIM2, ENABLE);  
}


// 单独设置预分频值
void pwm_set_prescaler(uint16_t pres)
{
	TIM_PrescalerConfig(TIM2, pres, TIM_PSCReloadMode_Immediate);
	
}
