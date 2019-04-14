/***********************89C51_it.c***************************/

#include "89C51_it.h"
#include "timer.h"
#include "main.h"

unsigned char xdata V1[32]={0x00,0x0f,0x1f,0x2f,0x3f,0x4f,0x5f,0x6f,0x7f,0x8f,0x9f,0xaf,0xbf,0xcf,0xdf,0xef,0xff,0xef,0xdf,0xcf,0xbf,0xaf,0x9f,0x8f,0x7f,0x6f,0x5f,0x4f,0x3f,0x2f,0x1f,0x0f};

extern microwBox_t microwBox;

/**
  * @brief	外部中断初始化
  * @note
  * @param	exITx：中断标号
*     			exIT0:中断0
*				exIT1:中断1
* @param	triggerMode:触发模式
*				EXIT_UPDOWN_TRIGGER：电平触发
*				EXIT_DOWN_TRIGGER：下降沿触发					
  * @retval none
  */
	
//外部中断使能失能函数
void ExternalITCmd(exITTypedef_t exITx, FunctionalState_t newState)
{
	//根据输入的中断号和状态对相应寄存器进行置位或复位
	if(exITx==exIT0)
	{
		EX0 = newState;
	}
	else if(exITx==exIT1)
	{
		EX1 = newState;
	}
}

void ExternalITInit(exITTypedef_t exITx , unsigned char triggerMode)
{
	//根据输入的中断号和触发模式对相应寄存器进行配置
	if(exITx==exIT0)
	{
		IT0 = triggerMode;
		ExternalITCmd(exIT0 , enable);
	}
	else if(exITx==exIT1)
	{
		IT1  = triggerMode;
		ExternalITCmd(exIT1 , enable);		
	}
}

//定时器0溢出中断服务函数
void time0()interrupt 1
{
	TimerClearOverFlowFlag(TIM0);
	// 设置程序周期
	microwBox.example3.timerCnt += 1;
	microwBox.example7.dacProCnt += 1;
	if(microwBox.example7.dacProCnt > 2)
	{
		microwBox.example7.dacProCnt = 0;
		dacOut(V1[microwBox.example7.dacNum]);
		microwBox.example7.dacNum += 1;
		if(microwBox.example7.dacNum == 32)
		{
			microwBox.example7.dacNum = 0;
		}
	}
	
  setRunTime();	
}

void time1()interrupt 3
{
	TimerClearOverFlowFlag(TIM1);
	microwBox.example3.timerCnt += 1;
	setRunTime();	
}

//外部中断0服务函数1KHz
void ExIT0_Handler() interrupt 0
{
	if(microwBox.example3.LedItStatus)
	{
		microwBox.example3.LedItStatus = 0;
	}else{
		microwBox.example3.LedItStatus = 1;
	}

}

//外部中断1服务函数
void ExIT1_Handler() interrupt 2
{
	microwBox.example7.vol = GetVoltage(0,5);
}

void UART1_ITHandler()interrupt 4
{
	if(UARTGetFlagStatus(UART1,UART_Rx_IT_FLAG)==SET)
	{
		microwBox.uart.enterIntCnt = 0;
		microwBox.uart.UART1Recieve = UARTRecieveByte(UART1);
		UARTClearFlagStatus(UART1, UART_Rx_IT_FLAG);
	}
	else if(UARTGetFlagStatus(UART1,UART_Tx_IT_FLAG)==SET)
	{
//		UARTClearFlagStatus(UART1, UART_Tx_IT_FLAG);
	}
}
