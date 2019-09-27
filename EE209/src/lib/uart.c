/*
 * uart.c
 *
 * Created: 26/09/2019 10:08:44 PM
 *  Author: Caelan
 */ 
#include "uart.h"

// uart init function
void uart_init(uint16_t ubrr)
{
	// Enable TX and RX
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	// set character size to 8-bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0C &= ~(1<<UPM00);
	UCSR0C &= ~(1<<UPM01);
	// Set the baud rate
	UBRR0 = ubrr;
}

// uart transmit function
void uart_transmit(uint8_t data)
{
	// wait until transmitter is ready
	while ((1<<UDRE0 & UCSR0A) == 0x00) {;} // do nothing
	// transmit data
	UDR0 = data;
}

// uart write function
// write multiple characters at once
void uart_write(char *data) 
{
	int i = 0;
	while (data[i] != '\0') {
		uart_transmit(data[i]);
		i++;
	}
}

// uart write line function
// write multiple characters at once on one line
void uart_write_line(char *data)
{
	uart_write(data);
	uart_write("\r\n");
}