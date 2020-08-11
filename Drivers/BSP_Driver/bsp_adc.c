/***********************************************************************
*@Author: your name
*@Date: 2020-08-02 22:31:56
*@LastEditTime: 2020-08-03 11:53:16
*@LastEditors: Please set LastEditors
*@Description: In User Settings Edit
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\bsp_adc.c
***********************************************************************/
#include "bsp_adc.h"

ADC_HandleTypeDef hadc1;
bool bsp_adc_init(void)
{
    GPIO_InitTypeDef GPIO_Init;
    HAL_StatusTypeDef ADC_STATUS = HAL_OK;

    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_Init.Mode = GPIO_MODE_ANALOG;
    GPIO_Init.Pin = GPIO_PIN_3;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOC, &GPIO_Init);

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;  //90M/4
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; //right dg
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = DISABLE;
    // hadc1.Init.ExternalTrigConv = 
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.NbrOfDiscConversion = 0;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; //12BIT 
    hadc1.Init.ScanConvMode = DISABLE;
    ADC_STATUS = HAL_ADC_Init(&hadc1);
    if(ADC_STATUS == HAL_OK)
    {
        return true;
    }
    else 
    {
        return false;
    }
}


uint32_t bsp_adc_get(uint32_t adc_channl_x)
{
    uint32_t adc_val = 0;
    ADC_ChannelConfTypeDef sConfig;
    HAL_StatusTypeDef STATUS = HAL_OK;
    uint32_t time_out = 1000;
    
    sConfig.Channel = adc_channl_x;
    sConfig.Offset = 0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; //most fast
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    STATUS = HAL_ADC_Start(&hadc1);
    while(STATUS != HAL_OK)
    {
        if((time_out--) == 0)
        {
            return bsp_adc_error_callback(1);
        }
    }

    time_out = 1000;
    STATUS = HAL_ADC_PollForConversion(&hadc1,1000);
    while(STATUS != HAL_OK)
    {
        if((time_out--) == 0)
        {
            return bsp_adc_error_callback(2);
        } 
    }

    adc_val = HAL_ADC_GetValue(&hadc1);
    return adc_val;
}

uint8_t bsp_adc_error_callback(uint32_t code)
{
    DEBUG_PRINT("adc error code:%d",code);
	
	return 0;
}








