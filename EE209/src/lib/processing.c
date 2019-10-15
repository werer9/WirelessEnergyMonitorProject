// Author: Caelan Murch
// Project: ELECTENG209 Signal Processing Library
// Date: 23/08/2019

#include "processing.h"



void get_uart_string(uint16_t val, char *string, char ident)
{
	sprintf(string, "%c=%02.2i.%02.2i\n", ident, val/1000, (val%1000)/10);
}

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
uint16_t getPhaseDifference(uint16_t *crossTimes1, uint8_t size1, 
		uint16_t *crossTimes2, uint8_t size2) 
{
	uint16_t phaseDifference = 0;
	uint16_t Tz = 0;
	uint16_t Tp = 0;

	if (size1 < 3 || size2 < 3)
		return phaseDifference;

	if (crossTimes1[0] > crossTimes2[0]) {
		Tz = crossTimes2[0] - crossTimes2[2];
		Tp = crossTimes1[2] - crossTimes2[2];
	} else if (crossTimes1[0] < crossTimes2[0]) {
		Tz = crossTimes1[0] - crossTimes1[2];
		Tp = crossTimes2[2] - crossTimes1[2];
	}

	phaseDifference = 360 * (Tz/Tp);

	return phaseDifference;
}

// calculate power factor
uint16_t calculatePowerFactor(uint16_t phase) 
{
	phase *= (PI/180);
	return (cos(phase) * 1000);
}

// calculate average power using standard equation
uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf)
{
	double p = (Vrms/1000 * Irms/1000 * pf/1000);
	return (uint16_t)(p*1000);
}
