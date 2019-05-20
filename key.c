#include "stm32f10x.h"
#include "key.h"

void KeyInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);	//GPIOEʱ�Ӵ�
	
	//KEY2---PA1, KEY3---PA0
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  //�������
   GPIO_Init(GPIOE,&GPIO_InitStructure);
	
 //KEY1---PC13
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //�������
   GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}




