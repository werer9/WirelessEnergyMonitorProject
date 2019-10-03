/*
 * timer_driver.c
 *
 * Created: 3/10/2019 9:50:09 PM
 *  Author: Caelan
 */ 

#include "timer_driver.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t counter;

ISR(TIMER0_COMPA_vect) {
	counter++;
	if (counter == 100) {
		PORTB ^= (1<<PINB5);
		counter = 0;
	}
}

void timer0_init()
{
	TCCR0A |= (1<<WGM01);
	TCCR0B |= 0x05;
	OCR0A = 156;
	counter = 0;
	TIMSK0 |= (1<<OCIE0A);
}
uint8_t timer0_checkAndClearOverflow()
{
	if (TIFR0 & (1<<OCF0A)) {
		TIFR0 &= ~(1<<OCF0A);
		return 1;
	}
	
	return 0;
}