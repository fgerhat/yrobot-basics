#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//yrobot specific
#include <leds.h>
#include <buttons.h>
#include <buzzer.h>
#include <display.h>
#include <drive.h>

int main()
{
	init_buzzer();
	init_leds();
	init_buttons();
	init_disp();
	init_drive();
	sei();

	int speed = 0;

	while(1)
	{
		disp_dec(steps_l);
		set_led_l(PIND & (1<<PD2));
		set_led_r(PIND & (1<<PD3));

		if(get_button_r())
		{
			speed++;
			if(speed > 255) speed = 255;
			set_motor_l(speed);
			_delay_ms(10);
		}
		else if(get_button_l())
		{
			speed--;
			if(speed < -255) speed = -255;
			set_motor_l(speed);
			_delay_ms(10);
		}
		else
		{
			if (speed > 0) speed--;
			if (speed < 0) speed ++;
			set_motor_l(speed);
			_delay_ms(10);
		}
		
	}

    return 0;
}