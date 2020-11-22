#ifndef __bsp_spi_h
#define __bsp_spi_h

#include "main.h"

extern SPI_HandleTypeDef hspi5; 

#define SPI1_MOSI_PORT              GPIOF
#define SPI1_MOSI_PIN               GPIO_PIN_9
#define SPI1_MISO_PORT              GPIOF
#define SPI1_MISO_PIN               GPIO_PIN_8
#define SPI1_CLK_PORT               GPIOF
#define SPI1_CLK_PIN                GPIO_PIN_7

void bsp_spi1_init(void);
uint8_t bsp_spi1_read_write_data(uint8_t tdata);
#endif
