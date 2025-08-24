#include "driver/gpio.h"
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"  // For vTaskDelay

#define led_button GPIO_NUM_4
#define push_button GPIO_NUM_5


static void IRAM_ATTR gpio_isr_handler(void *args){

    gpio_set_level(led_button,!gpio_get_level(push_button));
}


void app_main() {
    gpio_config_t io_conf ={};

    // setting gpio 4 as the ouput
    io_conf.pin_bit_mask=(1ULL<<led_button);
    io_conf.mode=GPIO_MODE_OUTPUT;
    io_conf.pull_up_en=GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en=GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type=GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    // setting gpio 5 as the input and setting the interrupt type 
    io_conf.pin_bit_mask=(1ULL<<push_button);
    io_conf.mode=GPIO_MODE_INPUT;
    io_conf.pull_up_en=GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en=GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type=GPIO_INTR_POSEDGE;
    gpio_config(&io_conf);

    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);
    gpio_isr_handler_add(push_button,gpio_isr_handler,NULL);
    gpio_set_level(led_button,0);
    while(1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }


}