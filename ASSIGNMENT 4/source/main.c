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
 * @file    PES_5813_PROJECT_4.c
 * @brief   Application entry point.
 */

#include "main.h"

post_status return_val;
/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

#if (LOG_ENABLE == 1)

	Log_enable();   /*  Calling this function to enable logging */

#endif

	/** Set the LOG_LEVEL **/
	/** Pass LOG_DEBUG to run the DEBUG and STATUS log statements **/
	/** Pass LOG_TEST to run all the log statements **/
	/** Pass LOG_STATUS to run the STATUS log statements **/
	Log_level(LOG_TEST);

	/* Configure I2C Module*/
	I2C_Config();

	LED_Initialize();

#if (TEST_MODE == 1)

	Test_Script();             // Run the Test Script

#else
	Init_SysTick();

	/*Run Power On Set Test (POST)*/
	return_val = POST_Test();

	if(return_val==0)
	{
		PRINTF("\r\nPower On Start-Up Test is Successful. ");
		Log(LOG_DEBUG, MAIN, "Power On Start-Up Test is Successful. ");
	}
	else
	{
		PRINTF("\r\n\nPower On Start-Up Test is failed.");
		Log(LOG_DEBUG, MAIN, "Power On Start-Up Test is failed.");
	}

	while(1)
	{
		if(return_val==0)
		{
			Log(LOG_TEST, MAIN, "Entering First State Machine");
			state_machine();
		}

	}
	return 0 ;

#endif
}
