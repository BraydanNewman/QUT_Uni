// n11272031

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include "qutyserial.h"

/***
 * Ex E8.0
 * 
 * Your task is to write code to implement a two-tone siren 
 * using the QUTy. You must use one of the Waveform Outputs 
 * of TCA0 to drive the buzzer. The buzzer should always
 * be driven with a 50% duty cycle signal.
 * 
 * Your siren must use the following two frequencies:
 *     f1 = 2120 Hz
 *     f2 = 4720 Hz
 * The siren should alternate between f1 and f2, with 
 * f1 active for 300 ms, and f2 active for 630 ms.
 * 
 * Your programme must be interrupt driven. The code you 
 * write in this file (extension08.c) will be compiled 
 * alongside a main.c which we provide. main() will call 
 * the init() function you write below and then drop into 
 * an infinite loop. The init() function you write MUST 
 * return (to demonstrate your code is interrupt driven).
 * 
 * In addition to init(), you may write any code you wish
 * in this file, including ISRs.
 * 
 * We have provided a copy of the main.c code we will use
 * to test your code, so that you can build and test your
 * code locally. You should not write any code in main.c
 * as it will be replaced when you upload your programme.
 */

volatile uint64_t count_30ms;


void f1(void) {
    TCA0.SINGLE.PERBUF = 767;
    TCA0.SINGLE.CMP0 = 384;
}

void f2(void) {
    TCA0.SINGLE.PERBUF = 1592;
    TCA0.SINGLE.CMP0 = 797;
}


void init(void) {
    cli();

    PORTB.DIRSET = PIN5_bm;
    PORTB.OUTSET = PIN5_bm;


//    PWM FOR BUZZER SETUP
    PORTB.DIRSET = PIN0_bm;
    PORTB.OUTSET = PIN0_bm;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

//    INTERRUPT SETUP
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;
    TCB0.CCMP = ;
    TCB0.INTCTRL |= 0x1;
    TCB0.CTRLA = TCB_CLKSEL_DIV2_gc | TCB_ENABLE_bm;

//    f2();
    sei();





    return;
}



ISR(TCB0_INT_vect) {
    printf(count_30ms);
    count_30ms ++;

    if (count_30ms > 10) {
        count_30ms = 0;
    }

    TCB0.INTFLAGS |= 0x1;
}
//
//
//IRS(TCA0_INT_vect) {
//
//}

// Write your code for Ex E8.0 above this line.

