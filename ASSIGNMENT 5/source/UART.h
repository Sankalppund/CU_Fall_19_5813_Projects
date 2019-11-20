/*
 * UART.h
 *
 *  Created on: Nov 13, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef UART_H_
#define UART_H_



/* Macros for UART Initialization*/

#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)





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
void polling_echo();
void interrupt_application(uint8_t*);




#endif /* UART_H_ */
