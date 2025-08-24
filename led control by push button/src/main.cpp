#include <avr/io.h>
#include <util/delay.h>

int main(void){
  DDRB = 0x02;
  while (1)
  { if(PINB&(0x01)){
    PORTB^=(0x02);
    _delay_ms(200);
  }  
  }
  return 0;
}