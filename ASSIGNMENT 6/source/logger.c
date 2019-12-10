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
extern uint32_t cnt;


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
				PRINTF(MessageToBeLogged);
			}
			if (LOG_DEBUG == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_DEBUG", ActiveFunc, "Debug Message-", message);
				PRINTF(MessageToBeLogged);
			}
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
				PRINTF(MessageToBeLogged);
			}

			break;

		case LOG_DEBUG:
			time_stamp();
			if (LOG_DEBUG == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_DEBUG", ActiveFunc, "Debug Message-", message);
				PRINTF(MessageToBeLogged);
			}
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
				PRINTF(MessageToBeLogged);
			}

			break;

		case LOG_STATUS:
			time_stamp();
			if (LOG_STATUS == level)
			{
				const char * ActiveFunc = Function_Printed_in_Log(Function_Name);
				sprintf(MessageToBeLogged, "\r\n%s: %s: %s: %s ", "LOG_STATUS", ActiveFunc, "Status Message-" , message);
				PRINTF(MessageToBeLogged);
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

	if (ADC_INIT_FUNC == FuncName)
	{
		char * Function_char = "Function_ADC_Init";
		return Function_char;
	}

	if (ADC_TASK == FuncName)
	{
		char * Function_char = "Thread_ADC_Task";
		return Function_char;
	}

	if (DAC_INIT_FUNC == FuncName)
	{
		char * Function_char = "Function_DAC_Init";
		return Function_char;
	}

	if (DAC_TASK == FuncName)
	{
		char * Function_char = "Thread_DAC_Task";
		return Function_char;
	}

	if (READ_ADC_FUNC == FuncName)
	{
		char * Function_char = "Function_Read_ADC";
		return Function_char;
	}

	if (WRITE_DAC_FUNC == FuncName)
	{
		char * Function_char = "Function_Write_DAC";
		return Function_char;
	}

	if (DMA_CALLBACK == FuncName)
	{
		char * Function_char = "Function_DMA_Callback";
		return Function_char;
	}

	if (DMA_INITIALIZE == FuncName)
	{
		char * Function_char = "Function_DMA_Initialize";
		return Function_char;
	}

	if (DMA_ONE_SHOT_TRANSFER == FuncName)
	{
		char * Function_char = "Function_DMA_One_Shot_Transfer";
		return Function_char;
	}

	if (GEN_SINE_SAMPLE == FuncName)
	{
		char * Function_char = "Function_Gen_Sine_Sample";
		return Function_char;
	}

	if (INC_SINE_WAVE == FuncName)
	{
		char * Function_char = "Function_Inc_Sine_Wave";
		return Function_char;
	}

	if (LED_INITIALIZE == FuncName)
	{
		char * Function_char = "Function_Led_Initialize";
		return Function_char;
	}

	if (LED_OFF_FUNC == FuncName)
	{
		char * Function_char = "Function_LED_Off";
		return Function_char;
	}

	if (LED_DELAY == FuncName)
	{
		char * Function_char = "Function_LED_Delay";
		return Function_char;
	}

	if (LED_RED_FUNC == FuncName)
	{
		char * Function_char = "Function_LED_Red";
		return Function_char;
	}

	if (LED_GREEN_FUNC == FuncName)
	{
		char * Function_char = "Function_LED_Green";
		return Function_char;
	}

	if (LED_BLUE_FUNC == FuncName)
	{
		char * Function_char = "Function_LED_Blue";
		return Function_char;
	}

	if (INIT_SYSTICK == FuncName)
	{
		char * Function_char = "Function_Init_Systick";
		return Function_char;
	}

	if (CALCULATE == FuncName)
	{
		char * Function_char = "Function_Calculate";
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
	//uint32_t current_t = cnt;

	float n = (current_t/10);

	uint32_t HH = (uint32_t)(n/SEC_IN_HOUR)%60;

	uint32_t MM = (uint32_t)(n/SEC_IN_MIN)%60;

	uint32_t SS = (uint32_t)n%60;

	sprintf(time_buff, "\r\n%02d:%02d:%02d.%1d \n", HH, MM, SS, current_t%10);

	PRINTF(time_buff);

}
