/***********************************************************************
*@Date: 2020-07-31 16:07:13
*@LastEditors: Please set LastEditors
*@LastEditTime: 2020-07-31 18:40:53
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\my_malloc.h
***********************************************************************/
#ifndef __my_malloc_h
#define __my_malloc_h

#include "main.h"

#define SRAM_BANK                               3
/*  */
#define MEM_ON_CHIP_SRAM_BLOCK                  64          //64bit for a block
#define MEM_ON_CHIP_SRAM_MAX_SIZE               160*1024    //160K
#define MEM_ON_CHIP_SRAM_ALLOC_TABLE_SIZE       MEM_ON_CHIP_SRAM_MAX_SIZE/MEM_ON_CHIP_SRAM_BLOCK

#define MEM_SDRAM_BLOCK                         64          //64bit for a block
#define MEM_SDRAM_MAX_SIZE                      2000*1024   //2000K
#define MEM_SDRAM_ALLOC_TABLE_SIZE              MEM_SDRAM_MAX_SIZE/MEM_SDRAM_BLOCK

/* warring : this sram ,just cpu can access,only exist cortex-m4 or more over */
#define MEM_ON_CHIP_CCM_BLOCK                   64          //64bit for a block
#define MEM_ON_CHIP_CCM_MAX_SIZE                64*1024     //64k
#define MEM_ON_CHIP_CCM_ALLOC_TABLE_SIZE        MEM_ON_CHIP_CCM_MAX_SIZE/MEM_ON_CHIP_CCM_BLOCK


struct _m_mallco_dev
{
	void (*init)(uint8_t);					    //初始化
	uint16_t (*perused)(uint8_t);		        //内存使用率
	uint8_t *membase[SRAM_BANK];				//内存池 管理SRAMBANK个区域的内存
	uint32_t *memmap[SRAM_BANK]; 				//内存管理状态表
	uint8_t memrdy[SRAM_BANK]; 	                //内存管理是否就绪
};
extern struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义

void mymemset(void *s, uint8_t c, uint32_t count);	//设置内存
void mymemcpy(void *des,void *src, uint32_t n);//复制内存     
void my_mem_init( uint8_t memx);				//内存管理初始化函数(外/内部调用)
 uint32_t my_mem_malloc( uint8_t memx, uint32_t size);	//内存分配(内部调用)
 uint8_t my_mem_free( uint8_t memx, uint32_t offset);		//内存释放(内部调用)
void my_free( uint8_t memx,void *ptr);  			//内存释放(外部调用)
uint16_t my_mem_perused(uint8_t memx);
void *mymalloc( uint8_t memx, uint32_t size);			//内存分配(外部调用)
void *myrealloc( uint8_t memx,void *ptr, uint32_t size);//重新分配内存(外部调用)

#endif
