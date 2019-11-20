/*
 * unitTest.h
 *
 *  Created on: Oct 20, 2019
 *      Author: saket penurkar and sankalp pund
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

/* Header files*/

#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "circular_buffer.h"
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

void Buffer_Creation (void);
void Data_Access_Test (void);
void Verify_Wrap_Remove_test (void);
void Verify_Wrap_Add_test (void);
void Overfill_test (void);
void Overempty_test(void);
void Destroy_Buffer_Test(void);
void Resize_Buffer_Test(void);
void Buffer_Full_Test(void);
void Buffer_Empty_Test(void);
void Test_Script(void);

#endif /* UNITTEST_H_ */
