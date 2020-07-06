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

void bsp_uart3_init(uint32_t baudrate)
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

#if USE_HANDLE_RXN
  __HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);  
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 2);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
#endif
  ringbuffer_init();
}

void bsp_usart3_send_data(uint8_t data)
{
    HAL_UART_Transmit(&huart3, &data, 1, 1000);
}

void bsp_usart3_send_byte(uint8_t *data)
{
    HAL_UART_Transmit(&huart3, data, 1, 1000);
}

void bsp_usart3_send_string(uint8_t *str)
{
    uint8_t k = 0;
    do
    {
        HAL_UART_Transmit(&huart3, (uint8_t *)(str+k), 1, 1000);
    } while (*(str + k) == '\0');
}


void USART3_IRQHandler(void)
{
  rt_interrupt_enter();
  uint8_t ch;
  if(__HAL_UART_GET_FLAG( &huart3, UART_FLAG_RXNE) != RESET)
  {
    ch = huart3.Instance->DR;
    ringbuffer_write(ch);
  }
  rt_interrupt_leave();
}

