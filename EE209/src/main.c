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
#include <util/delay.h>
#include <stdio.h>


int main(void)
{
    uart_init(UBBR_SETTING);
	adc_init();
	DDRC |= 0xFF;
	DDRC &= ~(1<<PC0) & ~(1<<PC1);
	uint16_t data = 0;
	char output[255] = "";
    while (1) 
    {
		data = read_adc_mv(0);
		snprintf(output, 255, "%u", data);
		uart_write(output);
		uart_write(" ");
		data = read_adc_mv(1);
		snprintf(output, 255, "%u", data);
		uart_write_line(output);
    }
}

