/*
 * State_Machine.h
 *
 *  Created on: Oct 31, 2019
 *  Author: Sankalp Pund and Saket Penurkar
 *
 *      Reference - 1) https://aticleworld.com/state-machine-using-c/
 *                  2) https://gist.github.com/nmandery/1717405
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

/*
 * Headers Section
 */
#include "POST_Test.h"
#include "fsl_debug_console.h"
#include "logger.h"

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_gpio.h"
#include "fsl_rtc.h"
#include "ss_led_control.h"

#define SLAVE_ADDR (0x90U)  // I2C Slave Address the TMP102 Sensor Address
#define REG_ADDR (0x00U)    // The register address of the TMP102

/* Different States of the System as described in the assignment document */
typedef enum
{
	Temp_Reading,
	Average_Wait,
	Temp_Alert,
	Disconnected,
	End

}state;

/* Different types of events described in the assignemnt document */

typedef enum
{
	Complete_event,
	Alert_event,
	Timeout_event,
	Disconnect_event,
	Last_event

}System_Event;


/******** Function Prototypes *****************/

void Resetting_Global_Var(void);
void table_state_machine(state);
state Temp_Reading_State(void);
state Average_Wait_State(void);
state Temp_Alert_State(void);
state Disconnected_State(void);
state End_State(void);
state Transition_in_Table(state, System_Event);

System_Event Temp_Reading_Func_for_Event(void);
System_Event Average_Wait_Func_for_Event(void);
System_Event Temp_Alert_Func_for_Event(void);
System_Event Disconnected_State_Func_for_Event(void);
System_Event End_State_Func_for_Event(void);



int (* State[])(void)=
{
		Temp_Reading_Func_for_Event, Average_Wait_Func_for_Event, Temp_Alert_Func_for_Event, Disconnected_State_Func_for_Event, End_State_Func_for_Event
};


struct Transition {

	 state Current_State;
	 System_Event Event_Table;
	 state Next_State;
};

/* State table comprising of the current state, event triggered and the next state */
struct Transition State_Transition_Table [] =
{
		//CURRENT STATE  -- EVENT --   NEXT STATE//
		//			   |             |           //
        //             |             |           //
		/* Temperature Reading State - Complete Event */
		{ Temp_Reading, Complete_event,  Average_Wait},

		/* Temperature Reading State - Alert Event */
		{ Temp_Reading, Alert_event,  Temp_Alert},

		/* Temperature Reading State - Disconnect Event */
		{ Temp_Reading, Disconnect_event,  Disconnected},

		/* Average_Wait State - Timeout Event */
		{ Average_Wait, Timeout_event,  Temp_Reading},

		/* Average_Wait State - Disconnected Event */
		{ Average_Wait, Disconnect_event,  Disconnected},

		/* Temp_Alert State - Complete Event */
		{ Temp_Alert, Disconnect_event,  Disconnected},

		/* Temp_Alert State - Disconnect Event */
		{ Temp_Alert, Complete_event,  Average_Wait},

		/* Disconnected State - Disconnect Event */
		{ Disconnected, Last_event,  End},

};


#endif /* STATE_MACHINE_H_ */
