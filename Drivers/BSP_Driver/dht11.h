/***********************************************************************
*@Date: 2020-05-22 04:47:09
*@LastEditors: SOLA
*@LastEditTime: 2020-05-24 18:05:57
*@FilePath: \RT1052\Libraries\hardware\dht11.h
***********************************************************************/
#ifndef __dht11_h
#define __dht11_h

#include "main.h"

/*底层接口*/
#define __DHT11_GPIO_INIT()     dht11_gpio_init()
#define __DHT11_MODE(MODE)      DHT11_MODE(MODE)
#define __DHT11_OUT_H()         HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET)
#define __DHT11_OUT_L()         HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_RESET)
#define __DHT11_READ()          HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)
#define __DHT11_DELAY_MS(nms)   delay_ms(nms)
#define __DHT11_DELAY_US(nms)   delay_us(nms)

/*硬件接口*/
#define __DHT11_PIN_CLK()		__HAL_RCC_GPIOE_CLK_ENABLE()       
#define DHT11_PIN              	GPIO_PIN_2 
#define DHT11_PORT              GPIOE

/*延时函数*/
#define  SYSCLK                             180000000/1000000                   //指明CPU工作频率为(SystemCoreClock/1000000)MHz
#define  A                                  3                                   //一次循环所花的周期数
#define  B                                  1                                   //调用、初始化、返回总共所用的周期数
#define  delay_us(nus)                      wait(((nus)*(SYSCLK)-(B))/(A))
#define  delay_ms(nms)                      delay_us((nms)*1000)
#define  delay_s(ns)                        delay_ms((ns)*1000)

/*结构体成员定义*/
typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
	float 	 humi;			//湿度
	float 	 temp;			//温度
		                 
}DHT11_Data_TypeDef;
extern DHT11_Data_TypeDef DHT11_Data;

/*函数声明*/
void  wait(unsigned long n);
void dht11_init(void);
uint8_t ReadByte(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
void DHT11_PRINTF(void);
#endif
