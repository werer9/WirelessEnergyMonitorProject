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

volatile uint32_t *voltageTriggers;
volatile uint32_t *currentTriggers;
volatile uint8_t size;
volatile uint8_t voltageIndex;
volatile uint8_t currentIndex;
volatile uint8_t enableVoltage;
volatile uint8_t enableCurrent;
uint32_t (*get_time_func)(void);

void enable_interrupts();
void disable_interrupts();
void set_index(uint8_t index);
uint8_t get_index();
void interrupt_init(uint32_t *voltageTriggers, uint32_t *currentTriggers, uint8_t arraySize, uint32_t (*get_time_ptr)(void));
void interrupt_handler(uint8_t interruptPin);

#endif /* INTERRUPT_H_ */