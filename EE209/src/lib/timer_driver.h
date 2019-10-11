/*
 * timer_driver.h
 *
 * Created: 3/10/2019 9:50:32 PM
 *  Author: Reeve D'Cunha and Caelan Murch
 */ 

#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

volatile uint16_t timerOverFlowCount;

void timer_init();
void resetTimer();
uint16_t getTimerCount();
uint16_t calculateTime(uint16_t scale);
void resetTimerOverflowCount();
uint16_t get_time();


#endif /* TIMER_DRIVER_H_ */