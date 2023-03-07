
// n11272031

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

#include "qutyserial.h" 

/***
 * Tutorial 07: Introduction
 *
 * In this week's tutorial you will be working with a number of new
 * features of C, including structs, bitfields and unions, a new type, 
 * "float" which can be used to represent floating point numbers, as 
 * well as some new embedded programming concepts, such as interrupts.
 * 
 * In Exercises 7.0-7.2, 7.4-7.5 you will use structs, bitfields and unions to 
 * destructure a float into its component fields (sign, exponent and
 * mantissa). This is a useful technique for accessing and referring to
 * strings of bits within a larger structure (e.g. array of bytes) and may
 * be helpful to use for Assessment 2 for decoding the fields in sequence
 * steps (see Assessment 2, Appendix 1).
 * 
 * In Exercises 7.3, 7.6-7.7 you will configure time TCB0 on the ATtiny1626
 * to generate a periodic interrupt. You will use this interrupt to
 * measure and compare the relative execution time of some integer and 
 * floating point arithmetic, to understand the implications of using
 * software floating point implementations on a fixed point processor.
 */

// Here we declare some global variables used later in the programme
volatile int32_t dividend_int32 = 20000;
volatile float dividend_float = 20000.0;
volatile int32_t divisor_int32 = 77;
volatile float divisor_float = 77.0;
volatile int32_t reciprocal_shift16 = 851;

// Here we declare some functions used later in the programme
float div77_fp(float dividend, float divisor) {
    return dividend/divisor;
}

int32_t div77_int(int32_t dividend, int32_t divisor) {
    return dividend/divisor;
}

int32_t div77_int_nodiv(int32_t dividend, int32_t reciprocal_shift16) {
    // This is integer division implemented using a multiply and
    // shift rather than a division operation
    return (dividend*reciprocal_shift16) >> 16;
}



/***
 * Ex 7.0
 * 
 * A "float" is a 32-bit representation for a floating point number.
 * The 32 bits of a float are divided into three fields:
 * 
 * | Bit 31 | Bits 30-23 | Bits 22-0 |
 * | Sign   | Exponent   | Mantissa  |
 *
 * In C we can use a structs and bitfields to destructure more complex
 * data types. Define a struct named "struct_float". Consistent with how
 * a float is structured, the struct should contain three fields:
 * sign, exponent, and mantissa. Use unsigned standard integer types
 * as the base type for each of these fields. Use bitfields of appropriate 
 * widths such that the overall struct occupies the same space in memory 
 * as a float.
 */

struct struct_float {
    uint32_t Mantissa: 23;
    uint8_t Exponent: 8;
    uint8_t Sign: 1;
};



// Write your code for Ex 7.0 above this line.



/***
 * Ex 7.1
 * 
 * We want to be able to use the struct declared above to be able 
 * to destructure a float. To do this we need to declare a union
 * so that we can refer access the same 32-bits as either a float
 * type, or our struct. Declare a union named "union_float" that
 * contains a float type, with the name "value", and the struct type
 * declared above, using the name "fields".
 * 
 * TIP: remember that we still need to use the struct keyword when 
 * specifying a named struct type.
 */

union union_float {
    struct struct_float fields;
    float value;
};

// Write your code for Ex 7.1 above this line.



/***
 * Ex 7.2
 * 
 * Write a typedef declaration such that we can refer to the union 
 * declared above using the type alias "float_fields".
 */

typedef union union_float float_fields;



// Write your code for Ex 7.2 above this line.



/***
 * Ex 7.3
 * 
 * Later in the programme we are going to implement an interrupt service
 * routine (ISR) that will execute at fixed intervals. We want to count
 * how many times this ISR executes, so will need to define a global 
 * variable to do this. Define a global variable of type uint32_t named 
 * "count_100us" to serve this purpose.
 * 
 * Once you have completed this exercise, uncomment the block of code 
 * at the bottom of main() which contains the code that uses this variable.
 * You will need to remove both the opening and closing symbols that compose
 * the block comment.
 *
 * 
 * HINT: We need to use a specific qualifier when declaring a global
 * variable that could be modified in an ISR.
 */

volatile uint32_t count_100us;

// Write your code for Ex 7.3 above this line.



