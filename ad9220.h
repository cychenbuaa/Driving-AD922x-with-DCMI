#ifndef __AD9220_H
#define __AD9220_H

#include "stm32f4xx.h"
/**************************************************************************
	ʹ�� MCO �����Ϊ AD9220 ��ʱ�� -> PA8
	
	ע��AD9220 ���������
		1. ʱ�ӵ͵�ƽ�ڼ䣬�����ȶ�
		2. ʱ�Ӹߵ�ƽ�ڼ䣬���ݿɱ�
	���ⲿ�ж��ж�ȡ 12-bit ���ݣ�ʹ���½����ж�
**************************************************************************/


void MCO1_GPIO_Config(void);
void ad9220_exit_init(FunctionalState ExitEnable);
void ad9220_data_gpio_init(void);
#endif
