#ifndef TONE_H
#define TONE_H

#include <stdint.h>

#define PERIOD_RESOLUTION_US 10

#define C4  261 //  C   note frequency
#define Cs4 277 //  C   sharp note frequency
#define D4  294 //  D   note frequency
#define Ds4 311 //  D   sharp note frequency
#define E4  329 //  E   note frequency
#define F4  349 //  F   note frequency
#define Fs4 370 //  F   sharp note frequency
#define G4  392 //  G   note frequency
#define Gs4 415 //  G   sharp note frequency
#define A4  440 //  A   note frequency
#define As4 466 //  A   sharp note frequency
#define B4  494 //  B   note frequency
//FIFTH OCTAVE NOTE FREQUENCIES
#define C5  523 //  C   note frequency
#define Cs5 554 //  C   sharp note frequency
#define D5  587 //  D   note frequency
#define Ds5 622 //  D   sharp note frequency
#define E5  659 //  E   note frequency
#define F5  698 //  F   note frequency
#define Fs5 740 //  F   sharp note frequency
#define G5  784 //  G   note frequency
#define Gs5 831 //  G   sharp note frequency
#define A5  880 //  A   note frequency
#define As5 932 //  A   sharp note frequency
#define B5  988 //  B   note frequency
//SIXTH OCTAVE NOTE FREQUENCIES
#define C6  1046    //  note frequency
#define Cs6 1109    //  sharp note frequency
#define D6  1175    //  note frequency
#define Ds6 1245    //  sharp note frequency
#define E6  1319    //  note frequency
#define F6  1397    //  note frequency
#define Fs6 1480    //  sharp note frequency
#define G6  1568    //  note frequency
#define Gs6 1661    //  sharp note frequency
#define A6  1760    //  note frequency
#define As6 1865    //  sharp note frequency
#define B6  1976    //  note frequency
//SEVENTH OCTAVE NOTE FREQUENCIES
#define C7  2093    //  note frequency
#define Cs7 2217    //  sharp note frequency
#define D7  2349    //  note frequency
#define Ds7 2489    //  sharp note frequency
#define E7  2637    //  note frequency
#define F7  2794    //  note frequency
#define Fs7 2960    //  sharp note frequency
#define G7  3136    //  note frequency
#define Gs7 3322    //  sharp note frequency
#define A7  3520    //  note frequency
#define As7 3729    //  sharp note frequency
#define B7  3951    //  note frequency
//EIGHTH OCTAVE NOTE FREQUENCIES
#define C8  4186    //  note frequency
#define Cs8 4434    //  sharp note frequency
#define D8  4699    //  note frequency
#define Ds8 4978    //  sharp note frequency
#define E8  5274    //  note frequency
#define F8  5588    //  note frequency
#define Fs8 5920    //  sharp note frequency
#define G8  6272    //  note frequency
#define Gs8 6645    //  sharp note frequency
#define A8  7040    //  note frequency
#define As8 7459    //  sharp note frequency
#define B8  7902    //  note frequency

void init_tone(void);
void play_tone(uint16_t f_Hz, uint16_t dur_ms);
void start_tone(uint16_t f_Hz);
void stop_tone(void);

#endif
