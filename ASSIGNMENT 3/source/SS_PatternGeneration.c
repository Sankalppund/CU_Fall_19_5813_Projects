/*
 * SS_PatternGeneration.c
 *
 *  Created on: Oct 19, 2019
 *
 * Reference - 1) https://sites.google.com/site/murmurhash/
 *             2) https://stackoverflow.com/questions/7602919/how-do-i-generate-random-numbers-without-rand-function
 * Author : Author: sankalp pund and saket penurkar
 */


#include "SS_PatternGeneration.h"

/*
 * Function Name - gen_pattern
 * Description/Explanation - This function is used to create a pattern of 8 bit unsigned integers. The working
 * 							 of this pattern generator involves taking two random numbers of 4 bytes and 1 byte respectively
 * 							  which is taken as reference from the website mentioned above Ref(1).
 * 							  The hash 'h' is operated with an operation which is dependent on seed and length along with
 * 							  the constant random number (bit shifting operations).
 * 							  For more randomization the random array is filled in with the  hash number itself and seed value.
 * 							  This random generator generates the same random numbers provided the seed value is same.
 *
 * Inputs -
 * Return Value - none
 */

void gen_pattern(uint8_t * pattern, size_t length, uint8_t seed)
{
	// 'm' is mixing constant generated offline

	const unsigned int m = 0x5bd1e995;
	uint8_t r = 24;

	// Initialize the hash to a 'random' value

	uint8_t h = (seed * length) + (((m >> 8) ^ (m >> 24)) & 1 );

	for (int Global_array_index = 0; Global_array_index < length; Global_array_index ++)
	{
		*(pattern)  = h;
		pattern = pattern + 1;
		h = (h + 1) * (seed - r);
		r = r - 1;
	}

}
