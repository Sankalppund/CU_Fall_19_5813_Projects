/*
 * Systick_timer.c
 *
 *  Created on: Nov 2, 2019
 *      Author: sankalp pund & saket penurkar
 */

#include "Systick_timer.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

extern int timeout_cnt;
extern int iteration_val;
int LCNT=0;

void Init_SysTick(void)
{

	SysTick->LOAD=(48000000L/5);

	NVIC_SetPriority(SysTick_IRQn,3);

	SysTick->VAL=0;

	SysTick->CTRL=SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk;

}

void SysTick_Handler()
{

	timeout_cnt++;

	iteration_val++;

	LCNT++;

	Log(LOG_TEST, SYSTICK_HANDLER, "TIME_OUT - ");
	Log_integer(LCNT);

	if(LCNT==4)
	{
		LCNT=0;
	}

}
