/*
 * button.h
 *
 * Created: 09.06.2020 20:45:05
 *  Author: ar725
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "tools.h"
#include "timers.h"

static volatile uint8_t ButtonsEnablingState = 1;

typedef struct ButtonConfigs {
	volatile uint8_t *port;
	volatile uint8_t *pcmsk;
	uint8_t pin;
	uint8_t pcie;
	volatile uint8_t pressed;
} ButtonConfigs;

void ButtonInit(ButtonConfigs *configs);

void ButtonsEnable();
void ButtonsDisable();

uint8_t ButtonIsPressed(ButtonConfigs *configs);

void ButtonUnPress(ButtonConfigs *configs);
void ButtonPress(ButtonConfigs *configs);


#endif /* BUTTON_H_ */