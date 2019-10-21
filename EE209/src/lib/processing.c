// Author: Caelan Murch
// Project: ELECTENG209 Signal Processing Library
// Date: 23/08/2019

#include "processing.h"




// convert adc value to real value
uint16_t convertADCValue(uint16_t sample, uint16_t maxVal, uint8_t bits)
{
	return (uint16_t)sample/pow(2,bits) * maxVal;
}

// find peak value of sinusoidal wave
uint16_t findPeak(uint16_t *samples, uint8_t size)
{
	uint16_t peak = 0;
	// iterate over samples and use largest value as peak
	for (uint8_t i = 0; i < size; i++) {
		if (samples[i] > peak)
			peak = samples[i];
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
