// Author: Caelan Murch
// Project: ELECTENG209 Signal Processing Library
// Date: 23/08/2019

#include "processing.h"


uint16_t findPeak(uint16_t *samples, uint8_t size, uint8_t pin, uint16_t (*read_adc_func)(uint8_t))
{
	uint16_t peak = 0;
	uint16_t Ioff;
	uint16_t Voff;
	// iterate over samples and use largest value as peak
	for (uint8_t i = 0; i < size; i++) {
		if (samples[i] > peak)
			peak = samples[i];
	}
	
	// determine which pin was read from to determine how to calculate 
	// original value before being processed by analogue circuits
	switch (pin) {
		case VOLTAGE_PIN:
			Voff = 0;
			for (int i = 0; i < 20; i++) {
				Voff += read_adc_func(VOLTAGE_OFFSET);
			}
			
			// get average Voff value
			Voff /= 20;	
			
			// subtract voltage offset from peak
			peak -= Voff;
			
			// convert peak voltage to real voltage value
			peak *= 5000/1024;
			
			// multiply peak by opamp gain to get orignal value
			peak *= 28;
			
			break;
		case CURRENT_PIN:
			Ioff = 0;
			for (int i = 0; i < 20; i++) {
				Ioff += read_adc_func(CURRENT_OFFSET);
			}
			
			// get average current offset
			Ioff /= 20;
			
			peak -= Ioff;
			
			// convert peak current to real value
			peak *= 5000/1024;
			// divide by shunt value to get real value
			peak /= SHUNT_VAL;
			// multiply by opamp gain to get real value
			peak *= 0.46;
			
			break;
		default:
			break;
	}
	
	return peak;
}

uint16_t calculateRMS(uint16_t peak)
{
	return peak/ROOT_2;
}

uint16_t getPhaseDifference(uint32_t *voltageTriggerTimes,
		uint32_t *currentTriggerTimes, uint8_t arraySize) 
{
	int16_t phaseDifference = 0;
	int16_t Tz = 0;
	int16_t Tp = 0;
	
	// determine difference between falling edge of both waves
	Tz = abs(currentTriggerTimes[0] - voltageTriggerTimes[0]) < abs(currentTriggerTimes[1] - voltageTriggerTimes[1]) ?
		abs(currentTriggerTimes[0] - voltageTriggerTimes[0]) : abs(currentTriggerTimes[1] - voltageTriggerTimes[1]);
	// determine wave length
	Tp = currentTriggerTimes[1] - currentTriggerTimes[0];
	// divide difference by wave length multiply by 2PI to get radians
	// and multiplu by 1000 to obtain angle as unsigned 16 bit integer
	phaseDifference = (uint16_t)((2.0*PI * Tz/Tp) * 1000);

	return (uint16_t)abs(phaseDifference);
}

uint16_t calculatePowerFactor(uint16_t phase) 
{
	// convert phase to double and real value by dividing by 1000
	double phaseRadians = phase/1000.0;
	
	// return absolute value of cos(phase) 
	// multiplied by 1000 to store as 16 bit unsigned integer
	return abs(cos(phaseRadians) * 1000);
}

uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf)
{
	// convert unsigned integers to doubles and multiply
	double p = ((Vrms/1000.0) * (Irms/1000.0) * (pf/1000.0));
	// return power as mW so it can be stored as unsigned integer
	return (uint16_t)(p*1000);
}
