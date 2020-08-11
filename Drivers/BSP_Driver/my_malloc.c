/***********************************************************************
*@Date: 2020-07-31 16:07:04
*@LastEditors: Please set LastEditors
*@LastEditTime: 2020-07-31 18:42:14
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\my_malloc.c
***********************************************************************/
#include "my_malloc.h"

/* mem pool */
__align(32) uint8_t mem_on_chip_sram_base[MEM_ON_CHIP_SRAM_MAX_SIZE];
__align(32) uint8_t mem_sdram_base[MEM_SDRAM_MAX_SIZE] __attribute__((at(0xD01F4000)));    /* SDRAM MEM  */
__align(32) uint8_t mem_on_chip_ccm_base[MEM_ON_CHIP_CCM_MAX_SIZE] __attribute__((at(0x10000000))); /* CCM MEM for cortex-m4 */

/* memory manger list */
uint32_t mem_on_chip_sram_map_base[MEM_ON_CHIP_SRAM_ALLOC_TABLE_SIZE];
uint32_t mem_sdram_map_base[MEM_SDRAM_ALLOC_TABLE_SIZE] __attribute__((at(0xD01F4000+MEM_SDRAM_MAX_SIZE)));
uint32_t mem_on_chip_ccm_map_base[MEM_ON_CHIP_CCM_ALLOC_TABLE_SIZE] __attribute__((at(0x10000000+MEM_ON_CHIP_CCM_MAX_SIZE)));

const uint32_t mem_block_s_size[SRAM_BANK]={MEM_ON_CHIP_SRAM_ALLOC_TABLE_SIZE,MEM_SDRAM_ALLOC_TABLE_SIZE,MEM_ON_CHIP_CCM_ALLOC_TABLE_SIZE};
const uint32_t mem_block_k_size[SRAM_BANK]={MEM_ON_CHIP_SRAM_BLOCK,MEM_SDRAM_BLOCK,MEM_ON_CHIP_CCM_BLOCK};
const uint32_t mem_size[SRAM_BANK]={MEM_ON_CHIP_SRAM_MAX_SIZE,MEM_SDRAM_MAX_SIZE,MEM_ON_CHIP_CCM_MAX_SIZE};


struct _m_mallco_dev mallco_dev=
{
	my_mem_init,						//内存初始化
	my_mem_perused,						//内存使用率
	mem_on_chip_sram_base,mem_sdram_base,mem_on_chip_ccm_base,	//内存池
	mem_on_chip_sram_map_base,mem_sdram_map_base,mem_on_chip_ccm_map_base,//内存管理状态表
	0,0,0,  		 					//内存管理未就绪
};


void my_men_copy(void *des, void *src ,uint32_t num)
{
    uint8_t *xdes = des;
    uint8_t *xsrc = src;
    while(num--) *xdes++ = *xsrc++;
}

void mymemset(void *s,uint8_t c,uint32_t count)  
{  
    uint8_t *xs = s;  
    while(count--)*xs++=c;  
}	

void my_mem_init(uint8_t memx)  
{  
    mymemset(mallco_dev.memmap[memx],0,mem_block_s_size[memx]*4);	//内存状态表数据清零  
 	mallco_dev.memrdy[memx]=1;								//内存管理初始化OK  
}  

uint16_t my_mem_perused(uint8_t memx)  
{  
    uint32_t used=0;  
    uint32_t i;  
    for(i=0;i<mem_block_s_size[memx];i++)  
    {  
        if(mallco_dev.memmap[memx][i])used++; 
    } 
    return (used*1000)/(mem_block_s_size[memx]);  
}  

//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址 
uint32_t my_mem_malloc(uint8_t memx,uint32_t size)  
{  
    signed long offset=0;  
    uint32_t nmemb;	//需要的内存块数  
	uint32_t cmemb=0;//连续空内存块数
    uint32_t i;  
    if(!mallco_dev.memrdy[memx])mallco_dev.init(memx);//未初始化,先执行初始化 
    if(size==0)return 0XFFFFFFFF;//不需要分配
    nmemb=size/mem_block_k_size[memx];  	//获取需要分配的连续内存块数
    if(size%mem_block_k_size[memx])nmemb++;  
    for(offset=mem_block_s_size[memx]-1;offset>=0;offset--)//搜索整个内存控制区  
    {     
		if(!mallco_dev.memmap[memx][offset])cmemb++;//连续空内存块数增加
		else cmemb=0;								//连续内存块清零
		if(cmemb==nmemb)							//找到了连续nmemb个空内存块
		{
            for(i=0;i<nmemb;i++)  					//标注内存块非空 
            {  
                mallco_dev.memmap[memx][offset+i]=nmemb;  
            }  
            return (offset*mem_block_k_size[memx]);//返回偏移地址  
		}
    }  
    return 0XFFFFFFFF;//未找到符合分配条件的内存块  
}  

uint8_t my_mem_free(uint8_t memx,uint32_t offset)  
{  
    int i;  
    if(!mallco_dev.memrdy[memx])//未初始化,先执行初始化
	{
		mallco_dev.init(memx);    
        return 1;//未初始化  
    }  
    if(offset<mem_size[memx])//偏移在内存池内. 
    {  
        int index=offset/mem_block_k_size[memx];			//偏移所在内存块号码  
        int nmemb=mallco_dev.memmap[memx][index];	//内存块数量
        for(i=0;i<nmemb;i++)  						//内存块清零
        {  
            mallco_dev.memmap[memx][index+i]=0;  
        }  
        return 0;  
    }else return 2;//偏移超区了.  
}  


void my_free( uint8_t memx,void *ptr)  
{  
	 uint32_t offset;   
	if(ptr==NULL)return;//地址为0.  
 	offset=( uint32_t)ptr-( uint32_t)mallco_dev.membase[memx];     
    my_mem_free(memx,offset);	//释放内存      
}  

void *mymalloc( uint8_t memx, uint32_t size)  
{  
     uint32_t offset;   
	offset=my_mem_malloc(memx,size);  	   	 	   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)(( uint32_t)mallco_dev.membase[memx]+offset);  
}

void *myrealloc( uint8_t memx,void *ptr, uint32_t size)  
{  
     uint32_t offset;    
    offset=my_mem_malloc(memx,size);   	
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	    my_men_copy((void*)(( uint32_t)mallco_dev.membase[memx]+offset),ptr,size);	//拷贝旧内存内容到新内存   
        my_free(memx,ptr);  											  		//释放旧内存
        return (void*)(( uint32_t)mallco_dev.membase[memx]+offset);  				//返回新内存首地址
    }  
}

