#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "sequence.h"
#include "uart.h"
#include "utils.h"
#include "initialize.h"
#include "interupts.h"


volatile uint8_t leftSeg;
volatile uint8_t rightSeg;

volatile uint8_t sequenceSelected = 0;
uint8_t partSequenceSelected = 0;

uint8_t payloadCharCount = 0;

unsigned char payload[32];

uint32_t checksumTest;
uint8_t checksum;


uint32_t offset = 0;

volatile uint8_t nextDuration;
volatile uint8_t currentDurationLeft;
volatile uint8_t nextBrightness;
volatile uint8_t nextOctave;
volatile uint8_t nextNote;


uint32_t freq;

uint32_t noteFreq[12] = {
        90909,
        85807,
        80991,
        76445,
        72155,
        68105,
        64282,
        60675,
        57269,
        54055,
        51021,
        48157,

};


uint8_t numToMask[16] = {
        0b00001000,
        0b01101011,
        0b01000100,
        0b01000001,
        0b00100011,
        0b00010001,
        0b00110000,
        0b01001011,
        0b00000000,
        0b00000011,
        0b00000010,
        0b00110000,
        0b00011100,
        0b01100000,
        0b00010100,
        0b00010110,
};

void setSegSequence(void) {
    leftSeg = numToMask[(sequenceSelected & 0xF)];
    rightSeg = numToMask[(sequenceSelected >> 4)];
}

void getNextStep(void);

void setNextStep(void);


typedef enum {
    NONE,
    SLASH,
    D_SLASH,
    CMD_SYNC,
    CMD_SEQIDX,
    CMD_TEST_SEQ,
    CMD_TEST_SEQNS,
} cmdModes;


typedef enum {
    NORMAL,
    TEST_SEQ,
    TEST_SEQNS
} testModes;

typedef enum {
    START,
    SEQUENCING,
    NEXT,
    STOP,
    STOPPED,
    PAUSED,
    ADVANCE,
    TEST,
} sequenceStatus;

volatile sequenceStatus sequenceState = STOPPED;
testModes testMode = NORMAL;


