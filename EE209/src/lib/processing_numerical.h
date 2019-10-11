// Author: Reeve D'Cunha

// include maths functions and uint8_t datatype for microcontroller
// efficiency

#ifndef PROCESSING_NUMERICAL_H_
#define PROCESSING_NUMERICAL_H_

#include "config.h"
#include <math.h>
#include <stdint.h>

// calculate UBRR value for given BAUD rate
uint16_t calculate_UBRR(uint16_t baud);

// convert adc value to real value
uint16_t convert_ADC_value(uint16_t sample, uint16_t maxVal, uint8_t bits);

// calculate the rms value from peak value of sinusoid
uint16_t get_voltage_rms(uint16_t *voltageArray, uint8_t size);

//returns peak 
uint16_t get_voltage_peak(uint16_t voltageRMS);

// calculate the rms value of load current
uint16_t get_current_rms(uint16_t voltageRMS, uint16_t shunt_val);

// calculates the average/real power
uint16_t get_avg_power(uint16_t vRMS, uint16_t iRMS, uint16_t pf);

#endif /* PROCESSING_NUMERICAL_H_ */
