/*
 * interrupt.c
 *
 * Created: 10/10/2019 6:28:40 PM
 *  Author: Caelan Murch
 */ 

#include "interrupt.h"

// handle interrupts during cycle
ISR(INT0_vect)
{
	// call interrupt handler
	interrupt_handler(0);
}

ISR(INT1_vect)
{
	// call interrupt handler
	interrupt_handler(1);
}

void enable_interrupts()
{
	sei();
}
void disable_interrupts()
{
	cli();
}

void set_index(uint8_t index)
{
	voltageIndex = index;
	currentIndex = index;
	enableVoltage = 0;
	enableCurrent = 0;
}

uint8_t get_index()
{
	// return index being used in the arrays to check if all required values are measured
	return voltageIndex > currentIndex ? currentIndex : voltageIndex;
}

void interrupt_init(uint32_t *voltageTriggersArray, uint32_t *currentTriggersArray, uint8_t arraySize, uint32_t (*get_time_ptr)(void))
{
	
	voltageTriggers = voltageTriggersArray;
	currentTriggers = currentTriggersArray;
	enableVoltage = 0;
	enableCurrent = 0;
	size = arraySize;
	get_time_func = get_time_ptr;
	
	// set interrupt on falling edge
	EICRA |= 0x0A;
	// enable external interrupts on both interrupt pins
	EIMSK |= 0x03;
	
	currentIndex = 0;
	voltageIndex = 0;
}

void interrupt_handler(uint8_t interruptPin)
{
	switch (interruptPin)
	{
		case 0:
			// break on first trigger since it is a false trigger
			if (!enableCurrent) {
				enableCurrent = 1;
				break;
			}
			// do not read if array is full
			if (currentIndex == size)
				break;
			// get time
			currentTriggers[currentIndex] = get_time_func();
			currentIndex++;
			break;
		case 1:
			// break on first trigger since it is a false trigger
			if (!enableVoltage) {
				enableVoltage = 1;
				break;
			}
			// do not read if array is full
			if (voltageIndex == size)
				break;
			// get time
			voltageTriggers[voltageIndex] = get_time_func();
			voltageIndex++;
			break;
		default:
			break;
	}
}