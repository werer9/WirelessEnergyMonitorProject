/*
 * uart.c
 *
 * Created: 26/09/2019 10:08:44 PM
 *  Author: Caelan
 */ 
#include "uart.h"

void get_uart_string(uint16_t val, char *string, char ident)
{
	double value = 0;
	// determine type of value
	// all values except for current
	// are converted to doubles
	switch (ident) {
		case 'V':
			value = (double)((double)val/1000);
			sprintf(string, "%c=%.4g\n", ident, value);
			break;
		case 'I':
			sprintf(string, "%c=%04u\n", ident, val);
			break;
		case 'F':
			value = (double)((double)val/1000);
			sprintf(string, "%c=%.4g\n", ident, value);
			break;
		case 'P':
			value = (double)((double)val/1000);
			sprintf(string, "%c=%.4g\n", ident, value);
			break;
	}
}

uint16_t calculateUBRR(uint16_t baud)
{
	return (uint16_t)(F_CPU/(16*(unsigned long)baud) - 1);
}

void uart_init(uint16_t baud)
{	
	uint16_t ubrr = calculateUBRR(baud);
	// Enable TX and RX
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	// set character size to 8-bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0C &= ~(1<<UPM00);
	UCSR0C &= ~(1<<UPM01);
	// Set the baud rate
	UBRR0 = ubrr;
}

void uart_transmit(uint8_t data)
{
	// wait until transmitter is ready
	while ((1<<UDRE0 & UCSR0A) == 0x00) {;} // do nothing
	// transmit data
	UDR0 = data;
}

void uart_write(char *data) 
{
	int i = 0;
	while (data[i] != '\0') {
		uart_transmit(data[i]);
		i++;
	}
	
	_delay_ms(75);
}

void uart_write_line(char *data)
{
	uart_write(data);
	uart_write("\r\n");
}