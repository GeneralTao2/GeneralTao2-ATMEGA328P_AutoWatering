/*
 * servo_motor.c
 *
 * Created: 09.06.2020 20:34:51
 *  Author: ar725
 */ 
#include "servo_motor.h"

void ServoMotorInit(ServoMotorConfigs *configs) {
	SB(*configs->ddr, configs->pin);
}

void ServoMotorRotateTo(ServoMotorConfigs *configs, uint16_t grade) {
	SB(*configs->port, configs->pin);
	delay_ms(grade);
	CB(*configs->port, configs->pin);
	configs->state = grade;
}

