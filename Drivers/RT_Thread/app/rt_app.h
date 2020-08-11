/***********************************************************************
*@Date: 2020-07-12 18:03:34
*@LastEditors: Please set LastEditors
*@LastEditTime: 2020-08-03 11:34:52
*@FilePath: \STM32F429_BSP\Drivers\RT_Thread\app\rt_app.h
***********************************************************************/
#ifndef __rt_app_h
#define __rt_app_h

#include "main.h"



void led_task_init(void);
void key_task_init(void);
void dht11_task_init(void);
void gizwits_handle_task_init(void);
void adc_v_task_init(void);
#endif
