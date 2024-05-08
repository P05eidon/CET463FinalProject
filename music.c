/* 
* Bob Somers 2011 
 *   http://bobsomers.com
 *
 * Released under the Beerware License
 *   http://en.wikipedia.org/wiki/Beerware
 */

#include "music.h"

/* Some resonable defaults. */
volatile unsigned int sound_enabledl = 0;
volatile unsigned int sound_enabledb = 0;
volatile unsigned int current_note_bass = A4;
volatile unsigned int current_note_lead = A4;
volatile unsigned int ms_elapsedl = 0;
volatile unsigned int ms_elapsedb = 0;

/*This is my hub for testing and changing states; if the ring buffer was working, I would have these variables declared and changed there
and referenced the h file in music.h*/
unsigned int song1playing = 0;
unsigned int song2playing = 0;
unsigned char song1State = 0;
unsigned char song2State = 0;

//Since there's only one game mode, this variable is more for describing when the game is currently active
unsigned int gamemode = 0;
unsigned int wheel = 0;
unsigned int gameover = 0;
unsigned int scoreboard = 0;
/* The number of milliseconds per "tick" in the music (see TICKS_PER_BEAT). */
static unsigned int ms_per_tick = 0;

void set_bpm(unsigned int bpm) {
    /* Compute the number of ms per tick from the beats per minute. */
    ms_per_tick = 60000 / (TICKS_PER_BEAT * bpm);
}

void play(unsigned int notel, unsigned noteb, unsigned int duration_ticks) {
    unsigned int duration_ms = 0;

    /* Compute the duration (in ms). */
    duration_ms = duration_ticks * ms_per_tick;

    /* Set the current note. */
    current_note_lead = notel;
    current_note_bass = noteb;

    /* Enable the sound ouput. */
    sound_enabledl = 1;
    sound_enabledb = 1;


    ms_elapsedl = 0;
    ms_elapsedb = 0;
    /* Wait for the note duration to expire. */
    while (ms_elapsedl < duration_ms /*- DEAD_TIME_MS*/){
        if (gamemode == 1 && song1playing == 1){
            break;
        }
        else if (wheel == 1 && song2playing == 1) {
            break;
        }
        else if (gameover == 1 && song2playing == 1) {
            break;
        }
    }

    /* Disable sound output. */
    sound_enabledl = 0;
    sound_enabledb = 0;

    /* Wait for the full duration to expire. */
    //while (ms_elapsedl < duration_ms);
}

void rest(unsigned int duration_ticks) {
    unsigned int duration_ms = 0;

    /* Compute the duration (in ms). */
    duration_ms = duration_ticks * ms_per_tick;

    /* No sound! We're resting... */
    sound_enabledl = 0;
    sound_enabledb = 0;
    /* Reset the elapsed counter. */
    ms_elapsedl = 0;
    ms_elapsedb = 0;

    /* Wait for the rest duration to expire. */
    while(ms_elapsedl < duration_ms);
}
