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
 * @file    Main.c
 * @brief   Application entry point.
 *
 * Auther: sankalp pund & saket penurkar
 *
 */

/*Header files*/

#include "main.h"
#include "uart.h"
#include "char_count.h"

#include "fsl_debug_console.h"


/* Global Variables*/

extern uint16_t count;

extern int received_flag;

extern int INT_received_flag;

extern char c_recieve;

char forreport_1[100]={'0'};

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */

	BOARD_InitBootPins();
	BOARD_InitBootClocks();

	/* Initializing Systick Timer */

	Init_SysTick();

	/* Initializing LEDs */

	LED_Initialize();

#if (TEST_MODE)
	/* Init board hardware. */
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif


	/* Initializing a buffer*/

	TSA=(circular_buffer*)initialize_buffer(BUFFER_SIZE);

	for(int i=0; i<15; i++)
	{
		add_new(TSA, i);
	}

	/* Enabling Logging */

#if (LOG_ENABLE)
	Log_enable();   /*  Calling this function to enable logging */

	/** Set the LOG_LEVEL **/
	/** Pass LOG_DEBUG to run the DEBUG and STATUS log statements **/
	/** Pass LOG_TEST to run all the log statements **/
	/** Pass LOG_STATUS to run the STATUS log statements **/
	Log_level(LOG_TEST);

#endif

#if (!TEST_MODE)

	/* Initializing UART0 */

	Init_UART0(BAUD_RATE);

#endif

	/* Operating Application Mode */

#if (APPLICATION_MODE)

	while(1)
	{

#if (USE_UART_INTERRUPTS)

		if(TSA->buffer[TSA->head - 1]=='=')
		{

			    destroy_buffer(TSA);

				sprintf(forreport_1, "\r\nGenerating Report\n");

				print_string(forreport_1);

				application_report();

		}

		interrupt_application(&(TSA->buffer[TSA->head - 1]));

#else
		char rc = uart_receive();

		if(rc == '=')
		{

			sprintf(forreport_1, "\r\nGenerating Report\n");

			print_string(forreport_1);

			application_report();


		}

		polling_application(&rc);


#endif

	}

	return 0;


#endif

	/* Operating ECHO Mode */

#if (ECHO_MODE)

	while(1)
	{

#if(USE_UART_INTERRUPTS)

		START_CRITICAL();
		interrupt_echo(c_recieve);
		END_CRITICAL();

#else
		polling_echo();
#endif

	}
	return 0;


#endif


	/* Operating TEST Mode */

#if (TEST_MODE)

	Test_Script();             // Run the Test Script

	LED_OFF();

	return 0;

#endif

}

