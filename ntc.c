#include "stm32f10x.h"
#include "ntc.h"
//#include "stm32f10x_adc.h"
//#include "stm32f10x_dma.h"

#define ADC1_DR_Address ((uint32_t)0x4001244C)   //ADC���ݴ洢��ַ
#define CHANNEL   1    //ͨ����
#define CNT       10    //ת������
//#define DELETECNT 10   //ɾ����� ���Ԫ�ظ���

uint16_t ADC_ConvertedValue[CHANNEL*CNT];   //ת�������ݴ�ŵ�ַ
uint16_t AD_CH1[CNT];    //��1ͨ�����ݴ洢
uint16_t AD_Value1 = 0;	     //��1ͨ��������ADֵ
float ADC_Voltage = 0;   //��1ͨ����ѹֵ

extern uint8_t NTC_Temp[18];

	

//http://www.embedu.org/Column/Column379.htm
//MF52-10K-3950,Dadc= 4096*Rm/(Rm+RT);  RmΪ��ѹ���裬RTΪ��������
//��0��---100��,������
uint16_t NTCTAB[101] =    //0~100��
{
	959,997,1036,1075,1115,1156,1198,1240,1283,1326,         //0~9
	1370,1414,1459,1504,1549,1594,1639,1686,1731,1776,       //10~19
	1822,1868,1913,1958,2003,2048,2093,2137,2182,2225,      //20~29
	2269,2312,2354,2396,2438,2479,2519,2559,2598,2636,       //30~39
	2674,2711,2748,2784,2819,2853,2887,2920,2952,2983,      //40~49
	3014,3045,3074,3103,3131,3158,3185,3211,3236,3261,      //50~59
	3284,3307,3330,3352,3373,3394,3414,3434,3452,3471,      //60~69
	3489,3506,3523,3538,3554,3569,3584,3598,3612,3625,      //70~79
	3639,3651,3663,3675,3687,3698,3709,3720,3730,3740,      //80~89
	3750,3759,3768,3777,3786,3794,3802,3810,3818,3825,3833      //90~100
};

//���ֲ��
//���ַ���������¶�ֵ���ڵ�λ��
//VoltVal�������õ��ĵ�ѹ������
//���ַ����ע���·NTC��������λ�����Ϻ��£������Ҫ�޸�
uint8_t CheckTemp(uint16_t VoltVal)
{  
    uint8_t TempMin = 0;     //
    uint8_t TempMax = 100;   //
    uint8_t MidVal = 0;     //
	if(VoltVal >= NTCTAB[TempMax]) //
		 return TempMax ; 
	else if(VoltVal <= NTCTAB[TempMin]) //
	   return  TempMin ;
	while(VoltVal<=NTCTAB[TempMax])  //
	{
		MidVal = (TempMax+TempMin)/2;  //
		if((MidVal == TempMin)||(MidVal == TempMax))  //
		{
			break;
		}
//		if(VoltVal == NTCTAB[MidVal])
//		{
//			break;
//		}
		if(VoltVal< NTCTAB[MidVal])   //
		{
			TempMax = MidVal;  //
		}
		else
		{
			TempMin = MidVal;   //
		}
	}
//	printf("%d    ",MidVal);
	return MidVal;
}


//���Բ�ֵ��õ�ǰ��ѹ��������Ӧ���¶�
//�¶�x=(y-y1)(x2-x1)/(y2-y1)+x1 
//X2-X1=1
//x=(y-y1)/(y2-y1)+x1
//y--VoltVal,y1--NTCTAB[TemperInt],y2--NTCTAB[TemperInt+1],x1--TemperInt
//����ֵΪ�¶�ʵ��ֵ��10��
uint16_t LineInter(uint16_t VoltVal)
{
	uint16_t Temperature =0;     //�����¶ȵ�10��
	uint8_t TemperInt = 0;      //���ַ������õ����¶�����ֵ
	float temp1 = 0,temp2 = 0,temp3 = 0,temp4 = 0;   //�ݴ����
	TemperInt = CheckTemp(VoltVal);       //���ַ���ȡ�¶�����
	temp3 = (VoltVal-NTCTAB[TemperInt]);  //�����ֵ��y-y1
	temp4 = NTCTAB[TemperInt+1]-NTCTAB[TemperInt];   //�����ֵ��y2-y1
	temp2 = temp3/temp4;       //�����ֵ��(y-y1)/(y2-y1)
	temp1 = temp2 +TemperInt;  //�����ֵ����¶�ֵ
	Temperature = (uint16_t)(temp1*10);  //��С������10����Ϊ���������㴦��
	return Temperature;
}
 
