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


int main(void)
{
    uart_init(UBBR_SETTING);
	adc_init();
	uint16_t data;
    while (1) 
    {
		data = read_adc(0);
		uart_write_line("Channel 0:");
		uart_write_line(calculate_original_value(8, 5000, 0, data));
		data = read_adc(1);
		uart_write_line("Channel 1:")
		uart_write_line(calculate_original_value(8, 5000, 0, data));
    }
}

