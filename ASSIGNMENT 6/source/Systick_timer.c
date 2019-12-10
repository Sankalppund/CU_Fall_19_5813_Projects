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
#include "fsl_debug_console.h"


/* Global Variables*/

uint32_t system_tick;

extern uint32_t cnt;

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

//void SysTick_Handler()
//{
//	system_tick++;
//}


/*
 * Function Name - current_time
 * Description - This function return the current counter time.
 * Inputs - pointer to uint32_t
 * Return Value - uint32_t
 */

uint32_t current_time()
{
	//PRINTF("Systick Count %d",system_tick);
//	system_tick = xTaskGetTickCount();
//	return system_tick;
	return cnt;
}

