#ifndef __KEYZD_H
#define __KEYZD_H 	

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)   //PC13//为什么要读取指定管脚的输入
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)    //PA1
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)    //PA0


void KeyInit(void);

#endif

