/*
 * logger.c
 *
 * Created on: Nov 04, 2019
 * Author: Saket penurkar and Sankalp pund
 */

/* Header file */

#include "logger.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "math.h"


/* Global Variable for logger.c */

static bool log_var = false;
Logging_Level_m LogLevel;
Function_Name_m FunctioName;
char MessageToBeLogged[100]={0};
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
		//time_elapsed(time_since);

		switch (Level_for_Logging)
		{

		case LOG_TEST:
			time_stamp();
			if (LOG_TEST == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_TEST", ActiveFunc, "Test Message-", message);
				print_string(MessageToBeLogged);
			}
			if (LOG_DEBUG == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_DEBUG", ActiveFunc, "Debug Message-", message);
				print_string(MessageToBeLogged);
			}
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
				print_string(MessageToBeLogged);
			}

			break;

		case LOG_DEBUG:
			time_stamp();
			if (LOG_DEBUG == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_DEBUG", ActiveFunc, "Debug Message-", message);
				print_string(MessageToBeLogged);
			}
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
				print_string(MessageToBeLogged);
			}

			break;

		case LOG_STATUS:
			time_stamp();
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
				print_string(MessageToBeLogged);
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

	if (ADD_NEW == FuncName)
	{
		char * Function_char = "Function_Add_New";
		return Function_char;
	}

	if (APPLICATION_REPORT == FuncName)
	{
		char * Function_char = "Function_Application_Report";
		return Function_char;
	}

	if (CHAR_COUNT == FuncName)
	{
		char * Function_char = "Function_Char_Count";
		return Function_char;
	}

	if (INIT_SYSTICK == FuncName)
	{
		char * Function_char = "Function_Init_Systick";
		return Function_char;
	}

	if (INITIALIZE_BUFFER == FuncName)
	{
		char * Function_char = "Function_Initialize_Buffer";
		return Function_char;
	}

	if (REMOVE_OLD == FuncName)
	{
		char * Function_char = "Function_Remove_Old";
		return Function_char;
	}

	if (BUFFER_FULL_CHECK == FuncName)
	{
		char * Function_char = "Function_Buffer_Full_Check";
		return Function_char;
	}

	if (BUFFER_EMPTY_CHECK == FuncName)
	{
		char * Function_char = "Function_Buffer_Empty_Check";
		return Function_char;
	}

	if (DESTROY_BUFFER == FuncName)
	{
		char * Function_char = "Function_Destroy_Buffer";
		return Function_char;
	}

	if (BUFFER_VALIDATION == FuncName)
	{
		char * Function_char = "Function_Buffer_Validation";
		return Function_char;
	}

	if (RESIZE_BUFFER == FuncName)
	{
		char * Function_char = "Function_Resize_Buffer";
		return Function_char;
	}

	if (INIT_UART0 == FuncName)
	{
		char * Function_char = "Function_Init_Uart0";
		return Function_char;
	}

	if (UART_TRANSMIT == FuncName)
	{
		char * Function_char = "Function_Uart_Transmit";
		return Function_char;
	}

	if (UART_RECEIVE == FuncName)
	{
		char * Function_char = "Function_Uart_Receive";
		return Function_char;
	}

	if (TRANSMITTER_WAIT == FuncName)
	{
		char * Function_char = "Function_Transmitter_Wait";
		return Function_char;
	}

	if (RECEIVER_WAIT == FuncName)
	{
		char * Function_char = "Function_Receiver_Wait";
		return Function_char;
	}

	if (POLLING_ECHO == FuncName)
	{
		char * Function_char = "Function_Polling_Echo";
		return Function_char;
	}

	if (POLLING_APPLICATION == FuncName)
	{
		char * Function_char = "Function_Polling_Application";
		return Function_char;
	}

	if (INTERRUPT_ECHO == FuncName)
	{
		char * Function_char = "Function_Interrupt_Echo";
		return Function_char;
	}

	if (INTERRUPT_APPLICATION == FuncName)
	{
		char * Function_char = "Function_Interrupt_Application";
		return Function_char;
	}

	if (BUFFER_EMPTY_CHECK == FuncName)
	{
		char * Function_char = "Function_Buffer_Empty_Check";
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
		// ********** to be updated ******/
		//print_string(string)("%d\n",Int_Var);
	}
}


/*
 * Function Name - time_stamp
 * Description - This function is used to get the timestamp in HH:MM:SS.n format
 * Inputs - none
 * Return Value - pointer to the timestamp string
 */

void time_stamp()
{
	char time_buff[14] = {0};

	uint32_t current_t = current_time();

	float n = (current_t/10);

	uint32_t HH = (uint32_t)(n/SEC_IN_HOUR)%60;

	uint32_t MM = (uint32_t)(n/SEC_IN_MIN)%60;

	uint32_t SS = (uint32_t)n%60;

	sprintf(time_buff, "\n%02d:%02d:%02d.%1d \n", HH, MM, SS, current_t%10);

	print_string(time_buff);

}
