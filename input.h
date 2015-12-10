#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdbool.h>

#define ON  1
#define OFF 0

// PORT A
#define BUTTON_2 0x08 
#define BUTTON_3 0x80
#define BUTTON_4 0x10
#define LED_2    0x02
#define LED_3    0x40
#define LED_4    0x20
#define POT      0x01
#define POWER_LED 0x01

// PORT B
#define LED_1	 0x01
#define BUTTON_1 0x02

#define ALL_LEDS (LED_1 | LED_2 | LED_3 | LED_4)

#define DEBOUNCE_TIME_MS 40
#define MAX_POT_VALUE    255

#define BUTTON_UNDEFINED 0xFF

void input_init(void);
void input_wait_for_button(void);
void set_leds(uint8_t leds, uint8_t state);

void configure_pot(void);
uint8_t read_pot(void);
uint8_t read_temp(void);

void input_clear_button_pressed(void);
bool input_button_pressed(void);
uint8_t input_last_button(void);

#endif
