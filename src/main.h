#ifndef __MAIN_H
#define __MAIN_H
#include "STC15F2K60S2.h"
#include "math.h"
#include <stdio.h>
#include "delay.h"
#include "stdDtype.h"
#include "PIO_1.h"
#include "timer.h"
#include "usart.h"
#include "89c51_it.h"
#include "stepMotor.h"
#include "HD7279.h"
#include "8255.h"
#include "8254.h"
#include "key.h"
#include "adc.h"
// 实验序号
/*
1、P1IO实验
2、步进电机控制实验
3
*/
/*
1、片内输入、输出实验
2、步进电机
3、定时/计数器与中断控制实验
4、串行通信实验
5、可编程并行I/O接口8255
6、可编程定时/计数器8254实验
71、A/D转换实验
8、时钟实验
9、期末考试
*/

#define MICROW_EXAM 9


//圆周率宏定义
#define PI (3.1415926f)

//错误返回代码
#define RETURN_ERROR (0xff)

//系统时钟定于
#define SYSCLK (12000000L)

//一微妙时间定义
#define TIMERUS (int)(12.0f/(float)(SYSCLK/1000000))
	
// 实验三相关标志位
typedef struct
{
	// 定时器进中断计数
	unsigned int timerCnt; 
	
	uint8_t LedItStatus;
	
}example3_t;
// 实验七相关标志位
typedef struct
{
	float vol;
	uint8_t dacNum;
	uint8_t dacNumFlag;
	int dacProCnt;
}example7_t;
typedef struct
{
	uint8_t UART1Recieve;
	// 记录没进中断的时间
	unsigned int enterIntCnt;
}uart_t;

//试验箱控制符号
typedef struct
{
	//程序运行周期标志位
	uint8_t pro_runFlag;
	
	example3_t example3;
	
	example7_t example7;
	
	uart_t uart;

}microwBox_t;

#endif
