/*
 * timer_driver.h
 *
 * Created: 3/10/2019 9:50:32 PM
 *  Author: Reeve D'Cunha and Caelan Murch
 */ 

#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

/**
 * \brief Intialise timer and its registers 
 * 
 * 
 * \return void
 */
void timer_init();
/**
 * \brief Set timer counter register 1 to 0
 * 
 * 
 * \return void
 */
void resetTimer();
/**
 * \brief Return value of timer 1 counter register
 * 
 * 
 * \return uint16_t Both timer counter 1 registers values
 */
uint16_t getTimerCount();
/**
 * \brief Calculate the time in uS based off clock scaler used
 * 
 * \param scale System clock prescaler used
 * 
 * \return uint32_t Elapsed time in uS
 */
uint32_t calculateTime(uint16_t scale);
/**
 * \brief Automatically call calculateTime with scale define in config.h
 * 
 * 
 * \return uint32_t Time in uS
 */
uint32_t get_time();


#endif /* TIMER_DRIVER_H_ */