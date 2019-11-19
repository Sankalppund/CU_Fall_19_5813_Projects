/*
 * main.h
 *
 *  Created on: Nov 11, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "logger.h"
#include "Systick_timer.h"
#include "circular_buffer.h"
#include "fsl_debug_console.h"


#define NO_OF_ELEMENTS (100)

#define START_CRITICAL()	__disable_irq()
#define END_CRITICAL()		__enable_irq()

#define BAUD_RATE (9600)


/* Pass value '1' to enable logging */
/* Pass value '0' to disable logging */
#define LOG_ENABLE (1)
/*
 *  Choose the mode of the system
 *  Enter '0' for disabling the specific mode
 *  Enter '1' for enabling the specific mode
 */
#define APPLICATION_MODE (1)
#define ECHO_MODE        (0)
#define TEST_MODE        (0)
#define USE_UART_INTERRUPTS 	(1) // 0 for polled UART communications, 1 for interrupt-driven

circular_buffer*TSA;
void Test_Script();

#endif /* MAIN_H_ */
