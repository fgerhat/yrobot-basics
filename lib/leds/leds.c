#include "leds.h"
#include <avr/io.h>

int init_leds()
{
    //set PA5 (left led) and PA6 (right led) as outputs
    DDRA |= (1<<PA5) | (1<<PA6);

    //turn off both leds
    PORTA |= (1<<PA5) | (1<<PA6);

    return 0;
}

int set_led_l(short state)
{
    if(state)
    {
        PORTA &= ~(1<<PA5);
    }
    else
    {
        PORTA |= (1<<PA5);
    }
    return 0;
}

int set_led_r(short state)
{
    if(state)
    {
        PORTA &= ~(1<<PA6);
    }
    else
    {
        PORTA |= (1<<PA6);
    }
    return 0;
}