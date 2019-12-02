/*
 * ADC_DAC.h
 *
 *  Created on: Dec 1, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef ADC_DAC_H_
#define ADC_DAC_H_

#include <stdint.h>
#include "board.h"
#include "fsl_dac.h"
#include "fsl_adc16.h"

#include "pin_mux.h"
#include "clock_config.h"





void ADC_INIT();
void DAC_INIT();
uint32_t READ_ADC();
void WRITE_DAC(uint32_t);

#endif /* ADC_DAC_H_ */
