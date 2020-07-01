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


void bsp_debug_usart_init(void);

#endif
