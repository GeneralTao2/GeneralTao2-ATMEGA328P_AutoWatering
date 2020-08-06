/*
 * led.c
 *
 * Created: 11.06.2020 11:51:40
 *  Author: ar725
 */ 
#include "led.h"

void LedEnable(LedConfigs *configs) {
	SB(*configs->ddr, configs->pin);
}

void LedDisable(LedConfigs *configs) {
	CB(*configs->ddr, configs->pin);
}

void LedOn(LedConfigs *configs) {
	SB(*configs->port, configs->pin);
}

void LedOff(LedConfigs *configs) {
	CB(*configs->port, configs->pin);
}

void LedToggle(LedConfigs *configs) {
	TB(*configs->port, configs->pin);
}