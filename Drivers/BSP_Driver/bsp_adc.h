/***********************************************************************
*@Author: your name
*@Date: 2020-08-02 22:32:04
*@LastEditTime: 2020-08-03 11:59:29
*@LastEditors: Please set LastEditors
*@Description: In User Settings Edit
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\bsp_adc.h
***********************************************************************/
#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "main.h"


bool bsp_adc_init(void);
uint32_t bsp_adc_get(uint32_t adc_channl_x);
uint8_t bsp_adc_error_callback(uint32_t code);
#endif
