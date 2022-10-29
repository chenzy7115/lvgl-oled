#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_demos.h"

/*用定时器给LVGL提供时钟*/
static void lv_tick_task(void *arg)
{
	(void)arg;
	lv_tick_inc(10);
}


void app_main(void)
{
    printf("这是一个EPS32IDF框架下移植LVGL使用OLED的例程:\n");
    printf("OLED的驱动为SSD1306/地址为0X78(0x3c)/SDA:22GPIO/SLC:21GPIO\n");
    lv_init();//LV初始化
    lv_port_disp_init();//初始化显示器

    /*  esp_register_freertos_tick_hook(lv_tick_task);
    Create and start a periodic timer interrupt to call lv_tick_inc 
    给定时器一个心跳
    */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));

   
    while(1)
    {
        lv_task_handler();//调用LVdemo
        lv_tick_inc(10);//lv心跳
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}