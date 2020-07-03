#include "hc_05.h"

UART_HandleTypeDef huart3;

static void bsp_usart3_gpio_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


}
void bsp_hc_05_uart_init(uint32_t baudrate)
{

  bsp_usart3_gpio_init();

  __HAL_RCC_USART3_CLK_ENABLE();

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

void hc_05_send_data(uint8_t data)
{
    HAL_UART_Transmit(&huart3, &data, 1, 1000);
}

void hc_05_send_byte(uint8_t *data)
{
    HAL_UART_Transmit(&huart3, data, 1, 1000);
}

void hc_05_send_string(uint8_t *str)
{
    uint8_t k = 0;

    do
    {
        HAL_UART_Transmit(&huart3, (uint8_t *)(str+k), 1, 1000);
    } while (*(str + k) == '\0');
    
}

