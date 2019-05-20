#include "stm32f10x.h"
#include "keyzd.h"

void KeyInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef  EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
   //ʱ������
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);	//GPIOEʱ�Ӵ�,ע��AFIOһ��Ҫ��
	
	//�˿�����
	//KEY2---PA1, KEY3---PA0
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  //�������
   GPIO_Init(GPIOA,&GPIO_InitStructure);         //û�������ٶ� ��ô�ٶ���50Mhz��
	
	
	
	
	
	
 //KEY1---PC13
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //�������
   GPIO_Init(GPIOC,&GPIO_InitStructure);


  //�ⲿ�ж�����//���û�д��жϻ����� �ж���ʲô��˼ �ж�������ʲô��˼
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //��PA0�ж�����
   EXTI_ClearITPendingBit(EXTI_Line0);	          //����жϱ�־
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); //��PA1�ж�����
   EXTI_ClearITPendingBit(EXTI_Line1);	          //����жϱ�־
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13); //��PC13�ж�����
   EXTI_ClearITPendingBit(EXTI_Line13);	          //����жϱ�־

   EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1|EXTI_Line13;		  //ѡ���ж���0,1,13
   EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;   //����Ϊ�ж�����
   EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;   //�½��ش���
   EXTI_InitStructure.EXTI_LineCmd=ENABLE;			      //ʹ���ж���
   EXTI_Init(&EXTI_InitStructure);	

   //�ж����ȼ�����
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //�ж����ȼ�����
		 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���USER1���ڵ��ⲿ�ж�ͨ��
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�1�� 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure); 
	 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���USER1���ڵ��ⲿ�ж�ͨ��
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1�� 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure); 
	 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���USER1���ڵ��ⲿ�ж�ͨ��
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�1�� 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure); 
}




