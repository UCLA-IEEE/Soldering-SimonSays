#ifndef TONE_H
#define TONE_H

#include <stdint.h>

#define PERIOD_RESOLUTION_US 10

#define C4  261 // C note frequency
#define Cs4 277 // C sharp note frequency
#define D4  294 // D note frequency
#define Ds4 311 // D sharp note frequency
#define E4  329 // E note frequency
#define F4  349 // F note frequency
#define Fs4 370 // F sharp note frequency
#define G4  392 // G note frequency
#define Gs4 415 // G sharp note frequency
#define A4  440 // A note frequency
#define As4 466 // A sharp note frequency
#define B4  494 // B note frequency
//FIFTH OCTAVE NOTE FREQUENCIES
#define C5  523
#define Cs5 554
#define D5  587
#define Ds5 622
#define E5  659
#define F5  698
#define Fs5 740
#define G5  784
#define Gs5 831
#define A5  880
#define As5 932
#define B5  988
//SIXTH OCTAVE NOTE FREQUENCIES
#define C6  1046
#define Cs6 1109
#define D6  1175
#define Ds6 1245
#define E6  1319
#define F6  1397
#define Fs6 1480
#define G6  1568
#define Gs6 1661
#define A6  1760
#define As6 1865
#define B6  1976
//SEVENTH OCTAVE NOTE FREQUENCIES
#define C7  2093
#define Cs7 2217
#define D7  2349
#define Ds7 2489
#define E7  2637
#define F7  2794
#define Fs7 2960
#define G7  3136
#define Gs7 3322
#define A7  3520
#define As7 3729
#define B7  3951
//EIGHTH OCTAVE NOTE FREQUENCIES
#define C8  4186
#define Cs8 4434
#define D8  4699
#define Ds8 4978
#define E8  5274
#define F8  5588
#define Fs8 5920
#define G8  6272
#define Gs8 6645
#define A8  7040
#define As8 7459
#define B8  7902

void init_tone(void);
void play_tone(uint16_t f_Hz, uint16_t dur_ms);
void start_tone(uint16_t f_Hz);
void stop_tone(void);

#endif
