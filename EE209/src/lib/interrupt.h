/*
 * interrupt.h
 *
 * Created: 10/10/2019 6:28:23 PM
 *  Author: Caelan
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include <avr/interrupt.h>
#include "config.h"

volatile uint16_t *voltageTriggers;
volatile uint16_t *currentTriggers;
uint8_t size;
uint8_t voltageIndex;
uint8_t currentIndex;
uint16_t (*get_time_func)(void);

void enable_interrupts();
void disable_interrupts();
void interrupt_init(uint16_t *voltageTriggers, uint16_t *currentTriggers, uint8_t size, uint16_t (*get_time_ptr)(void));
void interrupt_handler(uint8_t interruptPin);

#endif /* INTERRUPT_H_ */