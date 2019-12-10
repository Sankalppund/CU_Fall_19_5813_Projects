/*
 * frts_task.h
 *
 *  Created on: Dec 1, 2019
 *       Author: sankalp pund & saket penurkar
 */

#ifndef FRTS_TASK_H_
#define FRTS_TASK_H_

/*Header Files*/

#include <stdlib.h>
#include "circular_buffer.h"
#include "fsl_debug_console.h"
#include "logger.h"
#include "LookUp.h"
#include "ADC_DAC.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "timers.h"
#include "dma.h"
#include "ss_led_control.h"
#include "main.h"

/*Global Variables*/

extern SemaphoreHandle_t project_mutex;

#define RSL (3.30/4096.00)

extern uint16_t count;

uint8_t NEXT_SAMPLES = 0;

uint8_t adc_read_counter = 0;

uint16_t adc_read_val = 0;

uint32_t minV = 65535;

uint32_t maxV = 0;

uint32_t addition = 0;

uint32_t St_Deviation = 0;

float number[64];

float minimum_val;

float maximum_val;

float average_val;

float St_deviation_val;

uint8_t counter = 0;

TaskHandle_t DSPHandle;



/* Function Prototype*/

void soft_timer_Init();

void DAC_time_callback(TimerHandle_t);

void DAC_time_call();

void ADC_time_callback(TimerHandle_t);

void get_ticks(TimerHandle_t);

void DacTask(void*);

void AdcTask(void*);

void calculate(void*);

void dsp_calculation();

#endif /* FRTS_TASK_H_ */
