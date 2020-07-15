/***********************************************************************
*@Date: 2020-07-16 01:41:15
*@LastEditors: SOLA
*@LastEditTime: 2020-07-16 02:35:26
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\bsp_time.c
***********************************************************************/
#include "bsp_time.h"

TIM_HandleTypeDef htim7; 
void bsp_time7_init(uint16_t arr,uint16_t psc)
{
    __HAL_RCC_TIM7_CLK_ENABLE();//使能 TIM3 时钟

    htim7.Instance=TIM7; //通用定时器 7
    htim7.Init.Prescaler=psc; //分频系数
    htim7.Init.CounterMode=TIM_COUNTERMODE_UP; //向上计数器
    htim7.Init.Period=arr; //自动装载值
    htim7.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&htim7);

    HAL_NVIC_SetPriority(TIM7_IRQn,1,3); //设置中断优先级，抢占优先级 1，子优先级 3
    HAL_NVIC_EnableIRQ(TIM7_IRQn); //开启 ITM7 中断
    HAL_TIM_Base_Start_IT(&htim7);//使能定时器 7 更新中断： TIM_IT_UPDATE
}

void TIM7_IRQHandler(void)
{
    rt_enter_critical();
    if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) !=RESET)
        {
            __HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
            // gizTimerMs();//系统毫秒定时
        }
    }
    rt_exit_critical();
}

