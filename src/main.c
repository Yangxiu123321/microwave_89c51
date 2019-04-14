#include "main.h"
#include "timer.h"

microwBox_t microwBox = {0};

#if MICROW_EXAM == 1
//P1IO实验状态指示枚举变量
typedef enum
{
	//四个LED灯
	blinkIn4,
	//流水灯 
	flow,
	//LED灯指示开关状态
	showInput,
	// led通过二进制显示led
	key2LedBinary,
	//空闲状态
	p1Idle
}p1IOStatus_t;

void main(void)
{
		//状态指示变量
	p1IOStatus_t idata p1IOStatus = showInput;
	while(1)
	{
		//每20ms循环一次
		//DelayMs(20);
		switch(p1IOStatus)
		{
			//四个LED一组闪烁
			case blinkIn4:
				BlinkIn4(500);
			break;
			//流水灯
			case flow:
				Flow(500);
			break;
			//将P10~P13输入输出到P14~P17，用输入控制LED的亮灭
			case showInput:
				ShowInput();
			break;
			case key2LedBinary:
				Key2LedBinary();
			break;
			case p1Idle:
			break;
			default:
			break;
		}	
	}
}
#elif MICROW_EXAM == 2
void main(void)
{
	uint8_t motorCtrlCmd = 0x00;
	// 控制电机引脚初始化
	StepMotorPinInit();
	// 等待初始化完成
	//DelayMs(500);
	Delay500ms();
	while(1)
	{
		// 获得电机控制命令
		motorCtrlCmd = getStepMotorCtrlCmd();
		// 启动电机
			
		if(motorCtrlCmd & 0x04)
		{
//      motorCtrlCmd的4位控制转向，5、6位控制速度			
//			direction = -1 + 2*((motorCtrlCmd&0x08)>>3)
//			velSpeed = ((motorCtrlCmd&0x30)>>4) + 1;
//			vel = direction * velSpeed
			StepMotorSpeedControl((-1 + 2*((motorCtrlCmd&0x08)>>3)) * (((motorCtrlCmd&0x30)>>4) + 1))
		}else{
			//StepMotorSpeedControl(0);
		}
	}
}

#elif MICROW_EXAM == 3
typedef enum
{
	//实验1
	EXP1,
	//实验2
	EXP2
}timerExpStatus_t;
void main(void)
{
	timerExpStatus_t idata timerExpStatus = EXP2;
	
	//定时器初始化结构体 
	timeMode_t timeMode ={0};
	
	//对结构体进行赋值
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	//timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = byteAutoReload;
	
	//初始化定时器5ms
	TimeInit(TIM0 , timeMode ,200, TIMERUS);
	
	//使能定时器中断
	TimerOverFlowItInit(TIM0 , enable);

	//使能外部中断0
	ExternalITInit(exIT0,EXIT_DOWN_TRIGGER);
	
	//定时器1=88，0=82
//	IE = 0x88;
//	TMOD = 0x20;
//	TH1 = 0x37;
//	TL1 = 0x37;
	// 启动定时器0
	//TR1 = 1;
	while(1)
	{
		if(microwBox.pro_runFlag)
		{
			microwBox.pro_runFlag = 0;
			//每20ms循环一次
			//根据不同中断中的标志切换LED的状态
			switch(timerExpStatus)
			{
				case EXP1:
					  FlowLedOnly(100);
						//Flow(100);
				break;
				case EXP2:
					if(microwBox.example3.LedItStatus)
					{
						Flow(100);
					}
					else
					{
						//FlowContrary(100);
						BlinkIn4(100);
					}
				break;
				default:
				break;
			}		
		}
	}
}

