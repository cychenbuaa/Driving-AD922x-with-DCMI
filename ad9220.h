#ifndef __AD9220_H
#define __AD9220_H

#include "stm32f4xx.h"
/**************************************************************************
	使用 MCO 输出作为 AD9220 的时钟 -> PA8
	
	注：AD9220 的数据输出
		1. 时钟低电平期间，数据稳定
		2. 时钟高电平期间，数据可变
	在外部中断中读取 12-bit 数据，使用下降沿中断
**************************************************************************/


void MCO1_GPIO_Config(void);
void ad9220_exit_init(FunctionalState ExitEnable);
void ad9220_data_gpio_init(void);
#endif
