/*
 * LookUp.h
 *
 *  Created on: Dec 1, 2019
 *       Author: sankalp pund & saket penurkar
 */

#ifndef LOOKUP_H_
#define LOOKUP_H_

/*Header File*/

#include<math.h>
#include"fsl_debug_console.h"

/* Global Variables*/

uint32_t inc = 0;

/* Macros */

#define SIN_SAMPLES (50)

#define OFFSET_VOL (2)

#define PI (3.141592653589793238)

#define REF_BOARD_VOL (3.300)

#define SE_12BIT (4096.0)


/* Function Prototype*/

void gen_sin_sample();

uint32_t inc_sin_wave();

#endif /* LOOKUP_H_ */