#elif MICROW_EXAM == 4
void main(void)
{
	//	//对P1IO的输出引脚
	
	UARTMode_t UARTInitStruct = {0};
	
	P1 = 0x00;
	
	// 波特率发生器初始化
	UARTInitStruct.UARTMode = UART_MODE_1;
	UARTInitStruct.UARTIsMulti = 0;
	UARTInitStruct.isUARTBaudrateDouble = UART_BAUDRATE_DOUBLE;
	UARTInitStruct.itPriority = 0;
	UARTInit(UART1,UARTInitStruct,9600);
	
	while(1)
	{
		DelayMs(20);
		
		UARTSendByte(UART1,0xA5);
		
		//microwBox.uart.UART1Recieve = 0;
		
		//LEDShowInt(microwBox.uart.UART1Recieve);
		LEDShowInt(-1);
		//LedWrite(0x97, 0x30);
		if(microwBox.uart.enterIntCnt > 4)
		{
			microwBox.uart.UART1Recieve = 0;
		}else
		{
		  microwBox.uart.enterIntCnt++;
		}
		//LEDShowInt(12);
	}
}

#elif MICROW_EXAM == 51
void main(void)
{
	IO8255Init_t IO8255InitStuct = {0};
	unsigned char pinNum = 0;
	
	IO8255InitStuct.portAInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portAInit.IOInOrOut = IO8255_INPUT;

	IO8255InitStuct.portBInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portBInit.IOInOrOut = IO8255_OUTPUT;
	
	IO8255InitStuct.portCUInit.IOInOrOut = IO8255_OUTPUT;
	IO8255InitStuct.portCLInit.IOInOrOut = IO8255_OUTPUT;
	

	IO8255Init(IO8255InitStuct);
	
	while(1)
	{
		for(pinNum=0 ; pinNum < 8 ; pinNum++)
		{
			IO8255SetBit(PortB , pinNum , IO8255ReadBit(PortA , pinNum));
		}

	}
	//test8255();
}
#elif MICROW_EXAM == 52

#define STB(state) IO8255SetBit(PortC,4,state)
#define BUSY (IO8255ReadBit(PortC,0))

