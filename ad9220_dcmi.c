/********************************************************************************
  * @file    ad9220_dcmi.h
  * @author  chunyu
  * @version V1.0
  * @date    2018-05-02
  * @brief   ʹ�� STM32F4 �� DCMI �ӿڽ��� AD9220 ������
  ******************************************************************************
  * @attention
  * ��� STM32F4 �� DCMI �ӿڵĹ��ܣ�ʵ�ֶ�ȡ AD9220 ������
  *******************************************************************************/

#include "ad9220_dcmi.h"

uint32_t adc_convert_value[ADC_DMA_DATA_LENGTH]; //�洢�� DCMI ������������

/**************************************************************************
	ʹ�� MCO �����Ϊ AD9220 ��ʱ�� -> PA8
**************************************************************************/
void MCO1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PA8 ���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
  * @brief  ��ʼ�� DCMI �ӿ�ʹ�õ� GPIO
  * @param  None
  * @retval None
  * @brief  PCLK,HSYNC,VSYNC,D0-D11
  ******************************************************************************/
void dcmi_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ�� DCMI �������ʱ�� */
	RCC_AHB1PeriphClockCmd( DCMI_VSYNC_GPIO_CLK | DCMI_HSYNC_GPIO_CLK | DCMI_PIXCLK_GPIO_CLK|
							DCMI_D0_GPIO_CLK| DCMI_D1_GPIO_CLK| DCMI_D2_GPIO_CLK| DCMI_D3_GPIO_CLK|
							DCMI_D4_GPIO_CLK| DCMI_D5_GPIO_CLK| DCMI_D6_GPIO_CLK| DCMI_D7_GPIO_CLK| 
							DCMI_D8_GPIO_CLK| DCMI_D9_GPIO_CLK| DCMI_D10_GPIO_CLK| DCMI_D11_GPIO_CLK, ENABLE);

	/*��ʼ������/ͬ���ź���*/
	GPIO_InitStructure.GPIO_Pin = DCMI_VSYNC_GPIO_PIN;//��ʼ��֡ͬ���ź���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
	GPIO_Init(DCMI_VSYNC_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_PINSOURCE, DCMI_VSYNC_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_HSYNC_GPIO_PIN ;//��ʼ����ͬ���ź���
	GPIO_Init(DCMI_HSYNC_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_PINSOURCE, DCMI_HSYNC_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_PIXCLK_GPIO_PIN ;//��ʼ������ʱ���ź���
	GPIO_Init(DCMI_PIXCLK_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_PINSOURCE, DCMI_PIXCLK_AF);

	/*��ʼ�������ź���*/
	GPIO_InitStructure.GPIO_Pin = DCMI_D0_GPIO_PIN ;
	GPIO_Init(DCMI_D0_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D0_GPIO_PORT, DCMI_D0_PINSOURCE, DCMI_D0_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D1_GPIO_PIN ;
	GPIO_Init(DCMI_D1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D1_GPIO_PORT, DCMI_D1_PINSOURCE, DCMI_D1_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D2_GPIO_PIN ;
	GPIO_Init(DCMI_D2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D2_GPIO_PORT, DCMI_D2_PINSOURCE, DCMI_D2_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D3_GPIO_PIN ;
	GPIO_Init(DCMI_D3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D3_GPIO_PORT, DCMI_D3_PINSOURCE, DCMI_D3_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D4_GPIO_PIN ;
	GPIO_Init(DCMI_D4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D4_GPIO_PORT, DCMI_D4_PINSOURCE, DCMI_D4_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D5_GPIO_PIN ;
	GPIO_Init(DCMI_D5_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D5_GPIO_PORT, DCMI_D5_PINSOURCE, DCMI_D5_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D6_GPIO_PIN ;
	GPIO_Init(DCMI_D6_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D6_GPIO_PORT, DCMI_D6_PINSOURCE, DCMI_D6_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_D7_GPIO_PIN ;
	GPIO_Init(DCMI_D7_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D7_GPIO_PORT, DCMI_D7_PINSOURCE, DCMI_D7_AF);
	
	GPIO_InitStructure.GPIO_Pin = DCMI_D8_GPIO_PIN ;
	GPIO_Init(DCMI_D8_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D8_GPIO_PORT, DCMI_D8_PINSOURCE, DCMI_D8_AF);
	
	GPIO_InitStructure.GPIO_Pin = DCMI_D9_GPIO_PIN ;
	GPIO_Init(DCMI_D9_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D9_GPIO_PORT, DCMI_D9_PINSOURCE, DCMI_D9_AF);
	
	GPIO_InitStructure.GPIO_Pin = DCMI_D10_GPIO_PIN ;
	GPIO_Init(DCMI_D10_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D10_GPIO_PORT, DCMI_D10_PINSOURCE, DCMI_D10_AF);
	
	GPIO_InitStructure.GPIO_Pin = DCMI_D11_GPIO_PIN ;
	GPIO_Init(DCMI_D11_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_D11_GPIO_PORT, DCMI_D11_PINSOURCE, DCMI_D11_AF);	
}

/*����ͷ�ɼ�ͼ��Ĵ�С���ı�������ֵ���Ըı���������
img_width��imgheightҪ��Ϊ4�ı���
������ӿ�ɼ��ٶȣ�Ҫ�ӿ�ɼ��ٶ���Ҫ�ĳ�SVGAģʽ*/
//uint16_t img_width=852, img_height=480;

/********************************************************************************
  * @brief  ���� DCMI/DMA ���� AD9220 ����
  * @param  None
  * @retval None
  *******************************************************************************/
void ad9220_dcmi_dma_init(void)
{
	DCMI_InitTypeDef DCMI_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;
	
	/*** ����DCMI�ӿ� ***/
	/* ʹ��DCMIʱ�� */
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

	/* DCMI ����*/ 
	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;	//Specifies the Capture Mode: Continuous or Snapshot.
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;	//Ӳ��ͬ��ģʽ��ʹ�� HSYNC/VSYNC �ź�
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;		//AD9220 ����������½����ȶ��������Ҫ������ʱ�ӵ��½��ض�ȡ����
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;			//VSYNC �ߵ�ƽʱ��ͣ�������ݣ���Ҫ����Ӧ���Žӵ�
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;			//HSYNC �ߵ�ƽʱ��ͣ��������
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;	//Specifies the frequency of frame capture: All, 1/2 or 1/4.
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_12b;//��ȡ D0-D11 �� 12-bit ����
	DCMI_Init(&DCMI_InitStructure); 	

	/* ʹ��DMAʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
	DMA_Cmd(DMA2_Stream1,DISABLE); //�ȹر� DMA2 Stream1���ȴ�������ؼĴ���
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}	
	/* DMA2 Stream0 channel_1 configuration **************************************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_1;  						// DCMI��DMA2 Channel_1��
	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;				// DCMI���ݼĴ�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&adc_convert_value;	// DMA�����Ŀ�ĵ�ַ	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// ���ݴ��䷽��Ϊ���赽�洢��
	DMA_InitStructure.DMA_BufferSize =ADC_DMA_DATA_LENGTH; 					// ��������СΪ��ָһ�δ����������
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �洢����ַ����**************
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	// �������ݴ�СΪ�֣����ĸ��ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			// �洢�����ݴ�СҲΪ�֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// ѭ��ģʽ************
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// ��ֹDMA FIFO��ʹ��ֱ��ģʽ
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC8;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA2_Stream1, &DMA_InitStructure);/*DMA��ʼ�� */
		
	/* DMA2_Stream1 enable ���� DMA */
	DMA_Cmd(DMA2_Stream1,ENABLE);
	while(DMA_GetCmdStatus(DMA2_Stream1) != ENABLE){}
	
	/* �����ж� */
	//ע������Ӧʹ��DMA�����жϴ���������DCMI�ж�
 	
}

/********************************************************************************
  * @brief  ������ر�DCMI�ɼ�
  * @param  ENABLE��DISABLE
  *******************************************************************************/
void dcmi_capture_control(FunctionalState state)
{
	DMA_Cmd(DMA2_Stream1, state);	//DMA2,Stream1
	DCMI_Cmd(state); 				//DCMI�ɼ�����
	DCMI_CaptureCmd(state);			//DCMI����
}

/**************************************************************************
	���� DMA �ж�
	DCMI ʹ�� DMA2��������1
**************************************************************************/
void dcmi_dma_nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;		//DMA2 �� 1 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����
	//���� DMA2 stream1 �ж�
	DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE); //DMA_IT_TC����������жϣ�	ENABLE�������ж�
}

/**************************************************************************
	HSYNC �� VSYNC �����ȴ��ڸߵ�ƽ�����ú� DCMI ֮��������͵�ƽ������Ч����
	��ˣ��� IO �ĸߵ͵�ƽģ���Э��
	PE0 -> HSYNC
	PE1 -> VSYNC
**************************************************************************/
void HSYNC_VSYNC_init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

	//GPIOF9,F10��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//LED0��LED1��ӦIO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO

	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1);//GPIOE0,E1���ø�
}
