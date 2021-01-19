#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//yrobot specific
#include <leds.h>
#include <buttons.h>
#include <buzzer.h>
#include <display.h>

int main()
{
	init_buzzer();
	init_leds();
	init_buttons();
	init_disp();
	sei();

	unsigned short l, r;

	while(1)
	{
		set_led_l(get_button_l());
		set_led_r(get_button_r());

		l = get_button_l() ? 0b10111111 : 0b11111111;
		r = get_button_r() ? 0b10111111 : 0b11111111;

		disp_raw(l, r);
	}

    return 0;
}