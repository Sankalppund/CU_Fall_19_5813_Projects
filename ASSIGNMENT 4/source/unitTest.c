/*
 * unitTest.c
 *
 *  Created on: Oct 20, 2019
 *      Author: saket penurkar and sankalp pund
 *
 *      Reference - https://mcuoneclipse.com/2018/08/26/tutorial-μcunit-a-unit-test-framework-for-microcontrollers/
 */


#include "unitTest.h"

post_status return_value;


/*
 * Function Name - Test_Case_1_isEqual
 * Description - This function is used to test whether the Post_test status is success/failure
 * Inputs - none
 * Return Value - none
 */
void Test_Case_1_isEqual(void)
{
	  UCUNIT_TestcaseBegin("Post Test Equality - Success");
	  return_value = POST_Test();
	  UCUNIT_CheckIsEqual(Success, return_value);
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}


/*
 * Function Name - Test_Case_2_isEqual
 * Description - This function is used to test whether the Post_test status is success/failure
 * Inputs - none
 * Return Value - none
 */
void Test_Case_2_isEqual(void)
{
	  UCUNIT_TestcaseBegin("Post Test Equality - Failure");
	  return_value = POST_Test();
	  UCUNIT_CheckIsEqual(Failed, return_value);
	  UCUNIT_TestcaseEnd();
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
	  UCUNIT_TestcaseBegin("I2C_Read_BitSet_0");
	  int Temperature_Value = I2C_Read_Data();
	  UCUNIT_CheckIsBitSet(Temperature_Value, 0); /* check if bit 0 set */
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_4_is8Bit
 * Description - This function is used to test whether a particular bit is set in the returned value
 * Inputs - none
 * Return Value - none
 */
void Test_Case_4_is8BitSet (void)
{
	  UCUNIT_TestcaseBegin("I2C_Read_BitSet_8");
	  int Temperature_Value = I2C_Read_Data();
	  UCUNIT_CheckIsBitSet(Temperature_Value, 8); /* check if bit 8 set */
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_5_is8Bit
 * Description - This function is used to test whether the returned address's value is 8 bit value
 * Inputs - none
 * Return Value - none
 */
void Test_Case_5_is8Bit (void)
{

	  UCUNIT_TestcaseBegin("I2C_Return_Value_8Bit");
	  int Temperature_Value = I2C_Read_Data();
	  UCUNIT_CheckIs8Bit(Temperature_Value); /* check if not larger then 8 bit */
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_6_isEqual
 * Description - This function is used to test whether the return status is success/failure
 * Inputs - none
 * Return Value - none
 */
void Test_Case_6_isEqual(void)
{
	  UCUNIT_TestcaseBegin("Alert_Temperature_Success");
	  int Temperature_Value = I2C_Read_Data();
	  bool Status = alert_event(Temperature_Value);
	  UCUNIT_CheckIsEqual(true, Status);
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}

//
//
/*
 * Function Name - Test_Case_7_isEqual
 * Description - This function is used to test whether the return status is success/failure
 * Inputs - none
 * Return Value - none
 */
void Test_Case_7_isEqual(void)
{
	  UCUNIT_TestcaseBegin("Complete_Event_Success");
	  int Temperature_Value = I2C_Read_Data();
	  bool Status = complete_event(Temperature_Value);
	  UCUNIT_CheckIsEqual(true, Status);
	  UCUNIT_TestcaseEnd();
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

	  UCUNIT_TestcaseBegin("I2C_Return_Value_isNull");
	  int Temperature_Value = I2C_Read_Data();
	  UCUNIT_CheckIsNull(Temperature_Value); /* check if p == NULL */
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Test_Case_9_isEqual
 * Description - This function is used to test whether the return status is true/false
 * Inputs - none
 * Return Value - none
 */
void Test_Case_9_isEqual(void)
{
	  UCUNIT_TestcaseBegin("Alert_Temperature_Success");
	  int Temperature_Value = I2C_Read_Data();
	  bool Status = alert_event(Temperature_Value);
	  UCUNIT_CheckIsEqual(false, Status);
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Case_10_isEqual
 * Description - This function is used to test whether the return status is true/false
 * Inputs - none
 * Return Value - none
 */
void Test_Case_10_isEqual(void)
{
	  UCUNIT_TestcaseBegin("Alert_Temperature_Success");
	  int Temperature_Value = I2C_Read_Data();
	  bool Status = complete_event(Temperature_Value);
	  UCUNIT_CheckIsEqual(false, Status);
	  UCUNIT_TestcaseEnd();
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Test_Script
 * Description - This function is used to run a test script of 10 test cases
 * Inputs - none
 * Return Value - none
 */

void Test_Script(void)
{
	 UCUNIT_Init(); /* initialize framework */
	 Test_Case_1_isEqual ();
	 Test_Case_2_isEqual ();
	 Test_Case_3_isBitSet ();
	 Test_Case_4_is8BitSet ();
	 Test_Case_5_is8Bit ();
	 Test_Case_6_isEqual ();
	 Test_Case_7_isEqual ();
	 Test_Case_8_isNull ();
	 Test_Case_9_isEqual ();
	 Test_Case_10_isEqual();
	 UCUNIT_Shutdown();
}

