/*
 * EE209.c
 *
 * Created: 26/09/2019 10:02:27 PM
 * Author : Caelan Murch
 */ 

// config header
#include "lib/config.h"

// uart driver
#include "lib/uart.h"
#include "lib/adc.h"

// timer driver
#include "lib/timer_driver.h"

// interrupt handler
#include "lib/interrupt.h"

// processing functions
#include "lib/processing.h"

// finite state machines
#include "lib/fsm.h"

int main(void) 
{
	// create function pointer struct
	struct functionPointers funcs = {
		.uart_init = uart_init,
		.io_init = 0,
		.adc_init = adc_init,
		.int_init = interrupt_init,
		.get_uart_string = get_uart_string,
		.uart_write = uart_write,
		.disable_interrupts = disable_interrupts,
		.enable_interrupts = enable_interrupts,
		.read_adc = read_adc_mv,
		.get_time = 0,
	};
	
	
	// init fsm by passing structs to it
	fsmInit(&funcs);
	
	return run();
}

