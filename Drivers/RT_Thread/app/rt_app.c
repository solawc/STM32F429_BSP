#include "rt_app.h"

rt_thread_t led_thread = RT_NULL;
void led_task_entry(void *parg)
{   
    uint8_t buff_read;
    bool status = true;
    while(1)
    {
        bsp_led_toggle(BSP_LED_R);

        while(status == true)
        {
            status = ringbuffer_read(&buff_read);
            
            if(status == true)
            {
                HAL_UART_Transmit(&huart1,&buff_read,1,1);
            }
            
        }
        status = true;
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
                DEBUG_PRINT("key2 down");   
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
                                    4,
                                    20);

    if(key_thread != RT_NULL)
    {
        rt_thread_startup(key_thread);
    }
}


