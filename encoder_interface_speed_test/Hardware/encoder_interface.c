#include "stm32f10x.h"  

void encoder_interface_init(void)
{
	// 1. 使能RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	// 2. 配置 PA6 | PA7
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // EXTI 推荐浮空/上拉/下拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // GPIO 初始化
	
	
	// 选择时钟源 -- 不再需要了
	// TIM_InternalClockConfig(TIM3);	
	
	
	// 3. 配置时基单元
	TIM_TimeBaseInitTypeDef tim_time_base_init;
	tim_time_base_init.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_time_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_time_base_init.TIM_Period = 65536 - 1;  // ARR
	tim_time_base_init.TIM_Prescaler = 1 - 1;
	tim_time_base_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &tim_time_base_init);  	
	
	
	// 4. 初始化输入捕获通道
	TIM_ICInitTypeDef tim_ic_init;
	TIM_ICStructInit(&tim_ic_init);
	
	// --- 配置 通道1 --- 
	tim_ic_init.TIM_Channel = TIM_Channel_1;  // 通道选择
	tim_ic_init.TIM_ICFilter = 0xF;  // 滤波器
	tim_ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;  // 极性选择: 上升沿
	TIM_ICInit(TIM3, &tim_ic_init); 
	
	// --- 配置 通道2 ---	
	tim_ic_init.TIM_Channel = TIM_Channel_2;  // 通道选择
	tim_ic_init.TIM_ICFilter = 0xF;  // 滤波器
	tim_ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;  // 极性选择: 上升沿
	TIM_ICInit(TIM3, &tim_ic_init); 
	
	
	// 5. 配置编码器接口
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	
	// 6. 使能定时器
	TIM_Cmd(TIM3, ENABLE);
}


// 读取CNT值
int16_t encoder_get_cnt(void)
{
	return TIM_GetCounter(TIM3);
}


// 读取CNT值, 并清零
int16_t encoder_get_cnt_speed(void)
{
	int16_t temp;
	temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return temp;
}