/*******************************************
                   ADC��ʼ��
********************************************/
void ADC1_Config(void)
{
	
   GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;
	 DMA_InitTypeDef DMA_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE); 	
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;	  //PC1  I_REF
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
   GPIO_Init(GPIOC,&GPIO_InitStructure); 	

	
   ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
   ADC_InitStructure.ADC_ScanConvMode=DISABLE;
   ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
   ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
   ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfChannel=1;

   ADC_Init(ADC1,&ADC_InitStructure);	
	
	 ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_55Cycles5);	  //IGBT_TEMP
   ADC_DMACmd(ADC1,ENABLE);	  
   ADC_Cmd(ADC1,ENABLE);	  
   ADC_ResetCalibration(ADC1);  
   while(ADC_GetResetCalibrationStatus(ADC1));  
   ADC_StartCalibration(ADC1); 
   while(ADC_GetCalibrationStatus(ADC1));	 
	 
   DMA_DeInit(DMA1_Channel1);
   DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address;
   DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_ConvertedValue;
   DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
   DMA_InitStructure.DMA_BufferSize=CHANNEL*CNT;
   DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
   DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
   DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority=DMA_Priority_High;
   DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;

   DMA_Init(DMA1_Channel1,&DMA_InitStructure);

   DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);	  
   DMA_Cmd(DMA1_Channel1,ENABLE);   
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	 
}


void DMA_Interrupt(void)
{
  uint16_t i;
	uint32_t sum1=0;
 if(DMA_GetITStatus(DMA1_IT_TC1)) 
  {
   // DMA_ClearFlag(DMA1_FLAG_TC1);
    DMA_ClearITPendingBit(DMA1_IT_GL1);
	for(i=0;i<CNT;i++)
		{
		  AD_CH1[i]=ADC_ConvertedValue[i];
		}
	 for(i=0;i<CNT;i++)
  {
    sum1=sum1+AD_CH1[i];
  }
  AD_Value1=sum1/CNT;	

//	InsertSort(AD_CH1,CNT);
//  AD_Value1 = Select(AD_CH1,CNT,DELETECNT);	
//	InsertSort(AD_CH2,CNT);
//  AD_Value2 = Select(AD_CH2,CNT,DELETECNT);
//	InsertSort(AD_CH3,CNT);
//  AD_Value3 = Select(AD_CH3,CNT,DELETECNT);
//	InsertSort(AD_CH4,CNT);
//  AD_Value4 = Select(AD_CH4,CNT,DELETECNT);		
	
  }
}


void Temp_Process(uint16_t AD_Value1)
{
  uint16_t temperature = 0;
//	temperature =  CheckTemp(AD_Value1);    //���ַ��õ��¶�
	temperature = LineInter(AD_Value1);
	NTC_Temp[12] = temperature/100+48;	
	NTC_Temp[13] = temperature/10%10+48;
	NTC_Temp[15] = temperature%10+48;
}

//arrayҪ��������飬nΪ���鳤��
void InsertSort(uint16_t* array,uint8_t n)
{
    uint8_t i, j;
    uint16_t target = 0;
    for (i = 1; i < n; i++)
    {
        j = i;
        target = array[i];
        while (j > 0 && target < array[j - 1])
        {
            array[j] = array[j - 1];
            j--;
        }
 
        array[j] = target;
    }
}

//array�Ѿ��źõ�����nnΪ������Ԫ�ظ�����kҪȥ����ǰ����ֵ�ĸ���
uint16_t Select(uint16_t* array,uint8_t n,uint8_t k)  
{
	uint32_t  sum = 0;
	uint16_t AverageValue;
	uint8_t  i;
	for(i=k;i<n-k;i++)
	{
		sum = sum + array[i];
	}
	AverageValue = sum/(n-2*k);
	return AverageValue;
}
