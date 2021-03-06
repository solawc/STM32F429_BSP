/*
 * @Author: your name
 * @Date: 2020-08-28 06:37:14
 * @LastEditTime: 2020-08-28 06:50:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \STM32F429_BSP\Drivers\BSP_Driver\bsp_dma.h
 */

#ifndef __bsp_dma_h
#define __bsp_dma_h

#include "main.h"

#define USR_USART1_DMA              0

#if USR_USART1_DMA
#define DEBUG_DMA_ERROR(fmt)     debug_dma_printf(fmt)    
#define DEBUG_DMA_PRINT(fmt)     debug_dma_printf(fmt)
#else 
#define DEBUG_DMA_ERROR(fmt)         
#define DEBUG_DMA_PRINT(fmt)     
#endif

uint8_t bsp_usart1_dma2_init(void);
void debug_dma_printf(uint8_t *str);
#endif
