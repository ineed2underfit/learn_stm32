#include "stm32f10x.h"                  // Device header

void ic_init(void)
{
	// 1. 初始化 RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	// 2. 初始化 GPIO 
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // GPIO 初始化
	
	
	// 3. 选择时钟源
	TIM_InternalClockConfig(TIM3);

	
	// 4. 时基单元初始化
	TIM_TimeBaseInitTypeDef tim_time_base_init;
	tim_time_base_init.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_time_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_time_base_init.TIM_Period = 65532 - 1;  // ARR
	tim_time_base_init.TIM_Prescaler = 72 - 1;
	tim_time_base_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &tim_time_base_init);  	
	
	
	// 5. 初始化输入捕获通道
	TIM_ICInitTypeDef tim_ic_init;
	tim_ic_init.TIM_Channel = TIM_Channel_1;  // 通道选择
	tim_ic_init.TIM_ICFilter = 0xF;  // 滤波器
	tim_ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;  // 极性选择
	tim_ic_init.TIM_ICPrescaler = TIM_ICPSC_DIV1;  // 输入采样分频
	tim_ic_init.TIM_ICSelection = TIM_ICSelection_DirectTI;  // 指定触发信号的输入引脚
	TIM_ICInit(TIM3, &tim_ic_init);
	
	
	// 6. 选择从模式触发源
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	
	
	// 7. 选择从模式为复位模式
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	
	// 8. 使能运行控制
	TIM_Cmd(TIM3, ENABLE);
}


// 获取CCR的值, 根据公式, 求出待测频率
uint32_t get_pwm_freq(void)
	{
		return 1000000 / TIM_GetCapture1(TIM3);
	}
	
	
