/*
 * LookUp.h
 *
 *  Created on: Dec 1, 2019
 *       Author: sankalp pund & saket penurkar
 */

#ifndef LOOKUP_H_
#define LOOKUP_H_


#include<math.h>
#include"fsl_debug_console.h"


#define SIN_SAMPLES (50)

#define OFFSET_VOL (2)

#define PI (3.141592653589793238)

#define REF_BOARD_VOL (3.300)

#define SE_12BIT (4096.0)




void gen_sin_sample();

#endif /* LOOKUP_H_ */
