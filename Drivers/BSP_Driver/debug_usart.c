#include "debug_usart.h"

void bsp_debug_usart_init(void)
{
    MX_USART1_UART_Init();
}


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, sizeof(ch), 1000);

  return ch;
}




