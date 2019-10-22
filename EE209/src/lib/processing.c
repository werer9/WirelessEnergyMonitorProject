// Author: Caelan Murch
// Project: ELECTENG209 Signal Processing Library
// Date: 23/08/2019

#include "processing.h"

// find peak value of sinusoidal wave
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
	
	switch (pin) {
		case VOLTAGE_PIN:
			Voff = 0;
			for (int i = 0; i < 20; i++) {
				Voff += read_adc_func(VOLTAGE_OFFSET);
			}
			Voff /= 20;	
		
			peak -= Voff;
			peak *= 5000/1024;
			peak *= 28;
			
			break;
		case CURRENT_PIN:
			Ioff = 0;
			for (int i = 0; i < 20; i++) {
				Ioff += read_adc_func(CURRENT_OFFSET);
			}
			Ioff /= 20;
			
			peak -= Ioff;
			peak *= 5000/1024;
			peak /= SHUNT_VAL;
			peak *= 0.46;
			
			break;
		default:
			break;
	}
	
	return peak;
}

// calculate the rms value from peak value of sinusoid
uint16_t calculateRMS(uint16_t peak)
{
	return peak/ROOT_2;
}

// get phase difference in degrees
// since these are more accurate
uint16_t getPhaseDifference(uint32_t *voltageTriggerTimes,
		uint32_t *currentTriggerTimes, uint8_t arraySize) 
{
	int16_t phaseDifference = 0;
	int16_t Tz = 0;
	int16_t Tp = 0;

	Tz = abs(currentTriggerTimes[0] - voltageTriggerTimes[0]) < abs(currentTriggerTimes[1] - voltageTriggerTimes[1]) ?
		abs(currentTriggerTimes[0] - voltageTriggerTimes[0]) : abs(currentTriggerTimes[1] - voltageTriggerTimes[1]);
	Tp = currentTriggerTimes[1] - currentTriggerTimes[0];

	phaseDifference = (uint16_t)((2.0*PI * Tz/Tp) * 1000);

	return (uint16_t)abs(phaseDifference);
}

// calculate power factor
uint16_t calculatePowerFactor(uint16_t phase) 
{
	double phaseRadians = phase/1000.0;
	return abs(cos(phaseRadians) * 1000);
}

// calculate average power using standard equation
uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf)
{
	double p = ((Vrms/1000.0) * (Irms/1000.0) * (pf/1000.0));
	return (uint16_t)(p*1000);
}
