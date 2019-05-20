#ifndef __NTC_H
#define __NTC_H 			   
#include <stm32f10x.h>

uint8_t CheckTemp(uint16_t VoltVal);
uint16_t LineInter(uint16_t VoltVal);
//float GetTemp(uint16_t VoltVal);
void ADC1_Config(void);
void DMA_Interrupt(void);
void Temp_Process(uint16_t AD_Value1);

void InsertSort(uint16_t* array,uint8_t n);
uint16_t Select(uint16_t* array,uint8_t n,uint8_t k);

#endif

/*
uint8_t NTC_Temp[18] ="NTC Temper: 00.0 C";

int main里面要包含
ADC1_Config();
ADC_SoftwareStartConvCmd(ADC1, ENABLE); //软件启动AD转换，这一句不可少，否则不能启动AD转换

while语句里面要有
Temp_Process(AD_Value1);

*/