void main(void)
{
	uint8_t sendData = 0;
	
	IO8255Init_t IO8255InitStuct = {0};
	
	IO8255InitStuct.portAInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portAInit.IOInOrOut = IO8255_OUTPUT;

	IO8255InitStuct.portBInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portBInit.IOInOrOut = IO8255_INPUT;
	
	IO8255InitStuct.portCUInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portCUInit.IOInOrOut = IO8255_OUTPUT;
	
	IO8255InitStuct.portCLInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portCLInit.IOInOrOut = IO8255_INPUT;
	
	IO8255Init(IO8255InitStuct);
	
	while(1)
	{
		STB(1);
		if(BUSY == 0)
		{
			DelayMs(250);
			if(BUSY == 0)
			{
				sendData ++;
				SendData_8225(sendData);
				STB(0);
				DelayMs(20);
			}
			if(sendData > 20)
			{
				sendData = 0;
			}
		}else
		{
			DelayMs(20);
		}
	}
}
#elif MICROW_EXAM == 61
typedef enum
{
	//实验1
	EXP1,
	//实验2
	EXP2,
	EXP3
}timerExpStatus_t;
void main(void)
{

	timerExpStatus_t idata timerExpStatus = EXP3;
	uint8_t keyValue = 0;
	unsigned short pulseValue = 0;
	
	DelayMs(1000);
	CLK_DIV = (CLK_DIV&0x3f)|0x40;
	
	EA = 1;
	
	if(timerExpStatus != EXP3)
	{
		Timer8254CounterModeInit(timer8254Timer0, 5);
	}else
	{
		// 初始为200khz
		Timer8254SquareWaveModeInit(timer8254Timer0, 10);
		Timer8254SquareWaveModeInit(timer8254Timer1, 2000);
		Timer8254SquareWaveModeInit(timer8254Timer2, 2000);
		LEDShowInt(200);
	}

	
	//StepMotorPinInit();
	//使能外部中断0
	ExternalITInit(exIT0,EXIT_DOWN_TRIGGER);
	ExternalITCmd(exIT0, enable);

//	ExternalITInit(exIT1 , EXIT_DOWN_TRIGGER);
//	ExternalITCmd(exIT1, enable);
	
	while(1)
	{
		DelayMs(20);
		switch(timerExpStatus)
		{
			case EXP1:
				  LEDShowInt(Timer8254GetCounter(timer8254Timer0));
					if(microwBox.example3.LedItStatus)
					{
						BlinkIn4_P374(100);
					}
					else
					{
						Flow_P374(100);
						//FlowContrary(100);
					}
			break;
			case EXP2:
				
			break;
			case EXP3:
				keyValue = ReadKeyNum();
				if(keyValue == 0xff)
				{
					continue;
				}else
				{
					pulseValue = 2000/pow(10,(keyValue+1));
					LEDShowInt(pulseValue);
					Timer8254SquareWaveModeInit(timer8254Timer0,pow(10,(keyValue+1)));
				} 
			break;
		}
	}
}
#elif MICROW_EXAM == 71
void main(void)
{
		//定时器初始化结构体 
	timeMode_t timeMode ={0};
	//对结构体进行赋值
	timeMode.isGat8eCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	//timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = byteAutoReload;
	//初始化定时器5ms
	TimeInit(TIM0 , timeMode ,200, TIMERUS);
	//使能定时器中断
	TimerOverFlowItInit(TIM0 , enable);
	
	ExternalITInit(exIT1 , EXIT_DOWN_TRIGGER);
	ExternalITCmd(exIT1, enable);
	while(1)
	{
		startAdc();
		DelayMs(20);
		LEDShowFloat(microwBox.example7.vol);
		showNum(GetAdcValue());
	}
}
#elif MICROW_EXAM == 8
void main(void)
{	
	char timerData[8] = {0};
	//定时器初始化结构体 
	timeMode_t timeMode ={0};
	//对结构体进行赋值
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	//timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = byteAutoReload;
	//初始化定时器5ms
	TimeInit(TIM1 , timeMode ,200, TIMERUS);
	//使能定时器中断
	TimerOverFlowItInit(TIM1 , enable);
	while(1)
	{
		DelayMs(20);
		ShowTimeString(11,12,13);
	}
}
#elif MICROW_EXAM == 9
void main(void)
{
	uint8_t keyValue = 0;
	uint8_t step = 0;
	int time20MsCnt = 0;
	int time1SCnt = 10;
	//定时器初始化结构体 
	timeMode_t timeMode ={0};
	//对结构体进行赋值
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	//timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = byteAutoReload;
	//初始化定时器5ms
	TimeInit(TIM1 , timeMode ,200, TIMERUS);
	//使能定时器中断
	TimerOverFlowItInit(TIM1 , enable);
	
	while(1)
	{
		// 20ms循环一次
		if(microwBox.pro_runFlag)
		{
			microwBox.pro_runFlag = 0;
			time20MsCnt ++;
			if(time20MsCnt == 50 && time1SCnt != 0)
			{
				time20MsCnt = 0;
				time1SCnt = time1SCnt - 1;
			}
			// 显示倒计时
			LEDShowSec(time1SCnt);
			if(time1SCnt == 0)
			{
				// 如果计时时间到，所有的灯都熄灭
				LedAllOff();
				step = 4;
			}
			// 读取按键值
			keyValue = ReadKeyNum();
			// 找对应的按键值
			if(keyValue == 0xff)
			{
				step = step;
			}else if(keyValue == 12)
			{
				step = 0;
			}else if(keyValue == 13)
			{
				step = 2;
			}else
			{
				step = step;
			}
			
			switch(step)
			{
				case 0:
					time20MsCnt = 0;
					time1SCnt = 10;
					step = 1;
				break;
				case 1:
					// 从左到右一次点亮
					Flow_P374(50);
				break;
				case 2:
					time20MsCnt = 0;
					time1SCnt = 10;
					step = 3;
				break;
				case 3:
					// 从右到左依次点亮
					Flow_P374Contrary(50);
				break;
				default:
				break;
		  }
	  }		
	}
}
#endif