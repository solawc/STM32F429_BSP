/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "main.h"
static uint32_t timerMsCount;
uint8_t WIFI_STATUS = 0;      //0为断开连接，1为正在连接

/** Current datapoint */
dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_Filtrate:
        currentDataPoint.valueFiltrate = dataPointPtr->valueFiltrate;
        GIZWITS_LOG("Evt: EVENT_Filtrate %d \n", currentDataPoint.valueFiltrate);
        if(0x01 == currentDataPoint.valueFiltrate)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;


      case EVENT_Template_write:
        currentDataPoint.valueTemplate_write = dataPointPtr->valueTemplate_write;
        GIZWITS_LOG("Evt:EVENT_Template_write %4f\n",currentDataPoint.valueTemplate_write);
        //user handle
        break;
      case EVENT_Feed_time:
        currentDataPoint.valueFeed_time = dataPointPtr->valueFeed_time;
        GIZWITS_LOG("Evt:EVENT_Feed_time %d\n",currentDataPoint.valueFeed_time);
        //user handle
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:  WIFI_STATUS = 1;
 
        break;
      case WIFI_DISCON_M2M: WIFI_STATUS = 0;
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valueFeed_food = ;//Add Sensor Data Collection
    currentDataPoint.valueTemplate_read = ;//Add Sensor Data Collection
    
    */
    currentDataPoint.valueTemplate_read = ((float)DHT11_Data.temp_int +(((float)DHT11_Data.temp_deci)/10));
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueFiltrate = ;
      currentDataPoint.valueTemplate_write = ;
      currentDataPoint.valueFeed_time = ;
      currentDataPoint.valueFeed_food = ;
      currentDataPoint.valueTemplate_read = ;
    */
   currentDataPoint.valueTemplate_write = 30.0;
}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
  __set_FAULTMASK(1);
  HAL_NVIC_SystemReset();
}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
// void TIMER_IRQ_FUN(void)
// {
//   gizTimerMs();
// }

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function 锛孎or Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1锛孖nput Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    uint8_t data55[1] = {0x55};
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

    for(i=0; i<len; i++)
    {
        //USART_SendData(UART, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
        HAL_UART_Transmit(&huart3,&buf[i],1,1000);
         //wait the uart send finsh

        if(i >=2 && buf[i] == 0xFF)
        {
          //Serial port to achieve the function, the 0x55 sent to the module
          //USART_SendData(UART, 0x55);//STM32 test demo
          HAL_UART_Transmit(&huart3,data55,1,1000);
          while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TXE)== RESET); //wait the uart send finsh
        }
    }
    return len;
}

void bsp_gizwits_init(void)
{   
    userInit();
    bsp_uart3_init(9600);
    memset((uint8_t *)&currentDataPoint,0,sizeof(dataPoint_t));
    gizwitsInit(); 
    bsp_time7_init(10-1,9000-1);
    gizwitsSetMode(WIFI_AIRLINK_MODE);
}

