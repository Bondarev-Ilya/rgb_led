#ifndef FREQ_UP_H_
#define	FREQ_UP_H_

#include <stm32f411xe.h>

extern float time_s;
extern float time_ms;

void Freq_up_to_100_MHz(void);
void sysTickInit(void);
void SysTick_Handler(void);
void delay_ms(uint16_t delay);

#endif