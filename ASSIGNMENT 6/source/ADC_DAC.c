/*
 * ADC_DAC.c
 *
 *  Created on: Dec 1, 2019
 *      Author: sankalp pund & saket penurkar
 */

/*Header File*/

#include"ADC_DAC.h"



/*ADC16 channel conversion configuration.*/

static adc16_channel_config_t adc_channel_struct;

/*ADC16 converter configuration.*/

static adc16_config_t adc_config_struct;

/* DAC module configuration.*/

static dac_config_t dac_config_struct;




void ADC_INIT()
{
	ADC16_GetDefaultConfig(&adc_config_struct);

	ADC16_Init(ADC0, &adc_config_struct);

	/* Make sure the software trigger is used. */
	ADC16_EnableHardwareTrigger(ADC0, false);

	/* Prepare ADC channel setting */
	adc_channel_struct.channelNumber = 0U;

	adc_channel_struct.enableInterruptOnConversionCompleted = false;
}


void DAC_INIT()
{


	DAC_GetDefaultConfig(&dac_config_struct);

	DAC_Init(DAC0, &dac_config_struct);

	/*Enables the DAC module.*/

	DAC_Enable(DAC0, true);

	DAC_SetBufferReadPointer(DAC0, 0);
}


uint32_t READ_ADC()
{
	ADC16_SetChannelConfig(ADC0, 0U, &adc_channel_struct);

	while (0 == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0)))
	{

	}

	/* Gets the conversion value.*/

	return ADC16_GetChannelConversionValue(ADC0, 0);
}

void WRITE_DAC(uint32_t Data)
{
	DAC_SetBufferValue(DAC0, 0, Data);
}
