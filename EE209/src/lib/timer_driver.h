/*
 * timer_driver.h
 *
 * Created: 3/10/2019 9:50:32 PM
 *  Author: Caelan
 */ 

#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

void timer0_init();
uint8_t timer0_checkAndClearOverflow();


#endif /* TIMER_DRIVER_H_ */