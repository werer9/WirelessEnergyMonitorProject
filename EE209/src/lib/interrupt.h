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

/**
 * \brief Enable global interrupts
 * 
 * 
 * \return void
 */
void enable_interrupts();
/**
 * \brief Disable global interrupts
 * 
 * 
 * \return void
 */
void disable_interrupts();
/**
 * \brief Set index of trigger arrays
 * 
 * \param index Array index
 * 
 * \return void
 */
void set_index(uint8_t index);
/**
 * \brief Return smallest index used by trigger arrays
 * 
 * 
 * \return uint8_t Trigger index
 */
uint8_t get_index();
/**
 * \brief Initialise interrupts
 * 
 * \param voltageTriggers Voltage trigger array pointers
 * \param currentTriggers Current trigger array pointers
 * \param arraySize Size of trigger arrays
 * \param get_time_ptr Get time function pointer
 * 
 * \return void
 */
void interrupt_init(uint32_t *voltageTriggers, uint32_t *currentTriggers, uint8_t arraySize, uint32_t (*get_time_ptr)(void));

/**
 * \brief Initialise interrupts
 * 
 * \param interruptPin External interrupt pin number
 * 
 * \return void
 */
void interrupt_handler(uint8_t interruptPin);

#endif /* INTERRUPT_H_ */