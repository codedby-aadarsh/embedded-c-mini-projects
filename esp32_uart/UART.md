## UART Communication protocols

### what is UART?
- UART (Universal Asynchronous Receiver/Transmitter) is a hardware communication protocol used for asynchronous serial communication. It enables full-duplex or half-duplex data exchange between devices without a shared clock, using start/stop bits and optional parity for data framing. UART is widely used for device-to-device communication, debugging, and interfacing with peripherals like sensors, modems, and computers.
 
### How we are implementing this protocol?
- so uart is as we know a full duplex communication protocols doesnt requires any clock line and can be implemented with the few wires one is Tx and Rx , while the other need to be a common ground between them.
- The protocol is being implemented using the ESP-IDF hal and the source code is also provided you can check it out.
- Install the UART driver using uart_driver_install(), specifying:
 - UART port number - esp32 have got the namely three ports UART0,UART1,UART2 each with their respective gpio pins.
 - RX and TX buffer sizes - you have to set the buffer size for the data to be recieved and transmitted, as this helps in storing the incoming data before its read.
 - Event queue size - here you give the size for the queue handler for the event.
 - Pointer to event queue handle - this is the pointer queue handler type queue which is used to store the events which occurs during the communincation. 
 - Interrupt allocation flags - you can set the flags and multiple flags seperated by the or (|).

### flow for the code
- installing the uart driver.
```c
	// Installing the drivers 
    const int uart_buffer_size = (1024 * 2); // defining the uart buffer size 
    QueueHandle_t uart_queue; // defining the uart queue
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
```
- configuring the parameters
```c 
 uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

```
- configuring the parameter for the port and setting the pins we want,In the uart set pin , you can define your own pins and the gpio matrix handles the routing for you and for no change in the pins, writet simply the UART_PIN_NO_CHANGE. 

```C
// Updating the config parameters for UART_NUM_0
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));

    // Setting the pins for UART0 (TX=1, RX=3) — default pins
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, 1, 3, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
```


### thank you for reading.
