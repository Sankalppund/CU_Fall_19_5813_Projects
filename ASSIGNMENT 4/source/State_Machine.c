/*
 * State_Machine.c
 *
 * Created on: Oct 31, 2019
 * Author: Sankalp Pund & Saket Penurkar
 */

/*
 * Headers Section
 */
#include "State_Machine.h"
/*
 * Global Variables Section
 */
state current_state = Temp_Reading;
System_Event Event;

int Temp_Val=0;
int iteration_val =0;
int avg_val=0;
int timeout_cnt=0;
int timeout_cnt_2=0;
extern int DICON_FLAG;

bool State_Transition_Var = false;

/*
 * Function Name - state_machine
 * Description - This function runs the State machine which is event based
 * Inputs - none
 * Return Value - none
 */
void state_machine()
{

	State_Transition_Var = false;

	switch(current_state)
	{
	case Temp_Reading:

		LED_GREEN();

		Log(LOG_DEBUG, STATE_MACHINE, "Inside the Temperature Reading State of State Machine 1");

		current_state = Temp_Reading_State();

		break;

	case Average_Wait:

		LED_GREEN();

		Log(LOG_DEBUG, STATE_MACHINE, "Inside the Average Test State of State Machine 1");

		current_state = Average_Wait_State();

		break;

	case Temp_Alert:

		LED_BLUE();

		Log(LOG_DEBUG, STATE_MACHINE, "Inside the Temperature Alert State of State Machine 1");

		current_state = Temp_Alert_State();


		break;

	case Disconnected:

		LED_RED();

		Log(LOG_DEBUG, STATE_MACHINE, "Inside the Disconnected State of State Machine 1");

		current_state = End;

		break;


	case End:

		LED_RED();

		Log(LOG_DEBUG, STATE_MACHINE, "***************PROGRAM END*****************");

		current_state = End_State();

		break;
	}
}

/*
 * Function Name - table_state_machine
 * Description - This function runs the State machine which is table driven
 * Inputs - none
 * Return Value - none
 */
void table_state_machine(state current_state)
{
	Log(LOG_STATUS, TABLE_STATE_MACHINE , "Inside the Table state machine");
	System_Event Event_code;
	int (* state_fun)(void);

	while( State_Transition_Var != true)
	{
		state_fun = State[current_state];

		Event_code = state_fun();

		current_state = Transition_in_Table(current_state, Event_code);

	}
}

/*
 * Function Name - Transition_in_Table
 * Description - This function is called when the ttansitiosn from one state to other needs to be done in a table based approach
 * Inputs - none
 * Return Value - enum value of state type
 */
state Transition_in_Table ( state CR , System_Event EC)
{
	Log(LOG_STATUS, TRANSITION_IN_TABLE , "Inside the Table state machine");

	uint8_t maximum_items = 0;
	state Next_State;

	maximum_items = sizeof(State_Transition_Table) / sizeof(State_Transition_Table[0]);

	for(int i = 0; i < maximum_items; i++)
	{
		if ((State_Transition_Table[i].Current_State == CR) && (State_Transition_Table[i].Event_Table == EC))
		{
			Next_State = State_Transition_Table[i].Next_State;
			break;
		}
	}

	return Next_State;

}

/*
 * Function Name - Temp_Reading_State
 * Description - This function is called when the temperature reading state of the state machine is executed
 * Inputs - none
 * Return Value - enum value of state type
 */

state Temp_Reading_State(void)
{

	Log(LOG_TEST, TEMP_READING_STATE, "Inside Temp_Reading State");

	I2C_Read_Dat(SLAVE_ADDR,REG_ADDR);

	if (DICON_FLAG==1)
	{
		DICON_FLAG=0;

		return current_state = Disconnected;
	}

	Temp_Val=I2C_Read_Data(SLAVE_ADDR,REG_ADDR);

	if(complete_event(Temp_Val))
	{
		current_state = Average_Wait;
	}

	if(alert_event(Temp_Val))
	{
		current_state = Temp_Alert;
	}

	return current_state;


}

/*
 * Function Name - Temp_Reading_Func_for_Event
 * Description - This function runs the State machine in table based version and is called to read the temperature
 * Inputs - none
 * Return Value - enum value of System_Value
 */

System_Event Temp_Reading_Func_for_Event(void)
{

	LED_GREEN();

	PRINTF("\r\nState Machine 2 Temp_Reading State.");

	I2C_Read_Dat(0x90,0x00);

	if (DICON_FLAG==1)
	{
		DICON_FLAG=0;

		return Event = Disconnect_event;
	}

	Temp_Val=I2C_Read_Data(SLAVE_ADDR,REG_ADDR);

	if(complete_event(Temp_Val))
	{
		Event = Complete_event;
	}

	if(alert_event(Temp_Val))
	{
		Event = Alert_event;
	}

	return Event;

}

/*
 * Function Name - Average_Wait_State
 * Description - This function runs the State machine in the Average wait state in the event based state machine mode
 * Inputs - none
 * Return Value - enum value of state type
 */

