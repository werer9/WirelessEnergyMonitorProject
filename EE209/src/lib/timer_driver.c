/*
 * timer_driver.c
 *
 * Created: 3/10/2019 9:50:09 PM
 *  Author: Reeve D'Cunha and Caelan Murch
 */ 

#include "timer_driver.h"

// init timer function
void timer_init()
{
	//Sets a 256 prescaler, new Frequency = 62.5kHz
	//Time Period for 1 count = 0.000016s = 16us
	//Time Period for 65535 counts = 1.04s
	TCCR1B |= (1<<CS12);
}

void resetTimer()
{
	// clear the timer counter
	TCNT1 = 0;
}

uint16_t getTimerCount()
{
	//returns the current value stored in the two 8-bit TIMER1 Registers
	return TCNT1;
}

// return in us
uint32_t calculateTime(uint16_t scale)
{
	// set scale into time, convert clock speed from Hz to MHz to scale time to us
	double step = 1/((double)(F_CPU/1000000)/256);
	// multiply timer register by value of time step
	double timeSeconds = step * getTimerCount();
	return (uint32_t)(timeSeconds);
}

uint32_t get_time()
{
	// returns the current timer count to the function caller
	return getTimerCount();
	//return calculateTime(TIMER_PRESCALER);
}