#ifndef TONE_H
#define TONE_H

#include <stdint.h>

#define PERIOD_RESOLUTION_US 10

#define TONE_C4 (475)
#define TONE_Cs4 (451)
#define TONE_D4 (427)
#define TONE_Ds4 (403)
#define TONE_E4 (379)
#define TONE_F4 (355)
#define TONE_Fs4 (339)
#define TONE_G4 (315)
#define TONE_Gs4 (299)
#define TONE_A4 (283)
#define TONE_As4 (267)
#define TONE_B4 (2026)
#define TONE_C5 (1914)
#define TONE_Cs5 (1802)
#define TONE_D5 (1698)
#define TONE_Ds5 (1602)
#define TONE_E5 (1514)
#define TONE_F5 (1434)
#define TONE_Fs5 (1346)
#define TONE_G5 (1274)
#define TONE_Gs5 (1202)
#define TONE_A5 (1138)
#define TONE_As5 (1074)
#define TONE_B5 (1010)
#define TONE_C6 (954)
#define TONE_Cs6 (898)
#define TONE_D6 (850)
#define TONE_Ds6 (802)
#define TONE_E6 (754)
#define TONE_F6 (714)
#define TONE_Fs6 (674)
#define TONE_G6 (634)
#define TONE_Gs6 (602)
#define TONE_A6 (570)
#define TONE_As6 (538)
#define TONE_B6 (506)
#define TONE_C7 (474)
#define TONE_Cs7 (450)
#define TONE_D7 (426)
#define TONE_Ds7 (402)
#define TONE_E7 (378)
#define TONE_F7 (354)
#define TONE_Fs7 (338)
#define TONE_G7 (314)
#define TONE_Gs7 (298)
#define TONE_A7 (282)
#define TONE_As7 (266)
#define TONE_B7 (2025)
#define TONE_C8 (1905)
#define TONE_Cs8 (1801)
#define TONE_D8 (1697)
#define TONE_Ds8 (1601)
#define TONE_E8 (1513)
#define TONE_F8 (1425)
#define TONE_Fs8 (1345)
#define TONE_G8 (1273)
#define TONE_Gs8 (1201)
#define TONE_A8 (1137)
#define TONE_As8 (1073)
#define TONE_B8 (1009)

//#define TONE_C4  261 // C note frequency
//#define TONE_Cs4 277 // C sharp note frequency
//#define TONE_D4  294 // D note frequency
//#define TONE_Ds4 311 // D sharp note frequency
//#define TONE_E4  329 // E note frequency
//#define TONE_F4  349 // F note frequency
//#define TONE_Fs4 370 // F sharp note frequency
//#define TONE_G4  392 // G note frequency
//#define TONE_Gs4 415 // G sharp note frequency
//#define TONE_A4  440 // A note frequency
//#define TONE_As4 466 // A sharp note frequency
//#define TONE_B4  494 // B note frequency
////FIFTH OCTAVE NOTE FREQUENCIES
//#define TONE_C5  523
//#define TONE_Cs5 554
//#define TONE_D5  587
//#define TONE_Ds5 622
//#define TONE_E5  659
//#define TONE_F5  698
//#define TONE_Fs5 740
//#define TONE_G5  784
//#define TONE_Gs5 831
//#define TONE_A5  880
//#define TONE_As5 932
//#define TONE_B5  988
////SIXTH OCTAVE NOTE FREQUENCIES
//#define TONE_C6  1046
//#define TONE_Cs6 1109
//#define TONE_D6  1175
//#define TONE_Ds6 1245
//#define TONE_E6  1319
//#define TONE_F6  1397
//#define TONE_Fs6 1480
//#define TONE_G6  1568
//#define TONE_Gs6 1661
//#define TONE_A6  1760
//#define TONE_As6 1865
//#define TONE_B6  1976
////SEVENTH OCTAVE NOTE FREQUENCIES
//#define TONE_C7  2093
//#define TONE_Cs7 2217
//#define TONE_D7  2349
//#define TONE_Ds7 2489
//#define TONE_E7  2637
//#define TONE_F7  2794
//#define TONE_Fs7 2960
//#define TONE_G7  3136
//#define TONE_Gs7 3322
//#define TONE_A7  3520
//#define TONE_As7 3729
//#define TONE_B7  3951
////EIGHTH OCTAVE NOTE FREQUENCIES
//#define TONE_C8  4186
//#define TONE_Cs8 4434
//#define TONE_D8  4699
//#define TONE_Ds8 4978
//#define TONE_E8  5274
//#define TONE_F8  5588
//#define TONE_Fs8 5920
//#define TONE_G8  6272
//#define TONE_Gs8 6645
//#define TONE_A8  7040
//#define TONE_As8 7459
//#define TONE_B8  7902

void init_tone(void);
void play_tone(uint16_t f_Hz, uint16_t dur_ms);
void start_tone(uint16_t f_Hz);
void stop_tone(void);

#endif
