/*
 * unitTest.c
 *
 *  Created on: Oct 20, 2019
 *      Author: saket penurkar and sankalp pund
 *
 *      Reference - https://mcuoneclipse.com/2018/08/26/tutorial-μcunit-a-unit-test-framework-for-microcontrollers/
 */


#include "unitTest.h"



/*
 * Function Name - Test_Case_1_isEqual
 * Description - This function is used to test whether the Post_test status is success/failure
 * Inputs - none
 * Return Value - none
 */
void Buffer_Creation(void)
{
	  UCUNIT_TestcaseBegin("Buffer Creation Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum = verify_initilization(Buffer_Test);
	  UCUNIT_CheckIsEqual(VERIFY_INITIALIZATION_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();
}


/*
 * Function Name - Test_Case_2_isEqual
 * Description - This function is used to test whether the Post_test status is success/failure
 * Inputs - none
 * Return Value - none
 */
void Data_Access_Test(void)
{
	  UCUNIT_TestcaseBegin("Data Access Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum = add_new(Buffer_Test, 5);
	  UCUNIT_CheckIsEqual(ADDITION_BUFFER_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();
}

/*
 * Function Name - Test_Case_3_isBitSet
 * Description - This function is used to test whether a bit is set in the result
 * Inputs - none
 * Return Value - none
 */
void Verify_Wrap_Remove_test (void)
{
	  UCUNIT_TestcaseBegin("Verify Wrap Remove Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<5;i++)
	  {
		  add_new(Buffer_Test, i);
	  }
	  for(int i=0;i<5;i++)
	  {
	   Buffer_Test_enum =  remove_old(Buffer_Test);
	  }
	  UCUNIT_CheckIsEqual(REMOVE_BUFFER_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
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
void Verify_Wrap_Add_test (void)
{
	  UCUNIT_TestcaseBegin("Verify Wrap Add Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<7;i++)
	  {
		  Buffer_Test_enum = add_new(Buffer_Test, i);
	  }
	  UCUNIT_CheckIsEqual(ADDITION_BUFFER_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
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
void Overfill_test (void)
{
	  UCUNIT_TestcaseBegin("Verify Overfill Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<110;i++)
	  {
		  Buffer_Test_enum = add_new(Buffer_Test, i);
	  }
	  UCUNIT_CheckIsEqual(ADDITION_AFTER_RESIZE_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
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
void Overempty_test(void)
{
	  UCUNIT_TestcaseBegin("Verify Overfill Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum =  remove_old(Buffer_Test);
	  UCUNIT_CheckIsEqual(REMOVE_BUFFER_FAILED, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
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
void Destroy_Buffer_Test(void)
{
	  UCUNIT_TestcaseBegin("Destroy Buffer Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum =  destroy_buffer(Buffer_Test);
	  UCUNIT_CheckIsEqual(DESTROY_BUFFER_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
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
void Resize_Buffer_Test(void)
{

	  UCUNIT_TestcaseBegin("Resize Buffer Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<20;i++)
	  {
		  Buffer_Test_enum = add_new(Buffer_Test, i);
	  }
	  UCUNIT_CheckIsEqual(ADDITION_AFTER_RESIZE_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();

}
//
//
/*
 * Function Name - Buffer_Full_Test
 * Description - This function is used to test whether the return status is true/false
 * Inputs - none
 * Return Value - none
 */
void Buffer_Full_Test(void)
{
	  UCUNIT_TestcaseBegin("Buffer Full Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<100;i++)
	  {
		  Buffer_Test_enum = add_new(Buffer_Test, i);
	  }
	  UCUNIT_CheckIsEqual(BUFFER_FULL, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();
}
//
//
/*
 * Function Name - Buffer_Empty_Test
 * Description - This function is used to test whether the buffer is empty
 * Inputs - none
 * Return Value - none
 */
void Buffer_Empty_Test(void)
{
	  UCUNIT_TestcaseBegin("Buffer Empty Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum = buffer_empty_check(0);
	  UCUNIT_CheckIsEqual(BUFFER_EMPTY, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
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
	 Buffer_Creation();
	 Data_Access_Test();
	 Verify_Wrap_Remove_test();
	 Verify_Wrap_Add_test();
	 Overfill_test();
	 Overempty_test();
	 Destroy_Buffer_Test();
	 Resize_Buffer_Test ();
	 Buffer_Full_Test();
	 Buffer_Empty_Test();
	 UCUNIT_Shutdown();
}

