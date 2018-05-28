/**************************************************************************
	@file   main.c
	@author chunyu
	@date   2018.4.15 
	@brief  ��� DME �����źŵĲ���
	
	ע����Ŀ��ϸ���ĵ��ο� README.txt
**************************************************************************/
#include "stm32f4xx.h"
#include "ad9220_dcmi.h"

// ����ԭ�ӱ�д�ĺ�����������ʵ����ԣ����ں���ʹ�ã�����Ȩ��
#include "sys.h"
#include "delay.h"
#include "usart.h"

extern uint32_t adc_convert_value[ADC_DMA_DATA_LENGTH]; //�洢�� DCMI ������������
	
int main()
{
	MCO1_GPIO_Config();//���� PA8 Ϊ���ģʽ
	RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);//PA8 ��� 8M ʱ���ź�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	
	
	HSYNC_VSYNC_init();		//���� HSYNC �� VSYNC
	dcmi_gpio_init();		//��ʼ�� DCMI �ӿ�ʹ�õ� GPIO
	ad9220_dcmi_dma_init();	//���� DCMI/DMA ���� AD9220 ����
	dcmi_dma_nvic_init();	//���� DMA �ж�
	
	delay_init(168);        //����ʹ�ø�����ʱ���� delay_us(); delay_ms();
	uart_init(115200);	    //����1,  PA9,PA10  ���ڲ���������Ϊ 115200 ��ʹ�ô����ж�
	
	dcmi_capture_control(ENABLE);//����DCMI�ɼ�
	GPIO_ResetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1);//�� HSYNC �� VSYNC ���ͣ���ʼ�ɼ�
	while(1)
	{

//		printf("angry\r\n");
//		delay_ms(1000);
		
	}
}

/**************************************************************************
	DMA �жϴ�����
	ADC1 ʹ�� DMA2��������1,����жϴ�����Ϊ DMA2_Stream1_IRQHandler()
**************************************************************************/
void DMA2_Stream1_IRQHandler(void)
{
	uint16_t counter;

	dcmi_capture_control(DISABLE);//�ر�DCMI�ɼ�
	for(counter = 0; counter < ADC_DMA_DATA_LENGTH; counter++)
	{
//		printf("%u\r\n",adc_convert_value[counter]);//���ڴ�ӡ����
		printf("%u\r\n",(uint16_t)adc_convert_value[counter]);
		printf("%u\r\n",(uint16_t)(adc_convert_value[counter] >> 16));//���ڴ�ӡ����
	}
	
	DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1); //����жϱ�־λ TCIF:DMA �������
}







