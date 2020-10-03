/***********************************************************************
*@Date: 2020-07-16 01:41:15
*@LastEditors: SOLA
*@LastEditTime: 2020-07-16 08:02:29
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\bsp_time.c
***********************************************************************/
#include "bsp_time.h"

TIM_HandleTypeDef htim7; 
TIM_HandleTypeDef htim1; 

void bsp_time7_init(uint16_t arr,uint16_t psc)
{
    __HAL_RCC_TIM7_CLK_ENABLE();

    htim7.Instance=TIM7; 
    htim7.Init.Prescaler=psc; 
    htim7.Init.CounterMode=TIM_COUNTERMODE_UP; 
    htim7.Init.Period=arr; 
    htim7.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim7);

    HAL_NVIC_SetPriority(TIM7_IRQn,1,3); 
    HAL_NVIC_EnableIRQ(TIM7_IRQn); 
    HAL_TIM_Base_Start_IT(&htim7);
}

void TIM7_IRQHandler(void)
{
    if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) !=RESET)
        {
            __HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); 
        }
    }
}

void bsp_tim1_init(uint16_t arr,uint16_t psc)
{   
    TIM_OC_InitTypeDef sConfig;
    
    __HAL_RCC_TIM1_CLK_ENABLE();
    
    htim1.Instance=TIM1; 
    htim1.Init.Prescaler=psc; 
    htim1.Init.CounterMode=TIM_COUNTERMODE_UP; 
    htim1.Init.Period=arr; 
    htim1.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim1);
   
    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfig.Pulse = arr/2;
    HAL_TIM_PWM_ConfigChannel(&htim1,&sConfig,TIM_CHANNEL_1);
    
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);


    /* GPIO_Config */
}




