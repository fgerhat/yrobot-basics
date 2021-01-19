#include "buzzer.h"
#include <avr/io.h>

int init_buzzer()
{
    //set PA7 as output
    DDRA |= (1<<PA7);

    //turn buzzer off
    set_buzzer(0);

    return 0;
}

int set_buzzer(short state)
{
    if(state)
    {
        PORTA &= ~(1<<PA7);
    }
    else
    {
        PORTA |= (1<<PA7);
    }
    return 0;
}

  