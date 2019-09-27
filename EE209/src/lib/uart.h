/*
 * uart.h
 *
 * Created: 26/09/2019 10:08:35 PM
 *  Author: Caelan
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>

void uart_init(uint16_t ubrr);
void uart_transmit(uint8_t data);
void uart_write(char *data);
void uart_write_line(char *data);

#endif /* UART_H_ */