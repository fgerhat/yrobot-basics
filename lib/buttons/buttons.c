#include "buttons.h"
#include <avr/io.h>

int init_buttons()
{
    //set PB2 and PB3 as inputs
    DDRB &= ~((1<<PB2) | (1<<PB3));

    //enable internal pullups
    PORTB |= ((1<<PB2) | (1<<PB3));

    return 0;
}

short get_button_l()
{
    //SW2, active LOW
    if(PINB & (1<<PB2))
    {
        return 0;
    }
    else
    { 
        return 1;
    }
    return 0;
}

short get_button_r()
{
    //SW3, active LOW
    if(PINB & (1<<PB3))
    {
        return 0;
    }
    else
    { 
        return 1;
    }
    return 0;
}