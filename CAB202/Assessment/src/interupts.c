#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "uart.h"

volatile uint8_t pb_state = 0xFF;


void spi_write(uint8_t b){
    SPI0.DATA = b;
}

void displaySegments(void){
    static uint8_t digit = 0;
    if(digit) {
        spi_write(leftSeg);
    } else {
        spi_write((rightSeg)|10000000);
    }
    digit = !digit;
}



ISR(SPI0_INT_vect){
    PORTA.OUTCLR = PIN1_bm;
    PORTA.OUTSET = PIN1_bm;
    SPI0_INTFLAGS|=(1<<7);
}


ISR(TCB0_INT_vect) {
//    Buttons Debounce
    static uint8_t count0 = 0;
    static uint8_t count1 = 1;
    uint8_t pb_sample = PORTA.IN;
    uint8_t pb_changed = pb_sample ^ pb_state;
    count1 = (count1 ^ count0) & pb_changed;
    count0 = ~count0 & pb_changed;
    pb_state ^= (count1 & count0) | (pb_changed & pb_state);


    if(sequenceState == STOPPED) {
        setSegSequence();
        displaySegments();
    } else if(sequenceState == TEST) {
        displaySegments();
    } else {
        spi_write(0b10000000);
    }

    TCB0.INTFLAGS = TCB_CAPT_bm; //  Acknowledge Interrupt
}

ISR(TCB1_INT_vect) {
    if(sequenceState == SEQUENCING || sequenceState == NEXT) {
        if (currentDurationLeft > 0) {
            currentDurationLeft--;
        } else {
            setNextStep();
            if (currentDurationLeft != 0) sequenceState = NEXT;
            else sequenceState = STOP;
        }
    }
    TCB1.INTFLAGS = TCB_CAPT_bm; //  Acknowledge Interrupt
}
