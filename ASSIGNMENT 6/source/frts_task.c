/*
 * frts_task.c
 *
 *  Created on: Dec 1, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *  ref: freeRtos SDK example: sample_sw_timer_callback_rtos_examples_freertos_swtimer
 *  ref: freeRtos SDK example: frdmkl25z_rtos_examples_freertos_generic
 *  ref: https://stackoverflow.com/questions/44975229/max-min-avg-function-for-an-array-in-c
 *  ref: https://www.sanfoundry.com/c-program-mean-variance-standard-deviation/
 *
 */

/*Header Files*/

#include"frts_task.h"
#include "dma.h"

/*Global Variables for frts_task.c*/

uint16_t DSP_Buff[64];
uint16_t ADC_Buff_Temp[64];

extern dma_handle_t g_DMA_Handle;
extern volatile bool g_Transfer_Done;
extern bool DMA_Transfer;
extern dma_transfer_config_t transferConfig;
uint32_t cnt=0;

/*
 * Function Name - soft_timer_Init
 * Description - This function initializes and creates software timer.
 * Inputs - none
 * Return Value - none
 */

void soft_timer_Init()
{
	TimerHandle_t DAC_TimerHandle = NULL;

	TimerHandle_t ADC_TimerHandle = NULL;

	DAC_TimerHandle = xTimerCreate("DAC Write Timer", pdMS_TO_TICKS(100), pdTRUE, 0, DAC_time_callback);

	ADC_TimerHandle = xTimerCreate("ADC Read Timer", pdMS_TO_TICKS(100), pdTRUE, 0, ADC_time_callback);

	/* Start timer. */
	xTimerStart(DAC_TimerHandle, 0);

	xTimerStart(ADC_TimerHandle, 0);

	/* Start scheduling. */

	vTaskStartScheduler();
}

/*
 * Function Name - get_ticks
 * Description - This function is callback function for software timer.
 * Inputs - TimerHandle_t
 * Return Value - none
 */
void get_ticks(TimerHandle_t xTimer)
{
	cnt++;
}

/*
 * Function Name - DAC_time_callback
 * Description - This function is a callback function for software timer.
 * Inputs - TimerHandle_t
 * Return Value - none
 */

void DAC_time_callback(TimerHandle_t xTimer)
{
	Log(LOG_DEBUG, DMA_CALLBACK, "Inside DAC Timer Callback");

	uint16_t sin_sample = inc_sin_wave();

	WRITE_DAC(sin_sample);

	LED_BLUE();
	LED_OFF();


}

/*
 * Function Name - DAC_time_call
 * Description - This function takes value from lookup table and writes to DAC.
 * Inputs - none
 * Return Value - none
 */

void DAC_time_call()
{

	cnt++;

	LED_GREEN();
	uint16_t sin_sample = inc_sin_wave();

	WRITE_DAC(sin_sample);
	LED_OFF();
}

/*
 * Function Name - DacTask
 * Description - FreeRTOS Task to periodically (every .1 seconds)
 * change the value on DAC0 from the lookup table buffer of DAC register values.
 * Inputs - pointer to void
 * Return Value - none
 *
 * ref: freeRtos SDK example: frdmkl25z_rtos_examples_freertos_generic
 */

void DacTask(void* pointer)
{


	while(1)
	{
		if(project_mutex!=NULL)
		{
			if(xSemaphoreTake(project_mutex, (TickType_t) 100)==pdTRUE)
			{

				xSemaphoreGive(project_mutex);

				DAC_time_call();
			}
		}

		vTaskDelay(100);
	}
}

/*
 * Function Name - AdcTask
 * Description - FreeRTOS Task to periodically (every .1 seconds)
 * read the value on DAC0 via ADC0 and initialize DMA once 64 samples collected in queue.
 * Inputs - pointer to void
 * Return Value - none
 *
 * ref: freeRtos SDK example: frdmkl25z_rtos_examples_freertos_generic
 */

void AdcTask(void* pointer)
{
	PRINTF("\r\nLOG_DEBUG, ADC_TASK, Entered in ADC Task");


	while(1)
	{

		adc_read_counter++;


		if(adc_read_counter > 4)
		{
			xSemaphoreGive( project_mutex );
		}

		adc_read_val = READ_ADC();

		/* Send adc read value. Wait for 100 ticks for space to become available if necessary. */

		if((xQueueSend(ADC_Buff,(void *)&adc_read_val,100) != pdPASS))
		{

			adc_read_counter = 0;

			xSemaphoreTake(project_mutex, (TickType_t) 100);

			LED_BLUE();

			PRINTF("\r\nLOG_DEBUG, ADC_TASK, DMA Transfer is Initialized");

			DMA_One_Shot_Transfer(ADC_Buff->pcHead, DSP_Buff, 64);

			xQueueReset(ADC_Buff);

			LED_OFF();

			xTaskCreate(calculate,( portCHAR *)"calculate", configMINIMAL_STACK_SIZE, NULL, 1, &DSPHandle);
		}

		vTaskDelay(100);
	}


}

/*
 * Function Name - calculate
 * Description - FreeRTOS Task to trigger by interrupt received once DMA is completed.
 * Inputs - pointer to void
 * Return Value - none
 */

void calculate(void* pointer)
{
	PRINTF("\r\nLOG_DEBUG, ADC_TASK, DMA Transfer is Completed");
	time_stamp();

	while(1)
	{
		dsp_calculation();

		counter++;

		if(counter > 4)
		{

			vTaskEndScheduler();
		}

		vTaskSuspend(NULL);
	}
}

/*
 * Function Name - dsp_calculation
 * Description - Function for floating point calculation of volatage levels received after DMA
 * Inputs - none
 * Return Value - none
 * ref 1: https://stackoverflow.com/questions/44975229/max-min-avg-function-for-an-array-in-c
 * ref 2: https://www.sanfoundry.com/c-program-mean-variance-standard-deviation/
 */


void dsp_calculation()
{
	addition=0;

	for(int index_1 = 0; index_1<64; index_1++)
	{
		if(DSP_Buff[index_1] > maxV)
		{
			maxV = DSP_Buff[index_1];
		}
		if(DSP_Buff[index_1] < minV)
		{
			minV = DSP_Buff[index_1];
		}

		number[index_1] = DSP_Buff[index_1]* RSL;

		addition+=DSP_Buff[index_1];
	}

	minimum_val = minV*RSL;

	maximum_val = maxV*RSL;

	average_val = addition*RSL/64.0;

	float St_Deviation = 0.0f;

	for(int index_2=0; index_2 < 64; index_2++)
	{
		St_Deviation += powf((number[index_2] - average_val), 2);
	}

	St_deviation_val = sqrtf(St_Deviation/64.0);

	Log(LOG_DEBUG, CALCULATE,"*****Generating DSP Report*****");

	PRINTF("\r\nMinimum Value : %f\r\nMaximum Value : %f\r\nAverage Value : %f\r\nStandard Deviation : %f",minimum_val,maximum_val,average_val, St_deviation_val);

	Log(LOG_DEBUG, CALCULATE,"******DSP Report Generated*****");

}
