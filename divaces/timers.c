/*
 * timers.c
 *
 * Created: 10.06.2020 12:52:44
 *  Author: ar725
 */ 

#include "timers.h"

void TIM1_Init() {
	SB(TCCR1A, WGM11);
	OCR1A = TIM1_OCRA;
	
	SB(TCCR1B, CS10);
	SB(TCCR1B, CS11);
}
void TIM1_Start() {
	SB(TIMSK1, OCIE1A);
}
void TIM1_Stop() {
	CB(TIMSK1, OCIE1A);
}

void TIM2_Init() {
	SB(TCCR2A, WGM21);
	OCR2A = TIM2_OCRA;
	
	SB(TCCR2B, CS20);
	SB(TCCR2B, CS21);
	SB(TCCR2B, CS22);
	TIM2_Start();
}
void TIM2_Start() {
	SB(TIMSK2, OCIE2A);
}
void TIM2_Stop() {
	CB(TIMSK2, OCIE2A);
}

