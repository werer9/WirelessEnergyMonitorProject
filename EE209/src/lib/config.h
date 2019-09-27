/*
 * config.h
 *
 * Date: 26/9/19
 * Author: Caelan Murch
 * Description:
 * Header to define all values for the program
 * to make the software easier to maintain
*/



#ifndef CONFIG_H_
#define CONFIG_H_

// F_CPU set to 16MHz
#define F_CPU 16000000UL

// recommended UBBR for 9600 Baud rate
#define UBBR_SETTING 103

// pins
#define CURRENT_PIN 4 //TODO: update these to ATMEL pin values
#define VOLTAGE_PIN 5
#define CURRENT_INTR 0 // placeholder value
#define VOLTAGE_INTR 1 // placeholder value

// Using macro for root 2 to save processing power on ATMEGA
#define ROOT 1.414213
// Using macro for PI
#define PI 3.14159

// array size
#define SIZE 50

#endif /* CONFIG_H_ */