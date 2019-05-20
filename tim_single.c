#include "stm32f10x.h"
#include "tim_single.h"

/************************************************
函数名称：void RCC_Config(void)
函数功能：对用到的时钟进行初始化，打开各模块时钟
入口参数：无
返回值：  无
说明  ：  主要是打开GPIOF和TIM3的时钟
************************************************/
void TIM_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//GPIOF时钟打开
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//TIM3时钟打开
	
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//输出50MHz
   GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/************************************************
函数名称：void TIM_Init(void)
函数功能：对TIM3进行初始化
入口参数：无
返回值：  无
说明  ：  周期和分频比决定了定时长短，修改这两个值可修改定时时长
************************************************/
void TIM_Init(uint16_t arr,uint16_t duty)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
  TIM_DeInit(TIM3);
  TIM_TimeBaseStructure.TIM_Period= arr-1;	//自动重装载寄存器的值
  TIM_TimeBaseStructure.TIM_Prescaler= 1;//时钟预分频数
  TIM_TimeBaseStructure.TIM_ClockDivision=0x0;//采样分频
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
  TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//TIM的PWM1模式
  TIM_OCInitStructure.TIM_OutputState= TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse=duty;//设置占空比
  TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//TIM输出比较极性高

  TIM_OC4Init(TIM3,&TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能定时器TIM3在CCR3上的预装载寄存器
  TIM_ARRPreloadConfig(TIM3,ENABLE);//使能定时器TIM3在ARR上的预装载寄存器
  TIM_Cmd(TIM3,ENABLE);//使能定时器3

}

