#include "game.h"
#include "input.h"
#include "tone.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define DEFAULT_SEG_LENGTH 200
#define DEFAULT_SEG_DELAY  50
#define ROUND_DELAY        500

#define GAME_PASS 0
#define GAME_FAIL 1

static game_t current_game;
uint8_t random_seed;


// STATIC FUNCTION DECLARATIONS //
static uint8_t button_to_color(uint8_t button);

void game_free_play(void) {
    while (1) {
        game_get_input();
    }
}

void game_start(uint8_t starting_length) {
    uint8_t game_status = GAME_PASS;
    current_game.length = starting_length;
    game_generate_pattern();

    current_game.speed = 100;
    game_start_melody();
    _delay_ms(ROUND_DELAY);

    if (current_game.mode == MODE_FREE_PLAY) {
        game_free_play();
    }

    while (current_game.length < MAX_GAME_LENGTH) {
        game_display_pattern();
        input_clear_button_pressed();
        game_status = game_get_input();

        if (game_status == GAME_PASS && current_game.length <= MAX_GAME_LENGTH) {
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

void game_over(void) {
    if (current_game.mode == MODE_SILENT) {
        _delay_ms(100);
    }
    else {
        play_tone(A7, 50);
        play_tone(C7, 50);
        play_tone(Ds7, 50);
        _delay_ms(50);
        play_tone(A6, 50);
        play_tone(C6, 50);
        play_tone(Ds6, 50);
        _delay_ms(50);
        play_tone(A5, 50);
        play_tone(C5, 50);
        play_tone(Ds5, 50);
        _delay_ms(50);
    }

    set_leds(ALL_LEDS, ON);
    if (current_game.mode == MODE_SILENT)
        _delay_ms(100);
    else
        play_tone(70, 100);
    set_leds(ALL_LEDS, OFF);

    _delay_ms(100);

    set_leds(ALL_LEDS, ON);
    if (current_game.mode == MODE_SILENT)
        _delay_ms(100);
    else
        play_tone(70, 100);
    set_leds(ALL_LEDS, OFF);

    _delay_ms(100);

    set_leds(ALL_LEDS, ON);
    if (current_game.mode == MODE_SILENT)
        _delay_ms(100);
    else
        play_tone(70, 100);
    set_leds(ALL_LEDS, OFF);

    _delay_ms(100);
}

void game_victory(void) {
    play_tone(2000, 50);
    play_tone(4000, 50);
    play_tone(6000, 20);
}

void game_start_melody(void) {
    if (current_game.mode != MODE_SILENT) {
        play_tone(C5, 50);
        _delay_ms(50);
        play_tone(Ds5, 50);
        play_tone(E5, 50);
        play_tone(Ds5, 50);
        play_tone(E5, 50);
        _delay_ms(50);
        play_tone(G5, 50);
        _delay_ms(50);
        play_tone(A5, 50);
        _delay_ms(50);
        play_tone(C6, 200);
    }
}

void power_up_melody(void)
{
    play_tone(C5, 50);
    _delay_ms(50);
    play_tone(C5, 50);
    play_tone(Ds5, 50);
    play_tone(F5, 50);
    _delay_ms(50);
    play_tone(C5, 50);
    _delay_ms(50);
    play_tone(Gs5, 50);
}

void game_display_pattern(void) {
    int i;

    for (i = 0; i < current_game.length; i++) {
        game_display_segment(current_game.pattern[i]);
        _delay_ms(DEFAULT_SEG_DELAY);
    }
}

void game_set_mode(uint8_t mode) {
    current_game.mode = mode;
}

uint8_t game_get_input(void) {
    int i;

    for (i = 0; i < current_game.length; i++)
    {
        while (!input_button_pressed() || input_last_button() == BUTTON_UNDEFINED);

        if (game_input_correct(i, input_last_button())
            || current_game.mode == MODE_FREE_PLAY) {
            game_button_segment(button_to_color(input_last_button()));
        }
        else {
            return GAME_FAIL;
        }
        input_clear_button_pressed();
    }
    return GAME_PASS;
}

bool game_input_correct(uint8_t index, uint8_t input) {
    if (current_game.pattern[index] == button_to_color(input))
        return true;
    else
        return false;
}

void game_display_segment(uint8_t color) {
    uint16_t segment_length = DEFAULT_SEG_LENGTH;

    if (current_game.mode == MODE_HARD)
        segment_length = segment_length/4;
    else if (current_game.mode == MODE_FREE_PLAY) {
        segment_length = 25 + (read_pot() << 1);
    }

    switch (color) {
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

void game_button_segment(uint8_t color) {
        switch (color) {
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

void game_generate_pattern(void) {
    game_rand_setup();
    int i;

    for(i = 0; i < MAX_GAME_LENGTH; i++) {
        current_game.pattern[i] = rand() % 4;
    }
}

void game_rand_setup()
{
    static bool initial_setup = true;

    if(initial_setup)
    {
        //uint8_t seed = 0;

        //seed = eeprom_read_byte((uint8_t*) &random_seed) + 1;
        //eeprom_write_byte((uint8_t*) &random_seed, seed);
        /*srand(seed << 8);        */
        srand(read_pot() ^ read_temp());
        initial_setup = false;
    }
}

static uint8_t button_to_color(uint8_t button) {
    switch (button) {
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
