#include <avr/io.h>
#include <util/delay.h>

// main function
int main() {
  // init DDRB as output
  DDRB = 0xFF;
  // init port B to 0 
  PORTB = 0x01;
  // loop
  while (1) {
    // wait 1 second
    _delay_ms(1000);
    // shift left
    PORTB = PORTB << 1;
    // if PB5 is 1, reset to 1
    if (PORTB == (1 << 6)) {
      PORTB = 0x01;
    }
  }
  return 0;
}