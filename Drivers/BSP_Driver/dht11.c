#include "dht11.h"

DHT11_Data_TypeDef DHT11_Data;
/****************************************************************
*@function: dht11_gpio_init
*@input   : none
*@output  : none
*@describe: DHT11
*@author  : sola
****************************************************************/
void dht11_gpio_init(void)
{ 
	GPIO_InitTypeDef GPIO_Init;

	__DHT11_PIN_CLK();

	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pin = DHT11_PIN;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_Init);
}

/****************************************************************
*@function: DHT11_MODE
*@input   : mode    
*@output  : none
*@describe: DHT11 GPIO
*@author  : sola
****************************************************************/
void DHT11_MODE(uint8_t mode)
{	
	GPIO_InitTypeDef GPIO_Init;
	switch (mode)
	{
	case 0:
		GPIO_Init.Mode = GPIO_MODE_INPUT;
		GPIO_Init.Pin = DHT11_PIN;
		GPIO_Init.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(DHT11_PORT, &GPIO_Init);
		break;
	case 1:
		GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Init.Pin = DHT11_PIN;
		GPIO_Init.Pull = GPIO_NOPULL;
		GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(DHT11_PORT, &GPIO_Init);
		break;
	}
}


/*---------------------------Ӧ�ò�----------------------------*/

/****************************************************************
*@function: dht11_delay
*@input   : n (MHz)  
*@output  : none
*@describe: ��ʱ
*@author  : sola
****************************************************************/
void wait(unsigned long n)
{   
	do{
	n--;
	}while(n);
}

/****************************************************************
*@function: dht11_init
*@input   : none
*@output  : none
*@describe: DHT11 ��ʼ�ź�
*@author  : sola
****************************************************************/
void dht11_init(void)
{
    __DHT11_GPIO_INIT();
}

/****************************************************************
*@function: ReadByte
*@input   : none
*@output  : temp
*@describe: ��һ���ֽ�
*@author  : sola
****************************************************************/
uint8_t ReadByte(void) {

	uint8_t i, temp = 0;

	for(i=0;i<8;i++) {

		while(__DHT11_READ() == 0);
		
		__DHT11_DELAY_US(40);               //40us
	
		if(__DHT11_READ() == 1) {

			while(__DHT11_READ() == 1);

			temp |= (uint8_t)(0x01<<(7-i));
		}
		else {
			
			temp &= (uint8_t)~(0x01<<(7-i));
		}
	}	
	return temp;
} 

/****************************************************************
*@function: Read_DHT11
*@input   : *DHT11_Data
*@output  : temp
*@describe: DHT11 ������
*@author  : sola
****************************************************************/
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data) {
    
    
	__DHT11_MODE(1);            //����Ϊ���?
	
	__DHT11_OUT_L();            //����
	
	__DHT11_DELAY_MS(18);       //18ms

	__DHT11_OUT_H();            //����
    
    __DHT11_DELAY_US(13);       //13us

	__DHT11_MODE(0);            //����Ϊ����

	if(__DHT11_READ() == 0) {

		while(__DHT11_READ() == 0); 

		while(__DHT11_READ() == 1);

		DHT11_Data->humi_int= ReadByte();   //��ȡʪ������

		DHT11_Data->humi_deci= ReadByte();  //��ȡʪ��С��

		DHT11_Data->temp_int= ReadByte();   //��ȡ�¶�����

		DHT11_Data->temp_deci= ReadByte();  //��ȡ�¶�����

		DHT11_Data->check_sum= ReadByte();  //Ӧ����?

		__DHT11_MODE(1);                    //����Ϊ���?

		__DHT11_OUT_H();

		if(DHT11_Data->check_sum == 
                                    DHT11_Data->humi_int + 
                                        DHT11_Data->humi_deci + 
                                            DHT11_Data->temp_int+ 
                                                DHT11_Data->temp_deci) {
			return SUCCESS;
		}
		else {		
			return ERROR;	
		}
	}
    return 0;
}


/****************************************************************
*@function: DHT11_PRINTF
*@input   : none
*@output  : none
*@describe: DHT11 ��ӡ����
*@author  : sola
****************************************************************/
#if 1
void DHT11_PRINTF(void) {

    if(Read_DHT11(&DHT11_Data) == SUCCESS) {
              
            printf("%d.%d%% RH     %d.%d\r\n",
					DHT11_Data.humi_int,
					DHT11_Data.humi_deci,
					DHT11_Data.temp_int,
					DHT11_Data.temp_deci);
  } 
  else 
  {
		printf("\nDHT11 READ ERROR\r\n");
  }
}
#endif
