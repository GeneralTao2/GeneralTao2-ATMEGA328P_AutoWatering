#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/interrupt.h>
#include "divaces/tools.h"
#include "divaces/button.h"
#include "divaces/timers.h"
#include "divaces/servo_motor.h"
#include "divaces/DC_motor.h"
#include "divaces/USART_terminal.h"
#include "divaces/ADC_manager.h"
#include "divaces/led.h"

/* Auto-Watering (AW) units */
uint16_t AW_tankLevel = 10;
void AW_PrintTankSate();

/* Support functions */
void InitConfigs();
void TIM2_Handler();

/* Divaces in AW system */
ButtonConfigs buttonStartPomp;
ButtonConfigs buttonCloseCran;
ButtonConfigs buttonOpenCran;
ServoMotorConfigs servoMotor;
DC_MotorConfigs DC_motor;
LedConfigs troubleLed;

int main(void)
{
	/* Initialization of divaces */
	InitConfigs();
	DC_MotorInit(&DC_motor);
	USART_Init();
	ADC_Init();
	ServoMotorInit(&servoMotor);
	TIM1_Init();
	TIM2_Init();
	ButtonInit(&buttonStartPomp);
	ButtonInit(&buttonCloseCran);
	ButtonInit(&buttonOpenCran);
	sei();
	
	while(1) {
		/* TIM2-depended routines processing */
		if(TIM2_extraFlag) {
			TIM2_Handler();
			TIM2_extraFlag = 0;
		}
		
		/* Button-depended routines processing */
		if(ButtonIsPressed(&buttonStartPomp))  {
			USART_serialWriteStr("WARNING: Pomp is connected. \n\r");
			DC_MotorStart(&DC_motor);
			SN_StreamExtraFlag = 1;
			ButtonsDisable();
		} else if(ButtonIsPressed(&buttonCloseCran))  {
			USART_serialWriteStr("WARNING: Main crane is close. \n\r");	// <--
			ServoMotorRotateTo(&servoMotor, SERVO_MOTOR_CLOSE_STATE);
			ButtonsDisable();
		} else if(ButtonIsPressed(&buttonOpenCran))  {
			USART_serialWriteStr("WARNING: Main crane is open. \n\r");
			ServoMotorRotateTo(&servoMotor, SERVO_MOTOR_OPEN_STATE);
			ButtonsDisable();
		}
	}
}

void TIM2_Handler() {
	AW_PrintTankSate();
	
	/* Stream sensor delay calculation */
	if( SN_StreamExtraFlag &&
	++SN_StreamExtraTime >= SN_STREAM_INIT_TIME) {
		SN_StreamExtraFlag = 0;
		SN_StreamExtraTime = 0;
	}
	
	LedToggle(&troubleLed);
	
	/* Pressure sensor processing */
	if( DC_MotorIsWorking(&DC_motor) ) {
		if(!SN_PRESSURE_STATE) {
			DC_MotorStop(&DC_motor);
			USART_serialWriteStr("CRASH: Pomp stopped. ");
			LedEnable(&troubleLed);
			if(SN_PRESSURE_VAL > SN_PRESSURE_CRITICAL_HIGH_VAL) {
				USART_serialWriteStr("Big pression! \n\r");
			} else {
				USART_serialWriteStr("Pression sensor isn't working!! \n\r");
			}
		}
	}
	
	/* Water level sensor processing */
	SN_WATER_LVL_VAL = AW_tankLevel * 50; //here water lvl signal simulation
	if( DC_MotorIsWorking(&DC_motor) || servoMotor.state == SERVO_MOTOR_OPEN_STATE ) {
		if(!SN_WATER_LVL_STATE) {
			if(DC_MotorIsWorking(&DC_motor) && SN_WATER_LVL_VAL > SN_WATER_LVL_CRITICAL_HIGH_VAL) {
				DC_MotorStop(&DC_motor);
				USART_serialWriteStr("WARNINGG: Tank is full. Pomp is off. \n\r");
			} else if(SN_WATER_LVL_VAL < SN_WATER_LVL_CRITICAL_HIGH_VAL) {
				DC_MotorStart(&DC_motor);
				ServoMotorRotateTo(&servoMotor, SERVO_MOTOR_CLOSE_STATE);
				USART_serialWriteStr("WARNING: Tank is empty. Main crane is close, pomp is on. \n\r");	 // <--
			}
		}
	}
	
	/* Stream sensor processing */
	if( DC_MotorIsWorking(&DC_motor) ) {
		if(!SN_STREAM_STATE && !SN_StreamExtraFlag) {
			DC_MotorStop(&DC_motor);
			USART_serialWriteStr("CRASH: Pomp stopped. ");
			LedEnable(&troubleLed);
			if(SN_STREAM_VAL > SN_STREAM_CRITICAL_HIGH_VAL) {
				USART_serialWriteStr("Stream too high! \n\r");
			} else {
				USART_serialWriteStr("Stream is missing! \n\r");	 // <--
			}
		}
	}
	
	/* Tank level modification (in simulation) */
	if( DC_MotorIsWorking(&DC_motor) ) {
		AW_tankLevel+=2;
	}
	if(servoMotor.state == SERVO_MOTOR_OPEN_STATE) {
		AW_tankLevel-=1;
	}
}

