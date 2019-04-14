#ifndef __ADC_H
#define __ADC_H
#include "stdDtype.h"
#include "STC15F2K60S2.h"

//输出引脚定义


uint8_t GetAdcValue(void);
void startAdc(void);
float GetVoltage(float min,float max);
void dacOut(unsigned char dataNum);


#endif