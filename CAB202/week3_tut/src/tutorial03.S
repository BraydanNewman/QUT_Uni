; n11272031

#include <avr/io.h> // Include register definitions

.section .init0     // Places code at the top of programme memory

.include "include/buzzer.S" // Configures TCA0 to drive buzzer

    // These three lines are required by autograder; do not edit.
    ldi r16, 0x20
    push r16
    ldi r16, 0

entry:
    
    // Ex 3.0
    // 
    // In Ex 3.1 we are going to enable as an output PB5, which is 
    // connected to net DISP DP and controls LED DS1-DP (active low).
    //
    // Write assembly code such that when we enable PB5 as an output
    // LED DS1-DP is off.


    // Write your code for Ex 3.0 above this line.
    


    // Ex 3.1
    // 
    // Write assembly code to enable the pin connected to net DISP DP
    // as an output.


    // Write your code for Ex 3.1 above this line.



    // Ex 3.2
    // 
    // In later exercises you will be required to read the state of
    // pushbuttons BUTTON0..3. Write assembly code to enable the
    // internal pull-up resistors for the pins connected to these
    // pushbuttons.


    // Write your code for Ex 3.2 above this line.



    // Ex 3.3
    // 
    // Write assembly code to turn on LED DS1-DP


    // Write your code for Ex 3.3 above this line.



// The code between the "loop_100ms" and "end_loop_100ms" labels 
// will execute approximately 10 times per second.
loop_100ms:

    // Ex 3.4
    //
    // Write assembly code to read the state of BUTTON0, 
    // and store the result in r17. If BUTTON0 is pressed r17
    // should contain the value 0x00. If BUTTON0 is not pressed 
    // r17 should contain a non-zero value.
    //
    // Hint: You can use a bitmask and bitwise logical operation to 
    // isolate the bit that corresponds to the relevant pushbutton 
    // after reading the port state.


    // Write your code for Ex 3.4 above this line.



    // Ex 3.5
    //
    // The two instructions below will test the value in r17 to determine 
    // whether BUTTON0 is pressed. If the button is NOT pressed 
    // (the value in r17 is not zero), any code between the "brne" instruction 
    // and the label "end_loop_100ms" will be skipped. Write assembly code in 
    // the space provided that will toggle LED DS1-DP.

    cpi r17, 0
    brne end_loop_100ms
    // Write your code for Ex 3.5 below this line.


    // Write your code for Ex 3.5 above this line.
end_loop_100ms:



// The code between the "loop_10ms" and "end_loop_10ms" labels 
// will execute approximately 100 times per second.
loop_10ms:

    // Ex 3.6
    //
    // At the start of this programme, some code was included that sets up
    // the Timer Counter A 0 (TCA0) peripheral to synthesize a ~200 Hz tone
    // to drive the piezo buzzer connected to the BUZZER net.
    //
    // The TCA0 will automatically override the function of the pin connected
    // to the BUZZER net, however, the pin needs to be configured as an output
    // in order for the timer signal to drive the BUZZER.
    //
    // Write assembly code below such that the buzzer is driven (i.e an audible
    // tone is produced) when BUTTON2 is pressed, and not driven
    // (i.e. silent), when BUTTON2 is released.
    //
    // To assist you we have written some code below that will test r18: 
    //   If r18 equals zero, then: 
    //       any code between ex36_zero and rjmp end_ex36 will execute.
    //   Else, if r18 is not zero, then: 
    //       any code between ex36_nonzero and end_ex36 will execute.
    //
    // You can write your code for Ex 3.6 anywhere below this line


    cpi r18, 0
    brne ex36_nonzero

ex36_zero:

    rjmp end_ex36

ex36_nonzero:

end_ex36:

    // You can write your code for Ex 3.6 anywhere above this line

// END OF TUTORIAL03 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //
end_loop_10ms:



// For sys_clk = 3.33 MHz, ~33k cycles in 10ms
//
// Let's implement a delay loop based on 16-bit counter
//
// adiw takes 2 cycles to execute, we will also need at
// least one cycle for a test, so let's assume 4 cycles
// total, which we need to repeat ~8k times.
// 
// 0x2000 = 8192, so we can just test bit 5 in high byte

delay_10ms:
    adiw r30, 1     // 2 cycles
    cpi r31, 0x20   // 1 cycle
    brne delay_10ms // 1 cycle

    // Reset high byte of delay loop counter
    // (low byte should already be 0x00)
    ldi r31, 0

    // Every 10 of these cycles we need to execute the 100ms loop also
    inc r29
    cpi r29, 10
    brne loop_10ms

    // Reset 1s counter then jump to 1s loop
    ldi r29, 0
    rjmp loop_100ms

// We should never get here, but just in case
loop:
    rjmp loop
	
