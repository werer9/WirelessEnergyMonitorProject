/*
 * adc.c
 *
 * Created: 26/09/2019 10:08:10 PM
 *  Author: Caelan
 */ 

#include "adc.h"


uint16_t read_adc_mv(uint8_t channel)
{
	ADMUX &= 0xF0;
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	uint16_t adc_output = ADCW;
	uint32_t mv = (uint32_t)adc_output * ((uint32_t)5000/1023);
	return (uint16_t)mv;
}

void adc_init() 
{
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	ADMUX &= ~(1<<MUX3) & ~(1 << MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADSC);
}