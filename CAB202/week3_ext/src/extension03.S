; n11272031

#include <avr/io.h> // Include register definitions

.section .init0     // Places code at the top of programme memory

entry:
    
    // Ex E3.0
    // 
    // U2 is an IC which controls the 2-digit, 7-segment display 
    // on the QUTy. It is a shift register, and is controlled by 
    // its three digital input pins, which are connected to nets 
    // SPI CLK, SPI MOSI and DISP LATCH. 
    // 
    // The shift register's outputs, Q1-Q7 drive the LED segments 
    // of the display in an active-low configuration. Output Q0
    // selects the LHS or RHS digit via U3, U4 and Q1.
    //
    // We will learn how to elegantly drive the 7-segment display
    // in future weeks, but you now have enough tools to be able
    // to gain rudimentary control of the display using a process
    // called "bit-banging". The term "bit-banging" refers to the
    // the sequencing and control of general purpose input/output 
    // (GPIO) pins to implement some protocol or interface to a
    // device. We would usually use a peripheral in preference to
    // bit-banging.
    //
    // The shift register has 8-bits of internal memory. When the
    // input connected to the DISP LATCH net goes from LOW to HIGH, 
    // the state of this internal memory sets the state of outputs 
    // Q0-Q7. When the input connected to the SPI CLK net goes from 
    // LOW to HIGH (rising edge), bit 0 of the internal memory is set 
    // to the current state of the input connected to net SPI MOSI.
    // Simultaneously, the data in internal memory is shifted by
    // one bit position (bit 1 takes its new value from bit 0, etc.).
    //
    // For example, if we wanted to turn all segments of the display
    // off, we could:
    //   1) Drive SPI MOSI high
    //   2) Repeat 8x times: drive SPI CLK low, drive SPI CLK high
    //   3) Drive DISP LATCH low
    //   4) Drive DISP LATCH high
    //
    // If instead you wanted to turn some segments on, rather than
    // leaving SPI MOSI high the entire time, you would need to 
    // drive it to an appropriate state prior to driving SPI CLK
    // high each time. In this way you can independently set each 
    // bit in the internal memory of the shift register (and 
    // consequently, the corresponding output state).
    //
    // EXERCISE: Write assembly code below to configure the display 
    // on the QUTy to display the final digit of your student number. 
    // If the final digit of your student number is EVEN, it should 
    // be displayed on the left-hand-side (LHS) digit of the display. 
    // If the final digit of your student number is ODD, it should 
    // be displayed on the right-hand-side (RHS) digit of the display. 
    //
    // EXAMPLE: If your student number were n12345678, 
    //          "8" should be displayed on the LHS digit.
    //
    // Write your code for Ex E3.0 below this line.

// -------------------------------------
    // PORTA1 - DISP LATCH
    // PORTC0 - SPI CLK
    // PORTC2 - SPI MOSI

// -------------------------------------
    // Set Pin Bit Masks to Registers
    ldi r16, PIN2_bm // DISP LATCH
    ldi r17, PIN0_bm // SPI CLK
    ldi r18, PIN1_bm // SPI MOSI
    ldi r19, 0b10010100 // Set Bits to Map to Display

// -------------------------------------
    // Set all required pins to Safe State
    // SPI MOSI PIN (PC2) - Safe State (HIGH)
    sts PORTC_OUTSET, r16

    // SPI CLK (PC0) - Safe State (HIGH)
    sts PORTC_OUTSET, r17

    // DISP LATCH (PA1) - Safe State (HIGH)
    sts PORTA_OUTSET, r18

// -------------------------------------
    // Set all required pins to Output
    // SPI MOSI PIN (PC2)
    sts PORTC_DIRSET, r16

    // SPI CLK (PC0)
    sts PORTC_DIRSET, r17

    // DISP LATCH (PA1)
    sts PORTA_DIRSET, r18

// -------------------------------------
    // STEP 1 (SPI MOSI)
    // Set Pin High
    sts PORTC_OUTCLR, r16

// -------------------------------------
    // STEP 2
    ldi r21, 8
    output_loop:
        dec r21
        sts PORTC_OUTCLR, r17
        mov r24, r19
        mov r22, r21
        shift_loop:
            cpi r22, 0
            breq shift_finished
            lsr r24
            dec r22
            rjmp shift_loop
        shift_finished:
        andi r24,0x01
        cpi r24, 0x01
        brne condition_0
            sts PORTC_OUTCLR, r16
        rjmp end_condition
        condition_0:
            sts PORTC_OUTSET, r16
        end_condition:
        sts PORTC_OUTSET, r17
        cpi r21, 0
        brne output_loop

// -------------------------------------
    // STEP 3 (DISP LATCH)
    // Pulse Latch High to Enable Outputs
    // Set Pin Low Then High
    sts PORTA_OUTCLR, r18
    sts PORTA_OUTSET, r18
    sts PORTA_OUTCLR, r18 // Set back to low to be safe

// -------------------------------------
    // Write your code for Ex E3.0 above this line.

// END OF EXTENSION03 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //

    break // Stop here for autograder

loop:
    rjmp loop

