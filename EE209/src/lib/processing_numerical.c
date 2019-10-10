// Author: Reeve D'Cunha

#include "processing_numerical.h"

// calculate UBRR value for given BAUD rate
uint16_t calculate_UBRR(uint16_t baud)
{
	return (uint16_t)(F_CPU/(16*(unsigned long)baud) - 1);
}

// convert adc value to real value
uint16_t convert_ADC_value(uint16_t sample, uint16_t maxVal, uint8_t bits)
{
	return (uint16_t)sample/pow(2,bits) * maxVal;
}

// uses RMS definition to calculate Vrms
uint16_t get_voltage_rms(uint16_t* voltageArray, uint8_t size){
    uint32_t sumVoltageSquared = 0;

    //sum instantaneous voltages
    for (uint8_t i = 0; i < size ; i++){
        sumVoltageSquared += (uint32_t)(voltageArray[i]*voltageArray[i]);
    }

    //V^2 = sum/(number of samples)
    uint32_t voltageRMSsquared = (sumVoltageSquared/size);

    return (uint16_t)sqrt(voltageRMSsquared);
}

//returns peak 
uint16_t get_voltage_peak(uint16_t voltageRMS){

    return voltageRMS*ROOT_2;
}

//returns RMS current
uint16_t get_current_rms(uint16_t voltageRMS, uint16_t shunt_val){

    return voltageRMS/shunt_val;
}

/* 
Calculates and returns average power
*/
uint16_t get_avg_power(uint16_t vRMS, uint16_t iRMS, uint16_t pf)
{
    return vRMS * iRMS * pf;
}

uint8_t get_pf(uint16_t avgPower, uint16_t vRMS, uint16_t iRMS){
    return avgPower/(vRMS*iRMS);
}

/**
 * Old numerical integration function....
 * found to be redundant
 * **/
/* Integrates a given array of points using Simpon's rule
   Requires step size and the array being integrated
// */
// uint16_t numerical_integration(uint8_t stepSize, uint16_t *pointsArray, uint8_t size){

//     //initially add FIRST and LAST values
//     uint16_t sums = pointsArray[0] + pointsArray[size-1];

//     for (uint8_t i = 1; i < size - 2; i++){
//         if (i % 2 == 0){
//             //multiply EVENS by 2
//             sums += pointsArray[i]*2;
//         } else if (i % 2 == 1){
//             //multiply ODDS by 4
//             sums += pointsArray[i]*4;
//         }
//     }

//     return (stepSize/3)*sums;
// }


