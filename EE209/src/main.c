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
    while (1) 
    {
		uart_write_line("EE209");
    }
}

