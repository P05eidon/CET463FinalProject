/*
 * Sergio Campama 2011 
 *   http://kaipi.me
 *
 * Released under the Beerware License
 *   http://en.wikipedia.org/wiki/Beerware
 *
 * Super Mario Theme
 */
#include "sound.h"
/*
 * ALL SONGS MUST IMPLEMENT song_setup() AND song_play()!
 */

void noises_setup() {
    set_bpm(420);
}

void noise_1() {
    play(D4, 1);
    play(Cs4, 1);
    play(C4, 1);
    play(As3, 1);
    play(Gs3, 1);
    play(Fs3, 1);
    play(Ds3, 1);
    play(C3, 1);
    play(A2, 1);
}

void noise_2() {
    play(D5, 3);
    play(D6, 3);
}

void noise_3() {
    play(E2, 1);
    play(Fs2, 1);
    play(D2, 1);
}

void noise_4() {
    play(D4, 2);
    play(D5, 2);
}

void noise_5() {
    play(D4, 8);
    play(Cs4, 8);
    play(C4, 8);
    play(B3, 16);
}

void noise_6(){

}

void noise_7(){

}
