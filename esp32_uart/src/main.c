/*
THIS PROGRAM DEMONSTRATE THE UART CAPABLITY OF THE UART COMMUNICATION PROTOCOL
AND GOES STEP BY STEP ON HOW TO SET UP THE UART COMMUNICATION PROTOCOL USING THE 
ESP-IDF HAL AND THIS PROTOCOL IS INTENDED FOR THE SERIAL LOOPBACK, WHIC MEANS 
ANYTHING YOU WRITE YOU WILL RECIEVE BACK ON YOUR TERMINAL, BY CONNECTING THE UART TX
BACK TO THE UART RX. TO SHOW THE CAPABLITY OF THE DATA IS SENT AND RECIVED.
*/


#include <driver/uart.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void app_main() {
    //installing the drivers 
    const int uart_buffer_size = (1024*2); // defining the uart buffer size 
    QueueHandle_t uart_queue; // defining the uart queue
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0,uart_buffer_size,uart_buffer_size,10,&uart_queue,0));

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    //updating the config paramters for the UART_NUM_0
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0,&uart_config));

    // setting the pin for the uart 0 and it handled by the gpio matrix 
    // so you can enter the any pin you want but remember the pin order 
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0,1,3,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE));

     while (1) {
        // const char* test_str = "Hello UART0!";
        // uart_write_bytes(UART_NUM_0, test_str, strlen(test_str));

        // Read data 
        uint8_t data[128];
        int len = uart_read_bytes(UART_NUM_0, data, sizeof(data) - 1, 20 / portTICK_PERIOD_MS);

        if (len > 0) {
            data[len] = '\0'; // Null-terminate the data
            printf("Received: %s\n", data);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second
    }
    
}