#include "bsp_key.h"



/*
 * KEY1------PA0
 * KEY2------PC13
*/
bool bsp_key_init(void)
{
    GPIO_InitTypeDef BSP_KEY_GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    BSP_KEY_GPIO_Init.Mode = GPIO_MODE_INPUT;
    BSP_KEY_GPIO_Init.Pull = GPIO_NOPULL;

    BSP_KEY_GPIO_Init.Pin = BSP_KEY1;
    HAL_GPIO_Init(BSP_KEY1_GPIO, &BSP_KEY_GPIO_Init);
    BSP_KEY_GPIO_Init.Pin = BSP_KEY2;
    HAL_GPIO_Init(BSP_KEY2_GPIO, &BSP_KEY_GPIO_Init);

    return true;
}

uint8_t bsp_key_read(uint16_t bsp_key_x)
{
    GPIO_TypeDef *KEY_GPIO;
    switch (bsp_key_x)
    {
        case BSP_KEY1:KEY_GPIO = BSP_KEY1_GPIO; break;
        case BSP_KEY2:KEY_GPIO = BSP_KEY2_GPIO; break;
    }

    return HAL_GPIO_ReadPin(KEY_GPIO,bsp_key_x);
}




