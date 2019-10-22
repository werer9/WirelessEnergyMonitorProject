/*
 * uart.h
 *
 * Created: 26/09/2019 10:08:35 PM
 *  Author: Caelan
 */ 


#ifndef UART_H_
#define UART_H_
#include "config.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

/**
	\brief Return a string to be printed to UART that complies with the base station protocol
	
	\param val Measure value to be transmitted
	\param string String to be used for formatting and UART
	\param ident Letter identifying which value is being sent
				 V = Voltage, I = Current, F = Power Factor, P = Average Power
				 
	\return void
*/
void get_uart_string(uint16_t val, char *string, char ident);

/**
	\brief Calculate UBRR register value for clock speed
	
	\param baud Baud rate
	
	\return uint16_t UBRR setting
*/
uint16_t calculateUBRR(uint16_t baud);

/**
	\brief Initialise the UART with specified baud rate
	
	This will configure the UART registers to use 8-bit packets, no parity
	and one stop bit
	
	\param baud Baud rate
	
	\return void
*/
void uart_init(uint16_t ubrr);

/**
	\brief Transmit single character over UART
	
	\param data Character to be transmitted
	
	\return void
*/
void uart_transmit(uint8_t data);

/**
	\brief Write string to UART
	
	Uses uart_transmit to send each character in string via UART
	
	\param data String to be transmitted
	
	\return void
*/
void uart_write(char *data);

/**
	\brief Write line to UART
	
	Uses uear_write to send string with "/r/n" appended to the end
	
	\param data String to be transmitted
	
	\return void
*/
void uart_write_line(char *data);

#endif /* UART_H_ */