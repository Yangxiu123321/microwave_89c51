
/************************delay.c******************************/
#include "delay.h"
#include "intrins.h"
#include "stdDtype.h"

//毫秒延时函数
void DelayMs(unsigned int timeMs)
{
#define TIME_1_MS (355)
	unsigned int xdata nMsCounter = 0;
	unsigned short xdata msCounter = 0;
	unsigned char xdata i = 0;
	for(nMsCounter = 0 ; nMsCounter < timeMs ; nMsCounter++)
	{
		for(msCounter = 0 ; msCounter < TIME_1_MS ; msCounter++)
		{
			i = 1;
		}
	}
}

void DelayUs(uint16_t i)
{
	for(; i > 0; i --);
}
//10微秒延时函数
void Delay10Us(unsigned int timeUs)
{
#define TIME_10_US (4)
	unsigned int xdata nUsCounter = 0;
	unsigned char xdata usCounter = 0;
	for(nUsCounter = 0 ; nUsCounter < timeUs ; nUsCounter++)
	{
		for(usCounter = 0 ; usCounter < TIME_10_US ; usCounter++)
		{
		
		}
	}
}

void Delay10Us_4M(unsigned int timeUs)
{
	unsigned int xdata nUsCounter = 0;
	for(nUsCounter = 0 ; nUsCounter < timeUs ; nUsCounter++)
	{
		_nop_();
		_nop_();
		_nop_();
	}
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
