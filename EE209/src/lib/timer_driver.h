/*
 * timer_driver.h
 *
 * Created: 3/10/2019 9:50:32 PM
 *  Author: Caelan
 */ 

#include "config.h"
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

volatile uint16_t timer0OverFlowCount;
volatile uint16_t timer1OverFlowCount;

void timer0_init();
uint8_t getTimer0Count();
uint16_t calculateTime0(uint16_t scale);

void timer1Init();
void resetTimer1();
uint16_t getTimer1Count();
uint16_t calculateTime1(uint16_t scale);
void resetTimer1OverflowCount();


#endif /* TIMER_DRIVER_H_ */