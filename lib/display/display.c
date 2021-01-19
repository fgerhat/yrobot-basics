#include "display.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static unsigned short disp_l = 0xFF;
static unsigned short disp_r = 0xFF;
static unsigned short active_digit = 0;
static unsigned short disp_enabled = 0;

const unsigned short segments[] = {
  0b11000000, 
  0b11111001, 
  0b10100100, 
  0b10110000, 
  0b10011001, 
  0b10010010, 
  0b10000010, 
  0b11011000, 
  0b10000000, 
  0b10010000, 
  0b10001000, 
  0b10000011, 
  0b11000110, 
  0b10100001, 
  0b10000110, 
  0b10001110  
};

ISR(TIMER2_OVF_vect)
{
    //active digit - 0 is right display, 1 is left display

    if (active_digit)
    {
        PORTB |= (1<<PB1);
        PORTC = disp_l;
        PORTB &= ~(1<<PB0);
    }
    else
    {
        PORTB |= (1<<PB0);
        PORTC = disp_r;
        PORTB &= ~(1<<PB1);
    }

    active_digit = (active_digit + 1) % 2;
}

int init_disp()
{
    //set PORTC as outputs (segment cathodes)
    DDRC = 0xFF;

    //set PB0 and PB1 as outputs (anode tranzistors)
    DDRB |= ((1<<PB0) | (1<<PB1));

    disp_off();

    //setup timer2 for display multiplexing
    //diplay is OFF by default
    TCCR2 = 0x00; //normal mode, output pin disconnected, clock disconnected
    TIMSK &= ~(1<<TOIE2); //disable timer2 overflow interrupt

    return 0;
}

int disp_on()
{
    disp_enabled = 1;
    unsigned short prescaler = 0b110; // clk/256
    
    //set timer2 clock source
    TCCR2 |= (prescaler<<CS20); 

    //enable timer2 overflow interrupt
    TIMSK |= (1<<TOIE2); 

    return 0;
}

int disp_off()
{
    disp_enabled = 0;

    //all segments off
    PORTC = 0xFF;

    //both digits off
    PORTB |= ((1<<PB0) | (1<<PB1));

    //disable timer2
    TCCR2 &= ~(0b111 < CS22); //disconnect timer2 clock
    TIMSK &= ~(1<<TOIE2); //disable timer2 overflow interrupt

    return 0;
}

unsigned short get_segments(unsigned short value)
{
    if(value > 15)
        return 0b10111111; //display will show a "-" symbol
    else return segments[value];
}

int disp(unsigned short value)
{
    //get output bit values for correct segments
    disp_l = get_segments((value & 0xF0) >> 4);
    disp_r = get_segments(value & 0x0F);

    if(!disp_enabled)
        disp_on();
    
    return 0;
}

int disp_raw(unsigned short left, unsigned short right)
{
    disp_l = left;
    disp_r = right;

    if(!disp_enabled)
        disp_on();
    
    return 0;
}