#include "uart.h"

/***
 * Ex E10.0
 * 
 * Your task is to write code to implement the state machine described
 * by "state_machine_ext10.png". The intent of this state machine is
 * to interact with a user via the serial console. The user is required
 * to enter a four digit pin code. On recept of the correct sequence of
 * characters, the state machine transitions to the AUTHORISED state. 
 * Once in the AUTHORISED state the machine should return to the 
 * CHALLENGE state on receipt of a linefeed character.
 * 
 * If at any time during receipt of the pin code an incorrect character
 * is received, the state machine should return immediately to the
 * CHALLENGE state.
 * 
 * The output for each state is a series of characters which should be
 * sent to the serial console. These should only be sent when entering 
 * the state.
 * 
 * The correct sequence of character should be the first four digits of
 * your student number.
 * 
 * Your solution should use a baud rate of 9600, and 8N1 frame format.
 * 
 * Examples for student number n12345678:
 * 
 *      User enters: '1', '2', '3', '4', '\r', '\n'
 *      Output: 
 *          PIN: **** OK
 *          PIN: 
 * 
 *      User enters: '1', '2', '2', '4'
 *      Output: 
 *          PIN: **
 *          PIN: 
 */

typedef enum {
    CHALLENGE,
    DIGIT1,
    DIGIT2,
    DIGIT3,
    AUTHORIZED
} pinStates;


int main(void) {
    char *pin = "1127";

    uart_init();

    char *challengeOut = "\nPIN: ";
    char *digitOut = "*";
    char *authorizedOut = "* OK";

    pinStates pinState = CHALLENGE;

    while (1) {
        switch (pinState) {
            case CHALLENGE:
                uart_puts(challengeOut);
                if (pin[0] == uart_getc()) {
                    pinState = DIGIT1;
                }
                break;
            case DIGIT1:
                uart_puts(digitOut);
                if (pin[1] == uart_getc()) {
                    pinState = DIGIT2;
                } else {
                    pinState = CHALLENGE;
                }
                break;
            case DIGIT2:
                uart_puts(digitOut);
                if (pin[2] == uart_getc()) {
                    pinState = DIGIT3;
                } else {
                    pinState = CHALLENGE;
                }
                break;
            case DIGIT3:
                uart_puts(digitOut);
                if (pin[3] == uart_getc()) {
                    pinState = AUTHORIZED;
                    break;
                }
                pinState = CHALLENGE;
                break;
            case AUTHORIZED:
                uart_puts(authorizedOut);
                pinState = CHALLENGE;
                break;

        }
    }
}