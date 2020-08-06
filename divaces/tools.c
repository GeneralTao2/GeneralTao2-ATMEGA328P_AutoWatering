/*
 * tools.c
 *
 * Created: 10.06.2020 17:25:30
 *  Author: ar725
 */
#include "tools.h" 

void delay_ms(uint16_t count) {
	while(count--) {
		_delay_ms(0.01);

	}
}