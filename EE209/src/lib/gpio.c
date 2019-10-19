/*
 * gpio.c
 *
 *
 *  Author: Reeve D'Cunha & Caelan Murch
 */ 

#include "gpio.h"

void io_init()
{
	//Set all PORTC pins as inputs
	DDRC = 0x11;

	//Set PORTD Pins 1 and 0 as outputs
	DDRD = 0x00;
	DDRD |= (1<<PIND0) | (1<<PIND1);
	PORTD |= (1<<PIND2)|(1<<PIND3);
}