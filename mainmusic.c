
#include <msp430.h>

#include "player.h"
//#include "communicator.h"

/*
 * ============================ SELECT YOUR SONG ============================
 * Uncomment ONE (1) of the lines below to select which song you would like
 * to load onto your MSP 430. The reason you can only select ONE (1) is due
 * to the limited amount of code space available on the chips that come with
 * the LaunchPad kit. If you have a beefier chip and want to load longer songs,
 * by all means go for it!
 */

#include "song1.c"
#include "song2.c"

unsigned int states = 0;

void init() {
    /* Stop the watchdog. */
    WDTCTL = WDTPW | WDTHOLD;

    /* Set the system clock to 1 MHz. */
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    /* Initialize LEDs (output) and button (input). Was part of the previous code; not necessary but useful if you
     wanted to initiate something with the button*/
    LED_DIR |= LED_RED;
    LED_DIR |= LED_GREEN;
    BUTTON_DIR &= ~BUTTON;
    P1REN |= BUTTON;

    /* Initialize speaker (output). */
    SPEAKER1_DIR |= SPEAKER1;
    SPEAKER2_DIR |= SPEAKER2;

    /* Initialize the second timer. */
    TA1CTL |= TASSEL_2 | ID_0 | MC_2;// | TAIE;
    TA1CCTL0 |= CCIE;
    TA1CCTL1 |= CCIE;

    /* Initialize the first timer. */
    TA0CTL |= TASSEL_2 | ID_0 | MC_2;// | TAIE;
    TA0CCTL0 |= CCIE;
    TA0CCTL1 |= CCIE;

    /* Enable interrupts globally. */
    _BIS_SR(GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_sound_isr_lead(void) {
    /* Push the timer forward by one note cycle. */
    TA0CCR0 += current_note_lead;
    /* Output to the speaker if sound is enabled. */
    if (sound_enabledl) {
        SPEAKER1_OUT ^= SPEAKER1;
    }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer_sound_isr_bass(void) {
    // Push the timer forward by one note cycle.
    TA1CCR0 += current_note_bass;

    /*Not sure if this would work in this interrupt, but it can't be in the while loop or else
    it would be forced to wait for the song to finish*/
    //MessageReceiver();

    // Output to the speaker if sound is enabled.
    if (sound_enabledb) {
        SPEAKER2_OUT ^= SPEAKER2;
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_elapsed_isr_lead(void) {
    switch (TA0IV) {
        case 2: // CCR1
            TA0CCR1 += 1000; // 1 ms
            ms_elapsedl++;
            break;
    }
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer_elapsed_isr_bass(void) {
    switch (TA1IV) {
        case 2: // CCR1
            TA1CCR1 += 1000;// 1 ms
            ms_elapsedb++;
            break;
    }
}

void main() {
    /* Initialize the system. */
    init();
    while (1) {
        switch(states){
        case 0:
            if(gamemode == 1){
            states = 0x01;
            }
            else {
            song1_setup();
            song1_play();
            states = 0;
            }
            break;
        case 1:
            song2_setup();
            song2_play();
            if(wheel == 1)
                states = 0x04;
            else if(gameover == 1){
                states = 0x08;
                gamemode = 0;
            }
            else
                states = 0x01;
            break;
        case 4:
            /*The idea behind this was that there would be separate messages determining when the wheel started and stopped moving
            so it loops until the second message is sent*/
            if(wheel == 1){
                rest(1);
                states = 0x04;
            }
            else
                states = 0x01;
            break;
        case 8:
            if(scoreboard == 1)
            states = 0x09;
            else
            states = 0x08;
            break;
        case 9:
            //Same as with the wheel
            if(scoreboard == 1)
                states = 0x09;
            else
                states = 0;
            break;
        }
}
}
