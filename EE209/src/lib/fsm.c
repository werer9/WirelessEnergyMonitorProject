/*
* Date: 26/9/19
* Author: Caelan Murch and Reeve D'Cunha
* Description: Finite State Machine
*/

#include "fsm.h"

// initialis fsm with function pointers
void fsmInit(struct functionPointers *fsmFunctions) 
{
    functions = fsmFunctions;
    state = STATE_INIT;
    voltageTriggerIndex = 0;
    currentTriggerIndex = 0;
	
	triggerSize = 0;
	peakVoltage = 0;
	peakCurrent = 0;
	voltage = 0;
	current = 0;
	phase = 0;
	pf = 0;
	power = 0;
}
// main fsm function
int run()
{ 
    while (1) {
        switch(state) {
            case STATE_INIT:
                // set this to correct ubbr
                stateInit();
                break;
            case STATE_READ_POWER:
                // read data from adc and store it
                stateReadPower();
                break;
            case STATE_CALCULATE_POWER:
                // use data from adc to calculate power
                stateCalculatePower();
                break;
            case STATE_TRANSMIT_POWER:
                // send power to bt module with uart
                stateTransmitPower();
                break;
            default:
                // if state is not set, return 1 to main function
                return 1;
                break;
        }
    }

    return 0;
}

// init state
void stateInit()
{
    // init uart
    functions->uart_init(BAUD);
    // init io
    functions->io_init();
    // init adc
    functions->adc_init();
    // init timer
    functions->timer_init();
    // init interrupts
    functions->int_init(voltageTriggerTimes, currentTriggerTimes, SIZE, functions->get_time);
    // change state on function completion
    state = STATE_READ_POWER;
}

// read power state
void stateReadPower()
{
    // enable interrupts and reset timer
	functions->timer_reset();
	//functions->timer_init();
    functions->enable_interrupts();
    for (int8_t j = 0; j < SIZE; j++) {
		voltages[j] = functions->read_adc(VOLTAGE_PIN);
        //voltageTimes[j] = functions->get_time();
        currents[j] = functions->read_adc(CURRENT_PIN);
        //currentTimes[j] = functions->get_time();
    }

    // disable interrupts - prevent the trigger array from overflowing
    functions->disable_interrupts();

    // possible change the implementation to avoid interrupts by setting a 
    // volatile boolean with an int
    
    // need to add condition for state change
    state = STATE_CALCULATE_POWER;
}

// calculate power state
void stateCalculatePower()
{  
    // calculate peak, RMS
    peakVoltage = functions->find_peak(voltages, SIZE);
    peakCurrent = functions->find_peak(currents, SIZE);
    voltage = functions->calculate_RMS(peakVoltage);
    current = functions->calculate_RMS(peakCurrent);

    // calculate phase of two signals
    phase = functions->get_phase_difference(voltageTriggerTimes, voltageTriggerIndex,
            currentTriggerTimes, currentTriggerIndex);
    
    // place holder phase
    pf = functions->calculate_power_factor(phase);
    power = functions->calculate_average_power(voltage, 
            current, pf);
    
    // start iterating over the trigger arrays from zero
    // this effectively resets the array
    voltageTriggerIndex = 0;
    currentTriggerIndex = 0;
    
	// reset interrupt handler
	//functions->int_init(voltageTriggerTimes, currentTriggerTimes, SIZE, functions->get_time);
    // new state needed to be added for correct transition
    state = STATE_TRANSMIT_POWER;
}

// transmit the power over UART
void stateTransmitPower()
{
    char dataString[16];
    functions->get_uart_string(power, dataString, 'P');
    functions->uart_write(dataString);
	functions->get_uart_string(pf, dataString, 'F');
	functions->uart_write(dataString);
	functions->get_uart_string(voltage, dataString, 'V');
	functions->uart_write(dataString);
	functions->get_uart_string(current, dataString, 'I');
	functions->uart_write(dataString);

    state = STATE_READ_POWER;
}