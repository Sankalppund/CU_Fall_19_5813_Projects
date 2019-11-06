/*
 * POST_Test.h
 *
 *  Created on: Oct 31, 2019
 *      Author: sankalp pund & saket penurkar
 */

#ifndef POST_TEST_H_
#define POST_TEST_H_

/*
 * Macros Section
 */
#define TLOW_REG (0x02U)
#define THIGH_REG (0x03U)

/*
 * Enum for the POST Test
 */
typedef enum post_status
{
	Success,
	Failed

}post_status;




#endif /* POST_TEST_H_ */
