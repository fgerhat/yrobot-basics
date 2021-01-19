#include "drive.h"
#include <avr/io.h>
#include <avr/interrupt.h>

const static unsigned int timer1_top = 0x00FF;
const static unsigned short timer1_prescaler = 0b001; //clk/1

long steps_l = 0;
long steps_r = 0;

static short dir_l = DIR_FWD;
static short dir_r = DIR_FWD;

ISR(INT0_vect)
{
    cli();
    steps_r += dir_r;
    sei();
}

ISR(INT1_vect)
{
    cli();
    steps_l += dir_l;
    sei();
}

int init_drive()
{
    //set encoder pins as inputs
    DDRD &= ~((1<<PD2) | (1<<PD3));

    //disable encoder pullups
    PORTD &= ~((1<<PD2) | (1<<PD3));

    //set interrupt mode for INT0 and INT1 to detect both rising and falling edge
    MCUCR |= (1<<ISC10) | (1<<ISC00);

    //enable interrupts for encoder inputs
    GICR |= (1<<INT0) | (1<<INT1);

    //set motor direction pins as outputs
    DDRD |= (1<<PD6) | (1<<PD7);
    //set PB4 pin as output (motor driver M1 pin)
    DDRB |= (1<<PB4);
    //M1 should always be 0 to prevent voltage spikes on the motor coil
    PORTB &= ~(1<<PB4);

    //set PWM pins (OC1A/PD5 and OC1B/PD6) as outputs
    DDRD |= (1<<PD4) | (1<<PD5);
    motors_stop();

    //setup timer1 for phase and frequency correct operation (mode 8)
    TCCR1A |= (1<<COM1A1) | (1<<COM1B1); //clear output when upcounting, set when downcounting
    TCCR1B |= (1<<WGM13) | (timer1_prescaler<<CS10); //set mode 8, set prescaler
    ICR1 = timer1_top; //set the TOP value of the timer

    return 0;
}

int motors_stop()
{
    OCR1A = 0;
    OCR1B = 0;

    dir_l = DIR_STOP;
    dir_r = DIR_STOP;

    //turn both motors off
    PORTD &= ~((1<<PD4) | (1<<PD5));

    //set driver M1 pin low to connect both sides of the motor coil to ground
    PORTB &= ~(1<<PB4);

    return 0;
}


int set_motor_l(signed int speed)
{
    dir_l = (speed == 0) ? DIR_STOP : (speed > 0 ? DIR_FWD : DIR_REV);

    if(dir_l == DIR_REV)
    {
        speed *= -1;
        PORTD &= ~(1<<PD7);
    }
    else
    {
        PORTD |= (1<<PD7);      
    }
    
    OCR1B = speed & timer1_top;
    return OCR1B * dir_l;
}

int set_motor_r(signed int speed)
{
    dir_r = (speed == 0) ? DIR_STOP : (speed > 0 ? DIR_FWD : DIR_REV);
    OCR1A = speed & timer1_top;
    return OCR1A = dir_r;
}