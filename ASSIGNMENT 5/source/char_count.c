/*
 * char_count.c
 *
 *  Created on: Nov 17, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *      Ref: https://www.programmingsimplified.com/c-program-find-characters-frequency
 */

/* Header files*/

#include "char_count.h"
#include "logger.h"
#include "fsl_debug_console.h"
#include "UART.h"


/* Global Variables */

char ip_cnt[256] = {'0'};


/*
 * Function Name - application_report
 * Description - This function displays the report showing all characters received along with respective count.
 * Inputs - none
 * Return Value - none
 */

void application_report()
{
	for(int index=48; index<=122; index++)
	{
		char forreport[100] = {'0'};
		if(ip_cnt[index]!=0)
		{
			sprintf(forreport, " %c -> %d;",index,ip_cnt[index]);

			print_string(forreport);

		}
	}

	for(int index=48; index<=122; index++)
	{
		ip_cnt[index]=0;
	}


}

/*
 * Function Name - char_count
 * Description - This function maintains the number of count of received characters in an array.
 * Inputs - pointer to uint8_t
 * Return Value - none
 */

void char_count(uint8_t* character)
{
	ip_cnt[*character]++;
}
