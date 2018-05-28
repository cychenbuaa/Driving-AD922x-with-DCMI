/**************************************************************************
	@file   main.c
	@author chunyu
	@date   2018.4.15 
	@brief  完成 DME 脉冲信号的采样
	
	注：项目详细的文档参考 README.txt
**************************************************************************/
#include "stm32f4xx.h"
#include "ad9220_dcmi.h"

// 正点原子编写的函数（仅用于实验测试，属于合理使用，不侵权）
#include "sys.h"
#include "delay.h"
#include "usart.h"

extern uint32_t adc_convert_value[ADC_DMA_DATA_LENGTH]; //存储从 DCMI 接收来的数据
	
int main()
{
	MCO1_GPIO_Config();//配置 PA8 为输出模式
	RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);//PA8 输出 8M 时钟信号
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2:2位抢占优先级，2位响应优先级	
	
	HSYNC_VSYNC_init();		//拉高 HSYNC 和 VSYNC
	dcmi_gpio_init();		//初始化 DCMI 接口使用的 GPIO
	ad9220_dcmi_dma_init();	//配置 DCMI/DMA 接收 AD9220 数据
	dcmi_dma_nvic_init();	//配置 DMA 中断
	
	delay_init(168);        //方便使用各个延时函数 delay_us(); delay_ms();
	uart_init(115200);	    //串口1,  PA9,PA10  串口波特率设置为 115200 不使用串口中断
	
	dcmi_capture_control(ENABLE);//开启DCMI采集
	GPIO_ResetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1);//将 HSYNC 和 VSYNC 拉低，开始采集
	while(1)
	{

//		printf("angry\r\n");
//		delay_ms(1000);
		
	}
}

/**************************************************************************
	DMA 中断处理函数
	ADC1 使用 DMA2，数据流1,因此中断处理函数为 DMA2_Stream1_IRQHandler()
**************************************************************************/
void DMA2_Stream1_IRQHandler(void)
{
	uint16_t counter;

	dcmi_capture_control(DISABLE);//关闭DCMI采集
	for(counter = 0; counter < ADC_DMA_DATA_LENGTH; counter++)
	{
//		printf("%u\r\n",adc_convert_value[counter]);//串口打印数据
		printf("%u\r\n",(uint16_t)adc_convert_value[counter]);
		printf("%u\r\n",(uint16_t)(adc_convert_value[counter] >> 16));//串口打印数据
	}
	
	DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1); //清除中断标志位 TCIF:DMA 传输完成
}







