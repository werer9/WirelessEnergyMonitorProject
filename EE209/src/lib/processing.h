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

/**
	\brief Calculate the peak value of sinusoidal wave from samples read by ADC
	
	\param samples Array containing samples
	\param size Size of array
	\param pin ADC pin the samples were obtained from
	\param (*read_adc_func) Function pointer for ADC read
							This is needed to determine offset values
	
	\return uint16_t peak of waveform
*/
uint16_t findPeak(uint16_t *samples, uint8_t size, uint8_t pin, uint16_t (*read_adc_func)(uint8_t));

/**
	\brief Calculate RMS of sinusoidal wave
	
	\param peak Peak value from sinusoidal wave
	
	\return uint16_t RMS value
*/
uint16_t calculateRMS(uint16_t peak);

/**
	\brief Calculate phase difference between two waves
	
	Returns the phase angle in radians
	
	\param voltageTriggerTimes Time the voltage zero crossing detector is triggered
	\param currentTriggerTimes Time the current zero crossing detector is triggered
	\param arraySize Size of both arrays
	
	\return uint16_t phase angle in radians
*/
uint16_t getPhaseDifference(uint32_t *voltageTriggerTimes,
		uint32_t *currentTriggerTimes, uint8_t arraySize);

/**
	\brief Calculate the power factor given a phase angle in degrees
	
	\param phase Phase angle in radians
	
	\return uint16_t power factor
*/
uint16_t calculatePowerFactor(uint16_t phase);

/**
	\brief Calculate the average power from Vrms, Irms and power factor
	
	\param Vrms Voltage RMS value
	\param Irms Current Rms value
	\param Pf Power factor
	
	\return uint16_t average power in mW
*/
uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf);


#endif /* PROCESSING_H_ */