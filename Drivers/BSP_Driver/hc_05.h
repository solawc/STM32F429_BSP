#ifndef __hc_05_h
#define __hc_05_h

#include "main.h"

#define USE_BLUETOOSE           0

extern UART_HandleTypeDef huart3;


void bsp_hc_05_uart_init(uint32_t baudrate);
void hc_05_send_data(uint8_t data);
void hc_05_send_byte(uint8_t *data);
void hc_05_send_string(uint8_t *str);
#endif
