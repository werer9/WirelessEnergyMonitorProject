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
uint16_t read_adc_mv(uint8_t channel);
void adc_init();

#endif /* ADC_H_ */