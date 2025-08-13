#include <avr/io.h>// for using the portb and other register 
#include <util/delay.h> // for adding delays
#include "USART.h"



#define LED_PORT  PORTB 
#define LED_DDR   DDRB 

int main(){

char serialCharacter;
LED_DDR= 0xff; //making all of the port bits as outputs 

initUSART(); //initailsing the uart 
printString("hello world!\r\n"); // testing 

while(1){
serialCharacter =receiveByte();
transmitByte(serialCharacter);
LED_PORT = serialCharacter;
}

return 0;//never reaches this point 
}
