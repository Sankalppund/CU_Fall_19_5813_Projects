/*
 * circular_buffer.c
 *
 *  Created on: Nov 11, 2019
 *      Author: sankalp pund & saket penurkar
 *
 *
 * ref: https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
 * ref: https://embedjournal.com/implementing-circular-buffer-embedded-c/
 * ref: https://www.geeksforgeeks.org/g-fact-66/
 */


#include "circular_buffer.h"
#include "main.h"
#include "stddef.h"
#include "logger.h"

uint16_t count=0;
int16_t old_data=0;
int16_t resize = 1;


/*
 * Function Name - initialize_buffer
 * Description - This function is used to initialize the buffer
 * Inputs - data_length to set buffer length
 * Return Value - pointer to circular_buffer
 */

circular_buffer* initialize_buffer(uint8_t data_length)
{

	LED_BLUE();

	circular_buffer* circular_pointer = (circular_buffer*)malloc(sizeof(circular_buffer));

	circular_pointer->buffer = (int8_t*)malloc(sizeof(data_length));

	circular_pointer->head=0;

	circular_pointer->tail=0;

	circular_pointer->length = data_length;


	count = 0;

	return (circular_pointer);
}


/*
 * Function Name - add_new
 * Description - This function is used to add new data into circular buffer
 * Inputs - pointer to circular_buffer structure and new data to be added
 * Return Value - enum
 */

cir_buff_err add_new(circular_buffer*cir_ptr, uint8_t new_item)
{


	if(buffer_full_check(count) == BUFFER_EMPTY || buffer_full_check(count) == BUFFER_PARTIAL)
	{

		if(cir_ptr->head == cir_ptr->buffer + cir_ptr->length-1)
		{
			cir_ptr->buffer[cir_ptr->head] = new_item;

			cir_ptr->head = cir_ptr->buffer;

			//PRINTF("\r\nNew Item inserted at position %d = %d",cir_ptr->head,cir_ptr->buffer[cir_ptr->head]);

			count++;

			return ADDITION_BUFFER_SUCCESS;
		}
		else
		{

			cir_ptr->buffer[cir_ptr->head] = new_item;

			Log(LOG_TEST, ADD_NEW, "\r\nNew Value Added to Circular Buffer");

			count++;

			cir_ptr->head++;


			return ADDITION_BUFFER_SUCCESS;

		}
	}
	else
	{

		if(buffer_full_check(count) == BUFFER_FULL||buffer_full_check(count) == RESIZE_BUFFER_FULL)
		{

			resize_buffer(cir_ptr);

			cir_ptr->buffer[cir_ptr->head] = new_item;

			//PRINTF("\r\nNew Item inserted at position %d = %d",cir_ptr->head,cir_ptr->buffer[cir_ptr->head]);

			count++;

			cir_ptr->head++;

			return ADDITION_AFTER_RESIZE_SUCCESS;
		}
		else
		{
			return ADDITION_AFTER_RESIZE_FAILED;
		}

		return ADDITION_BUFFER_FAILED;

	}

}

/*
 * Function Name - remove_old
 * Description - This function is used to remove old item from circular buffer
 * Inputs - pointer to circular_buffer structure
 * Return Value - enum
 */

cir_buff_err remove_old(circular_buffer*cir_ptr)
{

	if(buffer_empty_check(count)== BUFFER_FULL || buffer_empty_check(count) == BUFFER_PARTIAL)
	{
		if(cir_ptr->tail == cir_ptr->buffer + cir_ptr->length-1)
		{
			//old_data = cir_ptr->buffer[cir_ptr->tail];

			old_data = cir_ptr->tail;

			cir_ptr->tail = cir_ptr->buffer;

			//PRINTF("\r\nOld item removed at position %d = %d",cir_ptr->head-count,cir_ptr->buffer[cir_ptr->head]);

			count--;

			return REMOVE_BUFFER_SUCCESS;
		}
		else
		{
			//old_data = cir_ptr->buffer[cir_ptr->tail];

			old_data = cir_ptr->tail;

			//PRINTF("\r\nOld item removed at position %d = %d %d %d",cir_ptr->head-count,old_data, cir_ptr->tail);

			cir_ptr->tail++;

			count--;

			return REMOVE_BUFFER_SUCCESS;
		}
	}
	else
	{
		return REMOVE_BUFFER_FAILED;
	}

}

/*
 * Function Name - buffer_full_check
 * Description - This function is used to check if buffer is full
 * Inputs - count value from add_new and remove_old functions
 * Return Value - enum
 */

cir_buff_err buffer_full_check(uint16_t count)
{
	if(count==0)
	{
		return BUFFER_EMPTY;
	}
	if(count==NO_OF_ELEMENTS)
	{
		return BUFFER_FULL;
	}
	if(count==(NO_OF_ELEMENTS*resize))
	{
		return RESIZE_BUFFER_FULL;
	}
	else
	{
		return BUFFER_PARTIAL;
	}
}

/*
 * Function Name - buffer_empty_check
 * Description - This function is used to check if buffer in empty
 * Inputs - count value from add_new and remove_old functions
 * Return Value - enum
 */

cir_buff_err buffer_empty_check(uint16_t count)
{
	if(count==0)
	{
		return BUFFER_EMPTY;
	}
	if(count==NO_OF_ELEMENTS)
	{
		return BUFFER_FULL;
	}
	if(count==(NO_OF_ELEMENTS*resize))
	{
		return RESIZE_BUFFER_FULL;
	}
	else
	{
		return BUFFER_PARTIAL;
	}
}

/*
 * Function Name - destroy_buffer
 * Description - This function is used to reset the buffer
 * Inputs - pointer to circular_buffer structure
 * Return Value - enum
 */

cir_buff_err destroy_buffer(circular_buffer*cir_ptr)
{
	if(cir_ptr->buffer==NULL)
	{
		return DESTROY_BUFFER_FAILED;
	}
	else
	{
		free(cir_ptr);

		return DESTROY_BUFFER_SUCCESS;
	}
}

/*
 * Function Name - buffer_validation
 * Description - This function is used to check if buffer pointer is valid
 * Inputs - pointer to circular_buffer structure
 * Return Value - enum
 */

cir_buff_err buffer_validation(circular_buffer*cir_ptr)
{
	if(cir_ptr->buffer==NULL)
	{
		return BUFFER_POINTER_VALIDATION_FAILED;
	}
	else
	{
		return BUFFER_POINTER_VALIDATION_SUCCESS;
	}
}

/*
 * Function Name - verify_initilization
 * Description - This function is used to check if buffer is initialized
 * Inputs - pointer to circular_buffer structure
 * Return Value - enum
 */

cir_buff_err verify_initilization(circular_buffer*cir_ptr)
{
	if(cir_ptr->buffer==NULL)
	{
		return VERIFY_INITIALIZATION_FAILED;
	}
	else
	{
		return VERIFY_INITIALIZATION_SUCCESS;
	}
}

/*
 * Function Name - resize_buffer
 * Description - This function is used to resize the buffer when overfill error occurs.
 * Inputs - pointer to circular_buffer structure
 * Return Value - enum
 */

cir_buff_err resize_buffer(circular_buffer*cir_ptr)
{

	//PRINTF("\r\nResizing the buffer after overfill error.");

	cir_ptr->buffer = (int8_t*)realloc(cir_ptr->buffer, (cir_ptr->length)*2);

	cir_ptr->length = (cir_ptr->length)*2;

	resize++;

	if(cir_ptr->buffer==NULL)
	{
		return RESIZE_BUFFER_FAILED;
	}
	else
	{
		return RESIZE_BUFFER_SUCCESS;
	}

}
