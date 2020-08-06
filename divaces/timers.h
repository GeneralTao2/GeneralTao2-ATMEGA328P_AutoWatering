/*
 * timers.h
 *
 * Created: 10.06.2020 12:51:30
 *  Author: ar725
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "tools.h"

#define TIM1_OCRA 1
#define TIM1_EXTRA_DELAY 100
static volatile uint16_t TIM1_extraTime = 0;
void TIM1_Init();
void TIM1_Start();
void TIM1_Stop();

#define TIM2_OCRA 255
#define TIM2_EXTRA_DELAY 40
static volatile uint8_t TIM2_extraFlag = 0;
static volatile uint16_t TIM2_extraTime = TIM2_EXTRA_DELAY - 1;
void TIM2_Init();
void TIM2_Start();
void TIM2_Stop();




#endif /* TIMERS_H_ */