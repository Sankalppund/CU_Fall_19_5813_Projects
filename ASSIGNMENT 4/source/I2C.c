/*
 * I2C.c
 *
 *  Created on: Oct 30, 2019
 *  Author: Sankalp Pund & Saket Penurkar
 *
 *  Ref:-> Lecture Slides:I2C Communications
 */

#include"I2C.h"

int DICON_FLAG=0;

/*
 * Function Name - I2C_Config
 * Description - This function is used to configure the I2C port for the KL25Z FRDM Board
 * Inputs - none
 * Return Value - none
 */

void I2C_Config(void)
{
	/* Enable clock for I2C0 module & Port E */

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	/* Configure PINS for I2C */

	PORTC->PCR[8] |=  PORT_PCR_MUX(2);

	PORTC->PCR[9] |=  PORT_PCR_MUX(2);


	I2C0->F = I2C_F_ICR(0x11)|I2C_F_MULT(0);

	/* Enable I2C & Master Mode*/

	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	/* Config High drive mode */

	I2C0->C2 |= (I2C_C2_HDRS_MASK);

	//I2C0->SLTH |= I2C_SLTH_SSLT(0x01);

}


/*
 * Function Name - I2C_Write_Data
 * Description - This function is used to write to the slave address using I2C Communication
 * Inputs - slave address, register address where data is to be written, data to be written
 * Return Value - none
 */

void I2C_Write_Data(u8 slave_addr, u8 reg_addr, u8 dat)
{
	I2C_TRANSFER;

	I2C_MASTER_START;

	I2C0->D = slave_addr;

	I2C_DELAY;

	I2C0->D = reg_addr;

	I2C_DELAY;

	I2C0->D = dat;

	I2C_DELAY;

	I2C_MASTER_STOP;

}


/*
 * Function Name - I2C_Read_Data
 * Description - This function is used to Read from the slave address using I2C Communication
 * Inputs - slave address, register address from where the data is to be read
 * Return Value - temperature value (int type)
 */

int I2C_Read_Data(u8 slave_addr, u8 reg_addr)
{

	int16_t data;

	int8_t data_0;

	int8_t data_1;

	int8_t temp,temp_c,N_temp;

	I2C_TRANSFER;

	I2C_MASTER_START;

	I2C0->D = slave_addr;

	I2C_DELAY;

	I2C0->D = reg_addr;

	I2C_DELAY;

	I2C_MASTER_RESTART;

	I2C0->D = (slave_addr|0x1);

	I2C_DELAY;

	I2C_RECEIVE;

	ACK;

	data_0=I2C0->D;

	I2C_DELAY;

	data_0=I2C0->D;

	I2C_DELAY;

	NACK;

	data_1=I2C0->D;

	I2C_DELAY;

	I2C_MASTER_STOP;

	data=((data_0<<4)+(data_1>>4));

	temp_c=(data*0.0625);

	return (temp_c);

}

/*
 * Function Name - alert_event
 * Description - This function is used to check whether the alert condition is activated or not
 * Inputs - temperature
 * Return Value - bool true/false
 */
bool alert_event(int Temperature_for_alert)
{
	if(Temperature_for_alert < 0)
	{
		return true;
	}

	return false;
}


/*
 * Function Name - complete_event
 * Description - This function is used to check whether event is complete or not
 * Inputs - temperature
 * Return Value - bool true/false
 */
bool complete_event(int Temperature_for_complete)
{
	if(Temperature_for_complete >=0 || Temperature_for_complete < 0)
	{
		//complete_flag=true;

		return true;
	}

	return false;
}

/*
 * Function Name - check_disconnect_event
 * Description - This function is used to check whether I2C0->S & I2C_S_IICIF_MASK is set or not.
 * Return Value - int
 */
int check_disconnect_event()
{

	volatile uint16_t discon=0;

	while((I2C0->S & I2C_S_IICIF_MASK)==0)
	{
		discon++;

		if(discon>250)
		{
			break;
		}
	}

	I2C0->S|= I2C_S_IICIF_MASK;

	if(discon>250)
	{
		Log(LOG_STATUS, CHECK_DISCONNECT_EVENT, "Disconnected Event has Occured");

		DICON_FLAG=1;
	}

return 0;

}


/*
 * Function Name - I2C_Read_Dat(uint8_t, uint8_t)
 * Description - This function is used to check whether the slave is in disconnected state or not
 * Inputs - none
 * Return Value - none
 */

void I2C_Read_Dat(u8 slave_addr, u8 reg_addr)
{

	int16_t data;

	int8_t data_0;

	int8_t data_1;

	int8_t temp,temp_c,N_temp;

	I2C_TRANSFER;

	I2C_MASTER_START;

	I2C0->D = slave_addr;

	check_disconnect_event();


}

