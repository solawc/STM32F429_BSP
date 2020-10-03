#include "bsp_spi.h"



SPI_HandleTypeDef hspi1;

void bsp_spi1_init(void)
{   
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF5_SPI1;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pin = SPI1_MOSI_PIN|
                    SPI1_MISO_PIN|
                    SPI1_CLK_PIN;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOF, &GPIO_Init);

    hspi1.Instance = SPI1;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    HAL_SPI_Init(&hspi1);
    __HAL_SPI_ENABLE(&hspi1);
}

uint8_t bsp_spi1_read_write_data(uint8_t tdata)
{   
    uint8_t rdata;

    HAL_SPI_TransmitReceive(&hspi1, &tdata,&rdata, 1,1000);

    return rdata;
}




