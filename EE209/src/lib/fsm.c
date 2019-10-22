/*
* Date: 26/9/19
* Author: Caelan Murch and Reeve D'Cunha
* Description: Finite State Machine
*/

#include "fsm.h"

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
    functions->int_init(voltageTriggerTimes, currentTriggerTimes, TRIGGER_SIZE, functions->get_time);
    // change state on function completion
    state = STATE_READ_POWER;
}

void stateReadPower()
{
    // enable interrupts and reset timer
    
    for (int8_t j = 0; j < SIZE; j++) {
		voltages[j] = functions->read_adc(VOLTAGE_PIN);
        currents[j] = functions->read_adc(CURRENT_PIN);
    }

	functions->timer_reset();
	functions->enable_interrupts();
	while (functions->get_trigger_index() < TRIGGER_SIZE) {}
	
    // disable interrupts - prevent the trigger array from overflowing
    functions->disable_interrupts();
    
    // need to add condition for state change
    state = STATE_CALCULATE_POWER;
}

void stateCalculatePower()
{  
    // calculate peak, RMS
    peakVoltage = functions->find_peak(voltages, SIZE, VOLTAGE_PIN, functions->read_adc);
    peakCurrent = functions->find_peak(currents, SIZE, CURRENT_PIN, functions->read_adc);
    voltage = functions->calculate_RMS(peakVoltage);
    current = functions->calculate_RMS(peakCurrent);

    // calculate phase of two signals
    phase = functions->get_phase_difference(voltageTriggerTimes, currentTriggerTimes, TRIGGER_SIZE);
    
    // place holder phase
    pf = functions->calculate_power_factor(phase);
    power = functions->calculate_average_power(voltage, current, pf);
    
    // start iterating over the trigger arrays from zero
    // this effectively resets the array
    voltageTriggerIndex = 0;
    currentTriggerIndex = 0;
	
	// reset interrupt trigger array index
	functions->set_trigger_index(voltageTriggerIndex);
   
    // new state needed to be added for correct transition
    state = STATE_TRANSMIT_POWER;
}

void stateTransmitPower()
{
    char dataString[16];
    functions->get_uart_string(power, dataString, 'P');
    functions->uart_write(dataString);
	functions->get_uart_string(pf, dataString, 'F');
	functions->uart_write(dataString);
	functions->get_uart_string(peakVoltage, dataString, 'V');
	functions->uart_write(dataString);
	functions->get_uart_string(current, dataString, 'I');
	functions->uart_write(dataString);

    state = STATE_READ_POWER;
}