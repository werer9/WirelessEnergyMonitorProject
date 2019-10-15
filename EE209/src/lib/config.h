/*
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

// 9600 Baud rate
#define BAUD 9600

// pins
#define CURRENT_PIN 1 // Port C
#define VOLTAGE_PIN 0 // Port C
#define CURRENT_INTR 3 // port D
#define VOLTAGE_INTR 2 // port D

// Using macro for root 2 to save processing power on ATMEGA
#define ROOT_2 1.414213
// Using macro for PI
#define PI 3.14159

// array size
#define SIZE 50

// timer prescaler
#define TIMER_PRESCALER 256

// range on wave corresponding to 50 points, size*2
#define RANGE SIZE*2

// shunt resistor value for current calculations
#define SHUNT_VAL 33

// FSM STATES
#define STATE_INIT 0
#define STATE_READ_POWER 1
#define STATE_CALCULATE_POWER 2
#define STATE_TRANSMIT_POWER 3

#endif /* CONFIG_H_ */