/*
 * USART_terminal.c
 *
 * Created: 09.06.2020 20:43:36
 *  Author: ar725
 */ 
#include "USART_terminal.h"

void USART_Init() {
	UBRR0H = (USART_BRC >> 8);
	UBRR0L = USART_BRC;
	
	SB(UCSR0B, TXEN0);
	SB(UCSR0B, TXCIE0);
	
	SB(UCSR0C, UCSZ00);
	SB(UCSR0C, UCSZ01);
}

void USART_appendSerial(char c) {
	USART_serialBuffer[USART_serialWritePos] = c;
	USART_serialWritePos++;
	if(USART_serialWritePos >= USART_TX_BUFFER_SIZE - 1) {
		USART_serialWritePos = 0;
	}
}

void USART_serialWriteStr(char *c) {
	for(uint8_t i=0; i<strlen(c); i++) {
		USART_appendSerial(c[i]);
	}
	if(UCSR0A & SH(UDRE0)) {
		UDR0 = 0;
	}
}

void  USART_serialWriteNmr(int a) {
	char str[10];
	sprintf(str, "%d", a);
	USART_serialWriteStr(str);
}


void USART_InterruptHundler() {
	if(USART_serialWritePos != USART_serialReadPos) {
		UDR0 = USART_serialBuffer[USART_serialReadPos];
		USART_serialReadPos++;
		if(USART_serialReadPos >= USART_TX_BUFFER_SIZE - 1) {
			USART_serialReadPos = 0;
		}
	}
}