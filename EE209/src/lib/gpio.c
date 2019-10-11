/*
 * gpio.c
 *
 *
 *  Author: Reeve D'Cunha
 */ 

#include "gpio.h"

void io_init()
{

//Set all PORTC pins as inputs
DDRC = 0x00;

//Set PORTD Pins 1 and 0 as outputs
DDRD = 0x03;
}