/*
 * unitTest.c
 *
 *  Created on: Oct 20, 2019
 *      Author: saket penurkar and sankalp pund
 *
 *      Reference - https://mcuoneclipse.com/2018/08/26/tutorial-μcunit-a-unit-test-framework-for-microcontrollers/
 */

/* Header files*/

#include "unitTest.h"

/*
 * Function Name - Buffer_Creation
 * Description - This function is used to test whether circular buffer initialization is success or failed.
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
 * Function Name - Data_Access_Test
 * Description - This function is used to test whether the data access from circular buffer is success of failed.
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
 * Function Name - Verify_Wrap_Remove_test
 * Description - This function is used to test whether wrap remove from circular buffer is success or failed
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

/*
 * Function Name - Verify_Wrap_Add_test
 * Description - This function is used to test whether wrap add to circular buffer is success or failed.
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

/*
 * Function Name - Overfill_test
 * Description - This function is used to test that circular buffer fails when too many items are added
 * Inputs - none
 * Return Value - none
 */
void Overfill_test (void)
{
	  UCUNIT_TestcaseBegin("Verify Overfill Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<6;i++)
	  {
		  Buffer_Test_enum = add_new(Buffer_Test, i);
	  }
	  UCUNIT_CheckIsEqual(ADDITION_AFTER_RESIZE_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();
}

/*
 * Function Name - Overempty_test
 * Description - This function is test that circular buffer fails to remove an item when circular buffer is empty
 * Inputs - none
 * Return Value - none
 */
void Overempty_test(void)
{
	  UCUNIT_TestcaseBegin("Verify Overempty Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum =  remove_old(Buffer_Test);
	  UCUNIT_CheckIsEqual(REMOVE_BUFFER_FAILED, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();
}


/*
 * Function Name - Destroy_Buffer_Test
 * Description - This function is used to test whether circular buffer reset is success or failed.
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

/*
 * Function Name - Resize_Buffer_Test
 * Description - This function is used to test whether circular buffer resizes as soon as more data is added than initialized length.
 * Inputs - none
 * Return Value - none
 */
void Resize_Buffer_Test(void)
{

	  UCUNIT_TestcaseBegin("Resize Buffer Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(10);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<12;i++)
	  {
		  Buffer_Test_enum = add_new(Buffer_Test, i);
	  }
	  UCUNIT_CheckIsEqual(ADDITION_BUFFER_SUCCESS, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();

}

/*
 * Function Name - Buffer_Full_Test
 * Description - This function is used to test whether circular buffer full.
 * Inputs - none
 * Return Value - none
 */
void Buffer_Full_Test(void)
{
	  UCUNIT_TestcaseBegin("Buffer Full Test");
	  circular_buffer* Buffer_Test = (circular_buffer*)initialize_buffer(5);
	  cir_buff_err Buffer_Test_enum;
	  for(int i=0;i<11;i++)
	  {
		 Buffer_Test_enum = buffer_full_check(i);
	  }
	  UCUNIT_CheckIsEqual(BUFFER_FULL, Buffer_Test_enum);
	  UCUNIT_TestcaseEnd();
	  free(Buffer_Test);
	  UCUNIT_WriteSummary();
}

/*
 * Function Name - Buffer_Empty_Test
 * Description - This function is used to test whether the circular buffer is empty
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
	 UCUNIT_Shutdown(); /*  function to stop the execution of the tests */
}

