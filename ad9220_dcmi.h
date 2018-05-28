#ifndef __AD9220_DCMI_H
#define	__AD9220_DCMI_H
/**
  ******************************************************************************
  * @file    ad9220_dcmi.c
  * @author  chunyu
  * @version V1.0
  * @date    2018-05-02
  * @brief   ʹ�� STM32F4 �� DCMI �ӿڽ��� AD9220 ������
  ******************************************************************************
  * @attention
  * ��� STM32F4 �� DCMI �ӿڵĹ��ܣ�ʵ�ֶ�ȡ AD9220 ������
  *   
  ******************************************************************************
  */
#include "stm32f4xx.h"

#define DCMI_DR_ADDRESS       (uint32_t)&DCMI->DR //�궨�� DCMI ���ݼĴ����ĵ�ַ
/**************************************************************************
	�궨�壺DCMI ͨ�� DMA һ�����ڴ�д������鳤��
	ע��  ������DMA����������� 32bit ���ݣ����� 16bit �͵� 16bit �ֱ������β����Ľ��
	����  ��ʵ�ʵĲ��������Ǹ����鳤�ȵ�����
**************************************************************************/
#define ADC_DMA_DATA_LENGTH 200

//DMCI �ӿ���� IO �궨��
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

//�����ź��� D0-D11
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

void MCO1_GPIO_Config(void);//���� MCO1 ���
void dcmi_gpio_init(void);//��ʼ�� DCMI �ӿ�ʹ�õ� GPIO
void ad9220_dcmi_dma_init(void);//���� DCMI/DMA ���� AD9220 ����
void dcmi_capture_control(FunctionalState state);//������ر�DCMI�ɼ�
void dcmi_dma_nvic_init(void);//���� DMA �ж�
void HSYNC_VSYNC_init(void);

#endif /* __AD9220_DCMI_H */

