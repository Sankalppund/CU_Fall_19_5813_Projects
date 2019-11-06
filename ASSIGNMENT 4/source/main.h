/*
 * main.h
 *
 *  Created on: Nov 2, 2019
 *      Author: Sankalp Pund & Saket Penurkar
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Pass value '1' to enable Test Mode */
/* Pass value '0' to disable Test Mode */
#define TEST_MODE (0)

/* Pass value '1' to enable logging */
/* Pass value '0' to disable logging */
#define LOG_ENABLE (1)


/*
 * Headers Section
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "I2C.h"
#include "logger.h"
#include "POST_Test.h"

#endif /* MAIN_H_ */
