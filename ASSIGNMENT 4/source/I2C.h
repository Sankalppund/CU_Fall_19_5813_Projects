/*
 * I2C.h
 *
 *  Created on: Oct 30, 2019
 *  Author: Sankalp Pund & Saket Penurkar
 */

#ifndef I2C_H_
#define I2C_H_

/*  SDK Included Files */
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "Driver_I2C.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "MKL25Z4.h"
#include "logger.h"

/* #define for I2C clocks, Ports & Pins */

#define SLAVE_ADDR (0x90U)
#define REG_ADDR (0x00U)

#define I2C_MASTER Driver_I2C0
#define I2C_SDA_PORT PORTE
#define I2C_SCL_PORT PORTE
#define I2C_SDA_GPIO GPIOE
#define I2C_SDA_PIN 25U
#define I2C_SCL_GPIO GPIOE
#define I2C_SCL_PIN 24U

#define I2C_MASTER_START (I2C0->C1 |= I2C_C1_MST_MASK)
#define I2C_MASTER_STOP  (I2C0->C1 &= ~I2C_C1_MST_MASK)
#define I2C_MASTER_RESTART (I2C0->C1 |= I2C_C1_RSTA_MASK)
#define I2C_TRANSFER     (I2C0->C1 |= I2C_C1_TX_MASK)
#define I2C_RECEIVE      (I2C0->C1 &= ~I2C_C1_TX_MASK)
#define I2C_DELAY        while((I2C0->S & I2C_S_IICIF_MASK)==0){}\
	                            I2C0->S|= I2C_S_IICIF_MASK;
#define NACK (I2C0->C1|=I2C_C1_TXAK_MASK)
#define ACK  (I2C0->C1 &= ~I2C_C1_TXAK_MASK)

/*
 * Globals Variables Section
 */

typedef uint8_t u8;

bool alert_event(int);

bool complete_event(int);

/*
 * Function Prototypes
 */

void check_connection(u8 slave_addr);

#endif /* I2C_H_ */
