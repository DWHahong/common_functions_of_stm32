#include "stm32f10x.h"	   //ϵͳ�ļ�������Ҫ����

/************************************************
�������ƣ�void RCC_Configuration(void)
�������ܣ����˿�ʱ�ӳ�ʼ������
��ڲ�������
����ֵ��  ��
˵��  ��  �򿪸�ģ��ʱ��
************************************************/
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//GPIOAʱ�Ӵ�
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//ʹ��USART2��ʱ�� 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
  GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
  USART_InitStructure.USART_BaudRate=9600;    //���ô���ͨ��ʱ�Ĳ�����Ϊ9600
  USART_InitStructure.USART_WordLength=USART_WordLength_8b;  //��������λ����8��λ
  USART_InitStructure.USART_StopBits=USART_StopBits_1;   //��֡��β����1��ֹͣλ
  USART_InitStructure.USART_Parity=USART_Parity_No;   //����У��λ���ޡ�
  //����Ӳ��������ʧ��
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
  USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//���÷��ͺͽ���ʹ��
  
  USART_Init(USART2,&USART_InitStructure);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //�����ж�����
  USART_Cmd(USART2,ENABLE);//����USART2
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //�ж����ȼ�����

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;     //ͨ������Ϊ����1�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //�ж�ռ�ȵȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //�ж���Ӧ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //���ж�
  NVIC_Init(&NVIC_InitStructure);                             //��ʼ��
}


