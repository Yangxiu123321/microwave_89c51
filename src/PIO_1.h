#ifndef __P1IO_H
#define __P1IO_H


#define P1_INPUT  (0x0f)

void BlinkIn4(unsigned short period);
void Flow(unsigned short flowPeriod);
void FlowContrary(unsigned short flowPeriod);
void FlowLedOnly(unsigned short flowPeriod);
void ShowInput(void);
void Key2LedBinary(void);
void led_flow_p374(void);
void BlinkIn4_P374(unsigned short period);
void Flow_P374(unsigned short flowPeriod);
void showNum(unsigned char dataNum);
void Flow_P374Contrary(unsigned short flowPeriod);
void LedAllOff(void);

#endif