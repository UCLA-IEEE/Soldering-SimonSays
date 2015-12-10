/*
 * Simon.c
 *
 * Created: 11/5/2013 10:56:54 PM
 *  Author: Julian
 */ 

/* Command for programming:
 * avrdude -b 19200 -p t84 -c avrisp -P com3 -U flash:w:\Users\Julian\Documents\Simon\Simon\Debug\Simon.hex
 *	
 */

#define FINAL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "tone.h"
#include "input.h"
#include "game.h"

#define DEFAULT_STARTING_LENGTH 3

void setup(void);
void display_mode(void);

int main(void)
{
	setup();
	sei(); // Enable interrupts

    power_up_melody();

	while(1)
    {
		display_mode();
		
		if (input_button_pressed()) {
			_delay_ms(100);
			input_clear_button_pressed();		
			game_start(DEFAULT_STARTING_LENGTH);
		}
		
		input_clear_button_pressed();
	}
}

void set_power_led_on(void)
{
    DDRA |= POWER_LED;
    PORTA |= POWER_LED;
}

void setup(void) {
	init_tone();
	input_init();
    configure_pot();

    set_power_led_on();

	return;
}

uint8_t read_mode(void)
{
	uint8_t pot_reading = read_pot();
	if (pot_reading > ((3 * MAX_POT_VALUE) / 4))
        return MODE_NORMAL;
	if (pot_reading > (MAX_POT_VALUE / 2))
		return MODE_SILENT;
	if (pot_reading > (MAX_POT_VALUE / 4))
		return MODE_HARD;
	return MODE_FREE_PLAY;
}

void set_mode_lights(uint8_t mode)
{
    switch(mode)
    {
    case MODE_FREE_PLAY:
	    set_leds(LED_3, ON);
	    set_leds(LED_1 | LED_2 | LED_4, OFF);
        break;

    case MODE_HARD:
	    set_leds(LED_4, ON);
	    set_leds(LED_1 | LED_2 | LED_3, OFF);
        break;

    case MODE_SILENT:
	    set_leds(LED_2, ON);
	    set_leds(LED_1 | LED_3 | LED_4, OFF);
        break;

    case MODE_NORMAL:
	    set_leds(LED_1, ON);
	    set_leds(LED_2 | LED_3 | LED_4, OFF);
        break;
    }
}

void display_mode(void) {
    uint8_t mode, last_mode;

    mode = last_mode = read_mode();
    set_mode_lights(mode);

	input_clear_button_pressed();
	while (1) {
        last_mode = mode;
		mode = read_mode();

        if(mode != last_mode)
        {
            set_mode_lights(mode);

            play_tone(2000,10);

            game_set_mode(mode);
        }
	
		if (input_button_pressed())
		{
			_delay_ms(100);
			break;
		}
	}
	
	set_leds(ALL_LEDS, OFF);
}
