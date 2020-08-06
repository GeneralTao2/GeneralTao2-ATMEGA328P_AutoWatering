/*
 * ADC_manager.c
 *
 * Created: 10.06.2020 21:33:11
 *  Author: ar725
 */ 

#include "ADC_manager.h"

void ADC_Init() {
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	DIDR0 = (1 << ADC5D);
	ADC_StartConversion();
}

void ADC_StartConversion() {
	ADCSRA |= (1 << ADSC);
}
