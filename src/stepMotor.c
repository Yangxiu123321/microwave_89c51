#include "stepMotor.h"
#include "delay.h"
#include <math.h>

void StepMotorPinInit(void)
{
	GPIOInit(PHASE_A_PORT, PHASE_A_PIN, GPIO_PUSHPULL);
	GPIOInit(PHASE_B_PORT, PHASE_B_PIN, GPIO_PUSHPULL);
	GPIOInit(PHASE_C_PORT, PHASE_C_PIN, GPIO_PUSHPULL);
	GPIOInit(PHASE_D_PORT, PHASE_D_PIN, GPIO_PUSHPULL);	
}

void StepMotorSpeedControl(float vel)
{
	static unsigned char xdata state = 0x00;
	static unsigned long xdata counter = 0;
	
	switch(state)
	{
		case 0:
			GPIOSetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 1:
			GPIOSetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOSetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 2:
			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOSetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 3:
			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOSetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOSetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 4:
			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOSetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 5:
			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOSetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOSetBit(PHASE_D_PORT,PHASE_D_PIN);
		break;
		case 6:
			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOSetBit(PHASE_D_PORT,PHASE_D_PIN);
		break;
		case 7:
			GPIOSetBit(PHASE_A_PORT, PHASE_A_PIN);
			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
			GPIOSetBit(PHASE_D_PORT,PHASE_D_PIN);
		break;
		default:
		break;
	}
	
	counter++;
 	
	if(counter==((unsigned long)((STEP_RESOLUTION/(fabs(vel)))*1000.0f)))
	{
		counter=0;
		if(vel>0)
		{
			// 不用延时函数，防止程序在延时函数处阻塞
			//DelayMs((int)((STEP_RESOLUTION/vel)*1000));
			state++;
			state%=8;
		}
		else if(vel<0)
		{
			//DelayMs((int)((STEP_RESOLUTION/(-vel))*1000));
			if(state<1)
			{
				state=8;
			}
			state--;	
		}
	}
}


/**
功能:返回电机的控制命令
命令:
P3^2->控制电机的启动与停止
P3^3->控制正反转
P3^4 P3^5:控制电机的转速
**/
uint8_t getStepMotorCtrlCmd(void)
{
	return GPIOReadByte(GPIOPort3);
}

