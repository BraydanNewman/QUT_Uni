#include "buttons.h"

/***
 * Tutorial 10: Introduction
 *
 * In this week's tutorial you will be working implementing pushbutton
 * handling, including debouncing, and implementing a state machine 
 * using enum and switch-case statements.
 * 
 * The Tutorial 10 exercises, once completed, should implement the 
 * state machine as documented in state_machine_tut10.png, and all
 * pushbuttons should be debounced.
 * 
 * Pushbutton handling on the QUTy is a core requirement for Assessment 2,
 * and use of a state machine is the preferred way to get the required
 * behavior for the different modes that must be implemented (as well as
 * for serial protocol handling which will be discussed in Week 11).
 */


/***
 * Ex 10.0
 * 
 * Declare an enumerated type (enum) that can hold the values of each state
 * required to implement the state machine in "state_machine_tut10.png".
 * Use meaningful names for each enum value.
 */


typedef enum {
    ON,
    CONFIRM_ON,
    OFF,
    CONFIRM_OFF
} states;

// Write your code for Ex 10.0 above this line


int main(void) {

    buttons_init();
    PORTB.DIRSET = PIN5_bm;
    PORTB.OUTSET = PIN5_bm;

    uint8_t pb = 0;
    uint8_t pb_prev = 0;

    /***
     * Ex 10.1
     * 
     * Declare a variable below, of the enumerated type you declared above.
     * Initialise this variable with the initial state of the state machine.
     */

    states state = OFF;

    // Write your code for Ex 10.1 above this line


    while (1) {
        /***
         * Ex 10.2
         * 
         * We have already written some code in "buttons.c" which uses periodic
         * interrupts to sample the state of the pushbuttons for you; the state 
         * of the pushbuttons will be available in variable "pb_state".
         * 
         * Write some code below which will allow you to detect button pressed events
         * for S1-S4 (i.e. that can detect the falling edge of the bits in "pb_state"). 
         * Store the output of this detection in a variable.
         */

        pb_prev = pb;
        pb = pb_state;

        uint8_t pb_changed = pb ^ pb_prev;
        uint8_t pb_falling = pb_changed & ~pb;

        // Write your code for Ex 10.2 above this line


        /***
         * Ex 10.3
         * 
         * Write the switch-case statement below that implements the state machine
         * documented in "state_machine_tut10.png".
         * 
         * Your switch statement should test the value of the variable declared
         * in Ex 10.1. A case should be defined for every state in the state machine.
         * 
         * Use the output of the code you wrote above in Ex 10.2 to trigger the
         * appropriate transitions between states.
         * 
         * LED DP should be controlled based on the current state of your state machine.
         */




        switch (state) {
            case OFF:
                if (pb_falling & PIN4_bm){
                    state = CONFIRM_ON;
                    PORTB.OUTSET = PIN5_bm;
                }
                break;
            case CONFIRM_ON:
                if (pb_falling & PIN5_bm){
                    state = ON;
                    PORTB.OUTCLR = PIN5_bm;
                } else if (pb_falling & PIN4_bm || pb_falling & PIN6_bm || pb_falling & PIN7_bm) {
                    state = OFF;
                    PORTB.OUTSET = PIN5_bm;
                }
                break;
            case ON:
                if (pb_falling & PIN6_bm){
                    state = CONFIRM_OFF;
                    PORTB.OUTCLR = PIN5_bm;
                }
                break;
            case CONFIRM_OFF:
                if (pb_falling & PIN7_bm) {
                    state = OFF;
                    PORTB.OUTSET = PIN5_bm;
                } else if (pb_falling & PIN4_bm || pb_falling & PIN5_bm || pb_falling & PIN6_bm) {
                    state = ON;
                    PORTB.OUTCLR = PIN5_bm;
                }
                break;
        }

        // Write your code for Ex 10.3 above this line

    } // end while

    /***
     * Ex 10.4
     * 
     * Modify the code in "buttons.c" such that the variable "pb_state" holds a 
     * debounced version of the pushbutton state, rather than just a raw sample of
     * PORTA.IN. You may need to modify the timer period to get effective debouncing.
     * 
     * NOTE: DO NOT WRITE YOUR CODE IN THIS FILE. You should edit "buttons.c".
     */

} // end main()