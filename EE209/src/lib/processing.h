// Author: Caelan Murch
// Project: ELECTENG209 Signal Processing Library
// Date: 23/08/2019

#ifndef PROCESSING_H_
#define PROCESSING_H_

// include maths functions and uint8_t datatype for microcontroller
// efficiency
#include "config.h"
#include <math.h> 
#include <stdint.h>
#include <stdio.h>


// return string in format needed by uart
void get_uart_string(uint16_t val, char *string, char ident);

// convert adc value to real value
uint16_t convertADCValue(uint16_t sample, uint16_t maxVal, uint8_t bits);

// find peak value of sinusoidal wave
uint16_t findPeak(uint16_t *samples, uint8_t size);

// calculate the rms value from peak value of sinusoid
uint16_t calculateRMS(uint16_t peak);

// get phase difference in radians
uint16_t getPhaseDifference(uint16_t *crossTimes1, uint8_t size1, 
		uint16_t *crossTimes2, uint8_t size2);

// calculate power factor
uint16_t calculatePowerFactor(uint16_t phase);

// calculate average power using standard equation
uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf);


#endif /* PROCESSING_H_ */