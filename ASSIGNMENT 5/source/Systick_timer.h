/*
 * Systick_timer.h
 *
 *  Created on: Nov16, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_

#include "logger.h"

void Init_SysTick(void);
uint64_t current_time();


#endif /* SYSTICK_TIMER_H_ */
