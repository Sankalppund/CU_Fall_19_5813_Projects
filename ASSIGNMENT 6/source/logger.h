/*
 * logger.h
 *
 *  Created on: Nov 04, 2019
 *  Author: Saket penurkar & Sankalp pund
 */

#ifndef LOGGER_H_
#define LOGGER_H_

/* Header files */

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Systick_timer.h"
#include "fsl_debug_console.h"

/* Logger Functionality for KL25Z */

#define KL25Z

#define SEC_IN_HOUR (3600)
#define SEC_IN_MIN (60)

/* Enumeration to set Modes of operation*/

typedef enum
{
	LOG_TEST,
	LOG_DEBUG,
	LOG_STATUS
}Logging_Level_m;


/* Enumeration for functions used*/

typedef enum
{
	MAIN,
	ADC_INIT_FUNC,
	ADC_TASK,
	CALCULATE,
	DAC_INIT_FUNC,
	DAC_TASK,
	READ_ADC_FUNC,
	WRITE_DAC_FUNC,
	DMA_CALLBACK,
	DMA_INITIALIZE,
	DMA_ONE_SHOT_TRANSFER,
	GEN_SINE_SAMPLE,
	INC_SINE_WAVE,
	LED_INITIALIZE,
	LED_OFF_FUNC,
	LED_DELAY,
	LED_RED_FUNC,
	LED_GREEN_FUNC,
	LED_BLUE_FUNC,
	INIT_SYSTICK
}Function_Name_m;

/* Function Prototypes */

void Log_enable(void);
void Log_disable(void);
bool Log_status(void);
void Log_level(Logging_Level_m);    // function to set the log level
void Log(Logging_Level_m, Function_Name_m, const char *);
void Log_integer(int Int_Var);
const char* Function_Printed_in_Log(Function_Name_m);
void time_stamp();

#endif /* LOGGER_H_ */
