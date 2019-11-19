/*
 * UART.c
 *
 *  Created on: Nov 13, 2019
 *      Author: sankalp pund & saket penurkar
 *
 * ref: https://www.nxp.com/webapp/sps/download/preDownload.jsp
 *
 * ref: https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/Serial-Demo/src
 */


#include "MKL25Z4.h"
#include "UART.h"
#include "circular_buffer.h"
#include "main.h"
#include "logger.h"
#include "char_count.h"

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
 * Inputs - the character to be transfered
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
 * Description - This function is used to wait till the data is ready to be sent
 * Inputs - none
 * Return Value - none
 */
void transmitter_wait()
{
	while(!(UART0->S1 & UART_S1_TDRE_MASK));
}

/*
 * Function Name - uart_transmit
 * Description - This function is used to block transmission over UART till the transmit data is ready
 * Inputs - none
 * Return Value - none
 */
void uart_transmit(char char_val)
{
	//LED_OFF();

	transmitter_wait();

	UART0->D = char_val;

	LED_GREEN();
}


/*
 * Function Name - uart_transmit
 * Description - This function is used to block transmission over UART till the transmit data is ready
 * Inputs - none
 * Return Value - none
 */
void receiver_wait()
{
	//LED_OFF();
	LED_BLUE();
	while(!(UART0->S1 & UART_S1_RDRF_MASK))
		{

		}
	//LED_BLUE();
	//LED_OFF();

}

char uart_receive()
{
	receiver_wait();

	received_flag = 1;

	return UART0->D;
}


#endif


void print_string(char *string)
{

	while(*string != '\0')
	{
		//transmitter_wait();

		uart_transmit(*string);

		string++;
	}
}


void print_num(uint16_t num)
{
	char string[20];

	sprintf(string, "%d",num);

	print_string(string);
}


void add_cb(char ch)
{
	add_new(rec_ptr, ch);
}



void UART0_IRQHandler()
{

	__disable_irq();


	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
			UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		LED_OFF();
		LED_RED();

		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;

		// read the data register to clear RDRF
		c_recieve= UART0->D;

	}

	if(UART0->S1 & UART0_S1_TDRE_MASK)
	{
		UART0->C2 &= ~(UART0_C2_TIE_MASK);

	}

	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		LED_BLUE();
		c_recieve= UART0->D;

		INT_received_flag = 1;

#if(APPLICATION_MODE)
		add_new(TSA, c_recieve);
#endif

	}



	__enable_irq();
}



void polling_echo()
{
	char a = uart_receive();

	if(received_flag==1)
	{
		received_flag=0;

		LED_OFF();
		LED_GREEN();

		uart_transmit(a);
	}
}



void interrupt_echo(char a)
{

	//char a = uart_receive();

	if(INT_received_flag==1)
	{
		//add_new(TSA, ch_to_send);

		INT_received_flag=0;

		uart_transmit(a);
	}
}

void polling_application(uint8_t* chr)
{
	if(received_flag==1)
	{
		received_flag=0;

		char_count(chr);

	}
}


void interrupt_application(uint8_t* chr)
{

	if(INT_received_flag==1)
	{
		INT_received_flag=0;

		char_count(chr);
	}
}
