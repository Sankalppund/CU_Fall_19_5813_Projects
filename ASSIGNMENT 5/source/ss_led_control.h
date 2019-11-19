/*
 * ss_led_control.h
 *
 *  Created on: Oct 22, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef SS_LED_CONTROL_H_
#define SS_LED_CONTROL_H_

/* #define for Board led color mapping */

#define BOARD_LED_GPIO_R BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN_R BOARD_LED_RED_GPIO_PIN

#define BOARD_LED_GPIO_G BOARD_LED_GREEN_GPIO
#define BOARD_LED_GPIO_PIN_G BOARD_LED_GREEN_GPIO_PIN

#define BOARD_LED_GPIO_B BOARD_LED_BLUE_GPIO
#define BOARD_LED_GPIO_PIN_B BOARD_LED_BLUE_GPIO_PIN

void LED_Initialize(void);
void LED_OFF(void);
void LED_BLUE(void);
void LED_GREEN(void);
void LED_RED(void);


#endif /* SS_LED_CONTROL_H_ */
