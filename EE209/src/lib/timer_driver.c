/*
 * timer_driver.c
 *
 * Created: 3/10/2019 9:50:09 PM
 *  Author: Reeve D'Cunha and Caelan Murch
 */ 

#include "timer_driver.h"

// Interrupt service routines
ISR(TIMER1_OVF_vect) {
	timerOverFlowCount++;
}

// init timer function
void timer_init()
{
	//Sets a 256 prescaler, new Frequency = 62.5kHz
	//Time Period for 1 count = 0.000016s = 16us
	//Time Period for 65535 counts = 1.04856s
	TCCR1B |= (1<<CS12);

	//Enables Timer Overflow interrupt (probably won't need it)
	TIMSK1 |= (1<<TOIE1);
	
	// initialise timer overflow count
	timerOverFlowCount = 0;
}

void resetTimer()
{
	// clear the timer counter
	TCNT1 = 0;
	resetTimerOverflowCount();
	// resets the timer overflow count
	//timerOverFlowCount = 0;
}

uint16_t getTimerCount()
{
	//returns the current value stored in the two 8-bit TIMER1 Registers
	return TCNT1;
}

uint16_t calculateTime(uint16_t scale)
{
	// set scale into time
	double scaleFactor = scale * 1/F_CPU;
	uint32_t time = (getTimerCount() * scaleFactor + 65536 * scaleFactor * timerOverFlowCount*100);
	return (uint16_t)time;
}

void resetTimerOverflowCount()
{
	// reset the overflow count
	timerOverFlowCount = 0;
}

uint16_t get_time()
{
	// returns the current timer count to the function caller
	return calculateTime(TIMER_PRESCALER);
}