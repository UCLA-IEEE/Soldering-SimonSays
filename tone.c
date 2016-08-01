#include "tone.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define BUZZER 2

void init_tone(void)
{
    DDRB |= _BV(BUZZER);

    TCCR0A =
        (0 << COM0A1) |
        (1 << COM0A0) |
        (1 << WGM01);
}

typedef enum
{
    T_DIV_1 = 1,
    T_DIV_8 = 2,
    T_DIV_64 = 3,
    T_DIV_256 = 4,
    T_DIV_1024 = 5
} timer_divider_t;

void play_tone(uint16_t f_Hz, uint16_t dur_ms)
{
    start_tone(f_Hz);

    while(dur_ms--)
    {
        _delay_ms(1);
    }

    stop_tone();
}

static inline void set_divider(timer_divider_t divider)
{
    TCCR0B &= ~(0x07);
    TCCR0B |= ((uint8_t)divider) & 0x07;
}

void start_tone(uint16_t f_Hz)
{
    //if(f_Hz <= 976)
    //{
    //    set_divider(T_DIV_1024);
    //    OCR0A = 977/f_Hz;
    //}
    //else if(f_Hz <= 3906)
    //{
    //    set_divider(T_DIV_256);
    //    OCR0A = 3906/f_Hz;
    //}
    //else if(f_Hz <= 15625)
    //{
    //    set_divider(T_DIV_64);
    //    OCR0A = 15625/f_Hz;
    //}
    //else
    //{
    TCCR0B &= ~(0x07);
    TCCR0B |= (f_Hz & 0x07);
    OCR0A = (f_Hz >> 3) & 0xFF;
    //}
    //TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
    //OCR0A = 125000 / f_Hz;
}

void stop_tone(void)
{
    TCCR0B = 0;
}
