/*
 * unitTest.c
 *
 *  Created on: Oct 20, 2019
 *      Author: saket penurkar and sankalp pund
 *
 *      Reference - https://mcuoneclipse.com/2018/08/26/tutorial-μcunit-a-unit-test-framework-for-microcontrollers/
 */


#include "unitTest.h"
extern uint32_t * Global_BSA_Test;

/*
 * Function Name - Test_Case_1_isEqual
 * Description - This function is used to test whether the block assigned by malloc is equal
 * Inputs - none
 * Return Value - none
 */
void Test_Case_1_isEqual (void)
{


	  UCUNIT_TestcaseBegin("Allocate Word Size");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIsEqual(Test_Block_Start_Address, Global_BSA_Test);
	  UCUNIT_TestcaseEnd();
	  /* finish all the tests */
	  UCUNIT_WriteSummary();

}


/*
 * Function Name - Test_Case_2_inRange
 * Description - This function is used to test whether the assigned memory is in range
 * Inputs - none
 * Return Value - none
 */
void Test_Case_2_inRange (void)
{
	  UCUNIT_TestcaseBegin("Allocate Word Size_Range");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIsInRange(allocate_words(TEST_ALLOCATE_WORD_SIZE), LOWER_HEAP_LIMIT, UPPER_HEAP_LIMIT);
	  UCUNIT_TestcaseEnd();
	  /* finish all the tests */
	  UCUNIT_WriteSummary();
}

/*
 * Function Name - Test_Case_3_isBitSet
 * Description - This function is used to test whether a bit is set in the result
 * Inputs - none
 * Return Value - none
 */
void Test_Case_3_isBitSet (void)
{
	  UCUNIT_TestcaseBegin("Getting Address_BitSet");
	  uint32_t * Test_Address = get_address(Global_BSA_Test, 4);
	  UCUNIT_CheckIsBitSet(Test_Address[4], 7); /* check if bit 7 set */
	  UCUNIT_TestcaseEnd();
	  /* finish all the tests */
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_4_isBitClear
 * Description - This function is used to test whether a particular bit is set in the returned address's value
 * Inputs - none
 * Return Value - none
 */
void Test_Case_4_isBitClear (void)
{
	  UCUNIT_TestcaseBegin("Getting Address_BitClear");
	  uint32_t * Test_Address = get_address(Global_BSA_Test, 4);
	  UCUNIT_CheckIsBitClear(Test_Address[4], 7); /* check if bit 7 cleared */
	  UCUNIT_TestcaseEnd();
	  /* finish all the tests */
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_5_is8Bit
 * Description - This function is used to test whether the returned address's value is 8 bit address
 * Inputs - none
 * Return Value - none
 */
void Test_Case_5_is8Bit (void)
{

	  UCUNIT_TestcaseBegin("Allocated address_8Bit");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIs8Bit(Test_Block_Start_Address[4]); /* check if not larger then 8 bit */
	  UCUNIT_TestcaseEnd();

	  /* finish all the tests */
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_6_is16Bit
 * Description - This function is used to test whether the returned address's value is a 16 bit address
 * Inputs - none
 * Return Value - none
 */
void Test_Case_6_is16Bit (void)
{
	  UCUNIT_TestcaseBegin("Allocated address_16Bit");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIs16Bit(Test_Block_Start_Address[5]); /* check if not larger then 16 bit */
	  UCUNIT_TestcaseEnd();

	  /* finish all the tests */
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Test_Case_7_is32Bit
 * Description - This function is used to test whether the returned address's value is a 32 bit number
 * Inputs - none
 * Return Value - none
 */
void Test_Case_7_is32Bit (void)
{
	  UCUNIT_TestcaseBegin("Allocated address_32Bit");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIs32Bit(Test_Block_Start_Address[2]); /* check if not larger then 32 bit */
	  UCUNIT_TestcaseEnd();
	  /* finish all the tests */
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Test_Case_8_isNull
 * Description - This function is used to test whether the returned address in NULL
 * Inputs - none
 * Return Value - none
 */
void Test_Case_8_isNull (void)
{

	  UCUNIT_TestcaseBegin("Allocated_Address_IsNull");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIsNull(Test_Block_Start_Address); /* check if p == NULL */
	  UCUNIT_TestcaseEnd();

	  /* finish all the tests */
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Test_Case_9_isNotNull
 * Description - This function is used to test whether the returned address is not NULL
 * Inputs - none
 * Return Value - none
 */
void Test_Case_9_isNotNull (void)
{

	  UCUNIT_TestcaseBegin("Allocated_Address_IsNull");
	  uint32_t * Test_Block_Start_Address = allocate_words(TEST_ALLOCATE_WORD_SIZE);
	  UCUNIT_CheckIsNotNull(Test_Block_Start_Address); /* check if p == NULL */
	  UCUNIT_TestcaseEnd();

	  /* finish all the tests */
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Test_Case_10_status
 * Description - This function is used to test the return type status of the function
 * Inputs - none
 * Return Value - none
 */
void Test_Case_10_status (void)
{
	  mem_status res = invert_block(Global_BSA_Test, 2);
	  UCUNIT_TestcaseBegin("Mem_Status");
	  UCUNIT_CheckIsEqual(res, 2); /* check if x == 2 */
	  UCUNIT_TestcaseEnd();

	  /* finish all the tests */
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Test_Case_Script
 * Description - This function is used to run a test script of 10 test cases
 * Inputs - none
 * Return Value - none
 */

void Test_Case_Script(void)
{
	 UCUNIT_Init(); /* initialize framework */
	 Test_Case_1_isEqual ();
	 Test_Case_2_inRange ();
	 Test_Case_3_isBitSet ();
	 Test_Case_4_isBitClear ();
	 Test_Case_5_is8Bit ();
	 Test_Case_6_is16Bit ();
	 Test_Case_7_is32Bit ();
	 Test_Case_8_isNull ();
	 Test_Case_9_isNotNull ();
	 Test_Case_10_status();
	 UCUNIT_Shutdown();
}

