// n11272031

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#include "qutyio.h" 

/***
 * Tutorial 06: Introduction
 *
 * In this week's tutorial you will be writing C code to implement
 * a descrambler, which operates on an array of scrambled characters.
 * This will be of particular relevance to your Assessment 2 project.
 * You may like to review Assessment 2, Appendix 2, Section 2.2 so
 * that you have an understanding of the project context and how this
 * weeks tutorial exercise might contribute towards one of the functional
 * requirements of the project.
 */

uint8_t scrambled[64] = {
    0x26, 0xC0, 0xA3, 0x96, 0xDD, 0x07, 0xC3, 0xB8,
    0x8E, 0xC8, 0x1A, 0x8B, 0x6C, 0x81, 0x73, 0x10,
    0xA1, 0x66, 0x86, 0xE7, 0xC3, 0xB5, 0x99, 0x0E,
    0x80, 0x38, 0xC9, 0xA2, 0x0F, 0x95, 0x34, 0xCB,
    0xBC, 0x11, 0x5C, 0xF2, 0x2E, 0x55, 0x71, 0x6E,
    0x6D, 0xE4, 0x73, 0xD0, 0xBF, 0x0E, 0xC4, 0x2C,
    0xC1, 0x36, 0x89, 0xBD, 0x91, 0x88, 0x1E, 0x0B,
    0x7B, 0x70, 0xF0, 0x28, 0xD3, 0xA4, 0xD2, 0xFE
};



// Ex 6.0
// 
// Define below a global variable called "state" with the type of 
// 32-bit unsigned integer. Initialise state with a value equal to
// your student number, where each decimal digit in your student 
// number is written as a hex digit in a hexadecimal literal.
//
// e.g. if your student number was n12345678 then you should
// assign the hex value 0x12345678 to "state".
//
// Once you have defined this variable uncomment the first printf()
// statement in main() such that this value is printed via the
// serial interface.

uint32_t state = 0x11272031;

// Write your code for Ex 6.0 above this line.



// Ex 6.1
// 
// Write a function prototype for a function called "next"
// which takes no parameters and returns no result.

void next(void);

// Write your code for Ex 6.1 above this line. 



// Ex 6.2
// 
// Write a function called "descramble" which returns no result
// and takes as a single argument a pointer to a uint8_t.
//
// The function should perform the bitwise XOR of the least
// significant byte of variable "state" and the uint8_t
// pointed to by the argument of the function. The result of
// this XOR should be stored back to the uint8_t pointed to by 
// the argument of the function. Finally, the function should
// call the next() function prototyped above.
//
// Once you have written this function uncomment the second printf()
// statement in main() such that its operation can be tested.


void descramble(uint8_t* a) {
    *a ^= state;
    next();
}


// Write your code for Ex 6.2 above this line.



// Ex 6.3
// 
// Complete below the implementation for the function next().
//
// next() should:
//     1) Right shift the bits in "state" by 1 bit position.
//     2) If the bit shifted out of state was set (1), take the XOR
//        of "state" with 0xBE48731D, and store the result in "state".
//
// Once you have written this function uncomment the third printf()
// statement in main() such that its operation can be tested.

void next(void) {
    uint8_t lsb_bit = state & 0x1;
    state = state >> 1;
    if (lsb_bit) {
        state ^= 0xBE48731D;
    }
}

// Write your code for Ex 6.3 above this line. 



// This is main(). It it the entry point for a C programme.
int main(void) {

    serial_init();

    // Uncomment the line below when Ex 6.0 is complete
     printf("Ex 6.0: student = n11272031, state = 0x%08lX\n", state);

    // Uncomment the line below when Ex 6.2 is complete
     uint8_t test = 0; descramble(&test); descramble(&test); descramble(&test); printf("Ex 6.2: mask = 0xBE48731D, test = 0x%02X\n", test);

    // Uncomment the line below when Ex 6.3 is complete
     printf("Ex 6.3: state = 0x%08lX", state); next(); next(); next(); next(); printf(", state = 0x%08lX\n", state);



    // Ex 6.4
    // 
    // The function descramble() you have written above takes
    // a pointer to a byte as an input, and descrambles this 
    // byte using the current value of the variable "state".
    //
    // The variable "state" together with the function next()
    // you have written above implement a linear-feedback shift
    // register, which can produce a pseudorandom binary sequence.
    // We seeded this sequence (i.e. set the initial value) with 
    // your student number at the start of the programme. The tests
    // above have already made a few calls to next() so you should
    // expect the value currently stored in "state" to be different
    // from the initial seed.
    //
    // At the start of this file an array of bytes called "scrambled"
    // has been declared. Write code below to apply the function
    // descramble() to each byte in this array in turn, from lowest
    // to highest index. If you are successful you will have decoded
    // this string of bytes into a human-readable message which will
    // be printed via the serial interface.
    // 
    // Tip: You will likely want to use a loop to access each byte
    //      in "scrambled" in turn.
    //
    // Tip: Recall that the unary operator "&" can be used to get a
    //      reference (pointer) to some data.
    //
    // Tip: Recall that we can use the name of an array like a pointer.

    for (uint8_t i = 0; i < 64; i++) {
        descramble(&scrambled[i]);
    }

    // Write your code for Ex 6.4 above this line. 

// END OF TUTORIAL06 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //

    printf("Ex 6.4: ");
    // Print the (hopefully descrambled) message
    for (uint8_t ii = 0; ii < 64; ii++) {
        if (scrambled[ii] == 0) break;
        printf("%c", scrambled[ii]);
    }
    printf("\n");

    asm("break");   // Stop here for autograder
    
    while(1) {
        // Loop forever
    }

} // end main()

