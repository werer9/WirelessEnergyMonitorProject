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

// gpio dirver
#include "lib/gpio.h"

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
		.io_init = io_init,
		.adc_init = adc_init,
		.timer_init = timer_init,
		.int_init = interrupt_init,
		.get_trigger_index = get_index,
		.set_trigger_index = set_index,
		.get_uart_string = get_uart_string,
		.uart_write = uart_write,
		.disable_interrupts = disable_interrupts,
		.enable_interrupts = enable_interrupts,
		.read_adc = read_adc_mv,
		.get_time = get_time,
		.timer_reset = resetTimer,
		.find_peak = findPeak,
		.calculate_RMS = calculateRMS,
		.get_phase_difference = getPhaseDifference,
		.calculate_power_factor = calculatePowerFactor,
		.calculate_average_power = calculateAveragePower,
	};
	
	
	// init fsm by passing structs to it
	fsmInit(&funcs);
	
	run();
}

