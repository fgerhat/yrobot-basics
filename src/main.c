#include <avr/io.h>
#include <util/delay.h>

const uint8_t segments[] = {
  0b11000000,
  0b11111001,
  0b10100100,
  0b10110000,
  0b10011001,
  0b10010010,
  0b10000010,
  0b11111000,
  0b10000000,
  0b10010000,
  0b10001000,
  0b10000011,
  0b11000110,
  0b10100001,
  0b10000110,
  0b10001110
};

int init()
{
  // init right and left leds
  DDRA |= ((1<<PA5) | (1<<PA6));
  PORTA |= ((1<<PA5) | (1<<PA6));

  // init 7seg disp
  DDRC = 0xFF;
  PORTC = 0xFF;
  DDRB |= ((1<<PB0) | (1<<PB1));
  PORTB |= ((1<<PB0) | (1<<PB1));

  // init buzzer
  DDRA |= (1<<PA7);
  PORTA |= (1<<PA7); // buzzer off, important!

  // init right and left buttons
  DDRB &= ~((1<<PB2) | (1<<PB3));
  PORTB |= ((1<<PB2) | (1<<PB3)); // enable pullups

  // init wheel encoders

  // init motor driver

  return 0;
}

int main()
{
  init();

  // enable both 7seg displays
  PORTB &= ~((1<<PB0) | (1<<PB1));

  short disp = 0;

  while(1)
  {
      PORTC = segments[disp];
      _delay_ms(500);
      disp = (disp + 1) % 16;
  }

  return 0;
}