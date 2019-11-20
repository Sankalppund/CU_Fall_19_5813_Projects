/*
 * main.h
 *
 *  Created on: Nov 11, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Header files */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "logger.h"
#include "Systick_timer.h"
#include "circular_buffer.h"

/* Enter No of elements to be added in circular buffer */

#define NO_OF_ELEMENTS (100)

/*macro functions to disable and enable interrupts*/

#define START_CRITICAL()	__disable_irq()
#define END_CRITICAL()		__enable_irq()

/* Enter the BAUD Rate */

#define BAUD_RATE (9600)


/* Pass value '1' to enable logging */
/* Pass value '0' to disable logging */

#define LOG_ENABLE (1)

/*
 *  Choose the mode of the system
 *  Enter '0' for disabling the specific mode
 *  Enter '1' for enabling the specific mode
 */

#define APPLICATION_MODE (0)
#define ECHO_MODE        (1)
#define TEST_MODE        (0)

/* Enter '0' for Polling mode
 * Enter '1' for Interrupt Mode
 */

#define USE_UART_INTERRUPTS (0)

circular_buffer*TSA;

void Test_Script();

#endif /* MAIN_H_ */
