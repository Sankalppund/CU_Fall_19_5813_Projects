/*
 * logger.c
 *
 *  Created on: Oct 22, 2019
 *      Author: saket penurkar and sankalp pund
 */

/* Header file */

#include "logger.h"

/* Global Variable for logger.c */

static bool log_var = false;


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
 * Function Name - Log_data
 * Description - This function display in hexadecimal an address and contents of a memory location
 * Inputs - pointer to a sequence of bytes and a specified length
 * Return Value - none
 */

void Log_data(uint8_t * Start_address, size_t size_of_array)
{
	if (log_var == true)
	{
#ifdef HOST_MACHINE
		printf ("\r\n== The contents of the array are ==\n");
		for (int i = 0; i < size_of_array; i++)
		{
			printf ("\r%x", Start_address[i]);
		}
#endif
#ifdef KL25Z
		PRINTF ("\r\n== The contents of the array are ==\n");
		for (int i = 0; i < size_of_array; i++)
		{
			PRINTF ("\r%x", Start_address[i]);
		}
#endif
	}
}

/*
 * Function Name - Log_string
 * Description - This function display string
 * Inputs - string to be printed
 * Return Value - none
 */
void Log_string(const char * strint_to_be_printed)
{
	if (log_var == true)
	{
#ifdef HOST_MACHINE
		printf("\r\n== %s ==\n", strint_to_be_printed);
#endif
#ifdef KL25Z
		PRINTF("\r\n== %s ==\n", strint_to_be_printed);
#endif
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
#ifdef HOST_MACHINE
		printf("\r\n%d\n", Int_Var);
#endif
#ifdef KL25Z
		PRINTF("\r\n           %d\n",Int_Var);
#endif
	}
}
