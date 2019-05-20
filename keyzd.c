#include "stm32f10x.h"
#include "keyzd.h"

void KeyInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef  EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
   //时钟配置
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);	//GPIOE时钟打开,注意AFIO一定要打开
	
	//端口配置
	//KEY2---PA1, KEY3---PA0
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  //推挽输出
   GPIO_Init(GPIOA,&GPIO_InitStructure);         //没有配置速度 那么速度是50Mhz吗
	
	
	
	
	
	
 //KEY1---PC13
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //推挽输出
   GPIO_Init(GPIOC,&GPIO_InitStructure);


  //外部中断配置//如果没有打开中断会怎样 中断是什么意思 中断请求是什么意思
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //打开PA0中断连接
   EXTI_ClearITPendingBit(EXTI_Line0);	          //清除中断标志
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); //打开PA1中断连接
   EXTI_ClearITPendingBit(EXTI_Line1);	          //清除中断标志
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13); //打开PC13中断连接
   EXTI_ClearITPendingBit(EXTI_Line13);	          //清除中断标志

   EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1|EXTI_Line13;		  //选择中断线0,1,13
   EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;   //设置为中断请求
   EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;   //下降沿触发
   EXTI_InitStructure.EXTI_LineCmd=ENABLE;			      //使能中断线
   EXTI_Init(&EXTI_InitStructure);	

   //中断优先级配置
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //中断优先级分组
		 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键USER1所在的外部中断通道
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级1， 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure); 
	 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键USER1所在的外部中断通道
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级1， 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure); 
	 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键USER1所在的外部中断通道
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级1， 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure); 
}




