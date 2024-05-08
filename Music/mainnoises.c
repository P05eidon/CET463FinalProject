
#include "mainnoises.h"
#include <msp430.h>
#include "noises.c"
//#include "communicator.h"

unsigned char state = 0;
unsigned int bumper = 0;
unsigned int flipper = 0;
unsigned int hole = 0;
unsigned int pit = 0;
unsigned int launcher = 0;

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
    SPEAKER_DIR |= SPEAKER;
    
    /* Initialize the first timer. */
    TA0CTL |= TASSEL_2 | ID_0 | MC_2;// | TAIE;
    TA0CCTL0 |= CCIE;
    TA0CCTL1 |= CCIE;

    /* Enable interrupts globally. */
    _BIS_SR(GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_sound_isr(void) {
    /* Push the timer forward by one note cycle. */
    TA0CCR0 += current_note;
    /* Output to the speaker if sound is enabled. */
    if (sound_enabled) {
        SPEAKER_OUT ^= SPEAKER;
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_elapsed_isr(void) {
    switch (TA0IV) {
        case 2: // CCR1
            TA0CCR1 += 1000; // 1 ms
            ms_elapsed++;
            break;
    }
}

void main() {
    /* Initialize the system. */
    init();

    while (1) {
       //MessageReceiver();
        switch(state){
        case 0:
            noises_setup();
            if(gamemode == 1){
                if(bumper == 1)
                    state = 0x02;
                else if(flipper == 1)
                    state = 0x03;
                else if(wheel == 1)
                    state = 0x04;
                else if(hole == 1)
                    state = 0x05;
                else if(pit == 1)
                    state = 0x06;
                else if(launcher == 1)
                    state = 0x07;
                else
                    state = 0;
            }
            else if(gameover == 1)
                state = 0x08;
            else
                state = 0;
            break;
        case 2:
            noise_3();
            bumper = 0;
            state = 0;
            break;
        case 3:
            noise_2();
            flipper = 0;
            state = 0;
            break;
        case 4:
            //Same concept as with the music wheel loop
            if(wheel == 1){
                noise_4();
                state = 0x04;
            }
            state = 0;
            break;
        case 5:
            noise_2();
            hole = 0;
            state = 0;
            break;
        case 6:
            noise_1();
            pit = 0;
            state = 0;
            break;
        case 7:
            noise_2();
            launcher = 0;
            state = 0;
            break;
        case 8:
            noise_1();
            noise_5();
            state = 0x09;
            break;
        case 9:
            //Same concept as with the music wheel loop
            if(scoreboard == 1){
                noise_4();
                state = 0x09;
            }
                state = 0;
            break;
        }
    }
}
