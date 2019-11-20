/*
 * Systick_timer.c
 *
 *  Created on: Nov 16, 2019
 *
 *      Author: sankalp pund & saket penurkar
 *
 *      Ref: Making embedded systems elicia white book (Pg No. 139)
 */

/* Header files */

#include "Systick_timer.h"
#include "MKL25Z4.h"

/* Global Variables*/

uint64_t system_tick = 0;

uint64_t max_time = ~0;

/*
 * Function Name - Init_SysTick
 * Description - This function initialize the systick timer.
 * Inputs - none
 * Return Value - none
 */

void Init_SysTick(void)
{

	SysTick->LOAD=(48000000L/100);

	NVIC_SetPriority(SysTick_IRQn,3);
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);

	SysTick->VAL=0;

	SysTick->CTRL=SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk;

}

/*
 * Function Name - SysTick_Handler
 * Description - This function is systick timer ISR.
 * Inputs - none
 * Return Value - none
 */

void SysTick_Handler()
{
	system_tick++;
}


/*
 * Function Name - current_time
 * Description - This function return the current counter time.
 * Inputs - pointer to uint32_t
 * Return Value - uint32_t
 */

uint32_t current_time()
{
	return system_tick;
}

