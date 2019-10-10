/*
 * interrupt.c
 *
 * Created: 10/10/2019 6:28:40 PM
 *  Author: Caelan
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

void interrupt_init(uint16_t *voltageTriggers, uint16_t *currentTriggers, uint8_t size, uint16_t (*get_time)(void))
{
	
	data.voltageTriggers = voltageTriggers;
	data.currentTriggers = currentTriggers;
	data.size = size;
	data.get_time = get_time;
	data.currentIndex = 0;
	data.voltageIndex = 0;
}

void interrupt_handler(uint8_t interruptPin)
{
	switch (interruptPin)
	{
		case 0:
			if (data.currentIndex == data.size)
				break;
			data.currentTriggers[data.currentIndex++] = data.get_time();
			break;
		case 1:
			if (data.voltageIndex == data.size)
				break;
			data.voltageTriggers[data.voltageIndex++] = data.get_time();
			break;
		default:
			break;
	}
}