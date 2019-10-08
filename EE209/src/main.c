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

#include <util/delay.h>
#include <stdio.h>


int main(void)
{
    //uart_init(UBBR_SETTING);
	//adc_init();
	//DDRC |= 0xFF;
	//DDRC &= ~(1<<0) & ~(1<<1);
	//uint16_t data = 0;
	//char output[255] = "";
    //while (1) 
    //{
		//data = read_adc_mv(0);
		//snprintf(output, 255, "%u", data);
		//uart_write(output);
		//uart_write(" ");
		//data = read_adc_mv(1);
		//snprintf(output, 255, "%u", data);
		//uart_write_line(output);
    //}
	
	uart_init(UBBR_SETTING);
	timer1Init();
	uint16_t time;
	char timeStr[255];
	
	sei();
	
	while (1) {
		//if (timer0_checkAndClearOverflow()) {
			//PORTB |= (1<<PINB5);
		//}
		//time = calculateTime1(1024);
		time = timer1OverFlowCount;
		snprintf(timeStr, 255, "%u", time);
		uart_write_line(timeStr);
		//_delay_ms(1000);
		//_delay_ms(1000);
	}
}