int main(void) {
//    SYSTEM CLOCK SETUP (10MHz)
    CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x1;


//    Init
    spi_init();
    uart_init();
    button_init();
    tcb0_init();
    adc_init();
    tca0_init();
    tcb1_init();

    uint8_t pb = 0;
    uint8_t pb_prev;
    uint8_t pb_changed;
    uint8_t pb_falling;


    cmdModes cmdMode = NONE;

    uint8_t input;


    while (1) {

//        UART
        if (USART0.STATUS & USART_RXCIF_bm) {
            input = USART0.RXDATAL;
        }

        if (input != 0) {
            switch (cmdMode) {
                case NONE:
                    if (input == '/') cmdMode = SLASH;
                    break;
                case SLASH:
                    if (input == '/') cmdMode = D_SLASH;
                    else cmdMode = NONE;
                    break;
                case D_SLASH:
                    switch (input) {
                        case 's':
//                        CMD_SEQ: Start sequence AND resume sequence
                            uart_puts("#ACK\n");
                            if (sequenceState == STOPPED) sequenceState = START;
                            else if (sequenceState == PAUSED) sequenceState = SEQUENCING;
                            cmdMode = NONE;
                            break;

                        case 't':
//                        CMD_TEST:
                            uart_puts("#ACK\n");
                            leftSeg = 0x77;
                            rightSeg = 0x77;
                            sequenceState = TEST;
                            cmdMode = NONE;
                            break;

                        case 'e':
//                        CMD_EXIT: Exit the sequence
                            uart_puts("#ACK\n");
                            if (sequenceState != STOPPED) sequenceState = STOP;
                            cmdMode = NONE;
                            break;

                        case 'p':
//                        CMD_PAUSE: Pause the sequence
                            uart_puts("#ACK\n");
                            if (sequenceState == SEQUENCING) sequenceState = PAUSED;
                            else if (sequenceState == NEXT) {
                                getNextStep();
                                sequenceState = PAUSED;
                            }
                            cmdMode = NONE;
                            break;

                        case 'n':
//                        CMD_STEP: Advance the step forward
                            uart_puts("#ACK\n");
                            if (sequenceState == PAUSED) sequenceState = ADVANCE;
                            cmdMode = NONE;
                            break;

                        case 'y':
//                        CMD_SYNC:
                            uart_puts("#ACK\n");
                            cmdMode = CMD_SYNC;
//                        TODO: NOT IMPLEMENTED
                            break;

                        case 'i':
//                            CMD_SEQIDEX: GETS Sequence index from uart
                            cmdMode = CMD_SEQIDX;
                            break;

                        case 'd':
                            cmdMode = CMD_TEST_SEQ;
                            payloadCharCount = 0;
                            checksum = 0;
                            checksumTest = 'd';
                            break;

                        case 'u':
                            cmdMode = CMD_TEST_SEQNS;
                            payloadCharCount = 0;
                            checksum = 0;
                            checksumTest = 'd';
                            break;
                        default:
                            uart_puts("#NACK\n");
                            cmdMode = NONE;
                            break;

                    }
                    break;
                case CMD_TEST_SEQ:
                    if ((input >= 48 && input <= 57) || (input >= 65 && input <= 90) || (input >= 97 && input <= 122)) {
                        if(payloadCharCount == 32) {
                            checksum = indexInTable(input);
                        } else {
                            checksumTest += input;
                            payload[payloadCharCount] = input;
                        }
                    } else {
                        uart_puts("#NACK\n");
                        cmdMode = NONE;
                    }
                    if(payloadCharCount == 32){
                        if(checksum == (checksumTest & 0x3F)) {
                            sequenceSelected = 0;
                            testMode = TEST_SEQ;
                            sequenceState = START;
                        } else {
                            uart_puts("#NACK\n");
                        }
                        cmdMode = NONE;
                    }
                    payloadCharCount++;
                    break;

                case CMD_TEST_SEQNS:
                    if ((input >= 48 && input <= 57) || (input >= 65 && input <= 90) || (input >= 97 && input <= 122)) {
                        if(payloadCharCount == 32) {
                            checksum = indexInTable(input);
                        } else {
                            checksumTest += input;
                            payload[payloadCharCount] = input;
                        }
                    } else {
                        uart_puts("#NACK\n");
                        cmdMode = NONE;
                    }
                    if(payloadCharCount == 32){
                        if(checksum == (checksumTest & 0x3F)) {
                            sequenceSelected = 0;
                            testMode = TEST_SEQNS;
                            sequenceState = START;
                        } else {
                            uart_puts("#NACK\n");
                        }
                        cmdMode = NONE;
                    }
                    payloadCharCount++;
                    break;

                case CMD_SEQIDX:
                    if (input >= '0' && input <= '9') input = input - 48;
                    else if (input >= 'a' && input <= 'f') input = input - 87;
                    else {
                        uart_puts("#NACK\n");
                        cmdMode = NONE;
                        break;
                    }
                    if (payloadCharCount == 0) {
                        partSequenceSelected = input * 16;
                        payloadCharCount++;
                    } else {
                        uart_puts("#ACK\n");
                        sequenceSelected = partSequenceSelected + input;
                        partSequenceSelected = 0;
                        payloadCharCount = 0;
                        cmdMode = NONE;
                    }
                    break;
                default:
                    cmdMode = NONE;
                    break;
            }
        }
        input = 0;

//        BUTTONS
        pb_prev = pb;
        pb = pb_state;

        pb_changed = pb ^ pb_prev;
        pb_falling = pb_changed & ~pb;

        if (!(PORTA.IN & PIN4_bm)) {
//            BUTTON: S1 (ONLY FOR GETTING VALUE FROM POTENTIOMETER)
            sequenceSelected = ADC0.RESULT;

        } else if (pb_falling & PIN5_bm) {
//            BUTTON: S2
//            Selected Sequence -1 AND Exit Playing Sequence
            if (sequenceState == STOPPED && sequenceSelected > 0) sequenceSelected--;
            else if (sequenceState == PAUSED) sequenceState = STOP;
//
        } else if (pb_falling & PIN6_bm) {
//            BUTTON: S3
//            Selected Sequence +1 AND Advance To Next Step
            if (sequenceState == STOPPED && sequenceSelected < 0xFF) sequenceSelected++;
            else if (sequenceState == PAUSED) sequenceState = ADVANCE;

        } else if (pb_falling & PIN7_bm) {
//            BUTTON: S4
//            Start Sequence AND Pause Playing AND Resume Playing
            if (sequenceState == STOPPED) sequenceState = START;
            else if (sequenceState == SEQUENCING) sequenceState = PAUSED;
            else if (sequenceState == NEXT) {
                getNextStep();
                sequenceState = PAUSED;
            } else if (sequenceState == PAUSED) sequenceState = SEQUENCING;
        }

//        SEQUENCING
        switch (sequenceState) {
            case START:
                state = 0x11272031;
//                SET OFFSET
                offset = 32 * sequenceSelected;

//                SET DESCRAMBLE STATE
                for (uint32_t i = 0; i < sequenceSelected * 24; ++i) next();

//                GET AND SET CURRENT STEP
                getNextStep();
                setNextStep();

//                TURN BUZZER AND BRIGHTNESS ON
                PORTB.DIRSET = PIN1_bm;
                PORTB.DIRSET = PIN0_bm;

                sequenceState = NEXT;
                break;

            case NEXT:
//                SET THE NEXT STEPS IN BUFFER
                getNextStep();
                sequenceState = SEQUENCING;
                break;

            case STOP:
//                TURN BUZZER AND BRIGHTNESS OFF
                PORTB.DIRCLR = PIN1_bm;
                PORTB.DIRCLR = PIN0_bm;

                if (testMode != NORMAL) sequenceState = TEST;
                else sequenceState = STOPPED;

                break;

            case ADVANCE:
//                ADVANCE ONE STEP FORWARD
                setNextStep();
                getNextStep();

                sequenceState = PAUSED;
                break;

            default:
                break;
        }
    }

}

