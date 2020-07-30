/***********************************************************************
*@Date: 2020-05-22 04:47:09
*@LastEditors: SOLA
*@LastEditTime: 2020-05-24 18:05:57
*@FilePath: \RT1052\Libraries\hardware\dht11.h
***********************************************************************/
#ifndef __dht11_h
#define __dht11_h

#include "main.h"

/*�ײ�ӿ�*/
#define __DHT11_GPIO_INIT()     dht11_gpio_init()
#define __DHT11_MODE(MODE)      DHT11_MODE(MODE)
#define __DHT11_OUT_H()         HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET)
#define __DHT11_OUT_L()         HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_RESET)
#define __DHT11_READ()          HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)
#define __DHT11_DELAY_MS(nms)   delay_ms(nms)
#define __DHT11_DELAY_US(nms)   delay_us(nms)

/*Ӳ���ӿ�*/
#define __DHT11_PIN_CLK()		__HAL_RCC_GPIOE_CLK_ENABLE()       
#define DHT11_PIN              	GPIO_PIN_2 
#define DHT11_PORT              GPIOE

/*��ʱ����*/
#define  SYSCLK                             180000000/1000000                   //ָ��CPU����Ƶ��Ϊ(SystemCoreClock/1000000)MHz
#define  A                                  3                                   //һ��ѭ��������������
#define  B                                  1                                   //���á���ʼ���������ܹ����õ�������
#define  delay_us(nus)                      wait(((nus)*(SYSCLK)-(B))/(A))
#define  delay_ms(nms)                      delay_us((nms)*1000)
#define  delay_s(ns)                        delay_ms((ns)*1000)

/*�ṹ���Ա����*/
typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
	float 	 humi;			//ʪ��
	float 	 temp;			//�¶�
		                 
}DHT11_Data_TypeDef;
extern DHT11_Data_TypeDef DHT11_Data;

/*��������*/
void  wait(unsigned long n);
void dht11_init(void);
uint8_t ReadByte(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
void DHT11_PRINTF(void);
#endif
