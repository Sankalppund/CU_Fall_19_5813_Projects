/*
 * circular_buffer.h
 *
 *  Created on: Nov 11, 2019
 *    Author: sankalp pund & saket penurkar
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

/* Header files*/

#include <stdint.h>
#include "fsl_debug_console.h"


/* Structure for Circular buffer */

typedef struct{

	//int8_t* buffer;               // to be converted to uint32_t format
	uint32_t * buffer;
	uint32_t head;
	uint32_t tail;
	uint8_t length;

}circular_buffer;


/*Enumeration for error checking*/

typedef enum cir_buff_err
{

	INITIALIZE_BUFFER_SUCCESS,
	INITIALIZE_BUFFER_FAILED,
	ADDITION_BUFFER_SUCCESS,
	ADDITION_BUFFER_FAILED,
	REMOVE_BUFFER_SUCCESS,
	REMOVE_BUFFER_FAILED,
	BUFFER_FULL,
	BUFFER_EMPTY,
	BUFFER_PARTIAL,
	DESTROY_BUFFER_SUCCESS,
	DESTROY_BUFFER_FAILED,
	BUFFER_POINTER_VALIDATION_SUCCESS,
	BUFFER_POINTER_VALIDATION_FAILED,
	VERIFY_INITIALIZATION_SUCCESS,
	VERIFY_INITIALIZATION_FAILED,
	RESIZE_BUFFER_SUCCESS,
	RESIZE_BUFFER_FAILED,
	RESIZE_BUFFER_FULL,
	ADDITION_AFTER_RESIZE_SUCCESS,
	ADDITION_AFTER_RESIZE_FAILED

}cir_buff_err;

/* Function Prototype */

circular_buffer* initialize_buffer(uint8_t);
cir_buff_err add_new(circular_buffer*,uint32_t);
cir_buff_err remove_old(circular_buffer*);
cir_buff_err buffer_full_check(uint16_t);
cir_buff_err buffer_empty_check(uint16_t);
cir_buff_err resize_buffer(circular_buffer*);
cir_buff_err destroy_buffer(circular_buffer*);
cir_buff_err buffer_validation(circular_buffer*);
cir_buff_err verify_initilization(circular_buffer*);


#endif /* CIRCULAR_BUFFER_H_ */
