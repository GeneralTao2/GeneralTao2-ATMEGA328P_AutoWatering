/*
 * DC_motor.h
 *
 * Created: 09.06.2020 20:37:35
 *  Author: ar725
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "tools.h"

typedef struct DC_MotorConfigs {
	volatile uint8_t *ddr;
	volatile uint8_t *port;
	uint8_t pin;
} DC_MotorConfigs;

void DC_MotorInit(DC_MotorConfigs *configs);
void DC_MotorStart(DC_MotorConfigs *configs);
void DC_MotorStop(DC_MotorConfigs *configs);
uint8_t DC_MotorIsWorking(DC_MotorConfigs *configs);



#endif /* DC_MOTOR_H_ */