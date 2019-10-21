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
	interrupt_handler(0);
}

ISR(INT1_vect)
{
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
	
	// set interrupt edge
	EICRA |= 0x0A;
	EIMSK |= 0x03;
	
	currentIndex = 0;
	voltageIndex = 0;
}

void interrupt_handler(uint8_t interruptPin)
{
	switch (interruptPin)
	{
		case 0:
			if (!enableCurrent) {
				enableCurrent = 1;
				break;
			}
			if (currentIndex == size)
				break;
			currentTriggers[currentIndex] = get_time_func();
			currentIndex++;
			break;
		case 1:
			if (!enableVoltage) {
				enableVoltage = 1;
				break;
			}
			if (voltageIndex == size)
				break;
			voltageTriggers[voltageIndex] = get_time_func();
			voltageIndex++;
			break;
		default:
			break;
	}
}