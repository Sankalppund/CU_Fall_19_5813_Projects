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
#include "fsl_debug_console.h"

/* Logger Functionality for KL25Z */

#define KL25Z

typedef enum
{
	LOG_TEST,
	LOG_DEBUG,
	LOG_STATUS
}Logging_Level_m;


// write enum for the functions used in the program
typedef enum
{
	MAIN,
	I2C_CONFIG,
	I2C_WRITE_DATA,
	I2C_READ_DATA,
	INIT_SYSTICK,
	SYSTICK_HANDLER,
	POST_TEST,
	AVERAGE_TEMPERATURE,
	STATE_MACHINE,
	TEMP_READING_STATE,
	AVERAGE_WAIT_STATE,
	TEMP_ALERT_STATE,
	DISCONNECTED_STATE,
	CHECK_DISCONNECT_EVENT,
	END_STATE,
	TABLE_STATE_MACHINE,
	TRANSITION_IN_TABLE
}Function_Name_m;

/* Function Prototypes used in Project 3 */
void Log_enable(void);
void Log_disable(void);
bool Log_status(void);

/* Function Prototypes used in Project 4 */
void Log_level(Logging_Level_m);    // function to set the log level
void Log(Logging_Level_m, Function_Name_m, const char *);
const char* Function_Printed_in_Log(Function_Name_m);

#endif /* LOGGER_H_ */
