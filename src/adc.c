#include "adc.h"
#include "stdDtype.h"
#include "delay.h"
#include "HD7279.h"
unsigned char xdata DAC0832 _at_ 0xFD00;
unsigned char xdata ADC0804 _at_ 0xFE00;

void startAdc(void)
{
	ADC0804 = 0x00;
}


//获得ADC值
uint8_t GetAdcValue(void)
{
	uint8_t adcvalue = 0;
	adcvalue = ADC0804;
	
	return adcvalue;
}

//ADC缩放
float GetVoltage(float min,float max)
{
	uint8_t adcvalue = GetAdcValue();
	float vol = (max - min)/255.0f*adcvalue + min;
	return vol;
}

//DAC输出
void dacOut(unsigned char dataNum)
{
	DAC0832 = dataNum;
}
