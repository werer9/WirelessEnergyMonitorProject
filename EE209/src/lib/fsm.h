/*
* Date: 26/09/19
* Author: Caelan Murch
* Description: Finite State Machine
*/

#ifndef FSM_H_
#define FSM_H_

#include "config.h"
#include <stdint.h>
#include <stdlib.h>

// states represented by state, states define in config.h
uint8_t state;

// function pointers so fsm can execute properly
struct functionPointers {
    void (*uart_init)(uint16_t baud);
    void (*io_init)(void);
    void (*adc_init)(void);
	void (*timer_init)(void);
    void (*int_init)(uint32_t *voltageTriggers, uint32_t *currentTriggers, uint8_t size, uint32_t (*get_time)(void));
	uint8_t (*get_trigger_index)(void);
	void (*set_trigger_index)(uint8_t index);
    void (*get_uart_string)(uint16_t val, char *string, char ident);
    void (*uart_write)(char* data_string);
	void (*disable_interrupts)(void);
	void (*enable_interrupts)(void);
    uint16_t (*read_adc)(uint8_t channel);
    uint32_t (*get_time)(void);
	void (*timer_reset)(void);
	uint16_t (*find_peak)(uint16_t *samples, uint8_t size, uint8_t pin, uint16_t (*read_adc_func)(uint8_t));
	uint16_t (*calculate_RMS)(uint16_t peak);
	uint16_t (*get_phase_difference)(uint32_t *voltageTriggerTimes,
		uint32_t *currentTriggerTimes, uint8_t arraySize);
	uint16_t (*calculate_power_factor)(uint16_t phase);
	uint16_t (*calculate_average_power)(uint16_t Vrms, uint16_t Irms, uint16_t pf);
};

// struct to store all values related to processing the data
uint8_t triggerSize;
uint16_t peakVoltage;
uint16_t peakCurrent;
uint16_t voltage;
uint16_t current;
uint16_t phase;
uint16_t pf;
uint16_t power;
uint16_t voltages[SIZE];
uint16_t currents[SIZE];
uint32_t voltageTriggerTimes[TRIGGER_SIZE];
uint32_t currentTriggerTimes[TRIGGER_SIZE];

// global member functions struct
struct functionPointers *functions;

// current index for the trigger arrays
uint8_t voltageTriggerIndex;
uint8_t currentTriggerIndex;

// init fsm
void fsmInit(struct functionPointers *fsmFunctions) ;

// main fsm function
int run();

// init state
void stateInit();

// read power state
void stateReadPower();

// calculate power state
void stateCalculatePower();

// transmit the power over UART
void stateTransmitPower();

#endif /* FSM_H_ */