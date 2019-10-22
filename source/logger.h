/*
 * logger.h
 *
 *  Created on: Oct 22, 2019
 *      Author: saket penurkar & sankalp pund
 */

/* Header files */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fsl_debug_console.h"

#ifndef LOGGER_H_
#define LOGGER_H_


/* Logger Functionality for PC Host and KL25Z */

#define KL25Z



/* Function Prototype */

void Log_enable(void);
void Log_disable(void);
bool Log_status(void);
void Log_data(uint8_t * Start_address, size_t size_of_array);
void Log_string(const char * strint_to_be_printed);
void Log_integer(int);





#endif /* LOGGER_H_ */
