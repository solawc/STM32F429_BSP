#ifndef __w25q64_h
#define __w25q64_h

#include "main.h"

#define W25Q64 	0XEF4017
#define W25Q128	0XEF4018
#define W25Q256 0XEF4019

//指令表

#define W25X_PageSize               256
#define W25X_PerWritePageSize       256

#define Dummy_Byte                  0xFF
#define W25X_WriteEnable	        0x06 
#define W25X_WriteDisable	        0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			    0x03 
#define W25X_FastReadData		    0x0B               
#define W25X_FastReadDual		    0x3B 
#define W25X_PageProgram		    0x02 
#define W25X_BlockErase			    0xD8 
#define W25X_SectorErase		    0x20 
#define W25X_ChipErase			    0xC7 
#define W25X_PowerDown			    0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			    0xAB 
#define W25X_ManufactDeviceID       0x90 
#define W25X_JedecDeviceID		    0x9F
#define W25X_ReadStatusRegister3    0x15
#define W25X_Enter4ByteMode		    0xB7

#define SPI1_W25QXX_CS_PORT         GPIOF
#define SPI1_W25QXX_CS_PIN          GPIO_PIN_6
#define	W25QXX_CS_L()               HAL_GPIO_WritePin(SPI1_W25QXX_CS_PORT,SPI1_W25QXX_CS_PIN,GPIO_PIN_RESET)
#define	W25QXX_CS_H()               HAL_GPIO_WritePin(SPI1_W25QXX_CS_PORT,SPI1_W25QXX_CS_PIN,GPIO_PIN_SET)


void bsp_w25qxx_init(void);
uint8_t bsp_w25qxx_read_write_byte(uint8_t tdata);
uint32_t bsp_w25qxx_read_id(void);
bool W25QXX_write_enable(void);
bool W25QXX_wait_busy(void);
bool W25QXX_erase_sector(uint32_t Sector_addr);
void W25QXX_Erase_chip(void);
bool W25QXX_write_page(uint8_t *buffer,uint32_t write_addr,uint16_t write_num);
void W25QXX_write_buffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void W25QXX_read_buffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
#endif
