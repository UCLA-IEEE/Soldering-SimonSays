
tone_data = [("TONE_C4", 261),
("TONE_Cs4", 277),
("TONE_D4", 294),
("TONE_Ds4", 311),
("TONE_E4", 329),
("TONE_F4", 349),
("TONE_Fs4", 370),
("TONE_G4", 392),
("TONE_Gs4", 415),
("TONE_A4", 440),
("TONE_As4", 466),
("TONE_B4", 494),
##FIFTH OCTAVE NOTE FREQUENCIES
("TONE_C5", 523),
("TONE_Cs5", 554),
("TONE_D5", 587),
("TONE_Ds5", 622),
("TONE_E5", 659),
("TONE_F5", 698),
("TONE_Fs5", 740),
("TONE_G5", 784),
("TONE_Gs5", 831),
("TONE_A5", 880),
("TONE_As5", 932),
("TONE_B5", 988),
##SIXTH OCTAVE NOTE FREQUENCIES
("TONE_C6", 1046),
("TONE_Cs6", 1109),
("TONE_D6", 1175),
("TONE_Ds6", 1245),
("TONE_E6", 1319),
("TONE_F6", 1397),
("TONE_Fs6", 1480),
("TONE_G6", 1568),
("TONE_Gs6", 1661),
("TONE_A6", 1760),
("TONE_As6", 1865),
("TONE_B6", 1976),
##SEVENTH OCTAVE NOTE FREQUENCIES
("TONE_C7", 2093),
("TONE_Cs7", 2217),
("TONE_D7", 2349),
("TONE_Ds7", 2489),
("TONE_E7", 2637),
("TONE_F7", 2794),
("TONE_Fs7", 2960),
("TONE_G7", 3136),
("TONE_Gs7", 3322),
("TONE_A7", 3520),
("TONE_As7", 3729),
("TONE_B7", 3951),
##EIGHTH OCTAVE NOTE FREQUENCIES
("TONE_C8", 4186),
("TONE_Cs8", 4434),
("TONE_D8", 4699),
("TONE_Ds8", 4978),
("TONE_E8", 5274),
("TONE_F8", 5588),
("TONE_Fs8", 5920),
("TONE_G8", 6272),
("TONE_Gs8", 6645),
("TONE_A8", 7040),
("TONE_As8", 7459),
("TONE_B8", 7902)]


dividers = [1, 8, 64, 256, 1024]
divider_masks = [1,2,3,4,5]

m_clk_freq = 1000000

t_clk_freqs = map(lambda x : m_clk_freq/float(x), dividers)

t_clk_freq_ranges = map(lambda x : (x/255, x), t_clk_freqs)

ofile = open('out.h', 'w')

for tone_name,freq in tone_data:
    # Calculate the capture compare register values for the tone frequency at
    # each timer frequency (different dividers)
    timer_ccvals = map(lambda clk_freq : int(clk_freq/freq), t_clk_freqs)

    # If the ccval is greater than 255, reduce to 0 to make the error large
    timer_ccvals = map(lambda x : (1 if (x > 255 or x == 0) else x), timer_ccvals)

    # Work backwards from the ccvals to find the tone frequency that would be
    # produced for that ccval
    timer_closest_freqs = map(lambda (ccval,clk_freq) : clk_freq/ccval, zip(timer_ccvals, t_clk_freqs))

    # Find the divider that would produce the smallest error
    timer_freq_errors = map(lambda closest_freq : int(abs(closest_freq - freq)), timer_closest_freqs)

    freq_index = sorted(enumerate(timer_freq_errors), lambda a,b : a[1]-b[1])[0][0]

    print "%s: ifreq %d --> div %d, ccval %d, cfreq %d (error %d)" % (tone_name, freq, dividers[freq_index], timer_ccvals[freq_index], timer_closest_freqs[freq_index], timer_freq_errors[freq_index])

    ofile.write("#define %s (%d)\n" % (tone_name, (timer_ccvals[freq_index] << 3) | (divider_masks[freq_index])))
