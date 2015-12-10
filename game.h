#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/eeprom.h>

#define MAX_GAME_LENGTH 50

#define RED    0
#define GREEN  1
#define YELLOW 2
#define BLUE   3

#define MODE_NORMAL 0
#define MODE_SILENT 1
#define MODE_HARD 2
#define MODE_FREE_PLAY 3
#define MODE_NONE

#define FREQ_1 C6
#define FREQ_2 E6
#define FREQ_3 G6
#define FREQ_4 A6

typedef struct {
	uint16_t length;
	uint16_t speed;
	uint8_t mode;
	uint8_t  pattern[MAX_GAME_LENGTH];
} game_t;

void game_start(uint8_t starting_length);
void game_free_play(void);
void game_over(void);
void game_victory(void);
void game_start_melody(void);
void power_up_melody(void);
void game_display_pattern(void);
void game_display_segment(uint8_t color);
void game_button_segment(uint8_t color);
uint8_t game_get_input(void);
bool game_input_correct(uint8_t index, uint8_t input);

void game_generate_pattern(void);
void game_set_speed(void);
void game_set_mode(uint8_t mode);
void game_rand_setup(void);

#endif //GAME_H
