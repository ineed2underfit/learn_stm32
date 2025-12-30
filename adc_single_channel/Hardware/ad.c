#include "stm32f10x.h"                  // Device header


void ad_init(void)
{
	// 1.1. 初始化时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // 配置 ADC 的时钟来源的分频, 选择 6 分频
	
	
	// 1.2. 使能 RCC 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	
	// 2. 初始化 GPIO
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // GPIO 初始化
	
	
	// 3. 配置规则组输入通道
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	
	// 4. 配置 ADC
	ADC_InitTypeDef adc_init;
	//adc_init.ADC_ContinuousConvMode = DISABLE;  // 是否连续模式
	adc_init.ADC_ContinuousConvMode = ENABLE;  // 是否连续模式
	adc_init.ADC_DataAlign = ADC_DataAlign_Right;  // 数据对齐方式
	adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  // 外部触发源
	adc_init.ADC_Mode = ADC_Mode_Independent;  // 独立模式
	adc_init.ADC_NbrOfChannel = 1;  // 扫描模式下通道数目
	adc_init.ADC_ScanConvMode = DISABLE;  // 是否扫描模式
	ADC_Init(ADC1, &adc_init);
	
	
	// 5. 看门狗
	// 按需配置
	
	
	// 6. 开启中断
	// 按需配置
	
	
	// 7. 使能 ADC
	ADC_Cmd(ADC1, ENABLE);
	
	
	// 8. 校准
	ADC_ResetCalibration(ADC1);  // 复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);  // 复位完毕则跳出循环
	ADC_StartCalibration(ADC1);  // 开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);  // 校准完毕则跳出循环

}



// 获取返回值 (单次转换模式)
uint16_t ad_get_value_single(void)
{
	// 软件触发 ADC 规则组
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  
	
	// 等待转换完毕
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);  
	
	// 获取转换结果并自动清除 EOC
	return ADC_GetConversionValue(ADC1);  
}


// 获取返回值 (连续转换模式)
uint16_t ad_get_value_continuous(void)
{
	// 软件触发 ADC 规则组
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  
	
	// 无需等待转换完毕
	
	// 获取转换结果并自动清除 EOC
	return ADC_GetConversionValue(ADC1);  
}

