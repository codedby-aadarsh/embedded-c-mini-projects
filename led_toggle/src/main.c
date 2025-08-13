// so the task here is to blink an led connected at gpio 18 and based on the input at the gpio4 , like
// the gpio 4 acts as an interrupt and its response is taken as the led at 18 toggle 
#include <stdlib.h>
#include "esp_rom_sys.h"
#define GPIO_OUT_REG        0x3FF44004
#define GPIO_OUT_W1TS_REG   0x3FF44008
#define GPIO_OUT_W1TC_REG   0x3FF4400C
#define GPIO_OUT_18_REG     18
#define IO_MUX_GPIO18_REG   *((volatile uint32_t*) 0x3FF49070)& ~0xF | 0 // setting the gpio18 as the func 0
#define GPIO_ENABLE_REG     0x3FF44020
#define GPIO_IN_REG         0x3FF4403C

// // GPIO Pull-up Register
// #define GPIO_PULLUP_REG     0x3FF49020  // GPIO Pull-up Register for pin configuration

// // Interrupt setup register (used to configure interrupt type)
// #define GPIO_INT_REG        0x3FF44030  // Register to set interrupt type (this may vary)


void gpio_isr_handler(void) {
    volatile uint32_t *out = (volatile uint32_t *) GPIO_OUT_REG;

    // Toggle the LED (GPIO18) on interrupt (GPIO4 press)
    *out ^= (1 << GPIO_OUT_18_REG);  // Toggle GPIO18 (LED)
    esp_rom_delay_us(500000); // Small delay for debounce
}

void app_main() {
    volatile uint32_t *set =(volatile uint32_t *) GPIO_OUT_W1TS_REG;
    volatile uint32_t *clear =(volatile uint32_t *) GPIO_OUT_W1TC_REG;
    volatile uint32_t *stat =(volatile uint32_t *)  GPIO_IN_REG;
    volatile uint32_t *out = (volatile uint32_t *)  GPIO_OUT_REG;
    volatile uint32_t *en = (volatile uint32_t *)  GPIO_ENABLE_REG;
    *en|=(1<<GPIO_OUT_18_REG);
    *en&=~(1<<4); // this sets the pin 4 as the input.
    *clear|=(1<<GPIO_OUT_18_REG); // initially i have cleared the signal at gpio 18
    *clear|=(1<<4);

    

    while(1){
        if (*stat&(1<<4)){
            gpio_isr_handler();
            esp_rom_delay_us(500000);
        }

    }
}
