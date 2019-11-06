/*
 * ss_led_control.c
 *
 *  Created on: Oct 20, 2019
 *      Author: sankalp pund & saket penurkar
 */

/* Header file */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_rtc.h"
#include "ss_led_control.h"

/*
 * Global variables
 */

int NOP_Index;

/* Define the init structure for the output LED pin*/

gpio_pin_config_t led_config = {
		kGPIO_DigitalOutput, 0,
};



/*
 * Function Name - LED_Initialize
 * Description - Initialize output LED GPIO.
 * Inputs - none
 * Return Value - none
 */

void LED_Initialize(void)
{
	GPIO_PinInit(BOARD_LED_GPIO_R, BOARD_LED_GPIO_PIN_R, &led_config);
	GPIO_PinInit(BOARD_LED_GPIO_G, BOARD_LED_GPIO_PIN_G, &led_config);
	GPIO_PinInit(BOARD_LED_GPIO_B, BOARD_LED_GPIO_PIN_B, &led_config);
}

/*
 * Function Name - LED_OFF
 * Description - Turns off LEDs.
 * Inputs - none
 * Return Value - none
 */

void LED_OFF(void)
{
	GPIO_SetPinsOutput(BOARD_LED_GPIO_R, 1u << BOARD_LED_GPIO_PIN_R);
	GPIO_SetPinsOutput(BOARD_LED_GPIO_G, 1u << BOARD_LED_GPIO_PIN_G);
	GPIO_SetPinsOutput(BOARD_LED_GPIO_B, 1u << BOARD_LED_GPIO_PIN_B);
}

/*
 * Function Name - delay
 * Description - generate time delay
 * Inputs - time
 * Return Value - integer
 */

int delay(int time_period)
{

	NOP_Index = 2400 * time_period;
	int i;
	for (i = 0; i < NOP_Index ; ++i)
	{
		__asm("NOP"); /* delay */
	}
	return i;
}

/*
 * Function Name - LED_RED
 * Description - Turn on RED LED
 * Inputs - none
 * Return Value - none
 */

void LED_RED()
{

	GPIO_SetPinsOutput(BOARD_LED_GPIO_G, 1u << BOARD_LED_GPIO_PIN_G);
	GPIO_SetPinsOutput(BOARD_LED_GPIO_B, 1u << BOARD_LED_GPIO_PIN_B);
	GPIO_ClearPinsOutput(BOARD_LED_GPIO_R, 1u << BOARD_LED_GPIO_PIN_R);
	delay(1000);
}

/*
 * Function Name - LED_GREEN
 * Description - Turn on GREEN LED
 * Inputs - none
 * Return Value - none
 */

void LED_GREEN()
{

	GPIO_SetPinsOutput(BOARD_LED_GPIO_R, 1u << BOARD_LED_GPIO_PIN_R);
	GPIO_SetPinsOutput(BOARD_LED_GPIO_B, 1u << BOARD_LED_GPIO_PIN_B);
	GPIO_ClearPinsOutput(BOARD_LED_GPIO_G, 1u << BOARD_LED_GPIO_PIN_G);
	delay(1000);
}

/*
 * Function Name - LED_BLUE
 * Description - Turn on BLUE LED
 * Inputs - none
 * Return Value - none
 */

void LED_BLUE()
{
	GPIO_SetPinsOutput(BOARD_LED_GPIO_R, 1u << BOARD_LED_GPIO_PIN_R);
	GPIO_SetPinsOutput(BOARD_LED_GPIO_G, 1u << BOARD_LED_GPIO_PIN_G);
	GPIO_ClearPinsOutput(BOARD_LED_GPIO_B, 1u << BOARD_LED_GPIO_PIN_B);
	delay(1000);
}
