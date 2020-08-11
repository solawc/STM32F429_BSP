#include "rt_app.h"

rt_thread_t led_thread = RT_NULL;

void led_task_entry(void *parg)
{   
    uint32_t led_duty = 0;
    uint32_t led_flag = 0;

    while(1)
    {
        if(led_flag == 0)
        {
            bsp_rgb_set(0,led_duty,0);
            led_duty++;
            if(led_duty == 250)
            {
                led_flag = 1;
            }
        }
        else if(led_flag == 1)
        {
            bsp_rgb_set(0,led_duty,0);
            led_duty--;
            if(led_duty == 0)
            {
                led_flag = 0;
            }
        } 
        
        if(WIFI_STATUS == 1) 
        {
            bsp_rgb_set(255,led_duty,0);
        }
        else
        {
            bsp_rgb_set(0,led_duty,255);
        }
        

        rt_thread_mdelay(10); 
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
                                    4,
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


rt_thread_t adc_v_thread = RT_NULL;
void adc_v_task_entry(void *parg)
{
    float adv_get_value = 0;
    int times = 0;
    float adc_get_str[255];
    float res = 0;
    while(1)
    {
        adv_get_value = bsp_adc_get(ADC_CHANNEL_13);
        adv_get_value = ((float)adv_get_value/(float)4096)*(float)3.3;

        adc_get_str[times] = adv_get_value;
        times++;

        if(times == 255)
        {
            for(int i=0;i<255;i++)
            {
                res += adc_get_str[i];
            }

            res = res /255;
            DEBUG_PRINT("res :%f",(float)res);
			times = 0;
        }

        //DEBUG_PRINT("adc get :%f",(float)adv_get_value);
        rt_thread_delay(10);
    }
}

void adc_v_task_init(void)
{
    adc_v_thread =  rt_thread_create( "adc v task",
                                    adc_v_task_entry,
                                    RT_NULL,
                                    4096,
                                    7,
                                    20);

    if(adc_v_thread != RT_NULL)
    {
        rt_thread_startup(adc_v_thread);
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
                                    1024,
                                    3,
                                    20);
    if(gizwits_thread != RT_NULL)
    {
        rt_thread_startup(gizwits_thread);
    }
}
