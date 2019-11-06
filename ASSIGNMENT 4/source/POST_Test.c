/*
 * POST_Test.c
 *
 *  Created on: Oct 31, 2019
 *      Author: sankalp pund & saket penurkar
 *
 * Ref: https://www.sparkfun.com/datasheets/Sensors/Temperature/tmp102.pdf
 */

#include"POST_Test.h"
#include "fsl_debug_console.h"

/*
 *  Global Variables Section
 */
int TL_Temp_Val = 0;
int TH_Temp_Val = 0;
int old_temp=0;


/*
 * Function Name - POST_Test
 * Description - This function is used to run Power on Self Test
 * Inputs - none
 * Return Value - return the status of the test
 */

post_status POST_Test()
{

	TL_Temp_Val=I2C_Read_Data(0x90U,TLOW_REG);
	TH_Temp_Val=I2C_Read_Data(0x90U,THIGH_REG);

	if(TL_Temp_Val==75 && TH_Temp_Val==80)
	{
		return Success;
	}
	else
	{
		return Failed;
	}

}


/*
 * Function Name - avg_temp
 * Description - This function is used to calculate the average of the temperatures received
 * Inputs - Temperature value and the iteration Count
 * Return Value - returns the average value of the temperature
 */

int avg_temp(int temp, int count)
{

	int avg_temp_val=(((old_temp)+temp)/(count));

	old_temp=old_temp+temp;

	return avg_temp_val;
}




