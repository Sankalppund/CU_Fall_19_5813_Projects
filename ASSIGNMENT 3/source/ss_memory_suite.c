/*
 * ss_memory_suite.c
 *
 *  Created on: Oct 19, 2019
 *      Author: sankalp pund and saket penurkar
 *
 *  Reference:https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
 */

/* Header files */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

/* user defined header files */

#include "ss_memory_suite.h"
#include "fsl_debug_console.h"
#include "SS_PatternGeneration.h"

/* Global Variables for ss_memory_suite.c */

uint32_t*pointer;

mem_status a;

uint8_t Global_Array_Pattern_Generator[0xFF];

uint8_t Local_array_display[0xFF];

uint32_t Allocated_Block_limit;

uint32_t Unmatched_array_in_verification[0xFF];


/*
 * Function Name - allocate_words
 * Description - This function Allocate a block of memory for the test using malloc.
 * Inputs - Number of bytes to allocate.
 * Return Value - pointer to uint32_t
 */

uint32_t * allocate_words(size_t length)
{
	Log_string("Memory Test Suit Begins.....");

	pointer=(int*)malloc(length*sizeof(int));

	int last;

	if(length>1024)    //  _HeapSize = 0x400 converted to decimal / Ref:PES_5813_PROJECT_3.map file of project
	{
		Log_string("Invalid Allocation Request.");
	}

	if(pointer==NULL)
	{
		Log_string("\r\nNo Memory block has been allocated.");
	}
	else
	{
		Log_string("Memory block has been allocated of below size");
		Log_integer(length);


	}

	Log_string("First address of the heap is mentioned below");
	Log_integer(pointer);
	Log_string("Last address of the heap is mentioned below");
	Log_integer(pointer+length);

	Allocated_Block_limit = pointer+length;

	return pointer;
}

/*
 * Function Name - free_words
 * Description - Free a previously allocated block of memory
 * Inputs - pointer of type uint32_t
 * Return Value - none
 */

void free_words(uint32_t * src)
{

	if(NULL == src)
	{
		Log_string("Warning:No memory was allocated to de-allocate it.");
	}

	free(src);

}

/*
 * Function Name - display_memory
 * Description - This function displays the contents of the memory location.
 * Inputs - pointer of type uint32_t and No of bytes.
 * Return Value - none
 */

void display_memory(uint32_t * loc, size_t length)
{
	for(int i=0; i < length; i++)
	{
		Log_string("Display Memory is mentioned below");
		Log_integer( loc[i]);

	}

}

/*
 * Function Name - write_memory
 * Description - This function modifies memory at specified location.
 * Inputs - pointer of type uint32_t and Value of Byte.
 * Return Value - Error code (success or failed)
 */

mem_status write_memory(uint32_t * loc, uint16_t value)
{

	if(pointer <= loc && loc <= Allocated_Block_limit) // checking bounds
	{
		*loc = value;
		return Success;
		LED_GREEN();
	}
	else
	{
		return Failed;
		LED_RED();
	}

}

/*
 * Function Name - invert_block
 * Description - This function inverts the bits of specified memory location.
 * Inputs - pointer of type uint32_t and No of bytes.
 * Return Value - Error code (Invert_success or Invert failed)
 */

mem_status invert_block(uint32_t * loc, size_t length)
{
	uint32_t * Temp_address_var = loc ;

	if(pointer <= loc && loc <= Allocated_Block_limit)  // checking bounds
	{
		for(int j=0; j<length; j++)
		{
			*(Temp_address_var+j)=((*(Temp_address_var+j))^(0xffffffff));

		}
		LED_GREEN();
		return Invert_success;
	}
	else
	{
		LED_RED();
		return Invert_failed;
	}

}

/*
 * Function Name - write_pattern
 * Description - This function is used to write pattern generated through pattern_generator to specified memory location.
 * Inputs - pointer of type uint32_t, No of bytes & seed value.
 * Return Value - Error code (Write_Pattern_success or Write_Pattern_failed)
 */

mem_status write_pattern(uint32_t * loc, size_t length, int8_t seed)
{
	uint32_t * Temp_address_var = loc ;

	if(pointer <= Temp_address_var && Temp_address_var <= Allocated_Block_limit) // checking bounds
	{

		for(int k=0; k<length; k++)
		{
			gen_pattern(Global_Array_Pattern_Generator,length,seed);  // pattern generation utility function

		}

		for (int array_index = 0; array_index < length ; array_index ++)
		{
			*(Temp_address_var + array_index) = *(Global_Array_Pattern_Generator + array_index);
		}
		LED_GREEN();
		return Write_Pattern_success;
	}
	else
	{
		LED_RED();
		return Write_Pattern_failed;
	}

}

/*
 * Function Name - verify_pattern
 * Description - This function is used to verify newly generated pattern with existing generated pattern.
 * Inputs - pointer of type uint32_t, No of bytes & seed value.
 * Return Value - list of memory location addresses where memory did not match the pattern.
 */
uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
{
	uint32_t * Temp_address_var = loc ;
	uint8_t  * Temp_gen_pattern_var = Global_Array_Pattern_Generator;
	int unmatched_array_index = 0;

	/* Generating the random pattern */
	gen_pattern(Global_Array_Pattern_Generator, length, seed);

	for(int l=0; l < length; l++)
	{
		//verify pattern function
		if ( * (Temp_address_var + l ) == * (Temp_gen_pattern_var + l ))
		{

			Log_string("Verification Successful");

		}
		else
		{
			Unmatched_array_in_verification [unmatched_array_index] = * (Temp_address_var + l );
			unmatched_array_index += 1;
			Log_string("Verification Not Successful");
		}

	}

	return Unmatched_array_in_verification;
}

/*
 * Function Name - get_address
 * Description - This function is used to address memory by an offset in region intended to use.
 * Inputs - pointer of type uint32_t &  pointer of type uint32_t.
 * Return Value - offset address
 */

uint32_t * get_address(uint32_t * base_addr, uint32_t * offset)
{
	uint32_t * temp_offset;

	temp_offset = base_addr - offset;

	return base_addr - temp_offset;
}

/*
 * Function Name - status_return
 * Description - This function is used to print the status as per error codes.
 * Inputs - enum
 * Return Value - none
 */

void status_return(mem_status a)
{
	if(a==0)
	{
		Log_string("write_memory is success\n");
	}
	if(a==1)
	{
		Log_string("write_memory is failed\n");
	}
	if(a==2)
	{
		Log_string("Invert block is success\n");
	}
	if(a==3)
	{
		Log_string("Invert block is failed\n");
	}
	if(a==4)
	{
		Log_string("write_pattern is success\n");
	}
	if(a==5)
	{
		Log_string("write_pattern is failed\n");
	}
}
