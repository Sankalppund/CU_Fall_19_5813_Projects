/*
 * dma.h
 *
 *  Created on: Dec 1, 2019
 *      Author: sanka
 */

#ifndef DMA_H_
#define DMA_H_

/*
 * Includes
 */

#include "fsl_dmamux.h"
#include "fsl_dma.h"
#include "fsl_debug_console.h"
#include "frts_task.h"

/*
 * Macros
 */
#define DMA_CHANNEL (0)
#define DMA_SOURCE  (63)


/*
 * Function Prototypes
 */
void DMA_Initialize();
void DMA_One_Shot_Transfer(uint32_t* , uint32_t*, uint32_t);
void DMA_Callback(dma_handle_t *, void *);

#endif /* DMA_H_ */
