#include "w25q64.h"

/***********************************************************************
*@Date: 2020-06-03 17:05:29
*@Function: W25QXX_write_enable
*@Input: 
*@Return: 
***********************************************************************/
uint8_t bsp_w25qxx_read_write_byte(uint8_t tdata)
{
  uint8_t rdata;
  rdata = bsp_spi1_read_write_data(tdata);
  return rdata;
}

void w25qxx_flash_mode(void)
{
  uint8_t Temp;
	
	/*选择 FLASH: CS 低 */
	W25QXX_CS_L();
	
	/* 发送状态寄存器 3 命令 */
	bsp_w25qxx_read_write_byte(W25X_ReadStatusRegister3); 
	
	Temp = bsp_w25qxx_read_write_byte(Dummy_Byte);
	
	/* 停止信号 FLASH: CS 高 */
	W25QXX_CS_H();
	
	if((Temp&0x01) == 0)
	{
		/*选择 FLASH: CS 低 */
		W25QXX_CS_L();
		
		/* 进入4字节模式 */
		bsp_w25qxx_read_write_byte(W25X_Enter4ByteMode);
		
		/* 停止信号 FLASH: CS 高 */
		W25QXX_CS_H();
	}
}

/***********************************************************************
*@Date: 2020-06-03 17:05:29
*@Function: W25QXX_write_enable
*@Input: 
*@Return: 
***********************************************************************/
uint32_t bsp_w25qxx_read_id(void)
{
    uint32_t temp[3];
    uint32_t id = 0;
    W25QXX_CS_L();
    bsp_w25qxx_read_write_byte(W25X_JedecDeviceID);
    temp[0] = bsp_w25qxx_read_write_byte(Dummy_Byte);
    temp[1] = bsp_w25qxx_read_write_byte(Dummy_Byte);
    temp[2] = bsp_w25qxx_read_write_byte(Dummy_Byte);
    W25QXX_CS_H();

    id = (temp[0]<<16) | (temp[1]<<8)|temp[2] ;
    
    
    return id;
}

/***********************************************************************
*@Date: 2020-06-03 17:05:29
*@Function: W25QXX_write_enable
*@Input: 
*@Return: 
***********************************************************************/
void bsp_w25qxx_init(void)
{   
    uint32_t id = 0;

    bsp_spi1_init();
    
    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin=SPI1_W25QXX_CS_PIN;          	
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //推挽输出
    GPIO_Initure.Pull=GPIO_NOPULL;                        //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;              //高速       
    HAL_GPIO_Init(SPI1_W25QXX_CS_PORT,&GPIO_Initure);     //初始化
    W25QXX_CS_H();
    w25qxx_flash_mode();
    id = bsp_w25qxx_read_id();

    switch (id)
    {
      case W25Q64:
          DEBUG_PRINT("W25qxx = W25Q64");
      break;
      case W25Q128:
          DEBUG_PRINT("W25qxx = W25Q128");
      break;
      case W25Q256:
          DEBUG_PRINT("W25qxx = W25Q256");
      break;
      default: 
          DEBUG_PRINT("id = 0x%x",id);
      break;
    }
}

/***********************************************************************
*@Date: 2020-06-03 17:05:29
*@Function: W25QXX_write_enable
*@Input: 
*@Return: 
***********************************************************************/
bool W25QXX_write_enable(void)
{
    W25QXX_CS_L();
    bsp_w25qxx_read_write_byte(W25X_WriteEnable);
    W25QXX_CS_H();
    return true;
}

/***********************************************************************
*@Date: 2020-06-03 17:13:10
*@Function: W25QXX_wait_busy
*@Input: void
*@Return: ture/false
***********************************************************************/
bool W25QXX_wait_busy(void)
{   
    uint8_t flash_status;
    uint32_t time_out_count = 0xffff;

    W25QXX_CS_L();

    bsp_w25qxx_read_write_byte(W25X_ReadStatusReg);

    do
    {
        flash_status = bsp_w25qxx_read_write_byte(Dummy_Byte);

        if((time_out_count--)==0)
        {
            return false;
        }

    } while ((flash_status & 0x01)==SET);

    W25QXX_CS_H();
        
    return true;
}

/***********************************************************************
*@Date: 2020-06-03 17:14:17
*@Function: W25QXX_Erase_Sector
*@Input: Sector_addr
*@Return: ture/false
*@Drscription: ²Á³ýÉÈÇø
***********************************************************************/
bool W25QXX_erase_sector(uint32_t Sector_addr)
{
    W25QXX_write_enable();
    W25QXX_wait_busy();

    W25QXX_CS_L();

    bsp_w25qxx_read_write_byte(W25X_SectorErase);

    bsp_w25qxx_read_write_byte((Sector_addr & 0xFF000000) >> 24);
    bsp_w25qxx_read_write_byte((Sector_addr & 0xFF0000) >> 16);
    bsp_w25qxx_read_write_byte((Sector_addr & 0xFF00) >> 8);
    bsp_w25qxx_read_write_byte((Sector_addr & 0xFF));

    W25QXX_CS_H();

    W25QXX_wait_busy();
    
    return true;
}


