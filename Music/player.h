/*
 * Bob Somers 2011 
 *   http://bobsomers.com
 *
 * Released under the Beerware License
 *   http://en.wikipedia.org/wiki/Beerware
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "music.h"

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
#define SPEAKER1 BIT7
#define SPEAKER2 BIT5
#define SPEAKER1_DIR P1DIR
#define SPEAKER1_OUT P1OUT
#define SPEAKER2_DIR P2DIR
#define SPEAKER2_OUT P2OUT

/*
 * Intialize the necessary peripherals.
 */
void init();

/*
 * CCR0 timer interrupt handler (note signal).
 */
__interrupt void timer_sound_isr_lead();

__interrupt void timer_sound_isr_bass();

/*
 * TAIV timer interrupt handler (elapsed time counting).
 */
__interrupt void timer_elapsed_isr_lead();

__interrupt void timer_elapsed_isr_bass();


#endif // PLAYER_H_
