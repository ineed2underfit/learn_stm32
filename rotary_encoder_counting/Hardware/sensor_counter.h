#ifndef __SENSOR_COUNTER_H
#define __SENSOR_COUNTER_H

void sensor_count_init(void);  // 初始化
uint16_t get_irq_count(void);  // 获取中断触发次数

// 中断函数不需要声明,  因为中断函数不需要调用,  他是自动执行的


#endif
