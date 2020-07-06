#ifndef __hc_05_h
#define __hc_05_h

#include "main.h"

#define USE_BLUETOOSE           0
#define USE_HANDLE_RXN          1

extern UART_HandleTypeDef huart3;


void bsp_uart3_init(uint32_t baudrate);
void bsp_usart3_send_data(uint8_t data);
void bsp_usart3_send_byte(uint8_t *data);
void bsp_usart3_send_string(uint8_t *str);
#endif
