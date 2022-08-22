// n11272031

// This header file provides register definitions and constants
// for AVR microcontroller. In this case it will provide the
// relevant definitions for the ATtiny1626 microcontroller which
// is used on the QUTy.
#include <avr/io.h>

#include <util/delay.h> // Delay utility functions for AVR

// This header file provides utility functions for working with
// standard input and ouput, such as the printf() function used
// throughout this programme.
#include <stdio.h>

// This header file provides access to library functions to 
// control the 7-segment display and serial output of the QUTy.
// You can use these functions to help debug your programme.
#include "qutyio.h" 

#include "individual.h"

// This is main(). It it the entry point for a C programme.
int main(void) {

    // These functions initialise the 7-segment display and
    // serial output on the QUTy for use later in the programme.
    serial_init();
    display_init();
    display_on();

    uint8_t digits;

    // Ex 5.0
    // 
    // We have defined immediately above this exercise a variable
    // called "digits" representing an 8-bit unsigned integer. Write
    // C code below to assign a value equal to the last two digits 
    // of your student number to this variable.
    //
    // e.g. if your student number was n12345678 then you should
    // assign the decimal value 78 to "digits".

    digits = 31;

    // Write your code for Ex 5.0 above this line.
    printf("Ex 5.0: Your student ID = %08lX, digits = %02u\n", STUDENTID, digits);



    // Ex 5.1
    //
    // With the help of the definitions included by the "#define <avr/io.h>"
    // preprocessor directive above, we can also assign values directly
    // to peripheral registers. The register definitions for the ATtiny1626
    // are accessed using a dot notation, e.g. we could write to the PORTB OUT
    // register using the expression: PORTB.OUT = 0;
    //
    // Write C code below to turn on the DS1-DP LED on the QUTy.

    PORTB.OUTSET = PIN5_bm;
    PORTB.DIRSET = PIN5_bm;
    PORTB.OUTCLR = PIN5_bm;

    // Write your code for Ex 5.1 above this line.
    _delay_ms(1); uint8_t pass = (_SFR_MEM8(0x0004) & ~_SFR_MEM8(0x0005) & 040);
    printf("Ex 5.1: pass = %u\n", pass >> 5);



    // Ex 5.2
    //
    // We have written a block of code below this exercise that is intended
    // to execute the statement "loop += 1" 191 times. Complete the #define 
    // preprocessor directive "CONDITION" below so that the for loop executes
    // the correct number of times.
    
    #define CONDITION i < 191

    // Write your code for Ex 5.2 above this line.
    uint8_t loop = 0;
    for (uint8_t i = 0; CONDITION; i++) {
        loop += 1;
    }
    printf("Ex 5.2: expected = %u, loop = %u\n", ITERATIONS, loop);



    // Ex 5.3
    //
    // Write C code below to correctly configure pushbutton S3 by
    // enabling the internal pull-up resistor for the corresponding pin.

    PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;

    // Write your code for Ex 5.2 above this line.
    printf("Ex 5.3: expected = 0xFF, found = 0x%02X\n", PB ^ 0xF7);



    // Ex 5.4
    //
    // Below we haw written a "while" loop that, as written, will execute 
    // forever. Add code to the body of this while loop so that the 
    // programme will exit the loop as soon as pushbutton S3 is pressed.
    //
    // Hint: You might like to review the "if", "continue" and "break" statements.
    
    printf("Ex 5.4: PORTA.IN = 0x%02X. Waiting for pushbutton press...", VPORTA.IN);
    
    while (1) { // Will always evaluate true so will loop forever
        
        // Write your code for Ex 5.4 below this line.

        if (!(PORTA.IN & PIN6_bm)) {
            break;
        }

        // Write your code for Ex 5.4 above this line.

    } //end while
    
    printf("DONE! PORTA.IN = 0x%02X\n", VPORTA.IN);

    

    // Ex 5.5
    //
    // Elsewhere in the programme we have defined some signed, 8-bit integers:
    // X and Y. Write C code multiply X by Y and store the result in a variable
    // called "alpha". Write some additional C code to determine if the value
    // of "alpha" is positive or negative. If "alpha" is positive, perform a 
    // bitwise left shift by one position and store the result in a variable
    // "beta". If result is negative perform an arithmetic right shift by four
    // positions and store the result in "beta". Once these calculations are
    // complete, uncomment the printf(..) statement below.

    uint16_t alpha = X * Y;
    uint16_t beta = alpha << 1;
    if (alpha < 0) {
//        Negative
//arithmetic right shift by four
        beta = alpha >> 4;

    }

    // Write your code for Ex 5.5 above this line. Uncomment the line below when complete.
    printf("Ex 5.5: X = %d, Y = %d, alpha = %d, beta = %d\n", X, Y, alpha, beta);

// END OF TUTORIAL05 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //

    asm("break");   // Stop here for autograder
    
    while(1) {
        // Loop forever
    }

} // end main()

