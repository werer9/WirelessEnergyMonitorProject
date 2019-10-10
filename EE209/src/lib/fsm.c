/*
* Date: 26/9/19
* Author: Caelan Murch
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
    // init interrupts
    functions->int_init(values.voltageTriggerTimes, values.currentTriggerTimes, SIZE, functions->get_time);
    // change state on function completion
    state = STATE_READ_POWER;
}

// read power state
void stateReadPower()
{
    // enable interrupts
    functions->enable_interrupts();
    // loop until voltages and currents full
    for (int i = 0; i < SIZE; i++) {
        values.voltages[i] = functions->read_adc(VOLTAGE_PIN);
        values.voltageTimes[i] = functions->get_time();
        values.currents[i] = functions->read_adc(VOLTAGE_PIN);
        values.currentTimes[i] = functions->get_time();
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
    values.peakVoltage = findPeak(values.voltages, SIZE);
    values.peakCurrent = findPeak(values.currents, SIZE);
    values.voltage = calculateRMS(values.peakVoltage);
    values.current = calculateRMS(values.peakCurrent);

    // calculate phase of two signals
    values.phase = getPhaseDifference(values.voltageTriggerTimes, voltageTriggerIndex,
            values.currentTriggerTimes, currentTriggerIndex);
    
    // place holder phase
    values.pf = calculatePowerFactor(values.phase);
    values.power = calculateAveragePower(values.voltage, 
            values.current, values.pf);
    
    // start iterating over the trigger arrays from zero
    // this effectively resets the array
    voltageTriggerIndex = 0;
    currentTriggerIndex = 0;
    
	// reset interrupt handler
	functions->int_init(values.voltageTriggerTimes, values.currentTriggerTimes, SIZE, functions->get_time);
    // new state needed to be added for correct transition
    state = STATE_TRANSMIT_POWER;
}

// transmit the power over UART
void stateTransmitPower()
{
    char dataString[16];
    functions->get_uart_string(values.power, dataString, 'P');
    functions->uart_write(dataString);
	functions->get_uart_string(values.pf, dataString, 'F');
	functions->uart_write(dataString);
	functions->get_uart_string(values.voltage, dataString, 'V');
	functions->uart_write(dataString);
	functions->get_uart_string(values.current, dataString, 'I');
	functions->uart_write(dataString);

    state = STATE_READ_POWER;
}