/*
 * char_count.c
 *
 *  Created on: Nov 17, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *      Ref: https://www.programmingsimplified.com/c-program-find-characters-frequency
 */


#include "char_count.h"
#include "logger.h"
#include "fsl_debug_console.h"
#include "UART.h"

char ip_cnt[256] = {'0'};


void application_report()
{
	for(int index=48; index<=122; index++)
	{
		char forreport[100] = {'0'};
		if(ip_cnt[index]!=0)
		{
			sprintf(forreport, "\r\n%c-%d;",index,ip_cnt[index]);

			print_string(forreport);

		}
	}


}

//uint8_t* char_count(uint8_t* character)
//{
//	ip_cnt[*character]++;
//
//	return ip_cnt;
//}

void char_count(uint8_t* character)
{
	ip_cnt[*character]++;
}
