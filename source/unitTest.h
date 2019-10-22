/*
 * unitTest.h
 *
 *  Created on: Oct 20, 2019
 *      Author: saket penurkar and sankalp pund
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_


#include "stddef.h"
#include "stdint.h"
#include "ss_memory_suite.h"
#include "SS_PatternGeneration.h"
#include "main.h"
#include "../ucunit-master/v1.0.1/uCUnit-v1.0.h"
#include "../ucunit-master/v1.0.1/System.h"

/*
 * Macros
 */
#define TEST_ALLOCATE_WORD_SIZE (16)
#define LOWER_HEAP_LIMIT        (0x1FFFF6B8)
#define UPPER_HEAP_LIMIT        (0x1FFFFAB8)



/*
 * Function Prototypes
 */

void Test_Case_1_isEqual (void);
void Test_Case_2_inRange (void);
void Test_Case_3_isBitSet (void);
void Test_Case_4_isBitClear (void);
void Test_Case_5_is8Bit (void);
void Test_Case_6_is16Bit (void);
void Test_Case_7_is32Bit (void);
void Test_Case_8_isNull (void);
void Test_Case_9_isNotNull (void);
void Test_Case_10_status(void);
void Test_Case_Script(void);

#endif /* UNITTEST_H_ */
