#include "game.h"

#include "input.h"
#include "tone.h"

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define DEFAULT_SEG_LENGTH 200
#define DEFAULT_SEG_DELAY  50
#define ROUND_DELAY        500

#define GAME_PASS 0
#define GAME_FAIL 1

static game_t current_game;
uint8_t random_seed;


// STATIC FUNCTION DECLARATIONS //
static uint8_t button_to_color(uint8_t button);

static const uint8_t surprise_sequence[] = {
    BUTTON_1,
    BUTTON_2,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_3,
    BUTTON_4
};

static const uint16_t surprise_note_sequence[] = {
    TONE_C5,
    TONE_D5,
    TONE_Ds5,
    TONE_F5,
    TONE_G5,
    TONE_Gs5,
    TONE_As5
};
static const uint8_t surprise_length = 8;

static bool game_advance_surprise_state_machine(uint8_t button)
{
    static uint8_t surprise_counter = 0;

    if(button == surprise_sequence[surprise_counter])
    {
        surprise_counter++;

        if(surprise_counter == (surprise_length-1))
            game_surprise_melody();
        else
            play_tone(surprise_note_sequence[surprise_counter], 100);

        return true;
    }
    else
    {
        surprise_counter = 0;
        return false;
    }
}

void game_free_play(void)
{
    while (1)
    {
        while (!input_button_pressed() || input_last_button() == BUTTON_UNDEFINED);

        uint8_t pot_val = read_pot();

        if(!((pot_val > 118 && pot_val < 138) &&
             game_advance_surprise_state_machine(input_last_button())))
            game_button_segment(button_to_color(input_last_button()));

        input_clear_button_pressed();
    }
}

void game_start(uint8_t starting_length)
{
    uint8_t game_status = GAME_PASS;
    current_game.length = starting_length;
    game_generate_pattern();

    current_game.speed = 100;
    game_start_melody();
    _delay_ms(ROUND_DELAY);

    if (current_game.mode == MODE_FREE_PLAY)
    {
        game_free_play();
    }

    while (current_game.length < MAX_GAME_LENGTH)
    {
        game_display_pattern();
        input_clear_button_pressed();
        game_status = game_get_input();

        if (game_status == GAME_PASS && current_game.length <= MAX_GAME_LENGTH)
        {
            current_game.length++;
            _delay_ms(ROUND_DELAY);
        }
        else
            break;
    }

    if (game_status == GAME_PASS)
        game_victory();
    else
        game_over();
}

void game_over(void)
{
    if (current_game.mode == MODE_SILENT)
    {
        _delay_ms(100);
    }
    else
    {
        play_tone(TONE_A7, 50);
        play_tone(TONE_C7, 50);
        play_tone(TONE_Ds7, 50);
        _delay_ms(50);
        play_tone(TONE_A6, 50);
        play_tone(TONE_C6, 50);
        play_tone(TONE_Ds6, 50);
        _delay_ms(50);
        play_tone(TONE_A5, 50);
        play_tone(TONE_C5, 50);
        play_tone(TONE_Ds5, 50);
        _delay_ms(50);
    }

    int i = 3;
    while(i--)
    {
        set_leds(ALL_LEDS, ON);
        if (current_game.mode == MODE_SILENT)
            _delay_ms(100);
        else
            play_tone(TONE_C4, 100);
        set_leds(ALL_LEDS, OFF);

        _delay_ms(100);
    }
}

void game_victory(void)
{
    play_tone(TONE_C7, 50);
    play_tone(TONE_C8, 50);
    play_tone(TONE_G8, 20);
}

void game_start_melody(void)
{
    if (current_game.mode != MODE_SILENT)
    {
        play_tone(TONE_C5, 50);
        _delay_ms(50);
        play_tone(TONE_Ds5, 50);
        play_tone(TONE_E5, 50);
        play_tone(TONE_Ds5, 50);
        play_tone(TONE_E5, 50);
        _delay_ms(50);
        play_tone(TONE_G5, 50);
        _delay_ms(50);
        play_tone(TONE_A5, 50);
        _delay_ms(50);
        play_tone(TONE_C6, 200);
    }
}

void game_power_up_melody(void)
{
    play_tone(TONE_C5, 50);
    _delay_ms(50);
    play_tone(TONE_C5, 50);
    play_tone(TONE_Ds5, 50);
    play_tone(TONE_F5, 50);
    _delay_ms(50);
    play_tone(TONE_C5, 50);
    _delay_ms(50);
    play_tone(TONE_Gs5, 50);
}

