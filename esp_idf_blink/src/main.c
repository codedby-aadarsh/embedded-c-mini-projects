#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"  // For vTaskDelay


void app_main() {
    gpio_config_t io_conf={};

    // Configure GPIO 4 as Output, no pull-up, no interrupt
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_4);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;  // No interrupt
    gpio_config(&io_conf);

    // Configure GPIO 5 as Input, with pull-up, interrupt enabled
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_5);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_POSEDGE;  // Interrupt on rising edge (button press)
    gpio_config(&io_conf);

    while(1){
        gpio_set_level(GPIO_NUM_4,0);
        vTaskDelay(pdMS_TO_TICKS(10000));
        gpio_set_level(GPIO_NUM_4,1);
        vTaskDelay(pdMS_TO_TICKS(10000));
    
    }

}