/*
 * adc.c
 *
 * Created: 26/09/2019 10:08:10 PM
 *  Author: Caelan
 */ 

#include "adc.h"

uint16_t read_adc(uint8_t channel)
{
	// clear ADMUX
	ADMUX &= 0xF0;
	// set least significant 4 bits to channel
	ADMUX |= channel;
	// start conversion
	ADCSRA |= (1<<ADSC);
	// wait until conversion is finished
	while (ADCSRA & (1<<ADSC));
	
	// read full 10 bits of ADC registers
	uint16_t adc_output = ADCW;
	// convert reading into millivolts
	return adc_output;
}


void adc_init() 
{
	// set ADMUX to read from VCC
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	// clear channel selection
	ADMUX &= 0xF0;
	// enable conversions, scale by system clock by 128
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
}