void game_surprise_melody(void)
{
    while(1)
    {
        play_tone(TONE_C5, 3*100);
        _delay_ms(1*100);
        play_tone(TONE_D5, 1*100);
        _delay_ms(1*100);
        play_tone(TONE_As4, 3*100);
        _delay_ms(1*100);
        play_tone(TONE_C5, 10*100);
        _delay_ms(4*100);

        play_tone(TONE_Ds5, 3*100);
        _delay_ms(1*100);
        play_tone(TONE_D5, 1*100);
        _delay_ms(1*100);
        play_tone(TONE_As4, 3*100);
        _delay_ms(1*100);
        play_tone(TONE_C5, 10*100);
        _delay_ms(4*100);
    }
}

void game_display_pattern(void)
{
    int i;

    for (i = 0; i < current_game.length; i++)
    {
        game_display_segment(current_game.pattern[i]);
        _delay_ms(DEFAULT_SEG_DELAY);
    }
}

void game_set_mode(uint8_t mode)
{
    current_game.mode = mode;
}

uint8_t game_get_input(void)
{
    int i;

    for (i = 0; i < current_game.length; i++)
    {
        while (!input_button_pressed() || input_last_button() == BUTTON_UNDEFINED);

        if (game_input_correct(i, input_last_button())
            || current_game.mode == MODE_FREE_PLAY)
        {
            game_button_segment(button_to_color(input_last_button()));
        }
        else
        {
            return GAME_FAIL;
        }
        input_clear_button_pressed();
    }
    return GAME_PASS;
}

bool game_input_correct(uint8_t index, uint8_t input)
{
    if (current_game.pattern[index] == button_to_color(input))
        return true;
    else
        return false;
}

void game_display_segment(uint8_t color)
{
    uint16_t segment_length = DEFAULT_SEG_LENGTH;

    if (current_game.mode == MODE_HARD)
        segment_length = segment_length/4;

    else if (current_game.mode == MODE_FREE_PLAY)
    {
        segment_length = 25 + (read_pot() << 1);
    }

    switch (color)
    {
        case YELLOW:
            set_leds(LED_1, ON);
            if (current_game.mode == MODE_SILENT)
                _delay_ms(DEFAULT_SEG_LENGTH << 1);
            else
                play_tone(FREQ_1, segment_length);
            break;

        case GREEN:
            set_leds(LED_2, ON);
            if (current_game.mode == MODE_SILENT)
                _delay_ms(DEFAULT_SEG_LENGTH << 1);
            else
                play_tone(FREQ_2, segment_length);
            break;

        case RED:
            set_leds(LED_3, ON);
            if (current_game.mode == MODE_SILENT)
                _delay_ms(DEFAULT_SEG_LENGTH << 1);
            else
                play_tone(FREQ_3, segment_length);
            break;

        case BLUE:
            set_leds(LED_4, ON);
            if (current_game.mode == MODE_SILENT)
                _delay_ms(DEFAULT_SEG_LENGTH << 1);
            else
                play_tone(FREQ_4, segment_length);
            break;
    }
    set_leds(ALL_LEDS, OFF);
}

void game_button_segment(uint8_t color)
{
    switch (color)
    {
        case YELLOW:
            set_leds(LED_1, ON);
            if (current_game.mode != MODE_SILENT)
                start_tone(FREQ_1);
            break;

        case GREEN:
            set_leds(LED_2, ON);
            if (current_game.mode != MODE_SILENT)
                start_tone(FREQ_2);
            break;

        case RED:
            set_leds(LED_3, ON);
            if (current_game.mode != MODE_SILENT)
                start_tone(FREQ_3);
            break;

        case BLUE:
            set_leds(LED_4, ON);
            if (current_game.mode != MODE_SILENT)
                start_tone(FREQ_4);
            break;
    }

    while ((PINA & (BUTTON_2 | BUTTON_3 | BUTTON_4)) | (PINB & BUTTON_1));

    stop_tone();
    set_leds(ALL_LEDS, OFF);
}

void game_generate_pattern(void)
{
    game_rand_setup();
    int i;

    for(i = 0; i < MAX_GAME_LENGTH; i++)
    {
        current_game.pattern[i] = rand() % 4;
    }
}

void game_rand_setup()
{
    static bool initial_setup = true;

    if(initial_setup)
    {
        srand(read_pot() ^ read_temp());
        initial_setup = false;
    }
}

static uint8_t button_to_color(uint8_t button)
{
    switch (button)
    {
        case BUTTON_1:
            return YELLOW;

        case BUTTON_2:
            return GREEN;

        case BUTTON_3:
            return RED;

        case BUTTON_4:
            return BLUE;

        default:
            return 0;
    }
}
