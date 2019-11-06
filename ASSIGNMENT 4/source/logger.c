/*
 * logger.c
 *
 * Created on: Nov 04, 2019
 * Author: Saket penurkar and Sankalp pund
 */

/* Header file */

#include "logger.h"

/* Global Variable for logger.c */
static bool log_var = false;
Logging_Level_m LogLevel;
Function_Name_m FunctioName;

static uint8_t Level_for_Logging = 0;


/*
 * Function Name - Log_enable
 * Description - Enables logging
 * Inputs - none
 * Return Value - none
 */

void Log_enable()
{
	log_var = true;
}

/*
 * Function Name - Log_disable
 * Description - Disable logging
 * Inputs - none
 * Return Value - none
 */
void Log_disable()
{
	log_var = false;
}

/*
 * Function Name - Log_status
 * Description - This function checks whether log is ON or OFF
 * Inputs - none
 * Return Value - bool
 */

bool Log_status()
{
	if (log_var == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Function Name - Log_level
 * Description - This function sets the log level
 * Inputs - The log level as an enum
 * Return Value - none
 */
void Log_level(Logging_Level_m LogLevel)
{
	if (LogLevel == LOG_TEST)
	{
		Level_for_Logging = LOG_TEST;
	}

	if (LogLevel == LOG_DEBUG)
	{
		Level_for_Logging = LOG_DEBUG;
	}

	if (LogLevel == LOG_STATUS)
	{
		Level_for_Logging = LOG_DEBUG;
	}
}


/*
 * Function Name - Log
 * Description - This function displays the log statement
 * Inputs - The log level, the function enum, the text message
 * Return Value - none
 */
void Log(Logging_Level_m level, Function_Name_m Function_Name, const char * message)
{

	if (log_var == true)
	{
		switch (Level_for_Logging)
		{
		case LOG_TEST:

			if (LOG_TEST == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				PRINTF( "\r\n%s: %s: %s: %s ", "LOG_TEST", ActiveFunc, "Test Message-", message);
			}
			if (LOG_DEBUG == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				PRINTF( "\r\n%s: %s: %s: %s ", "LOG_DEBUG", ActiveFunc, "Debug Message-", message);
			}
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				PRINTF( "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
			}

			break;

		case LOG_DEBUG:

			if (LOG_DEBUG == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				PRINTF( "\r\n%s: %s: %s: %s ", "LOG_DEBUG", ActiveFunc, "Debug Message-", message);
			}
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				PRINTF( "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
			}

			break;

		case LOG_STATUS:

			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				PRINTF( "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
			}

			break;
		}
	}
}


/*
 * Function Name - Function_Printed_in_Log
 * Description -
 * Inputs -
 * Return Value -
 */
const char* Function_Printed_in_Log(Function_Name_m FuncName)
{
	if (MAIN == FuncName)
	{
		char * Function_char = "Function_Main";
		return Function_char;
	}

	if (I2C_CONFIG == FuncName)
	{
		char * Function_char = "Function_I2C_Config";
		return Function_char;
	}

	if (I2C_WRITE_DATA == FuncName)
	{
		char * Function_char = "Function_I2C_Write_Data";
		return Function_char;
	}

	if (I2C_READ_DATA == FuncName)
	{
		char * Function_char = "Function_I2C_Read_Data";
		return Function_char;
	}

	if (INIT_SYSTICK == FuncName)
	{
		char * Function_char = "Function_Init_Systick";
		return Function_char;
	}

	if (POST_TEST == FuncName)
	{
		char * Function_char = "Function_POST_Test";
		return Function_char;
	}

	if (AVERAGE_TEMPERATURE == FuncName)
	{
		char * Function_char = "Function_Average_Temperature";
		return Function_char;
	}

	if (STATE_MACHINE == FuncName)
	{
		char * Function_char = "Function_State_Machine";
		return Function_char;
	}

	if (TEMP_READING_STATE == FuncName)
	{
		char * Function_char = "Function_Temp_Reading_State";
		return Function_char;
	}

	if (AVERAGE_WAIT_STATE == FuncName)
	{
		char * Function_char = "Function_Average_Wait_State";
		return Function_char;
	}

	if (TEMP_ALERT_STATE == FuncName)
	{
		char * Function_char = "Function_Temp_Alert_State";
		return Function_char;
	}

	if (DISCONNECTED_STATE == FuncName)
	{
		char * Function_char = "Function_Disconnected";
		return Function_char;
	}

	if (END_STATE == FuncName)
	{
		char * Function_char = "Function_End_State";
		return Function_char;
	}

	if (TABLE_STATE_MACHINE == FuncName)
	{
		char * Function_char = "Function_Table_State_Machine";
		return Function_char;
	}

	if (TRANSITION_IN_TABLE == FuncName)
	{
		char * Function_char = "Function_Transition_in_Table";
		return Function_char;
	}

	if (CHECK_DISCONNECT_EVENT == FuncName)
	{
		char * Function_char = "Function_Check_Disconnect_Event";
		return Function_char;
	}

	if (SYSTICK_HANDLER == FuncName)
	{
		char * Function_char = "Function_Systick_Handler";
		return Function_char;
	}
}


/*
 * Function Name - Log_integer
 * Description - This function display an integer
 * Inputs - integer to be dispalyed
 * Return Value - none
 */

void Log_integer(int Int_Var)
{
	if (log_var == true)
	{
		PRINTF("%d\n",Int_Var);
	}
}
