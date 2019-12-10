/*
 * main.h
 *
 *  Created on: Dec 1, 2019
 *      Author: sankalp pund and saket penurkar
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Standard includes. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"


/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "logger.h"
/********************************************************/
#include "circular_buffer.h"
#include "frts_task.h"
#include "dma.h"
/*******************************************************/

#define NO_OF_ELEMENTS (10)

/* Enable Program_1 by passing 1*/
#define PROGRAM_1 (0)

/* Enable Program_2 by passing 1*/
#define PROGRAM_2 (1)

/* Pass value '1' to enable logging */
/* Pass value '0' to disable logging */
#define LOG_ENABLE (1)

extern QueueHandle_t ADC_Buff;
extern QueueHandle_t dspBuffer;

#endif /* MAIN_H_ */
