/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    main.c
 * @brief   Application entry point.
 *
 * Author - Sankalp Pund and Saket Penurkar
 */

/* Header files */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
/* TODO: insert other include files here. */
#include "ss_memory_suite.h"
#include "main.h"
#include "logger.h"

/* TODO: insert other definitions and declarations here. */
mem_status Return_Status_Memory_Check;
mem_status Invert_Status_Check;
extern uint32_t Unmatched_array_in_verification;

uint32_t *  Global_BSA_Test;


int main(void) {

	/* Init board hardware. */

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	/* Init FSL debug console. */

	BOARD_InitDebugConsole();

	/* Define the init structure for the output LED pin*/

		gpio_pin_config_t led_config = {
				kGPIO_DigitalOutput, 0,
		};

#if (MEMORY_SUITE_MODE == 1)
	/* Init output LED GPIO. */

	LED_Initialize();

	/* Memory Test Starts with LED Blue ON */

	LED_BLUE();

	/* Enabling & Disabling Logger */

	Log_enable();                 //Comment this function to disable logging


	/* Allocate Memory */
	uint32_t * Block_Start_Address;
	Block_Start_Address = allocate_words(NO_OF_BYTES_TO_ALLOCATE);
	uint32_t *  Global_BSA_Test = Block_Start_Address;

	/* Write Memory Pattern */

	Return_Status_Memory_Check = write_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	/* Display String */

	Log_string("The return status after write pattern 1");

	/* Returns Success or failure Status of functions */

	status_return(Return_Status_Memory_Check);

	/* Display Content of Memory Region */

	display_memory(Block_Start_Address, NO_OF_BYTES);

	/* Verify newly generated pattern with existing generated pattern */

	verify_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	/* Modify Memory at specified location */

	Return_Status_Memory_Check = write_memory(Block_Start_Address + OFFSET, BYTE_VALUE);

	/* Display String */

	Log_string("The return status after write pattern 2");

	/* Returns Success or failure Status of functions */

	status_return(Return_Status_Memory_Check);

	/* Display Content of Memory Region */

	display_memory(Block_Start_Address, NO_OF_BYTES);

	/* Verify newly generated pattern with existing generated pattern */

	Unmatched_array_in_verification = verify_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	Return_Status_Memory_Check = write_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	/* Display String */

	Log_string("The return status after write pattern 3");

	/* Returns Success or failure Status of functions */

	status_return(Return_Status_Memory_Check);

	/* Display Content of Memory Region */

	display_memory(Block_Start_Address, NO_OF_BYTES);

	/* Verify newly generated pattern with existing generated pattern */

	verify_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	/* Invert bits in specified memory region using XOR */

	Invert_Status_Check = invert_block(Block_Start_Address + OFFSET ,BYTE_VALUE_INVERT);

	/* Display String */

	Log_string("The return status after 1st Invert Pattern");

	/* Returns Success or failure Status of functions */

	status_return(Invert_Status_Check);

	/* Display Content of Memory Region */

	display_memory(Block_Start_Address, NO_OF_BYTES);

	/* Verify newly generated pattern with existing generated pattern */

	verify_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	/* Invert bits in specified memory region using XOR */

	Invert_Status_Check = invert_block(Block_Start_Address + OFFSET ,BYTE_VALUE_INVERT);

	/* Display String */

	Log_string("The return status after 2nd Invert Pattern");

	/* Returns Success or failure Status of functions */

	status_return(Invert_Status_Check);

	/* Display Content of Memory Region */

	display_memory(Block_Start_Address, NO_OF_BYTES);

	/* Verify newly generated pattern with existing generated pattern */

	verify_pattern(Block_Start_Address, NO_OF_BYTES, SEED_VALUE);

	/* Free previously allocated block of Memory */

	free_words(Block_Start_Address);

#endif

#if (ENABLE_TESTING == 1)
	Test_Case_Script();
#endif


	return 0 ;
}
