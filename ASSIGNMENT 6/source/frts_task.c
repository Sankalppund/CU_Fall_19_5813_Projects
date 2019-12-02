/*
 * frts_task.c
 *
 *  Created on: Dec 1, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *  ref: freertos_swtimer SDK example
 */


#include"frts_task.h"


void soft_timer()
{
	TimerHandle_t DAC_TimerHandle = NULL;

	TimerHandle_t ADC_TimerHandle = NULL;

	DAC_TimerHandle = xTimerCreate("DAC Write Timer", pdMS_TO_TICKS(100), pdTRUE, 0, DAC_time_callback);

	ADC_TimerHandle = xTimerCreate("ADC Read Timer", pdMS_TO_TICKS(100), pdTRUE, 0, ADC_time_callback);

	/* Start timer. */
	xTimerStart(DAC_TimerHandle, 0);

	xTimerStart(ADC_TimerHandle, 0);


	/* Initializing a circular buffer*/

	ADC_Buff=(circular_buffer*)initialize_buffer(BUFFER_SIZE);

	DSP_Buff=(circular_buffer*)initialize_buffer(BUFFER_SIZE);

    /* Start scheduling. */

    vTaskStartScheduler();
}



void DAC_time_callback(TimerHandle_t xTimer)
{
	uint32_t sin_sample = inc_sin_wave();

	WRITE_DAC(sin_sample);
}


void ADC_time_callback(TimerHandle_t xTimer)
{
	uint32_t adc_read_val = READ_ADC();

	add_new(ADC_Buff, adc_read_val);

	if(buffer_full_check(count) == BUFFER_FULL)
	{
		/* Initiate DMA Transfer here*/

		//DMA_One_Shot_Transfer(ADC_Buff->buffer, DSP_Buff->buffer);

		destroy_buffer(ADC_Buff);
	}
}
