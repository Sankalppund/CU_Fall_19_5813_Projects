/*
 * dma.c
 *
 *  Created on: Dec 1, 2019
 *      Author: sanka
 */


/*
 * Includes
 */
#include "dma.h"


dma_handle_t g_DMA_Handle;
volatile bool g_Transfer_Done = false;
bool DMA_Transfer = false;
dma_transfer_config_t transferConfig;

void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
}


void DMA_Initialize(void)
{

    /* Configure DMAMUX */
    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);
}

void DMA_One_Shot_Transfer(uint32_t* Src_Addr, uint32_t* Dest_Addr, uint32_t Buff_Size)
{

    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_PrepareTransfer(&transferConfig, Src_Addr, sizeof(Src_Addr[0]), Dest_Addr, sizeof(Dest_Addr[0]), sizeof(Src_Addr)*Buff_Size,
                        kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
    DMA_StartTransfer(&g_DMA_Handle);
    /* Wait for DMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }

    /** Add DMA Transfer Complete Time stamp here **/

    DMA_Transfer = true;
}

