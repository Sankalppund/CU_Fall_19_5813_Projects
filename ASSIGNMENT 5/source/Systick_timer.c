/*
 * Systick_timer.c
 *
 *  Created on: Nov 16, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *      Ref: Making embedded systems elicia white book (Pg No. 139)
 */

#include "Systick_timer.h"
#include "MKL25Z4.h"


uint64_t system_tick = 0;

uint64_t max_time = ~0;

void Init_SysTick(void)
{

	SysTick->LOAD=(48000000L/100);

	NVIC_SetPriority(SysTick_IRQn,3);
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);

	SysTick->VAL=0;

	SysTick->CTRL=SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk;

}

void SysTick_Handler()
{
	//Log(LOG_TEST, SYSTICK_HANDLER, "Getting Interrupts");
	system_tick++;
}

uint64_t current_time()
{
	return system_tick;
}


uint64_t time_elapsed(uint64_t time_since)
{
	uint32_t current = system_tick;

	if(current >= time_since)
	{
		return (current - time_since);
	}

	// for rollover condition

	return (current + (max_time-time_since));
}