/* Tank state printing */
void AW_PrintTankSate() {
	USART_serialWriteStr("INFO: TANK LEVEL - ");
	USART_serialWriteNmr(AW_tankLevel);
	USART_serialWriteStr("\n\r");
}

/* Initialization of PINs of divaces */
void InitConfigs() {
	buttonStartPomp.port = &PORTD;
	buttonStartPomp.pcmsk = &PCMSK2;
	buttonStartPomp.pin = PORTD7;
	buttonStartPomp.pcie = PCIE2;
	buttonStartPomp.pressed = 0;
	
	buttonCloseCran.port = &PORTD;
	buttonCloseCran.pcmsk = &PCMSK2;
	buttonCloseCran.pin = PORTD3;
	buttonCloseCran.pcie = PCIE2;
	buttonCloseCran.pressed = 0;
	
	buttonOpenCran.port = &PORTD;
	buttonOpenCran.pcmsk = &PCMSK2;
	buttonOpenCran.pin = PORTD2;
	buttonOpenCran.pcie = PCIE2;
	buttonOpenCran.pressed = 0;
	
	servoMotor.ddr = &DDRD;
	servoMotor.port = &PORTD;
	servoMotor.pin = PORTD5;
	
	DC_motor.ddr = &DDRD;
	DC_motor.port = &PORTD;
	DC_motor.pin = PORTD4;
	
	troubleLed.ddr = &DDRB;
	troubleLed.port = &PORTB;
	troubleLed.pin = PORTB4;
}

/* TIM1 interrupt for against contact bounce of buttons*/
ISR(TIMER1_COMPA_vect) {
	if( ++TIM1_extraTime >= TIM1_EXTRA_DELAY ) {
		ButtonsEnable();
		TIM1_extraTime = 0;
	}
}

/* TIM2 interrupt code pricessing every 0.5 sec*/
ISR(TIMER2_COMPA_vect) {
	if( ++TIM2_extraTime >= TIM2_EXTRA_DELAY ) {
		TIM2_extraTime = 0;
		TIM2_extraFlag = 1;
	}
}

/* ADC interrupt for ADC pin values collection*/
ISR(ADC_vect) {
	ADC_values[ADC_input_index] = ADC;
	if( ++ADC_input_index >= ADC_COUNT ) {
		ADC_input_index = 0;
	}
	ADMUX = (1 << REFS0) | ADC_input_index;
	ADC_StartConversion();
}

/* USART interrupt for messages sending to terminal */
ISR(USART_TX_vect) {
	USART_InterruptHundler();
}

/* PCINT2 interrupt for button pressing handling */
ISR(PCINT2_vect) {
	if(!ButtonsEnablingState)
	return;
	if(PIND & SH(buttonStartPomp.pin) ) {
		ButtonPress(&buttonStartPomp);
		return;
	} else {
		ButtonUnPress(&buttonStartPomp);
	}
	if(PIND & SH(buttonCloseCran.pin) ) {
		ButtonPress(&buttonCloseCran);
		return;
	} else {
		ButtonUnPress(&buttonCloseCran);
	}
	if(PIND &SH(buttonOpenCran.pin) ) {
		ButtonPress(&buttonOpenCran);
		return;
	} else {
		ButtonUnPress(&buttonOpenCran);
	}
}