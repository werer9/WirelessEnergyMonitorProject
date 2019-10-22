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
#include <stdlib.h>

// find peak value of sinusoidal wave
uint16_t findPeak(uint16_t *samples, uint8_t size, uint8_t pin, uint16_t (*read_adc_func)(uint8_t));

// calculate the rms value from peak value of sinusoid
uint16_t calculateRMS(uint16_t peak);

// get phase difference in radians
uint16_t getPhaseDifference(uint32_t *voltageTriggerTimes,
		uint32_t *currentTriggerTimes, uint8_t arraySize);

// calculate power factor
uint16_t calculatePowerFactor(uint16_t phase);

// calculate average power using standard equation
uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf);


#endif /* PROCESSING_H_ */