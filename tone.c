#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "tone.h"

#define BUZZER 2

void init_tone(void) {
    DDRB |= _BV(BUZZER);

    TCCR0A =
        (0 << COM0A1) |
        (1 << COM0A0) |
        (1 << WGM01);
}

void play_tone(uint16_t f_Hz, uint16_t dur_ms) {
    uint16_t i = 0;
    uint16_t dur_converted = 100 * dur_ms;

    TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
    OCR0A = 125000 / f_Hz;
    for (i = 0; i < dur_converted; i++) {_delay_us(PERIOD_RESOLUTION_US);}
    TCCR0B = 0;
}

void start_tone(uint16_t f_Hz) {
    TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
    OCR0A = 125000 / f_Hz;
}

void stop_tone(void) {
    TCCR0B = 0;
}
