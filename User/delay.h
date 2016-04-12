#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
/* Exported functions ------------------------------------------------------- */
void SysTick_Configuration(void);
void Delay_1ms(uint32_t nTime);
void TimingDelay_Decrement(void);

#endif
