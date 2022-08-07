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



    // Write your code for Ex E3.0 above this line.

// END OF EXTENSION03 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //

    break // Stop here for autograder

loop:
    rjmp loop