void setNextStep(void) {
    currentDurationLeft = nextDuration;
    freq = noteFreq[nextNote] >> nextOctave;

    TCA0.SINGLE.PER = freq;
    TCA0.SINGLE.CMP0BUF = (freq >> 1);
    if (nextBrightness == 0) TCA0.SINGLE.CMP1BUF = 0;
    else
        TCA0.SINGLE.CMP1BUF = (freq * (nextBrightness + 1)) >> 8;
}


void getNextStep(void) {
    char a;
    char b;
    char c;
    char d;
    if (testMode == NORMAL){
        a = pgm_read_byte_near(SEQUENCE + offset);
        b = pgm_read_byte_near(SEQUENCE + offset + 1);
        c = pgm_read_byte_near(SEQUENCE + offset + 2);
        d = pgm_read_byte_near(SEQUENCE + offset + 3);
    } else {
        a = payload[offset];
        b = payload[offset + 1];
        c = payload[offset + 2];
        d = payload[offset + 3];
    }

    offset = offset + 4;
    uint32_t data = decode(a, b, c, d);

    nextDuration = data >> 16;
    nextBrightness = data >> 8;
    uint8_t feqData = data;

    if (testMode != TEST_SEQNS){
        descramble(&nextDuration);
        descramble(&nextBrightness);
        descramble(&feqData);
    }

    nextOctave = feqData >> 4;
    nextNote = feqData & 0b00001111;
}
