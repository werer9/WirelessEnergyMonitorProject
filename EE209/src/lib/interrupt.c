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

void interrupt_init(uint16_t *voltageTriggers, uint16_t *currentTriggers, uint8_t arraySize, uint16_t (*get_time_ptr)(void))
{
	
	voltageTriggers = voltageTriggers;
	currentTriggers = currentTriggers;
	size = arraySize;
	get_time_func = get_time_ptr;
	
	// set interrupt edge
	EICRA |= 0x0F;
	EIMSK |= 0x03;
	
	currentIndex = 0;
	voltageIndex = 0;
}

void interrupt_handler(uint8_t interruptPin)
{
	switch (interruptPin)
	{
		case 0:
			if (currentIndex == size)
				break;
			currentTriggers[currentIndex++] = get_time_func();
			break;
		case 1:
			if (voltageIndex == size)
				break;
			voltageTriggers[voltageIndex++] = get_time_func();
			break;
		default:
			break;
	}
}