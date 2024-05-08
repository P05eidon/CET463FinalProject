/*
 * Bob Somers 2011 
 *   http://bobsomers.com
 *
 * Released under the Beerware License
 *   http://en.wikipedia.org/wiki/Beerware
 */

#ifndef MAINNOISES_H_
#define MAINNOISES_H_

#include "sound.h"

/* Define led port connections. */
#define LED_RED BIT0
#define LED_GREEN BIT6
#define LED_DIR P1DIR
#define LED_OUT P1OUT

/* Define button connections. */
#define BUTTON BIT3
#define BUTTON_DIR P1DIR
#define BUTTON_IN P1IN

/* Define speaker connections. */
#define SPEAKER BIT7
#define SPEAKER_DIR P1DIR
#define SPEAKER_OUT P1OUT

/*
 * Intialize the necessary peripherals.
 */
void init();

/*
 * CCR0 timer interrupt handler (note signal).
 */
__interrupt void timer_sound_isr();

/*
 * TAIV timer interrupt handler (elapsed time counting).
 */
__interrupt void timer_elapsed_isr();


#endif // MAINNOISES_H_
