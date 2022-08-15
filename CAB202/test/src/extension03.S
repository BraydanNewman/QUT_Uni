#include <avr/io.h>

.section .init0

entry:

    ldi r16, PIN5_bm
    sts PORTB_OUTSET, r16
    sts PORTB_DIRSET, r16

    sts PORTB_OUTCLR, r16

loop:
    rjmp loop

