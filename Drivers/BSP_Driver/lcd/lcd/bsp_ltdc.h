/***********************************************************************
*@Author: your name
*@Date: 2020-08-11 15:10:49
*@LastEditTime: 2020-08-11 16:02:01
*@LastEditors: Please set LastEditors
*@Description: In User Settings Edit
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\lcd\lcd\bsp_ltdc.h
***********************************************************************/
#ifndef __bsp_ltdc_h
#define __bsp_ltdc_h

#include "main.h"


/* GPIO Config */
/* Red */
#define BSP_LTDC_R0             GPIOH
#define BSP_LTDC_R0_PORT        GPIO_PIN_2
#define BSP_LTDC_R1             GPIOH
#define BSP_LTDC_R1_PORT        GPIO_PIN_3
#define BSP_LTDC_R2             GPIOH
#define BSP_LTDC_R2_PORT        GPIO_PIN_8
#define BSP_LTDC_R3             GPIOB
#define BSP_LTDC_R3_PORT        GPIO_PIN_0
#define BSP_LTDC_R4             GPIOA
#define BSP_LTDC_R4_PORT        GPIO_PIN_11
#define BSP_LTDC_R5             GPIOA
#define BSP_LTDC_R5_PORT        GPIO_PIN_12
#define BSP_LTDC_R6             GPIOB
#define BSP_LTDC_R6_PORT        GPIO_PIN_1
#define BSP_LTDC_R7             GPIOG
#define BSP_LTDC_R7_PORT        GPIO_PIN_6
/* Green */
#define BSP_LTDC_G0             GPIOE
#define BSP_LTDC_G0_PORT        GPIO_PIN_5
#define BSP_LTDC_G1             GPIOE
#define BSP_LTDC_G1_PORT        GPIO_PIN_6
#define BSP_LTDC_G2             GPIOH
#define BSP_LTDC_G2_PORT        GPIO_PIN_13
#define BSP_LTDC_G3             GPIOG
#define BSP_LTDC_G3_PORT        GPIO_PIN_10
#define BSP_LTDC_G4             GPIOH
#define BSP_LTDC_G4_PORT        GPIO_PIN_15
#define BSP_LTDC_G5             GPIOI
#define BSP_LTDC_G5_PORT        GPIO_PIN_0
#define BSP_LTDC_G6             GPIOC
#define BSP_LTDC_G6_PORT        GPIO_PIN_7
#define BSP_LTDC_G7             GPIOI
#define BSP_LTDC_G7_PORT        GPIO_PIN_2
/* Blue */
#define BSP_LTDC_B0             GPIOE
#define BSP_LTDC_B0_PORT        GPIO_PIN_4
#define BSP_LTDC_B1             GPIOG
#define BSP_LTDC_B1_PORT        GPIO_PIN_12
#define BSP_LTDC_B2             GPIOD
#define BSP_LTDC_B2_PORT        GPIO_PIN_6
#define BSP_LTDC_B3             GPIOG
#define BSP_LTDC_B3_PORT        GPIO_PIN_11
#define BSP_LTDC_B4             GPIOI
#define BSP_LTDC_B4_PORT        GPIO_PIN_4
#define BSP_LTDC_B5             GPIOA
#define BSP_LTDC_B5_PORT        GPIO_PIN_3
#define BSP_LTDC_B6             GPIOB
#define BSP_LTDC_B6_PORT        GPIO_PIN_8
#define BSP_LTDC_B7             GPIOB
#define BSP_LTDC_B7_PORT        GPIO_PIN_9
/* CLK */
#define BSP_LTDC_CLK            GPIOG
#define BSP_LTDC_CLK_PORT       GPIO_PIN_7
/* HSYNC */
#define BSP_LTDC_HSYNC          GPIOI
#define BSP_LTDC_HSYNC_PORT     GPIO_PIN_10
/* VSYNC */
#define BSP_LTDC_VSYNC          GPIOI
#define BSP_LTDC_VSYNC_PORT     GPIO_PIN_9
/* DE */
#define BSP_LTDC_DE             GPIOF
#define BSP_LTDC_DE_PORT        GPIO_PIN_10
/* DISP */
#define BSP_LTDC_DISP           GPIOD
#define BSP_LTDC_DISP_PORT      GPIO_PIN_4
/* BL */
#define BSP_LTDC_BL             GPIOD
#define BSP_LTDC_BL_PORT        GPIO_PIN_7


//定义颜色像素格式,一般用RGB888
#define LCD_PIXFORMAT				LCD_PIXEL_FORMAT_RGB888	

#define LCD_PIXEL_FORMAT_ARGB8888       0X00    
#define LCD_PIXEL_FORMAT_RGB888         0X01    
#define LCD_PIXEL_FORMAT_RGB565         0X02       
#define LCD_PIXEL_FORMAT_ARGB1555       0X03      
#define LCD_PIXEL_FORMAT_ARGB4444       0X04     
#define LCD_PIXEL_FORMAT_L8             0X05     
#define LCD_PIXEL_FORMAT_AL44           0X06     
#define LCD_PIXEL_FORMAT_AL88           0X07      


/* LCD Config */
typedef struct 
{
    uint32_t pwidth;		    //LCD面板的宽度,固定参数,不随显示方向改变,如果为0,说明没有任何RGB屏接入
	uint32_t pheight;		    //LCD面板的高度,固定参数,不随显示方向改变
	uint16_t hsw;			    //水平同步宽度
	uint16_t vsw;			    //垂直同步宽度
	uint16_t hbp;			    //水平后廊
	uint16_t vbp;			    //垂直后廊
	uint16_t hfp;			    //水平前廊
	uint16_t vfp;			    //垂直前廊 
	uint8_t activelayer;		//当前层编号:0/1	
	uint8_t dir;				//0,竖屏;1,横屏;
	uint16_t width;			    //LCD宽度
	uint16_t height;			//LCD高度
	uint32_t pixsize;		    //每个像素所占字节数 
}_ltdc_dev;



#endif 
