#include <Arduino.h>
// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO 16

void setup() {
  // set the LED as an output
  pinMode(ledPin, OUTPUT);
}

void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM

     Serial.println("i work man ");
    analogWrite(ledPin, dutyCycle);
    Serial.print(ledPin);
    delay(15);
  }
  Serial.println("i work man ");

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    analogWrite(ledPin, dutyCycle);
    Serial.print(ledPin);
    delay(15);
  }
}