/*
 * interrupt.h
 *
 * Created: 10/10/2019 6:28:23 PM
 *  Author: Caelan
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include <avr/interrupt.h>

struct interruptData {
	uint16_t *voltageTriggers;
	uint16_t *currentTriggers;
	uint8_t size;
	uint8_t voltageIndex;
	uint8_t currentIndex;
	uint16_t (*get_time)(void);
};

volatile struct interruptData data;

void interrupt_handler(uint8_t interruptPin);
void enable_interrupts();
void disable_interrupts();
void interrupt_init(uint16_t *voltageTriggers, uint16_t *currentTriggers, uint8_t size, uint16_t (*get_time)(void));

#endif /* INTERRUPT_H_ */