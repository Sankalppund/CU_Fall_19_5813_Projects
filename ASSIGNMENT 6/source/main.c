/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
 *
 * Authors: Sankalp Pund & Saket Penurkar
 *
 * ref : freeRtos SDK example: frdmkl25z_rtos_examples_freertos_generic
 */

/*
 * Includes
 */
#include "main.h"

/*
 * Globals
 */
SemaphoreHandle_t project_mutex;
QueueHandle_t ADC_Buff;
QueueHandle_t dspBuffer;

int main(void)
{

#if (LOG_ENABLE == 1)

	Log_enable();   /*  Calling this function to enable logging */

	/** Set the LOG_LEVEL **/
	/** Pass LOG_DEBUG to run the DEBUG and STATUS log statements **/
	/** Pass LOG_TEST to run all the log statements **/
	/** Pass LOG_STATUS to run the STATUS log statements **/
	Log_level(LOG_DEBUG);

#endif
#if (PROGRAM_1 == 1)

	//Log(LOG_DEBUG, MAIN, "Initializing Program 1");

	TimerHandle_t DAC_TimerHandle = NULL;
	TimerHandle_t GET_TICKSHandle = NULL;
	GET_TICKSHandle = xTimerCreate("TICK", (100 / portTICK_PERIOD_MS), pdTRUE, 0, get_ticks);

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	/* Initialize the DAC0*/
	DAC_INIT();

	/* Generate Sine Wave and store in lookup table*/
	gen_sin_sample();

	LED_OFF();

	/*Create Software Timer*/
	DAC_TimerHandle = xTimerCreate("DAC_Write_Timer", (1000 / portTICK_PERIOD_MS), pdTRUE, 0, DAC_time_callback);

	xTimerStart(DAC_TimerHandle, 0);
	xTimerStart(GET_TICKSHandle, 0);

	vTaskStartScheduler();

	while(1)
	{

	}


#endif

#if(PROGRAM_2 == 1)

	//Log(LOG_DEBUG, MAIN, "Initializing Program 2");

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	/* Generate Sine Wave and store in lookup table*/
	gen_sin_sample();

	/* Initialize the ADC0*/
	ADC_INIT();

	/* Initialize the DAC0*/
	DAC_INIT();

	/* Initialize the DMA0*/
	DMA_Initialize();

	project_mutex = xSemaphoreCreateMutex();

	/* Initializes the Queues*/

	ADC_Buff = xQueueCreate(64,sizeof(uint16_t));

	/* Creating Tasks 1*/
	xTaskCreate(DacTask,(portCHAR*)"DacTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	/* Creating Tasks 2*/
	xTaskCreate(AdcTask,(portCHAR*)"AdcTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1)
	{

	}


#endif


}


