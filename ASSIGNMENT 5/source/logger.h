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
//#include "fsl_debug_console.h"
#include "Systick_timer.h"

/* Logger Functionality for KL25Z */

#define KL25Z

#define SEC_IN_HOUR (3600)
#define SEC_IN_MIN (60)

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
	ADD_NEW,
	INIT_SYSTICK,
	SYSTICK_HANDLER,
	APPLICATION_REPORT,
	CHAR_COUNT,
	INITIALIZE_BUFFER,
	REMOVE_OLD,
	BUFFER_FULL_CHECK,
	BUFFER_EMPTY_CHECK,
	DESTROY_BUFFER,
	BUFFER_VALIDATION,
	VERIFY_INITIALIZATION,
	RESIZE_BUFFER,
	INIT_UART0,
	UART_TRANSMIT,
	UART_RECEIVE,
	TRANSMITTER_WAIT,
	RECEIVER_WAIT,
	POLLING_ECHO,
	POLLING_APPLICATION,
	INTERRUPT_ECHO,
	INTERRUPT_APPLICATION
}Function_Name_m;

/* Function Prototypes used in Project 3 */
void Log_enable(void);
void Log_disable(void);
bool Log_status(void);

/* Function Prototypes used in Project 4 */
void Log_level(Logging_Level_m);    // function to set the log level
void Log(Logging_Level_m, Function_Name_m, const char *);
void Log_integer(int Int_Var);
const char* Function_Printed_in_Log(Function_Name_m);
void time_stamp();

#endif /* LOGGER_H_ */
