/*
Timer0 TIMER0_OVF_vect OK
Timer1 TIMER1_OVF_vect OK
Timer2 used for internal Arduino PWM TIMER2_OVF_vect
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Timer1 interrupt handler
ISR(TIMER0_OVF_vect) {
  static uint16_t nCount = 0;
  if (nCount++ >= 1000) {
    // Toggle PB5
    PORTB ^= (1 << PB5);
    nCount = 0;
  }
}

// Function to initialize Timer1 for interrupt every 1 second
void Timer0_Init() {
  // Set Timer0 Control Register A (TCCR0A)
  TCCR0A = 0; // Normal mode

  // Set Timer0 Control Register B (TCCR0B)
  TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64

  // Set Timer/Counter Register (TCNT0)
  TCNT0 = 6; // 16 MHz / (64 * 1 KHz) - 1

  // Enable Timer0 Overflow interrupt
  TIMSK0 = (1 << TOIE0);
}

// Timer1 interrupt handler
ISR(TIMER1_COMPA_vect) {
  // Toggle PB5
  // PORTB ^= (1 << PB5);
}

// Function to initialize Timer1 for interrupt every 1 second
void Timer1_Init() {
  // Set Timer1 Control Register A (TCCR1A)
  TCCR1A = 0;

  // Set Timer1 Control Register B (TCCR1B)
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, prescaler 1024

  // Set Timer1 Output Compare Register A (OCR1A)
  OCR1A = 15624; // 1 second at 16MHz with prescaler 1024

  // Enable Timer1 Output Compare A Match Interrupt
  TIMSK1 = (1 << OCIE1A);
}

// main function
int main() {
  int nBit = 1;
  // init DDRB as output
  DDRB = 0xFF;
  // init port B to 0 
  PORTB = nBit;
  Timer0_Init();
  // Enable global interrupts
  sei();

  // loop
  while (1) {
    // wait 1 second
    _delay_ms(1000);
    // shift left
    PORTB ^= nBit;
    nBit <<= 1;
    // if PB5 is 1, reset to 1
    if (nBit & (1 << 5)) {
      nBit = 0x01;
    }
    PORTB |= nBit;
  }
  return 0;
}