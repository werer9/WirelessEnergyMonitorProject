/*
 * adc.c
 *
 * Created: 26/09/2019 10:08:10 PM
 *  Author: Caelan
 */ 

#include "adc.h"

uint8_t read_adc(uint8_t channel)
{
	ADMUX &= 0xF0;
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return ADCH;
}

void adc_init() 
{
	ADMUX |= (1<<REFS0) | (1<<ADLAR);
	ADMUX &= ~(1<<REFS1);
	ADMUX &= ~(1<<MUX3) | ~(1 << MUX2) | ~(1<<MUX1) | ~(1<<MUX0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADSC);
}