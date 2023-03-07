#include "uart.h"

/***
 * Ex E11.0
 * 
 * Your task is to write code which handles a sequence of input characters
 * from the UART interface, and respond with the output specified below.
 * It is strongly recommended that you design a state machine to complete
 * this task, and practice drawing a state machine diagram before you
 * begin coding.
 * 
 * On receipt of the character sequence: 
 *   "foo" your programme should print '0' to the UART interface.
 *   "bar" your programme should print '1' to the UART interface.
 *   "foobar" your program should not print either '0' nor '1' as
 *   specified above, but should instead print a linefeed ('\n') 
 *   character.
 * 
 * Your solution should use a baud rate of 9600, and 8N1 frame format.
 * Your solution MUST NOT use qutyio.o or qutyserial.o.
 * 
 * Examples:
 * 
 *   Input:  
 *     ...foo.bar.foo.barfoobarfood
 *   Output: 
 *     0101
 *     0
 * 
 *   Input:
 *     barsfoosbarforbarfoobarrforfoobarfoobarfood
 *   Output:
 *     1011
 *     
 *     
 *     0
 */

typedef enum {
    NONE,
    F,
    FO,
    FOO,
    B,
    BA,
    BAR,
}states;

states state = NONE;


int main(void) {
    uart_init();

    uint8_t foobarCheck = 0;
    uint8_t bCount = 0;

    uint8_t input;

    while(1) {
        input = uart_getc();

        if(input == 'f') state = F;
        if(input == 'b') state = B;

        switch (state) {
            case F:
                state = FO;
                foobarCheck = 0;
                break;
            case B:
                if(bCount == 1 && foobarCheck == 1) {
                    uart_putc('0');
                    foobarCheck = 0;
                }
                bCount = 1;
                state = BA;
                break;

            case FO:
                if (input == 'o') state = FOO;
                else state = NONE;
                break;
            case FOO:
                if (input == 'o') {
                    foobarCheck = 1;
                }
                state = NONE;
                break;
            case BA:

                if(input == 'a') {
                    state = BAR;
                    bCount = 0;
                }
                else {
                    state = NONE;
                    if(foobarCheck == 1) {
                        uart_putc('0');
                        foobarCheck = 0;
                    }
                }
                break;
            case BAR:
                if(input == 'r') {
                    if (foobarCheck == 1) uart_putc('\n');
                    else uart_putc('1');
                } else if (foobarCheck == 1) uart_putc('0');
                state = NONE;
            default:
                foobarCheck = 0;
                break;

        }
    }


}