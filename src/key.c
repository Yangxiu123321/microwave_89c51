#include "key.h"
#include "HD7279.h"
#include "stdDtype.h"

uint8_t xdata keyCode[16] = {27, 19, 11, 3, 26, 18, 10, 2, 25, 17, 9, 1, 24, 16, 8, 0};

uint8_t ReadKeyNum(void)
{
	uint8_t keyValue = 0;
	uint8_t keyNum = 0;
	keyValue = KeyRead();
	if(keyValue == 0XFF)
	{
		return 0xff;
	}
	for(keyNum = 0;keyNum < 16;keyNum++)
	{
		if(keyCode[keyNum] == keyValue)
		{
			break;
		}
	}
	return keyNum;
}



uint8_t KeyScan(void)
{
	static uint8_t flag = 1;
	uint8_t keyValue = 0;
	uint8_t keyNum = 0;
	keyValue = KeyRead();
	
	if(keyValue != 0xff && flag)
	{
		flag = 0;
		for(keyNum = 0;keyNum < 16;keyNum++)
		{
			if(keyCode[keyNum] == keyValue)
			{
				break;
			}
		}
		return keyNum;
	}else if(keyValue == 0xff)
	{
		flag = 1;
	}
	return 0xff;
}