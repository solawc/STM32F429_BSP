#ifndef __debug_usart_h
#define __debug_usart_h

#include "main.h"



#define DEBUG_SWITCH                      1

#if DEBUG_SWITCH
#define DEBUG_ERROR(fmt,arg...)        do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)        do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)                       
#else
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#endif 

#define RINGBUF_LENGTH              4096
typedef struct 
{
    uint32_t head;
    uint32_t tail;
    uint8_t buff[RINGBUF_LENGTH];
    uint32_t len;
}ringbuff_t;


extern ringbuff_t debug_ringbuf;



void bsp_debug_usart_init(void);

bool ringbuffer_init(void);
bool ringbuffer_write(uint8_t data);
bool ringbuffer_read(uint8_t *data);

#endif
