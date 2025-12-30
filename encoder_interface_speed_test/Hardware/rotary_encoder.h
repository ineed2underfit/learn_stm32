#ifndef __ROTARY_ENCODER_H
#define __ROTARY_ENCODER_H

void rotary_encoder_init(void);  // 初始化 GPIOB14 | GPIO_Pin_15
int16_t get_encoder_irq_count();  // 返回变化值

// 中断函数不需要声明,  因为中断函数不需要调用,  他是自动执行的



#endif

