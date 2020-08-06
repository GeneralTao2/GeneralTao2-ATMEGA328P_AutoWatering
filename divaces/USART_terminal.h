/*
 * USART_terminal.h
 *
 * Created: 09.06.2020 20:43:54
 *  Author: ar725
 */ 


#ifndef USART_TERMINAL_H_
#define USART_TERMINAL_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "tools.h"
#include <string.h>
#include <stdio.h>

#define USRAT_BUAD 9600
#define USART_BRC ((F_CPU/16/USRAT_BUAD) - 1)
#define USART_TX_BUFFER_SIZE 128

static uint8_t USART_serialBuffer[128];
static uint8_t USART_serialReadPos = 0;
static uint8_t USART_serialWritePos = 0;

void USART_Init();

void USART_serialWriteStr(char *c);
void USART_serialWriteNmr(int a);

void USART_InterruptHundler();



#endif /* USART_TERMINAL_H_ */