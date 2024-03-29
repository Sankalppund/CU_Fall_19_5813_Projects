/*
 * LookUp.c
 *
 *  Created on: Dec 1, 2019
 *       Author: sankalp pund & saket penurkar
 *
 *   ref 1 : Example code under demo_apps called dac_adc
 */

/*Header File*/

#include"LookUp.h"


uint32_t lookup_table[SIN_SAMPLES] = {0};


 /* Convert ADC value to a voltage based on 3.3V VREFH on board
  *  ref 1 : Example code under demo_apps called dac_adc
  */
const static float Volt_Conv = (SE_12BIT/REF_BOARD_VOL);

/*
 * Function Name - gen_sin_sample
 * Description - This function generates sine wave samples and stores in lookup table .
 * Inputs - none
 * Return Value - none
 */

void gen_sin_sample()
{

	for(int sample=0; sample<SIN_SAMPLES; sample++)
	{
		lookup_table[sample] = (sin((2.0 * PI * (sample/(float)(SIN_SAMPLES)))) + OFFSET_VOL)*Volt_Conv;
	}

}

/*
 * Function Name - inc_sin_wave
 * Description - This function returns sample value from lookup table one by one.
 * Inputs - none
 * Return Value - uint32_t
 */

uint32_t inc_sin_wave()
{
	return lookup_table[inc++%SIN_SAMPLES];
}