state Average_Wait_State(void)
{

	if(timeout_cnt==1)
	{
		timeout_cnt=0;

		I2C_Read_Dat(0x90,0x00);

		if (DICON_FLAG==1)
		{
			DICON_FLAG=0;

			return current_state = Disconnected;
		}

		Log(LOG_STATUS, AVERAGE_WAIT_STATE, "Current Temperature Value is");
		Log_integer(Temp_Val);

		avg_val=avg_temp(Temp_Val,iteration_val);

		Log(LOG_STATUS, AVERAGE_WAIT_STATE, "Average Temperature Value is");
		Log_integer(avg_val);

		current_state = Temp_Reading;

		timeout_cnt_2++;

	}

	if(timeout_cnt_2==4)
	{
		timeout_cnt_2=0;

		PRINTF("\r\n\nShifting from #State Machine 1>>>>>>>>State Machine 2#");
		// Temp_read state of next state machine.
		Resetting_Global_Var();
		// call table_state_machine() function here  --- pass 'current_state' as 'Temp_reading' state
		table_state_machine(Temp_Reading);
	}

	return current_state;
}

/*
 * Function Name - Average_Wait_Func_for_Event
 * Description - This function is called when the average wait state needs to return an event in the state machine using table
 * Inputs - none
 * Return Value - enum value of System_Event type
 */

System_Event Average_Wait_Func_for_Event(void)
{
	LED_GREEN();

	if(timeout_cnt==1)
	{
		PRINTF("\r\nState Machine 2 Average Wait State.");

		timeout_cnt=0;

		I2C_Read_Dat(0x90,0x00);

		if (DICON_FLAG==1)
		{
			DICON_FLAG=0;

			return Event = Disconnect_event;
		}


		PRINTF("\r\n\nCurrent Temperature Value = %dC",Temp_Val);
		//Log(LOG_TEST, AVERAGE_WAIT_STATE, "\r\n\nCurrent Temperature Value = %dC",Temp_Val);

		avg_val=avg_temp(Temp_Val,iteration_val);

		PRINTF("\r\nAverage Temperature Value = %dC",avg_val,167);


		Event = Timeout_event;


		timeout_cnt_2++;
	}

	if(timeout_cnt_2==4)
	{
		timeout_cnt_2=0;

		PRINTF("\r\n\nShifting from #State Machine 2>>>>>>>>State Machine 1#");

		State_Transition_Var = true;

		// Temp_read state of next state machine.
		Resetting_Global_Var();

		// call table_state_machine() function here  --- pass 'current_state' as 'Temp_reading' state
		table_state_machine(Temp_Reading);
	}

	return Event;

}



/*
 * Function Name - Temp_Alert_State
 * Description -  This function is called when the alert state is reached in the state machine using events
 * Inputs - none
 * Return Value - state value value enum
 */

state Temp_Alert_State(void)
{

	I2C_Read_Dat(0x90,0x00);

	if (DICON_FLAG==1)
	{
		DICON_FLAG=0;

		return current_state = Disconnected;
	}

	if(complete_event(Temp_Val))
	{
		 current_state = Average_Wait;
	}

	return current_state;
}


/*
 * Function Name - Temp_Alert_Func_for_Event
 * Description - This function is called when the alert state is reached in the state machine using table
 * Inputs - none
 * Return Value - event enum of 'System_Event' type
 */

System_Event Temp_Alert_Func_for_Event(void)
{
	LED_BLUE();

	I2C_Read_Dat(0x90,0x00);

	if (DICON_FLAG==1)
	{
		DICON_FLAG=0;

		return Event = Disconnect_event;
	}

	if(complete_event(Temp_Val))
	{
		PRINTF("\r\nState Machine 2 Temp Alert State.");

		Event = Complete_event;
	}

	return Event;
}


/*
 * Function Name - Disconnected_State
 * Description - This function is called whenever a Disconnect event is observed for state machine using event
 * Inputs - none
 * Return Value - enum of value of 'state' type
 */

state Disconnected_State(void)
{
	PRINTF("\nInside the Disconnected\n");

	current_state=End;

	return current_state;

}


/*
 * Function Name - Disconnected_State_Func_for_Event
 * Description - This function is called whenever a Disconnect event is observed for state machine using table
 * Inputs - none
 * Return Value - Enum Vakue of Event 'System_Event' type
 */

System_Event Disconnected_State_Func_for_Event(void)
{
	LED_RED();

	PRINTF("\r\nState Machine 2 disconnected State.");

	Event = Last_event;
	return Event;
}


/*
 * Function Name - End_State
 * Description - This function runs when the State machine has reached to its last state
 * Inputs - none
 * Return Value - enum of type 'state'
 */
state End_State(void)
{
	// logic for the end state...........while(1)?

	PRINTF("\n\r >>>>> END END END END END END END >>>>>\n");

	PRINTF("\r\n PROCEDURE COMPLETE \n");

	return current_state;
}


/*
 * Function Name - End_State_Func_for_Event
 * Description - This function runs when the last state of the program is reached
 * Inputs - none
 * Return Value - Enum of System_Event tyoe
 */

System_Event End_State_Func_for_Event(void)
{

	LED_RED();

	PRINTF("\n\r >>>>> END END END END END END END >>>>>\n");

	PRINTF("\r\n PROCEDURE COMPLETE \n");

	return Event;
}


/*
 * Function Name - Resetting_Global_Var
 * Description - This function resets the flags/variables, called inside the function
 * Inputs - none
 * Return Value - none
 */

void Resetting_Global_Var()
{
	timeout_cnt=0;
	timeout_cnt_2=0;
}

