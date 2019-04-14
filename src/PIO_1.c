#include "PIO_1.h"
#include "STC15F2K60S2.h"
#include "stdDtype.h"

unsigned char xdata PLED_374 _at_ 0xFA00;

//将P1口0~3位的输入输出到P1口4~7位，用开关控制LED亮灭
void ShowInput(void)
{
	unsigned char xdata p1Input = 0;
	
	//P1为准双向，在读取前要写入1，避免读取出错
	P1 |= P1_INPUT;
	
	p1Input = P1&P1_INPUT;
	
	p1Input<<=4;
	P1 = p1Input;
	
}

//P1口输出控制LED四个一组循环闪烁，输入为闪烁周期，单位毫秒
void BlinkIn4(unsigned short period)
{
	static unsigned short xdata blinkTimeCounter  = 0;
	
	blinkTimeCounter+=2;
	blinkTimeCounter%=2*period;
	
	if(blinkTimeCounter/period)
	{
		P1 = 0x0f;
	}
	else
	{
		P1 = 0xf0;
	}
}

//P1口输出控制LED流水灯，输入为流水等的周期，单位：毫秒
void Flow(unsigned short flowPeriod)
{
	static unsigned short xdata flowCounter = 0;
	static unsigned char xdata flowState = 0x01;
	
	flowCounter+=1;
	flowCounter%=flowPeriod;
	
	//电路连接为输出低时LED亮
	P1 = ~flowState;
	
	if(flowCounter == 0)
	{
		if(flowState!=0x80)
		{
			flowState<<=1;
		}
		else
		{
			flowState = 0x01;
		}
	}
}

// 反方向旋转
void FlowContrary(unsigned short flowPeriod)
{
	static unsigned short xdata flowCounter = 0;
	static unsigned char xdata flowState = 0x01;
	
	flowCounter+=1;
	flowCounter%=flowPeriod;
	
	//电路连接为输出低时LED亮
	P1 = ~flowState;
	
	if(flowCounter == 0)
	{
		if(flowState!=0x01)
		{
			flowState>>=1;
		}
		else
		{
			flowState = 0x80;
		}
	}
}

//每一个灯在一个周期内高电平占空比(50%占空比)亮
void FlowLedOnly(unsigned short flowPeriod)
{
	static unsigned short xdata flowCounter = 0;
	static unsigned char xdata flowState = 0x01;
	
	flowCounter+=1;
	flowCounter%=flowPeriod;
		
	if(flowCounter == 0)
	{
		if(flowState!=0x01)
		{
			flowState>>=1;
		}
		else
		{
			flowState = 0x80;
		}
	}else if(flowCounter >= (flowPeriod/2))
	{
		// 灯全部熄灭
		P1 = 0xff;
	}else
	{
		//电路连接为输出低时LED亮
		P1 = ~flowState;
	}
}

//将按键的编号用led等二进制的方式显示出来
void Key2LedBinary(void)
{	
	if((P1&0x01))
	{
		P1 = 0xff;
	}else if((P1&0x02))
	{
		P1 = 0xef;
	}
	else if((P1&0x04))
	{
		P1 = 0xdf;
	}else if((P1&0x08))
	{
		P1 = 0xcf;
	}else
	{
		P1 = 0xff;
	}
}

void led_flow_p374(void)
{
	uint8_t status = 0;
	status = 0x0f;
	PLED_374 = status;
}

//374输出控制LED四个一组循环闪烁，输入为闪烁周期，单位毫秒
void BlinkIn4_P374(unsigned short period)
{
	static unsigned short xdata blinkTimeCounter  = 0;
	
	blinkTimeCounter+=2;
	blinkTimeCounter%=2*period;
	
	if(blinkTimeCounter/period)
	{
		PLED_374 = 0x0f;
	}
	else
	{
		PLED_374 = 0xf0;
	}
}

//374输出控制LED流水灯，输入为流水等的周期，单位：毫秒
void Flow_P374(unsigned short flowPeriod)
{
	static unsigned short xdata flowCounter = 0;
	static unsigned char xdata flowState = 0x01;
	
	flowCounter+=1;
	flowCounter%=flowPeriod;
	
	//电路连接为输出低时LED亮
	PLED_374 = ~flowState;
	
	if(flowCounter == 0)
	{
		if(flowState!=0x80)
		{
			flowState<<=1;
		}
		else
		{
			flowState = 0x01;
		}
	}
}

//灯逆时针流水灯
void Flow_P374Contrary(unsigned short flowPeriod)
{
	static unsigned short xdata flowCounter = 0;
	static unsigned char xdata flowState = 0x01;
	
	flowCounter+=1;
	flowCounter%=flowPeriod;
	
	//电路连接为输出低时LED亮
	PLED_374 = ~flowState;
	
	if(flowCounter == 0)
	{
		if(flowState!=0x01)
		{
			flowState>>=1;
		}
		else
		{
			flowState = 0x80;
		}
	}
}

void LedAllOff(void)
{
	PLED_374 = 0xff;
}

void showNum(unsigned char dataNum)
{
	PLED_374 = dataNum;
}