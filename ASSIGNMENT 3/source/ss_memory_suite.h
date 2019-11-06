/*
 * ss_memory_suite.h
 *
 *  Created on: Oct 19, 2019
 *      Author: sankalp pund and saket penurkar
 */

#ifndef SS_MEMORY_SUITE_H_
#define SS_MEMORY_SUITE_H_


/* Enum to check the return status of the memory test functions */

typedef enum mem_status
{
	Success,
	Failed,
	Invert_success,
	Invert_failed,
	Write_Pattern_success,
	Write_Pattern_failed

}mem_status;



/* Prototype of functions */

uint32_t * allocate_words(size_t);
void free_words(uint32_t *);
void display_memory(uint32_t *, size_t);
mem_status write_memory(uint32_t *, uint16_t);
mem_status invert_block(uint32_t *, size_t);
mem_status write_pattern(uint32_t *, size_t, int8_t);
uint32_t * verify_pattern(uint32_t *, size_t, int8_t);
uint32_t * get_address(uint32_t *, uint32_t *);
void status_return(mem_status);


#endif /* SS_MEMORY_SUITE_H_ */
