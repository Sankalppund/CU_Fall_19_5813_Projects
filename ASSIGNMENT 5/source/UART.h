/*
 * UART.h
 *
 *  Created on: Nov 13, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef UART_H_
#define UART_H_





#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)




#define INTURRUPT_ENABLE (0)

#define MCGFKKCLK (0x04000000)
//#define PORT_PCR_MUX (0x200)
#define UART0_MODE_DIS (0x00)
#define UART0_MODE (0x00)
#define BAUD_RATE_HIGH (0x00)
#define BAUD_RATE_LOW (0x0C)
#define SAMPLING_RATE (0x0F)
#define UART0_MODE_ENB (0x0C)



/*
 * Function Prototypes
 */

void Init_UART0(uint32_t);
void transmitter_wait();
void uart_transmit(char );
void receiver_wait();
char uart_receive();
void print_string(char *);
void print_num(uint16_t);
void add_cb(char);
void polling_application(uint8_t*);
void interrupt_echo(char );
void interrupt_application(uint8_t*);




#endif /* UART_H_ */
