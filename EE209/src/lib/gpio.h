/*
 * gpio.h
 *
 *
 *  Author: Reeve D'Cunha & Caelan Murch
 */ 

#include "config.h"
#include <avr/io.h>


#ifndef GPIO_H_
#define GPIO_H_

/**
 * \brief Set the data direction registers to output for PORTC and PORTD
 * 
 * 
 * \return void
 */
void io_init();


#endif /* GPIO_H_ */