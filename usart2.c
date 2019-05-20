#include "stm32f10x.h"	   //系统文件，必须要包含

/************************************************
函数名称：void RCC_Configuration(void)
函数功能：各端口时钟初始化配置
入口参数：无
返回值：  无
说明  ：  打开各模块时钟
************************************************/
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//GPIOA时钟打开
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART2的时钟 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
  GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
  USART_InitStructure.USART_BaudRate=9600;    //设置串口通信时的波特率为9600
  USART_InitStructure.USART_WordLength=USART_WordLength_8b;  //设置数据位长度8个位
  USART_InitStructure.USART_StopBits=USART_StopBits_1;   //在帧结尾传输1个停止位
  USART_InitStructure.USART_Parity=USART_Parity_No;   //设置校验位“无”
  //设置硬件控制流失能
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
  USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//设置发送和接收使能
  
  USART_Init(USART2,&USART_InitStructure);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //接收中断允许
  USART_Cmd(USART2,ENABLE);//开启USART2
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //中断优先级分组

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;     //通道设置为串口1中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //中断占先等级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //中断响应优先级0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //打开中断
  NVIC_Init(&NVIC_InitStructure);                             //初始化
}


