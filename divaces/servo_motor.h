/*
 * servo_motor.h
 *
 * Created: 09.06.2020 20:34:07
 *  Author: ar725
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "tools.h"

#define SERVO_MOTOR_OPEN_STATE 360
#define SERVO_MOTOR_CLOSE_STATE 1

typedef struct ServoMotorConfigs {
	volatile uint8_t *ddr;
	volatile uint8_t *port;
	uint8_t pin;
	uint16_t state;
} ServoMotorConfigs;

void ServoMotorInit(ServoMotorConfigs *configs);
void ServoMotorRotateTo(ServoMotorConfigs *configs, uint16_t grade);






#endif /* SERVO_MOTOR_H_ */