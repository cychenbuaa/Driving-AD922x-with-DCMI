#ifndef __AD9220_DCMI_H
#define	__AD9220_DCMI_H
/**
  ******************************************************************************
  * @file    ad9220_dcmi.c
  * @author  chunyu
  * @version V1.0
  * @date    2018-05-02
  * @brief   使用 STM32F4 的 DCMI 接口接收 AD9220 的数据
  ******************************************************************************
  * @attention
  * 理解 STM32F4 的 DCMI 接口的功能，实现读取 AD9220 的数据
  *   
  ******************************************************************************
  */
#include "stm32f4xx.h"

#define DCMI_DR_ADDRESS       (uint32_t)&DCMI->DR //宏定义 DCMI 数据寄存器的地址
/**************************************************************************
	宏定义：DCMI 通过 DMA 一次向内存写入的数组长度
	注意  ：由于DMA传输过来的是 32bit 数据，即高 16bit 和低 16bit 分别是两次采样的结果
	所以  ：实际的采样数量是该数组长度的两倍
**************************************************************************/
#define ADC_DMA_DATA_LENGTH 200

//DMCI 接口相关 IO 宏定义
//VSYNC
#define DCMI_VSYNC_GPIO_PORT        	GPIOB
#define DCMI_VSYNC_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define DCMI_VSYNC_GPIO_PIN         	GPIO_Pin_7
#define DCMI_VSYNC_PINSOURCE        	GPIO_PinSource7
#define DCMI_VSYNC_AF			          GPIO_AF_DCMI
//HSYNC
#define DCMI_HSYNC_GPIO_PORT        	GPIOA
#define DCMI_HSYNC_GPIO_CLK         	RCC_AHB1Periph_GPIOA
#define DCMI_HSYNC_GPIO_PIN         	GPIO_Pin_4
#define DCMI_HSYNC_PINSOURCE        	GPIO_PinSource4
#define DCMI_HSYNC_AF			          GPIO_AF_DCMI
//PIXCLK
#define DCMI_PIXCLK_GPIO_PORT        	GPIOA
#define DCMI_PIXCLK_GPIO_CLK         	RCC_AHB1Periph_GPIOA
#define DCMI_PIXCLK_GPIO_PIN         	GPIO_Pin_6
#define DCMI_PIXCLK_PINSOURCE        	GPIO_PinSource6
#define DCMI_PIXCLK_AF			          GPIO_AF_DCMI

//数据信号线 D0-D11
#define DCMI_D0_GPIO_PORT        	GPIOC
#define DCMI_D0_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define DCMI_D0_GPIO_PIN         	GPIO_Pin_6
#define DCMI_D0_PINSOURCE        	GPIO_PinSource6
#define DCMI_D0_AF			        GPIO_AF_DCMI

#define DCMI_D1_GPIO_PORT        	GPIOC
#define DCMI_D1_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define DCMI_D1_GPIO_PIN         	GPIO_Pin_7
#define DCMI_D1_PINSOURCE        	GPIO_PinSource7
#define DCMI_D1_AF			        GPIO_AF_DCMI

#define DCMI_D2_GPIO_PORT        	GPIOC
#define DCMI_D2_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define DCMI_D2_GPIO_PIN         	GPIO_Pin_8
#define DCMI_D2_PINSOURCE        	GPIO_PinSource8
#define DCMI_D2_AF			        GPIO_AF_DCMI

#define DCMI_D3_GPIO_PORT        	GPIOC
#define DCMI_D3_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define DCMI_D3_GPIO_PIN         	GPIO_Pin_9
#define DCMI_D3_PINSOURCE        	GPIO_PinSource9
#define DCMI_D3_AF			        GPIO_AF_DCMI

#define DCMI_D4_GPIO_PORT        	GPIOE
#define DCMI_D4_GPIO_CLK         	RCC_AHB1Periph_GPIOE
#define DCMI_D4_GPIO_PIN         	GPIO_Pin_4
#define DCMI_D4_PINSOURCE        	GPIO_PinSource4
#define DCMI_D4_AF			        GPIO_AF_DCMI

#define DCMI_D5_GPIO_PORT        	GPIOB
#define DCMI_D5_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define DCMI_D5_GPIO_PIN         	GPIO_Pin_6
#define DCMI_D5_PINSOURCE        	GPIO_PinSource6
#define DCMI_D5_AF			        GPIO_AF_DCMI

#define DCMI_D6_GPIO_PORT        	GPIOE
#define DCMI_D6_GPIO_CLK         	RCC_AHB1Periph_GPIOE
#define DCMI_D6_GPIO_PIN         	GPIO_Pin_5
#define DCMI_D6_PINSOURCE        	GPIO_PinSource5
#define DCMI_D6_AF			        GPIO_AF_DCMI

#define DCMI_D7_GPIO_PORT        	GPIOE
#define DCMI_D7_GPIO_CLK         	RCC_AHB1Periph_GPIOE
#define DCMI_D7_GPIO_PIN         	GPIO_Pin_6
#define DCMI_D7_PINSOURCE        	GPIO_PinSource6
#define DCMI_D7_AF			        GPIO_AF_DCMI

#define DCMI_D8_GPIO_PORT        	GPIOC
#define DCMI_D8_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define DCMI_D8_GPIO_PIN         	GPIO_Pin_10
#define DCMI_D8_PINSOURCE        	GPIO_PinSource10
#define DCMI_D8_AF			        GPIO_AF_DCMI

#define DCMI_D9_GPIO_PORT        	GPIOC
#define DCMI_D9_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define DCMI_D9_GPIO_PIN         	GPIO_Pin_12
#define DCMI_D9_PINSOURCE        	GPIO_PinSource12
#define DCMI_D9_AF			        GPIO_AF_DCMI

#define DCMI_D10_GPIO_PORT        	GPIOB
#define DCMI_D10_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define DCMI_D10_GPIO_PIN         	GPIO_Pin_5
#define DCMI_D10_PINSOURCE        	GPIO_PinSource5
#define DCMI_D10_AF			        GPIO_AF_DCMI

#define DCMI_D11_GPIO_PORT        	GPIOD
#define DCMI_D11_GPIO_CLK         	RCC_AHB1Periph_GPIOD
#define DCMI_D11_GPIO_PIN         	GPIO_Pin_2
#define DCMI_D11_PINSOURCE        	GPIO_PinSource2
#define DCMI_D11_AF			        GPIO_AF_DCMI

void MCO1_GPIO_Config(void);//配置 MCO1 输出
void dcmi_gpio_init(void);//初始化 DCMI 接口使用的 GPIO
void ad9220_dcmi_dma_init(void);//配置 DCMI/DMA 接收 AD9220 数据
void dcmi_capture_control(FunctionalState state);//开启或关闭DCMI采集
void dcmi_dma_nvic_init(void);//配置 DMA 中断
void HSYNC_VSYNC_init(void);

#endif /* __AD9220_DCMI_H */

