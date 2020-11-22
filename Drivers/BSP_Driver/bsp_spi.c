#include "bsp_spi.h"

SPI_HandleTypeDef hspi5;

void bsp_spi1_init(void)
{   
    GPIO_InitTypeDef GPIO_Init;
    HAL_StatusTypeDef status;

    __HAL_RCC_SPI5_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF5_SPI1;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pin = SPI1_MOSI_PIN|
                    SPI1_MISO_PIN|
                    SPI1_CLK_PIN;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_Init);

    hspi5.Instance = SPI5;
    hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi5.Init.CRCPolynomial = 7;
    hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi5.Init.Direction = SPI_DIRECTION_2LINES;
    hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi5.Init.Mode = SPI_MODE_MASTER;
    hspi5.Init.NSS = SPI_NSS_SOFT;
    hspi5.Init.TIMode = SPI_TIMODE_DISABLE;

    status = HAL_SPI_Init(&hspi5);
    if (status != HAL_OK)
    {
        while(1);
    }
    __HAL_SPI_ENABLE(&hspi5);
    // bsp_w25qxx_read_write_byte(0xff);
}

uint8_t bsp_spi1_read_write_data(uint8_t tdata)
{   
    uint8_t rdata;
    HAL_SPI_TransmitReceive(&hspi5, &tdata,&rdata, 1,1000);
    return rdata;
}




