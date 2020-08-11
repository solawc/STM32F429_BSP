/***********************************************************************
*@Author: your name
*@Date: 2020-08-11 15:10:40
*@LastEditTime: 2020-08-11 16:12:42
*@LastEditors: Please set LastEditors
*@Description: In User Settings Edit
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\lcd\lcd\bsp_ltdc.c
***********************************************************************/
#include "bsp_ltdc.h"

LTDC_HandleTypeDef hltdc;
_ltdc_dev lcdltdc;

uint32_t *ltdc_framebuf[2];
//根据不同的颜色格式,定义帧缓存数组
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	uint32_t ltdc_lcd_framebuf[1280][800] __attribute__((at(SDRAM_BANK_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
#else
	uint16_t ltdc_lcd_framebuf[1280][800] __attribute__((at(SDRAM_BANK_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
#endif

static void bsp_ltdc_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF14_LTDC;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
/* LTDC RED   */
    GPIO_Init.Pin = BSP_LTDC_R0;
    HAL_GPIO_Init(BSP_LTDC_R0_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R1;
    HAL_GPIO_Init(BSP_LTDC_R1_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R2;
    HAL_GPIO_Init(BSP_LTDC_R2_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R3;
    HAL_GPIO_Init(BSP_LTDC_R3_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R4;
    HAL_GPIO_Init(BSP_LTDC_R4_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R5;
    HAL_GPIO_Init(BSP_LTDC_R5_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R6;
    HAL_GPIO_Init(BSP_LTDC_R6_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_R7;
    HAL_GPIO_Init(BSP_LTDC_R7_PORT,&GPIO_Init);
/* LTDC GREEN */
    GPIO_Init.Pin = BSP_LTDC_G0;
    HAL_GPIO_Init(BSP_LTDC_G0_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G1;
    HAL_GPIO_Init(BSP_LTDC_G1_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G2;
    HAL_GPIO_Init(BSP_LTDC_G2_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G3;
    HAL_GPIO_Init(BSP_LTDC_G3_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G4;
    HAL_GPIO_Init(BSP_LTDC_G4_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G5;
    HAL_GPIO_Init(BSP_LTDC_G5_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G6;
    HAL_GPIO_Init(BSP_LTDC_G6_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_G7;
    HAL_GPIO_Init(BSP_LTDC_G7_PORT,&GPIO_Init);
/* LTDC BLUE  */
    GPIO_Init.Pin = BSP_LTDC_B0;
    HAL_GPIO_Init(BSP_LTDC_B0_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B1;
    HAL_GPIO_Init(BSP_LTDC_B1_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B2;
    HAL_GPIO_Init(BSP_LTDC_B2_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B3;
    HAL_GPIO_Init(BSP_LTDC_B3_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B4;
    HAL_GPIO_Init(BSP_LTDC_B4_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B5;
    HAL_GPIO_Init(BSP_LTDC_B5_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B6;
    HAL_GPIO_Init(BSP_LTDC_B6_PORT,&GPIO_Init);
    GPIO_Init.Pin = BSP_LTDC_B7;
    HAL_GPIO_Init(BSP_LTDC_B7_PORT,&GPIO_Init);
/* LTDC CLK   */
    GPIO_Init.Pin = BSP_LTDC_CLK;
    HAL_GPIO_Init(BSP_LTDC_CLK_PORT,&GPIO_Init);
/* LTDC HSYNC */
    GPIO_Init.Pin = BSP_LTDC_HSYNC;
    HAL_GPIO_Init(BSP_LTDC_HSYNC_PORT,&GPIO_Init);
/* LTDC VSYNC */
    GPIO_Init.Pin = BSP_LTDC_VSYNC;
    HAL_GPIO_Init(BSP_LTDC_VSYNC_PORT,&GPIO_Init);
/* LTDC DE    */
    GPIO_Init.Pin = BSP_LTDC_DE;
    HAL_GPIO_Init(BSP_LTDC_DE_PORT,&GPIO_Init);


    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
/* LTDC DISP  */
    GPIO_Init.Pin = BSP_LTDC_DISP;
    HAL_GPIO_Init(BSP_LTDC_DISP_PORT,&GPIO_Init);
/* LTDC BL  */
    GPIO_Init.Pin = BSP_LTDC_BL;
    HAL_GPIO_Init(BSP_LTDC_BL_PORT,&GPIO_Init);
}

static void bsp_ltdc_config(void)
{   
    __HAL_RCC_LTDC_CLK_ENABLE();

    lcdltdc.pwidth=800;		    //面板宽度,单位:像素
    lcdltdc.pheight=480;	    //面板高度,单位:像素
    lcdltdc.hbp=46;			    //水平后廊
    lcdltdc.hfp=22;		    	//水平前廊
    lcdltdc.hsw=1;			    //水平同步宽度
    lcdltdc.vbp=23;			    //垂直后廊
    lcdltdc.vfp=22;			    //垂直前廊
    lcdltdc.vsw=1;				//垂直同步宽度

#if (LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888)||(LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888) 
	ltdc_framebuf[0]=(u32*)&ltdc_lcd_framebuf;
	lcdltdc.pixsize=4;				//每个像素占4个字节
#else 
    lcdltdc.pixsize=2;				//每个像素占2个字节
	ltdc_framebuf[0]=(u32*)&ltdc_lcd_framebuf;
#endif 	

    hltdc.Instance = LTDC;
    hltdc.Init.AccumulatedActiveH = lcdltdc.vsw + lcdltdc.vbp + (lcdltdc.pheight -1);
    hltdc.Init.AccumulatedActiveW = lcdltdc.hsw + lcdltdc.hbp + (lcdltdc.pwidth -1);//HSW+HBP+LCD_PIXEL_WIDTH-1;
    hltdc.Init.AccumulatedHBP =  lcdltdc.hsw + lcdltdc.hbp - 1;     //HSW+HBP-1;
    hltdc.Init.AccumulatedVBP =  lcdltdc.vsw + lcdltdc.vbp - 1；    //VSW+VBP-1;
    hltdc.Init.HorizontalSync =  lcdltdc.hsw - 1;   //HSW-1
    hltdc.Init.TotalHeigh = lcdltdc.vsw + lcdltdc.vbp + lcdltdc.pheight + lcdltdc.vfp - 1//VSW+ VBP+LCD_PIXEL_HEIGHT + VFP-1;
    hltdc.Init.TotalWidth = lcdltdc.hsw + lcdltdc.hbp + lcdltdc.pwidth + lcdltdc.hfp -1;  //HSW+ HBP+LCD_PIXEL_WIDTH + HFP-1;
    hltdc.Init.VerticalSync = lcdltdc.vsw - 1; //VSW-1

    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;      

    hltdc.LayerCfg->ImageWidth  = lcdltdc.pwidth;
    hltdc.LayerCfg->ImageHeight = lcdltdc.pheight;                                          

    hltdc.Init.Backcolor.Red = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Blue = 0;
    
    HAL_LTDC_Init(&hltdc);
}

void bsp_ltdc_init(void)
{
    bsp_ltdc_gpio_init();
    bsp_ltdc_config();
}   


