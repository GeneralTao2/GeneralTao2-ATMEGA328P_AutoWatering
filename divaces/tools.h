/*
 * tools.h
 *
 * Created: 09.06.2020 21:13:41
 *  Author: ar725
 */ 


#ifndef TOOLS_H_
#define TOOLS_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define SH(BITx) (1 << (BITx))
#define NSH(BITx) ~(1 << (BITx))
#define SB(PORTx, BITx) ((PORTx) |= (1 << (BITx)))
#define CB(PORTx, BITx) ((PORTx) &= ~(1 << (BITx)))
#define TB(PORTx, BITx) ((PORTx) ^= (1 << (BITx)))

void delay_ms(uint16_t count);

#endif /* TOOLS_H_ */