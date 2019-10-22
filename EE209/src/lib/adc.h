/*
 * adc.h
 *
 * Created: 26/09/2019 10:08:00 PM
 *  Author: Caelan
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <avr/interrupt.h>

/**
	\brief Read ADC value
	
	\param channel Select the ADC channel to read from
	
	\return uint16_t ADC registers value
*/
uint16_t read_adc(uint8_t channel);

/**
	\brief Enable the ADC and set the VCC as its reference
	
	The ADC clock is set to 125kHz
	VCC is used as the ADC reference
	
	\return void
*/
void adc_init();

#endif /* ADC_H_ */