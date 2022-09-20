#include "uart.h"
#include "timer.h"
#include "spi.h"


/***
 * Tutorial 09: Introduction
 *
 * In this week's tutorial you will be working with the USART0 and
 * SPI0 peripherals to read/write data via the USB-UART interface
 * and to control the 7-segment display.
 * 
 * Interfacing with these hardware devices on the QUTy is a core
 * requirement for Assessment 2. Specifically you should refer to
 * Assessment 2, Functional Specifications, Parts A3 & B2.4 and C.
 */



/***
 * Ex 9.0
 * 
 * We have declared some functions in "uart.c" and corresponding function
 * prototypes in "uart.h":
 *   void uart_init(void);      // Initialise the UART peripheral to 9600 baud, 8N1
 *   void uart_putc(uint8_t c); // Blocking write of byte c to UART
 *   void uart_getc(uint8_t c); // Blocking read of byte c from UART
 * 
 * Your task for exercise 9.0 is to complete in "uart.c" the function
 * "void uart_puts(char* string)" which takes as an argument a pointer to
 * a string, and should transmit this string via the UART.
 * 
 * NOTE: DO NOT WRITE YOUR CODE FOR THIS EXERCISE IN THIS FILE.
 *       This exercise should be completed in file "uart.c".
 */



int main(void) {

    uart_init();

    /***
     * Ex 9.1
     * 
     * Write code below that will call uart_puts() to print your student number
     * via the UART interface. The string you print should begin with a leading 'n'
     * and should be terminated with a newline character '\n';
     */

    char *string = "n11272031\n";

    uart_puts(string);


    // Write your code for Ex 9.1 above this line



    /***
     * Ex 9.2
     * 
     * Create two new files: 
     *     src/spi.c
     *     include/spi.h
     * 
     * In "spi.c" declare and implement a function spi_init() that will initialise SPI0 in 
     * unbuffered mode, such that data can be written to the shift register that controls 
     * the 7-segment display, and which enables the SPI interrupt via the IE bit in INTCTRL.
     * You might also like to enable DISP EN as an output and drive it high so the display
     * is enabled.
     * 
     * Next, declare and implement a function spi_write(uint8_t b) which will write the 
     * byte b out via the SPI interface.
     * 
     * Finally, declare and implement an ISR that will handle the SPI interrupt enabled
     * above, and which will drive a rising edge onto the DISP LATCH net. You might need
     * to add some code to spi_init() if you didn't already enable all the required pins
     * as outputs.
     * 
     * Declare prototypes for these functions in "spi.h" and include "spi.h at the
     * top of "tutorial09.c".
     * 
     * Once this exercise is complete, uncomment the lines below. The 7-segment display
     * should be blank after this code executes.
     */

    spi_init();       // Initialise SPI
    spi_write(0xFF);  // Clear display

    // Uncomment the lines above once you have completed Ex 9.2



    /***
     * Ex 9.3
     * 
     * We have declared some functions in "timer.c" and corresponding function
     * prototypes in "timer.h":
     *   void timer_init(void);     // Initialise TCB0 to produce interrupts every 1ms
     * 
     * Your task for Ex 9.3 is to complete the ISR declared in "timer.c" to display 
     * simultaneously the first digit of your student number on the LHS of the 7-segment
     * display and the second digit of your student number on the RHS of this display (only
     * after timer_init() is called).
     * 
     * TIP: Every time a new interrupt occurs you should swap which digit you are displaying.
     * 
     * TIP: You will want to declare a global or static variable so you know which digit to 
     *      display on each iteration.
     * 
     * TIP: You might like to refer to the following truth table for 7-segment digit mapping.
     *      (remember to check which output Q0..Q6 maps to which segment on the QUTy)
     * 
     *    ABCDEFG
     * 0: 0000001 
     * 1: 1001111
     * 2: 0010010
     * 3: 0000110
     * 4: 1001100
     * 5: 0100100
     * 6: 0100000
     * 7: 0001111
     * 8: 0000000
     * 9: 0000100 
     * 
     * NOTE: DO NOT WRITE YOUR CODE FOR THIS EXERCISE IN THIS FILE.
     *       This exercise should be completed in file "timer.c".
     */



    /***
     * Ex 9.4
     * 
     * Write code below that will call timer_init() only after the character 'a'
     * has been received via the UART interface.
     */ 


    //Write your code for Ex 9.4 above this line


// END TUTORIAL09 EXERCISES. DO NOT EDIT BELOW THIS LINE.

    asm("break");   // Stop here for autograder
    while(1);

} // end main()