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

void song1_setup() {
    set_bpm(158);
}

void song1_measure_1() {
    play(A4, D3, 4);
    play(A4, D3, 2);
    play(B4, D3, 2);
    play(Cs5, D3, 6);
    play(B4, D3, 2);
    play(Cs5, Cs4, 4);
    play(Cs5, Cs4, 2);
    play(D5, Cs4, 2);
    play(A4, Cs4, 2);
    play(F5, Cs4, 2);
    play(Fs5, Cs4, 4);
    play(Fs5, D4, 4);
    play(A4, D4, 4);
    play(B4, A3, 2);
    play(Cs5, A3, 2);
    play(D5, A3, 4);
    play(E5, B3, 4);
    play(A4, B3, 2);
    play(B4, B3, 2);
    play(A4, B3, 4);
    play(Cs5, B3, 4);
}

void song1_measure_2() {
    play(A4, D3, 4);
    play(Cs5, D3, 2);
    play(A4, D3, 2);
    play(D5, D3, 6);
    play(B4, D3, 2);
    play(Cs5, A3, 6);
    play(D5, A3, 4);
    play(F5, A3, 2);
    play(Fs5, A3, 4);
    play(Fs5, D3, 4);
    play(E5, D3, 4);
    play(Cs5, Fs3, 2);
    play(D5, Fs3, 2);
    play(E5, Fs3, 4);
    play(A4, B3, 4);
    play(B4, B3, 2);
    play(A4, B3, 2);
    play(B4, Cs4, 4);
    play(Cs5, Cs4, 4);
}

void song1_play() {
    song1State = 0;
    switch (song1State){
    case 0:
        song1playing = 1;
        song1State = 1;
    case 1:
        song1_measure_1();
        song1State = 2;
    case 2:
        song1_measure_2();
        song1State = 9;
    case 9:
        song1playing = 0;
    }
}
