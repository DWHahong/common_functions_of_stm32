/*****************************************
文件创建时间：  2014年7月11日
文件版本：      V1
最近修改时间： 
作者：          中山火炬职业技术学院电子信息工程专业   杨立宏
说明：          本程序实现采用滴答定时器SysTick实现精确的延时，程序中实现了us和ms的延时
******************************************/
#include <stm32f10x.h>
#include "delay.h"
 
static u8  fac_us=0;  //us延时倍乘数
static u16 fac_ms=0;  //ms延时倍乘数

/*******************************************
函数名称：void delay_init(u8 SYSTICLK)
函数功能：初始化SysTick的时钟源
输入参数：SYSCLK---系统时钟，一般72MHz
返回值：  无
说明：系统时钟一般采用外部晶振倍频得到，一般使用最高频率72MHz，
      由STM32的时钟树可以看出，SysTick的时钟源为系统时钟除以8即9MHz
*******************************************/
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;   //bit2清空,选择外部时钟  HCLK/8
	fac_us=SYSCLK/8; 		    
	fac_ms=(u16)fac_us*1000;
}

								  
/*******************************************
函数名称：void delay_ms(u16 nms)
函数功能：实现ms级延时
输入参数： nms---实现延时的ms数值，即延时时长
返回值： 无
说明：SysTick->LOAD为24位寄存器,所以,最大延时为:nms<=0xffffff*8*1000/SYSCLK
      对72M条件下,nms<=1864
*******************************************/
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}

/*******************************************
函数名称：void delay_ms(u16 nms)
函数功能：实现ms级延时
输入参数： nms---实现延时的ms数值，即延时时长
返回值： 无
说明：
*******************************************/   		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
