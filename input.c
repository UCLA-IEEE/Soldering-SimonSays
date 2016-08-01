#include "input.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <stdbool.h>
#include <util/delay.h>

static uint8_t last_button;
static bool button_pressed;

ISR(PCINT0_vect)        // interrupt service routine
{              // called when PCINT0 changes state
    _delay_ms(DEBOUNCE_TIME_MS);
    if (PINA & BUTTON_2)
        last_button = BUTTON_2;
    if (PINA & BUTTON_3)
        last_button = BUTTON_3;
    if (PINA & BUTTON_4)
        last_button = BUTTON_4;

    button_pressed = true;

    GIFR |= (1<<PCIF0);
}

ISR(PCINT1_vect)
{
    _delay_ms(DEBOUNCE_TIME_MS);
    if (PINB & BUTTON_1)
        last_button = BUTTON_1;
    button_pressed = true;

    GIFR |= (1<<PCIF1);
}

void input_init(void)
{
    button_pressed = false;

    DDRA   |= LED_2 | LED_3 | LED_4;
    DDRB   |= LED_1;

    DDRA   &= ~(POT | BUTTON_2 | BUTTON_3 | BUTTON_4);
    DDRB   &= ~BUTTON_1;
    PORTA  &= ~(POT | BUTTON_2 | BUTTON_3 | BUTTON_4);
    PORTB  &= ~BUTTON_1;

    PCMSK0 |= (1<<PCINT7) | (1<<PCINT4) | (1<<PCINT3);
    PCMSK1 |= (1<<PCINT9);
    GIMSK  |= (1<<PCIE0)  | (1<<PCIE1);

    DIDR0 |= ADC0D;
}

void input_wait_for_button(void)
{
    button_pressed = false;
    while (!input_button_pressed());
    input_clear_button_pressed();
}

bool input_button_pressed(void)
{
    return button_pressed;
}

uint8_t input_last_button(void)
{
    return last_button;
}

void input_clear_button_pressed(void)
{
    button_pressed = false;
    last_button = BUTTON_UNDEFINED;
}

void set_leds(uint8_t leds, uint8_t state)
{
        if (state == OFF)
        {
            PORTA &= ~((LED_2 | LED_3 | LED_4) & leds);
            PORTB &= ~(LED_1 & leds);
        }
        else if (state == ON)
        {
            PORTA |= ((LED_2 | LED_3 | LED_4) & leds);
            PORTB |= (LED_1 & leds);
        }
}

void configure_pot(void)
{
    // Disable the digital input buffer on ADC2 (PA2).
    // [16.13.5]
    DIDR0 = (0b1 << 2);

    // Set the ADC to reference VCC, source conversions from ADC2 (PA2).
    // [16.13.1]
    ADMUX = (0b00 << 6) | (0b000010 << 0);

    // Set the ADC prescaler to 64.
    // [16.13.2]
    ADCSRA = (0b110 << 0);

    // Set the ADC to left-adjust the conversion result.
    // [16.13.4]
    ADCSRB = (0b1 << 4);
}

uint8_t read_pot(void)
{
    // Enable the ADC.
    // [16.13.2]
    ADCSRA |= (0b1 << 7);

    // Wait for the conversion flag to be clear.
    // [16.13.2]
    while (ADCSRA & (0b1 << 6));

    // Start the conversion.
    ADCSRA |= (0b1 << 6);

    // Wait for the conversion to finish.
    while (ADCSRA & (0b1 << 6));

    return ADCH;
}

uint8_t read_temp(void)
{
    uint8_t old_admux = ADMUX;

    ADMUX = (0b10 << 6) | (0b100010 << 0);

    uint8_t ret = read_pot();

    ADMUX = old_admux;

    return ret;
}
