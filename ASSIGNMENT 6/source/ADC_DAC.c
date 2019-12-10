/*
 * ADC_DAC.c
 *
 *  Created on: Dec 1, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *        ref 1 : Example code under demo_apps called dac_adc
 */

/*Header File*/

#include"ADC_DAC.h"



/*ADC16 channel conversion configuration.*/

static adc16_channel_config_t adc_channel_struct;

/*ADC16 converter configuration.*/

static adc16_config_t adc_config_struct;

/* DAC module configuration.*/

static dac_config_t dac_config_struct;


/*
 * Function Name - ADC_INIT
 * Description - Initialization of ADC
 * Inputs - none
 * Return Value - none
 */

void ADC_INIT()
{
	ADC16_GetDefaultConfig(&adc_config_struct);

	ADC16_Init(ADC0, &adc_config_struct);

	/* Make sure the software trigger is used. */
	ADC16_EnableHardwareTrigger(ADC0, false);

	ADC16_DoAutoCalibration(ADC0);

	/* Prepare ADC channel setting */
	adc_channel_struct.channelNumber = 0U;

	adc_channel_struct.enableInterruptOnConversionCompleted = false;
}


/*
 * Function Name - DAC_INIT
 * Description - Initialization of DAC
 * Inputs - none
 * Return Value - none
 */
void DAC_INIT()
{

	DAC_GetDefaultConfig(&dac_config_struct);

	DAC_Init(DAC0, &dac_config_struct);

	/*Enables the DAC module.*/

	DAC_Enable(DAC0, true);

	DAC_SetBufferReadPointer(DAC0, 0);
}

/*
 * Function Name - READ_ADC
 * Description - Reads the value from the channel and return the ADC value
 * Inputs - none
 * Return Value - ADC_Value
 */
uint16_t READ_ADC()
{
	ADC16_SetChannelConfig(ADC0, 0U, &adc_channel_struct);

	while (0 == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0)))
	{

	}

	/* Gets the conversion value.*/

	return (uint16_t)ADC16_GetChannelConversionValue(ADC0, 0);
}


/*
 * Function Name - WRITE_DAC
 * Description - Takes the value and writes it over the DAC
 * Inputs - none
 * Return Value - none
 */
void WRITE_DAC(uint16_t Data)
{

	DAC_SetBufferValue(DAC0, 0, Data);

}
