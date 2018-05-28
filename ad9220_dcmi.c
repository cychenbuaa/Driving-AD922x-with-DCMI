/********************************************************************************
  * @file    ad9220_dcmi.h
  * @author  chunyu
  * @version V1.0
  * @date    2018-05-02
  * @brief   使用 STM32F4 的 DCMI 接口接收 AD9220 的数据
  ******************************************************************************
  * @attention
  * 理解 STM32F4 的 DCMI 接口的功能，实现读取 AD9220 的数据
  *******************************************************************************/

#include "ad9220_dcmi.h"

uint32_t adc_convert_value[ADC_DMA_DATA_LENGTH]; //存储从 DCMI 接收来的数据

/**************************************************************************
	使用 MCO 输出作为 AD9220 的时钟 -> PA8
**************************************************************************/
void MCO1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PA8 输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
  * @brief  初始化 DCMI 接口使用的 GPIO
  * @param  None
  * @retval None
  * @brief  PCLK,HSYNC,VSYNC,D0-D11
  ******************************************************************************/
void dcmi_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能 DCMI 相关引脚时钟 */
	RCC_AHB1PeriphClockCmd( DCMI_VSYNC_GPIO_CLK | DCMI_HSYNC_GPIO_CLK | DCMI_PIXCLK_GPIO_CLK|
							DCMI_D0_GPIO_CLK| DCMI_D1_GPIO_CLK| DCMI_D2_GPIO_CLK| DCMI_D3_GPIO_CLK|
							DCMI_D4_GPIO_CLK| DCMI_D5_GPIO_CLK| DCMI_D6_GPIO_CLK| DCMI_D7_GPIO_CLK| 
							DCMI_D8_GPIO_CLK| DCMI_D9_GPIO_CLK| DCMI_D10_GPIO_CLK| DCMI_D11_GPIO_CLK, ENABLE);

	/*初始化控制/同步信号线*/
	GPIO_InitStructure.GPIO_Pin = DCMI_VSYNC_GPIO_PIN;//初始化帧同步信号线
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
	GPIO_Init(DCMI_VSYNC_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_PINSOURCE, DCMI_VSYNC_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_HSYNC_GPIO_PIN ;//初始化行同步信号线
	GPIO_Init(DCMI_HSYNC_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_PINSOURCE, DCMI_HSYNC_AF);

	GPIO_InitStructure.GPIO_Pin = DCMI_PIXCLK_GPIO_PIN ;//初始化像素时钟信号线
	GPIO_Init(DCMI_PIXCLK_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_PINSOURCE, DCMI_PIXCLK_AF);

	/*初始化数据信号线*/
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

/*摄像头采集图像的大小，改变这两个值可以改变数据量，
img_width和imgheight要求为4的倍数
但不会加快采集速度，要加快采集速度需要改成SVGA模式*/
//uint16_t img_width=852, img_height=480;

/********************************************************************************
  * @brief  配置 DCMI/DMA 接收 AD9220 数据
  * @param  None
  * @retval None
  *******************************************************************************/
void ad9220_dcmi_dma_init(void)
{
	DCMI_InitTypeDef DCMI_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;
	
	/*** 配置DCMI接口 ***/
	/* 使能DCMI时钟 */
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

	/* DCMI 配置*/ 
	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;	//Specifies the Capture Mode: Continuous or Snapshot.
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;	//硬件同步模式，使用 HSYNC/VSYNC 信号
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;		//AD9220 数据输出在下降沿稳定，因此需要在像素时钟的下降沿读取数据
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;			//VSYNC 高电平时暂停传输数据，需要将对应引脚接地
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;			//HSYNC 高电平时暂停传输数据
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;	//Specifies the frequency of frame capture: All, 1/2 or 1/4.
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_12b;//获取 D0-D11 的 12-bit 数据
	DCMI_Init(&DCMI_InitStructure); 	

	/* 使能DMA时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
	DMA_Cmd(DMA2_Stream1,DISABLE); //先关闭 DMA2 Stream1，等待配置相关寄存器
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}	
	/* DMA2 Stream0 channel_1 configuration **************************************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_1;  						// DCMI在DMA2 Channel_1中
	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;				// DCMI数据寄存器地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&adc_convert_value;	// DMA传输的目的地址	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// 数据传输方向为外设到存储器
	DMA_InitStructure.DMA_BufferSize =ADC_DMA_DATA_LENGTH; 					// 缓冲区大小为，指一次传输的数据量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 存储器地址递增**************
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	// 外设数据大小为字，即四个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			// 存储器数据大小也为字，跟外设数据大小相同
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// 循环模式************
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// 禁止DMA FIFO，使用直连模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC8;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA2_Stream1, &DMA_InitStructure);/*DMA初始化 */
		
	/* DMA2_Stream1 enable 开启 DMA */
	DMA_Cmd(DMA2_Stream1,ENABLE);
	while(DMA_GetCmdStatus(DMA2_Stream1) != ENABLE){}
	
	/* 配置中断 */
	//注：这里应使用DMA来做中断触发，不用DCMI中断
 	
}

/********************************************************************************
  * @brief  开启或关闭DCMI采集
  * @param  ENABLE或DISABLE
  *******************************************************************************/
void dcmi_capture_control(FunctionalState state)
{
	DMA_Cmd(DMA2_Stream1, state);	//DMA2,Stream1
	DCMI_Cmd(state); 				//DCMI采集数据
	DCMI_CaptureCmd(state);			//DCMI捕获
}

/**************************************************************************
	配置 DMA 中断
	DCMI 使用 DMA2，数据流1
**************************************************************************/
void dcmi_dma_nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;		//DMA2 流 1 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
	//配置 DMA2 stream1 中断
	DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE); //DMA_IT_TC：传输完成中断；	ENABLE：允许中断
}

/**************************************************************************
	HSYNC 和 VSYNC 必须先处于高电平，配置好 DCMI 之后在输入低电平才能有效工作
	因此，用 IO 的高低电平模拟该协议
	PE0 -> HSYNC
	PE1 -> VSYNC
**************************************************************************/
void HSYNC_VSYNC_init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO

	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1);//GPIOE0,E1设置高
}
