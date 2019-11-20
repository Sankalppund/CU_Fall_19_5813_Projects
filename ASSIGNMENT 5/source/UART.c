/*
 * UART.c
 *
 *  Created on: Nov 13, 2019
 *      Author: sankalp pund & saket penurkar
 *
 * ref: https://www.nxp.com/webapp/sps/download/preDownload.jsp
 *
 * ref: https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/Serial-Demo/src
 *
 */

/*Global Variables*/

#include "MKL25Z4.h"
#include "UART.h"
#include "circular_buffer.h"
#include "main.h"
#include "logger.h"
#include "char_count.h"
#include "ss_led_control.h"

/* Global Variables*/

extern circular_buffer* rec_ptr;

char add_char;

int rec_arr[256];

int received_flag=0;

int INT_received_flag=0;

char c_recieve=0;

/*
 * Function Name - Init_UART0
 * Description - This function is used to initialize UART0
 * Inputs - the baud rate of the UART communication
 * Return Value - none
 * ref: https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/Serial-Demo/src
 */

void Init_UART0(uint32_t baud_rate) {

	LED_OFF();
	LED_BLUE();

	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
																	| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
			UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

#if USE_UART_INTERRUPTS

	NVIC_SetPriority(UART0_IRQn, 1); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}

#if(USE_UART_INTERRUPTS)

/*
 * Function Name - uart_transmit
 * Description - This function is used to transmit a character over UART
 * Inputs - the character to be transfered.
 * Return Value - none
 */

void uart_transmit(char char_val)
{
	LED_GREEN();

	UART0->D = char_val;
}

/*
 * Function Name - uart_receive
 * Description - This function is used to receive the data over uart
 * Inputs - none
 * Return Value - returns the char received
 */
char uart_receive()
{
	LED_BLUE();

	return UART0->D;
}


#else

/*
 * Function Name - transmitter_wait
 * Description - This function is used to check whether the transmitter is available to accept a new character for transmission
 * Inputs - none
 * Return Value - none
 */

void transmitter_wait()
{
	while(!(UART0->S1 & UART_S1_TDRE_MASK));
}

/*
 * Function Name - uart_transmit
 * Description - This function is used to transmit data over UART as soon as data to be sent is ready.
 * Inputs - none
 * Return Value - none
 */

void uart_transmit(char char_val)
{
	transmitter_wait();

	UART0->D = char_val;

	LED_GREEN();
}


/*
 * Function Name - receiver_wait
 * Description - This function is used to check whether the receiver has a new character to receive
 * Inputs - none
 * Return Value - none
 */

void receiver_wait()
{
	LED_BLUE();

	while(!(UART0->S1 & UART_S1_RDRF_MASK))
	{

	}


}

/*
 * Function Name - uart_receive
 * Description - This function is used to receive data over UART.
 * Inputs - none
 * Return Value - none
 */

char uart_receive()
{
	receiver_wait();

	received_flag = 1;

	return UART0->D;
}


#endif

/*
 * Function Name - print_string
 * Description - This function is to print string data on terminal using UART0
 * Inputs - pointer to character
 * Return Value - none
 */

void print_string(char *string)
{

	while(*string != '\0')
	{
		uart_transmit(*string);

		string++;
	}
}

/*
 * Function Name - print_string
 * Description - This function is to print numeric data on terminal using UART0
 * Inputs - pointer to character
 * Return Value - none
 */

void print_num(uint16_t num)
{
	char string[20];

	sprintf(string, "%d",num);

	print_string(string);
}


/*
 * Function Name - UART0_IRQHandler
 * Description - This function is an ISR for UART0 Interrupt.
 * Inputs - none
 * Return Value - none
 */

void UART0_IRQHandler()
{

	__disable_irq();

	/* Error checking */

	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
			UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		LED_OFF();
		LED_RED();

		/*clear the error flags*/

		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;

		/*read the data register to clear RDRF*/

		c_recieve= UART0->D;

	}

	/* Transmitter interrupt received*/

	if(UART0->S1 & UART0_S1_TDRE_MASK)
	{

		/* Clearing the Transmitter interrupt*/

		UART0->C2 &= ~(UART0_C2_TIE_MASK);
	}

	/* Receiver interrupt received */

	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		LED_BLUE();

		/*Clearing the receiver interrupt by receiving the data*/

		c_recieve= UART0->D;

		INT_received_flag = 1;

#if(APPLICATION_MODE&&USE_UART_INTERRUPTS)

		/* Adding the received character from UART to circular buffer */

		add_new(TSA, c_recieve);
#endif

	}

	__enable_irq();
}

/*
 * Function Name - polling_echo
 * Description - This function is used to transmit back the received data from PC terminal in polling mode
 * Inputs - none
 * Return Value - none
 */

void polling_echo()
{
	char a = uart_receive();

	if(received_flag==1)
	{
		received_flag=0;

		LED_GREEN();

		uart_transmit(a);
	}
}


/*
 * Function Name - interrupt_echo
 * Description - This function is used to transmit back the received data from PC terminal in interrupt mode
 * Inputs - character value
 * Return Value - none
 */


void interrupt_echo(char a)
{

	if(INT_received_flag==1)
	{
		INT_received_flag=0;

		uart_transmit(a);
	}
}

/*
 * Function Name - polling_application
 * Description - This function is used to maintain the count of received character in polling mode.
 * Inputs - pointer to character
 * Return Value - none
 */

void polling_application(uint8_t* chr)
{
	if(received_flag==1)
	{
		received_flag=0;

		char_count(chr);
	}
}

/*
 * Function Name - interrupt_application
 * Description - This function is used to maintain the count of received character in interrupt mode.
 * Inputs - pointer to character
 * Return Value - none
 */
void interrupt_application(uint8_t* chr)
{

	if(INT_received_flag==1)
	{
		INT_received_flag=0;

		char_count(chr);
	}
}
