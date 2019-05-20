#include "stm32f10x.h"
#include "beep.h"

void LedInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	//GPIOEʱ�Ӵ�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_2);
}
