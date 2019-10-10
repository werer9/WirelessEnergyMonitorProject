// Author: Caelan Murch
// Project: ELECTENG209 Signal Processing Library
// Date: 23/08/2019

#include "processing.h"

// calculate UBRR value for given BAUD rate
uint16_t calculateUBRR(uint16_t baud)
{
	return (uint16_t)(F_CPU/(16*(unsigned long)baud) - 1);
}

void get_uart_string(uint16_t val, char *string, char ident)
{
	sprintf(string, "%c=%02d.%02d\n", ident, val/100, val%100);
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
// TODO: process with level cross trigger times
// since these are more accuratemake
uint16_t getPhaseDifference(uint16_t *crossTimes1, uint8_t size1, 
		uint16_t *crossTimes2, uint8_t size2) 
{
	uint16_t phaseDifference = 0;
	uint16_t Tz, Tp = 0;

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
	return (cos(phase) * 100);
}

// calculate average power using standard equation
uint16_t calculateAveragePower(uint16_t Vrms, uint16_t Irms, uint16_t pf)
{
	return Vrms * Irms * pf;
}
