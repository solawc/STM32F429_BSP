#include "rt_app.h"

rt_thread_t led_thread = RT_NULL;

void led_task_entry(void *parg)
{   
    uint8_t ring_read = 0;
    bool ring_status = true;
    while(1)
    {
        bsp_led_toggle(BSP_LED_R);

        while (ring_status == true)
        {
           ring_status = ringbuffer_read(&ring_read);
           if(ring_status == true)
           {
               HAL_UART_Transmit(&huart1,&ring_read,1,1);
           }
        }
        ring_status = true;
        rt_thread_mdelay(50); 
    }
}

void led_task_init(void)
{
    led_thread =  rt_thread_create( "led task",
                                    led_task_entry,
                                    RT_NULL,
                                    512,
                                    4,
                                    20);

    if(led_thread != RT_NULL)
    {
        rt_thread_startup(led_thread);
    }
}

rt_thread_t key_thread = RT_NULL;
void key_task_entry(void *parg)
{
    uint8_t key_read_num;
    while(1)
    {
        key_read_num = bsp_key_scanf();

        switch (key_read_num)
        {
            case 1: 
                bsp_key1_thread_callback();

            break;
            case 2: 
                bsp_key2_thread_callback();
            break;
        }
        rt_thread_mdelay(20);
    }
}

void key_task_init(void)
{
    key_thread =  rt_thread_create( "key task",
                                    key_task_entry,
                                    RT_NULL,
                                    512,
                                    5,
                                    20);

    if(key_thread != RT_NULL)
    {
        rt_thread_startup(key_thread);
    }
}

rt_thread_t dht11_thread = RT_NULL;
void dht11_task_entry(void *parg)
{
    while (1)
    {
        rt_enter_critical();

        DHT11_PRINTF();
        
        rt_exit_critical();
        
        rt_thread_delay(1000);
    }
}

void dht11_task_init(void)
{
    dht11_thread =  rt_thread_create( "dht11 task",
                                    dht11_task_entry,
                                    RT_NULL,
                                    1024,
                                    6,
                                    20);

    if(dht11_thread != RT_NULL)
    {
        rt_thread_startup(dht11_thread);
    }
}


rt_thread_t gizwits_thread = RT_NULL;
void gizwits_handle_task_entry(void *parg)
{
    
    while (1)
    {   
        rt_enter_critical();  //enter critical
        userHandle();
        gizwitsHandle((dataPoint_t *)&currentDataPoint); //deal with 
        rt_exit_critical(); //exit critical
		rt_thread_delay(200);
    }
}

void gizwits_handle_task_init(void)
{
    gizwits_thread = rt_thread_create( "gizwits task",
                                    gizwits_handle_task_entry,
                                    RT_NULL,
                                    4096,
                                    3,
                                    20);
    if(gizwits_thread != RT_NULL)
    {
        rt_thread_startup(gizwits_thread);
    }
}
