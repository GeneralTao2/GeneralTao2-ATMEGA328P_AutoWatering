/*
 * led.h
 *
 * Created: 11.06.2020 11:51:17
 *  Author: ar725
 */ 


#ifndef LED_H_
#define LED_H_

#include "tools.h"

typedef struct LedConfigs {
	volatile uint8_t *ddr;
	volatile uint8_t *port;
	uint8_t pin;
} LedConfigs;

void LedEnable(LedConfigs *configs);
void LedDisable(LedConfigs *configs);
void LedOn(LedConfigs *configs);
void LedOff(LedConfigs *configs);
void LedToggle(LedConfigs *configs);



#endif /* LED_H_ */