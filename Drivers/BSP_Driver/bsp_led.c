#include "bsp_led.h"

bool bsp_led_init(void)
{
    GPIO_InitTypeDef BSP_LED_GPIO_Init;

    __HAL_RCC_GPIOH_CLK_ENABLE();

    HAL_GPIO_WritePin(BSP_LED_R_GPIO,BSP_LED_R,GPIO_PIN_SET);
    HAL_GPIO_WritePin(BSP_LED_G_GPIO,BSP_LED_G,GPIO_PIN_SET);
    HAL_GPIO_WritePin(BSP_LED_B_GPIO,BSP_LED_B,GPIO_PIN_SET);

    BSP_LED_GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    BSP_LED_GPIO_Init.Pull = GPIO_NOPULL;
    BSP_LED_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;

    BSP_LED_GPIO_Init.Pin = BSP_LED_R;
    HAL_GPIO_Init(BSP_LED_R_GPIO, &BSP_LED_GPIO_Init);
    BSP_LED_GPIO_Init.Pin = BSP_LED_G;
    HAL_GPIO_Init(BSP_LED_G_GPIO, &BSP_LED_GPIO_Init);
    BSP_LED_GPIO_Init.Pin = BSP_LED_B;
    HAL_GPIO_Init(BSP_LED_B_GPIO, &BSP_LED_GPIO_Init);

    return true;
}


void bsp_led_on(uint16_t bsp_led_x)
{
    GPIO_TypeDef *LED_GPIO;

    switch (bsp_led_x)
    {
        case BSP_LED_R:LED_GPIO = BSP_LED_R_GPIO; break;
        case BSP_LED_G:LED_GPIO = BSP_LED_G_GPIO; break;
        case BSP_LED_B:LED_GPIO = BSP_LED_B_GPIO; break;
    }

    HAL_GPIO_WritePin(LED_GPIO,bsp_led_x,GPIO_PIN_RESET);
}

void bsp_led_off(uint16_t bsp_led_x)
{
    GPIO_TypeDef *LED_GPIO;

    switch (bsp_led_x)
    {
        case BSP_LED_R:LED_GPIO = BSP_LED_R_GPIO; break;
        case BSP_LED_G:LED_GPIO = BSP_LED_G_GPIO; break;
        case BSP_LED_B:LED_GPIO = BSP_LED_B_GPIO; break;
    }

    HAL_GPIO_WritePin(LED_GPIO,bsp_led_x,GPIO_PIN_SET);
}

void bsp_led_toggle(uint16_t bsp_led_x)
{
    GPIO_TypeDef *LED_GPIO;

    switch (bsp_led_x)
    {
        case BSP_LED_R:LED_GPIO = BSP_LED_R_GPIO; break;
        case BSP_LED_G:LED_GPIO = BSP_LED_G_GPIO; break;
        case BSP_LED_B:LED_GPIO = BSP_LED_B_GPIO; break;
    }

    HAL_GPIO_TogglePin(LED_GPIO,bsp_led_x);
}


void bsp_led_pwm_mode_init(void)
{


}

void bsp_led_pwm_set(uint16_t bsp_led_x,uint32_t duty)
{


}

