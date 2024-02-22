#include <Arduino.h>

void setup() {
  // init DDRB as output
  DDRB = 0xFF;
  // init port B to 0 
  PORTB = 0x01;
}

void loop() {
  // wait 1 second
  delay(1000);
  // shift left
  PORTB = PORTB << 1;
  // if PORTB is 0, reset to 1
  if (PORTB == (1 << 5)) {
    PORTB = 0x01;
  }
}