/***********************************************************************
*@Date: 2020-06-03 18:19:13
*@Function: W25QXX_Erase_chip
*@Input: 
*@Return: 
*@Drscription: W25QXX整片擦除
***********************************************************************/
void W25QXX_Erase_chip(void)
{
  W25QXX_write_enable();

  W25QXX_CS_L();

  bsp_w25qxx_read_write_byte(W25X_ChipErase);

  W25QXX_CS_H();

  W25QXX_wait_busy();
}


/***********************************************************************
*@Date: 2020-06-03 18:10:37
*@Function: W25QXX_write_page
*@Input: 
*@Return: 
*@Drscription: ¶ÔW25QXX½øÐÐÒ³Ð´Èë write_numÒªÐ¡ÓÚW25X_PageSize = 256
***********************************************************************/
bool W25QXX_write_page(uint8_t *buffer,uint32_t write_addr,uint16_t write_num)
{
    W25QXX_write_enable();
    
    W25QXX_CS_L();

    bsp_w25qxx_read_write_byte(W25X_PageProgram);

    bsp_w25qxx_read_write_byte((write_addr & 0xFF000000) >> 24);
    bsp_w25qxx_read_write_byte((write_addr & 0xFF0000) >> 16);
    bsp_w25qxx_read_write_byte((write_addr & 0xFF00) >> 8);
    bsp_w25qxx_read_write_byte((write_addr & 0xFF));

    if(write_num > W25X_PerWritePageSize)
    {
        write_num = W25X_PerWritePageSize;

        //return false;
    }

    while (write_num--)
    {
        bsp_w25qxx_read_write_byte(*buffer);

        buffer++;
    }
    
    W25QXX_CS_H();

    W25QXX_wait_busy();
    return true;
}

/***********************************************************************
*@Date: 2020-06-03 18:22:03
*@Function: W25QXX_write_buffer
*@Input: 
*@Return: 
***********************************************************************/
void W25QXX_write_buffer(uint8_t* pBuffer, 
                         uint32_t WriteAddr, 
                         uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
  Addr = WriteAddr % W25X_PageSize;
	
  count = W25X_PageSize - Addr;	
	
  NumOfPage =  NumByteToWrite / W25X_PageSize;

  NumOfSingle = NumByteToWrite % W25X_PageSize;

  if (Addr == 0) 
  {
    if (NumOfPage == 0) 
    {
      W25QXX_write_page(pBuffer, WriteAddr, NumByteToWrite);
    }
    else 
    {
      while (NumOfPage--)
      {
        W25QXX_write_page(pBuffer, WriteAddr, W25X_PageSize);
        WriteAddr +=  W25X_PageSize;
        pBuffer += W25X_PageSize;
      }
      W25QXX_write_page(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	
  else 
  {
		
    if (NumOfPage == 0) 
    {
      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;
		
        W25QXX_write_page(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;
				
        W25QXX_write_page(pBuffer, WriteAddr, temp);
      }
      else
      {				
        W25QXX_write_page(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / W25X_PageSize;
      NumOfSingle = NumByteToWrite % W25X_PageSize;

      W25QXX_write_page(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;
			
      while (NumOfPage--)
      {
        W25QXX_write_page(pBuffer, WriteAddr, W25X_PageSize);
        WriteAddr +=  W25X_PageSize;
        pBuffer += W25X_PageSize;
      }
      if (NumOfSingle != 0)
      {
        W25QXX_write_page(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/***********************************************************************
*@Date: 2020-06-03 18:38:14
*@Function: W25QXX_read_buffer
*@Input: 
*@Return: 
*@Drscription: ÈÎÒâ×Ö½Ú¶Á³ö
***********************************************************************/
void W25QXX_read_buffer(uint8_t* pBuffer,
                        uint32_t ReadAddr,
                        uint16_t NumByteToRead)
{
  W25QXX_CS_L();

  bsp_w25qxx_read_write_byte(W25X_ReadData);

  bsp_w25qxx_read_write_byte((ReadAddr & 0xFF0000) >> 16);

  bsp_w25qxx_read_write_byte((ReadAddr& 0xFF00) >> 8);

  bsp_w25qxx_read_write_byte(ReadAddr & 0xFF);
  
  while (NumByteToRead--)
  {
    *pBuffer = bsp_w25qxx_read_write_byte(Dummy_Byte);
    pBuffer++;
  }

  W25QXX_CS_H();
}
