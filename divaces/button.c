/*
 * button.c
 *
 * Created: 09.06.2020 20:44:50
 *  Author: ar725
 */ 
#include "button.h"

void ButtonInit(ButtonConfigs *configs) {
	SB(*configs->port, configs->pin);
	SB(*configs->pcmsk, configs->pin);
	SB(PCICR, configs->pcie);
}

void ButtonPress(ButtonConfigs *configs) {
	if(ButtonsEnablingState) {
		configs->pressed = 1;
	}
}

uint8_t ButtonIsPressed(ButtonConfigs *configs) {
	return configs->pressed && ButtonsEnablingState;
}

void ButtonUnPress(ButtonConfigs *configs) {
	configs->pressed = 0;
}


void ButtonsEnable() {
	TIM1_Stop();
	ButtonsEnablingState = 1;
}
void ButtonsDisable() {
	TIM1_Start();
	ButtonsEnablingState = 0;
}
