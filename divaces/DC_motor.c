/*
 * DC_motor.c
 *
 * Created: 09.06.2020 20:38:00
 *  Author: ar725
 */ 

#include "DC_motor.h"

void DC_MotorInit(DC_MotorConfigs *configs) {
	SB(*configs->ddr, configs->pin);
}

void DC_MotorStart(DC_MotorConfigs *configs) {
	SB(*configs->port, configs->pin);
}

void DC_MotorStop(DC_MotorConfigs *configs) {
	CB(*configs->port, configs->pin);
}

uint8_t DC_MotorIsWorking(DC_MotorConfigs *configs) {
	return *configs->port & SH(configs->pin);
}