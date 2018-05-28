/**************************************************************************
	ʹ�� MCO �����Ϊ AD9220 ��ʱ�� -> PA8
	
	ע��AD9220 ���������
		1. ʱ�ӵ͵�ƽ�ڼ䣬�����ȶ�
		2. ʱ�Ӹߵ�ƽ�ڼ䣬���ݿɱ�
	���ⲿ�ж��ж�ȡ 12-bit ���ݣ�ʹ���½����ж�
**************************************************************************/
#include "ad9220.h"

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

/**************************************************************************
	�ⲿ�жϳ�ʼ�� PA0
**************************************************************************/
void ad9220_exit_init(FunctionalState ExitEnable)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//��ʼ�� PA0 ��Ϊ�ⲿ�ж�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0

	/* ����EXTI_Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
	EXTI_Init(&EXTI_InitStructure);//����

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ExitEnable;//���������β�ȷ���Ƿ�ʹ���ⲿ�ж�
	NVIC_Init(&NVIC_InitStructure);//����
}

/**************************************************************************
	��ʼ������ AD9220 ���ݵ� IO �ڣ�ʹ�� PC0~PC11
**************************************************************************/
void ad9220_data_gpio_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	
}

