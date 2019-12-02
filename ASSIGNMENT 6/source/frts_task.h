/*
 * frts_task.h
 *
 *  Created on: Dec 1, 2019
 *       Author: sankalp pund & saket penurkar
 */

#ifndef FRTS_TASK_H_
#define FRTS_TASK_H_

#include <stdlib.h>
#include "circular_buffer.h"
#include "logger.h"
#include "LookUp.h"
#include "ADC_DAC.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "dma.h"


#define BUFFER_SIZE (64)

extern uint16_t count;

circular_buffer*ADC_Buff;

circular_buffer*DSP_Buff;


void soft_timer();

void DAC_time_callback(TimerHandle_t);

void ADC_time_callback(TimerHandle_t);

#endif /* FRTS_TASK_H_ */
