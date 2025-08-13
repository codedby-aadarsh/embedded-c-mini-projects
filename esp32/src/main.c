#include <stdio.h>
#define GPIO_OUT_REG      0x3FF44004 // read and write access
#define GPIO_OUT_W1TS_REG 0x3FF44008 //write only access(WO)
#define GPIO_OUT_W1TC_REG 0x3FF4400C // WO access
#define GPIO_ENABLE_REG   0x3FF44020
#define DELAY_MS          500
#define GPIO_PIN          2
#define IO_MUX_GPIO26_REG ((*IO_MUX_GPIO26_REG & ~0xF)|FUNC_GPIO 0x3FF49068) 
#define FUNC_GPIO         0
    
// so the thing here what i did  and this register io mux 26  register 

void delay(volatile int delay){
    while (delay--) {
        for (volatile int i = 0; i < 1000; i++);
    }
}

void app_main(void){
    volatile uint32_t *gpio_ena_reg = (volatile uint32_t*) GPIO_ENABLE_REG;
    //volatile uint32_t *gpio_out_reg = (volatile uint32_t*) GPIO_OUT_REG;
    volatile uint32_t *gpio_w1ts_reg = (volatile uint32_t*) GPIO_OUT_W1TS_REG;
    volatile uint32_t *gpio_w1tc_reg = (volatile uint32_t*) GPIO_OUT_W1TC_REG;
    // volatile uint32_t *iomux_26_reg  = (volatile uint32_t*) IO_MUX_GPIO26_REG;
    // *iomux_26_reg = (*iomux_26_reg & ~0xF) | FUNC_GPIO;
    *gpio_ena_reg |= (1<<GPIO_PIN)|(1<<26);


    while(1){
        *gpio_w1ts_reg |=(1<<GPIO_PIN);
        *gpio_w1tc_reg |=(1<<26);
        delay(DELAY_MS);
        *gpio_w1ts_reg |=(1<<26);
        *gpio_w1tc_reg |=(1<<GPIO_PIN);
        delay(DELAY_MS);
    }


}