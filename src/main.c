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

	unsigned short x = 0;

	while(1)
	{
		disp_hex(x++);
		x = x % 256;
		_delay_ms(250);
	}

    return 0;
}