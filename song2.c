/*
 * Sergio Campama 2011 
 *   http://kaipi.me
 *
 * Released under the Beerware License
 *   http://en.wikipedia.org/wiki/Beerware
 *
 * Super Mario Theme
 */
#include "music.h"
/*
 * ALL SONGS MUST IMPLEMENT song_setup() AND song_play()!
 */

void song2_setup() {
    set_bpm(160);
}

void song2_measure_1() {
    play(B3, B2, 4);
    play(D4, B2, 4);
    play(Fs4, G3, 4);
    play(B4, G3, 4);
    play(A3, D3, 4);
    play(Fs4, D3, 4);
    play(E4, E3, 4);
    play(G4, E3, 4);
    play(B3, B2, 4);
    play(D4, B2, 4);
    play(E4, G3, 4);
    play(Fs4, G3, 4);
    play(D4, D3, 4);
    play(Fs4, D3, 4);
    play(E4, B2, 4);
    play(B3, B2, 4);
}

void song2_measure_2() {
    play(B4, B2, 4);
    play(D5, B2, 4);
    play(E5, G3, 8);
    play(D5, D3, 4);
    play(Fs5, D3, 4);
    play(E5, E3, 4);
    play(B4, E3, 4);
    play(B4, B2, 4);
    play(D5, B2, 4);
    play(E5, G3, 8);
    play(D5, D3, 4);
    play(B4, D3, 4);
    play(E5, B2, 4);
    play(B4, B2, 4);
}

void song2_play() {
    song2State = 0;
    switch (song2State){
    case 0:
        song2playing = 1;
        song2State = 1;
    case 1:
        song2_measure_1();
        song2State = 9;
    case 2:
        song2_measure_2();
        song2State = 9;
    case 9:
        song2playing = 0;
    }
}
