/*
 * timer_driver.c
 *
 * Created: 3/10/2019 9:50:09 PM
 *  Author: Caelan
 */ 

#include "timer_driver.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// Interrupt service routines
ISR(TIMER0_COMPA_vect) {
	timer0OverFlowCount++;
	if (timer0OverFlowCount == 100) {
		PORTB ^= (1<<PINB5);
		timer0OverFlowCount = 0;
	}
}

ISR(TIMER1_OVF_vect) {
	timer1OverFlowCount++;
}

// functions
void timer0_init()
{
	// enable CTC mode
	TCCR0A |= (1<<WGM01);
	// enable OCR0A
	TCCR0B |= 0x05;
	// set overflow A value
	OCR0A = 156;
	// set over flow counter to 0
	timer0OverFlowCount = 0;
	// enable interrupt on OCROA overflow
	TIMSK0 |= (1<<OCIE0A);
}

uint8_t getTimer0Count()
{
	// return value from timer count register
	return TCNT0;
}

uint16_t calculateTime0(uint16_t scale) 
{
	return getTimer0Count() * scale + 256 * scale * timer0OverFlowCount;
}


// init timer function
void timer1Init()
{
	TCCR1B |= (1<<CS12) | (1<<CS10);
	TIMSK1 |= (1<<TOIE1);
	sei();
}

void resetTimer1()
{
	// clear the timer counter
	TCNT1 = 0;
}

uint16_t getTimer1Count()
{
	// return the value of the two 8-bit counter registers
	return TCNT1;
}

uint16_t calculateTime1(uint16_t scale)
{
	// set scale into time
	double scaleFactor = scale * 1/F_CPU;
	uint32_t time = (uint32_t)(getTimer1Count() * scaleFactor + pow(2,16) * scaleFactor * timer1OverFlowCount*100);
	return (uint16_t)time;
}

void resetTimer1OverflowCount()
{
	// reset the overflow count
	timer1OverFlowCount = 0;
}