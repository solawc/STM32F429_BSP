/***********************************************************************
*@Date: 2020-07-12 18:03:34
*@LastEditors: Please set LastEditors
*@LastEditTime: 2020-08-03 11:26:51
*@FilePath: \STM32F429_BSP\Inc\main.h
***********************************************************************/
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gizwits_product.h"
#include "stdbool.h"
#include "stdio.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_time.h"
#include "bsp_i2c.h"
#include "bsp_sdram.h"
#include "bsp_lcd.h"
#include "bsp_adc.h"
#include "debug_usart.h"
#include "hc_05.h"
#include "dht11.h"
#include "board.h"
#include "rt_app.h"
#include "bsp_dma.h"
#include "bsp_spi.h"
#include "w25q64.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* Printf Debug define  */


/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void SystemClock_Config(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