int main(void) {

    serial_init();

    /***
     * Ex 7.4
     * 
     * Declare a float named "my_float" below to hold the value 229.90.
     * Once this is complete uncomment the printf statement below so that 
     * this value is printed via the serial interface.
     */

    static float my_float = 229.90;


    // Write your code for Ex 7.4 above this line.
    printf("Ex 7.4: my_float = %.2f\n", my_float);



    /***
     * Ex 7.5
     * 
     * 1) Declare a variable named "my_union" of the type of the union you
     *    declared above.
     * 2) Assign the value stored in "my_float" into this new variable using
     *    the "value" field.
     * 3) Modify the three assignment statements below for variables sign, 
     *    exponent and mantissa, so that the values of these fields in the
     *    float are printed via the serial interface (i.e. replace 0 in 
     *    each assignment with an appropriate read of a field in your union).
     * 
     * TIP: You might like to use a webtool to check the ouput is correct,
     * e.g. https://www.h-schmidt.net/FloatConverter/IEEE754.html
     * 
     * TIP: If the output doesn't look correct, check your Ex 7.0 and 7.1.
     */

    float_fields my_union;
    my_union.value = my_float;

    uint8_t sign = my_union.fields.Sign;
    uint8_t exponent = my_union.fields.Exponent;
    uint32_t mantissa = my_union.fields.Mantissa;


    // Write your code for Ex 7.5 above this line.
    printf("Ex 7.5: ");
    printf("sign = %u, ", sign);
    printf("exponent = %u, ", exponent);
    printf("mantissa = 0x%06lX", mantissa);
    printf("\n");



    /***
     * Ex 7.6
     * 
     * The code below partially configures the Timer Counter B 0 (TCB0) 
     * peripheral to generate interrupts at a fixed interval of 100 
     * microseconds. You need to complete this block of code by writing
     * a line which will enable the CAPT interrupt for TCB0. Refer to the
     * definition for register TCB0.INTCTRL (datasheet p. 259).
     * 
     * TIP: Remember you can use the *_bm and *_gc definitions included by
     *      <avr/io.h> to set register values.
     * 
     * TIP: After you enable an interrupt you must ensure you declare an
     *      ISR to handle this interrupt before your code will run correctly
     *      (see Ex 7.7).
     */

    cli();  // Disable interrupts globally
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
    TCB0.CCMP = 333;                    // Set interval for 100us (333 clocks @ 3.3 MHz)
    // Write your code for Ex 7.6 below this line.

    TCB0.INTCTRL |= 0x1;

    // Write your code for Ex 7.6 above this line.
    TCB0.CTRLA = TCB_CLKSEL_DIV1_gc | TCB_ENABLE_bm; // Clock select is not required
    sei();  // Enable interrupts globally

    

    uint32_t tick, tock, i;
    volatile float result_float;
    volatile int32_t result_int;

    tick = count_100us;   // get the current value of count
    // Time 50000 iterations of a float division
    for (i = 0; i < 50000; i++) result_float = div77_fp(dividend_float, divisor_float);
    tock = count_100us;   // get the current value of count
    printf("               Float division: result = %.2f, (%lu ms)\n", result_float, (tock-tick)/10);

    tick = count_100us;   // get the current value of count
    // Time 50000 iterations of an integer division
    for (i = 0; i < 50000; i++) result_int = div77_int(dividend_int32, divisor_int32);
    tock = count_100us;   // get the current value of count
    printf("             Integer division: result = %ld,    (%lu ms)\n", result_int, (tock-tick)/10);

    tick = count_100us;   // get the current value of count
    // Time 50000 iterations of an integer division (using mult/shift)
    for (i = 0; i < 50000; i++) result_int = div77_int_nodiv(dividend_int32, reciprocal_shift16);
    tock = count_100us;   // get the current value of count
    printf("Integer division (mutl/shift): result = %ld,    (%lu ms)\n", result_int, (tock-tick)/10);


    while(1) {
        // Loop forever
    }

} // end main()

/***
 * Ex 7.7
 * 
 * Declare an interrupt service routine (ISR) to handle the interrupt
 * you enabled in Ex 7.6. You will need to follow these steps:
 * 
 * 1) Find the vector number and name that corresponds to the interrupt
 *    you enabled (i.e. the TCB0 CAPT interrupt). Refer to datasheet
 *    section 8.2 Interrupt Vector Mapping on p. 63).
 * 2) Find the corresponding vector definition in "iotn1626.h". This will
 *    be named like *_vect and should correspond to the vector number you
 *    identified in step 1 above.
 * 3) Declare an ISR function below using this ISR(vector) macro, where 
 *    "vector" is replaced with the definition you identified in step 2.
 * 4) In the body of your ISR write code that will increment the global 
 *    variable you declared in Ex 7.3 by one each time the ISR executes.
 * 5) Finally, you need to acknowledge that the interrupt has been handled
 *    by clearing the CAPT bit in the TCB0.INTFLAGS register. Write code
 *    at the bottom of your ISR to do this.
 * 
 * TIP: Refer to the datasheet for the correct way of clearing bits in the
 *      TCB0.INTFLAGS register.
 */


ISR(TCB0_INT_vect) {
    count_100us++;
    TCB0.INTFLAGS |= 0x1;

}


// Write your code for Ex 7.7 above this line.

// END OF TUTORIAL06 EXERCISES //

