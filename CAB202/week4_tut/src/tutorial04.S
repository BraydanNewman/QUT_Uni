; n11272031

#include <avr/io.h> // Include register definitions

.section .init0     // Places code at the top of programme memory

.include "include/individual.S"

entry:
    
    // Ex 4.0
    // 
    // Write assembly code below to advance the program counter such that
    // the next instruction executed is the "push r8" instruction below.

    rjmp some_label_00

    // Write your code for Ex 4.0 above this line.
    
some_label_00:
    push r8
    rjmp end_ex40
some_label_01:
    push r9
    rjmp end_ex40
some_label_02:
    push r10
    rjmp end_ex40
some_label_03:
    push r11
    rjmp end_ex40
some_label_04:
    push r12
    rjmp end_ex40
some_label_05:
    push r13
    rjmp end_ex40
some_label_06:
    push r14
    rjmp end_ex40
some_label_07:
    push r15
    rjmp end_ex40
end_ex40:



    // Ex 4.1
    // 
    // In the code included at the top of this program (by the .include "individual.S"
    // assembler directive), there has been a number of procedures defined. Write
    // assembly code below to call the procedure "some_procedure_00".

    rcall some_procedure_00

    // Write your code for Ex 4.1 above this line.
    lds r16, 0x3401
    push r16



    // Ex 4.2
    // 
    // We have defined a procedure "init_led_dp" below which is intended to 
    // configure the pin that drives LED DS1-DP as an output, with the LED 
    // initially off. Add, in the space indicated, the code required to add 
    // this functionality to the procedure.
    
    rjmp end_ex42 // Do not edit this line, it jumps over the procedure below.
                  // We will call this procedure later in the programme.

    // Write your code for Ex 4.2 below this line.
init_led_dp:

    ldi r19, PIN5_bm
    sts PORTB_OUTSET, r19
    sts PORTB_DIRSET, r19


    ret
    // Write your code for Ex 4.2 above this line.
end_ex42:
    rcall init_led_dp
 


    // Ex 4.3
    // 
    // Write a procedure "toggle_led" in the space indicated below that 
    // will toggle LED DS1-DP.
    
    rjmp end_ex43 // Do not edit this line, it jumps over the procedure below.
                  // We will call this procedure later in the programme.

    // Write your code for Ex 4.3 below this line.

toggle_led:
    sts PORTB_OUTTGL, r19
    ret

    // Write your code for Ex 4.3 above this line.
end_ex43: 



    // Ex 4.4
    // 
    // We have started writing a loop below that is intended to call the 
    // procedure "some_procedure_08" a total of 153 times. Complete
    // the code for this loop.
    
    // Write your code for Ex 4.4 below this line.
ldi r16, 153
some_loop:
    call some_procedure_08
    dec r16
    cpi r16, 0
    brne some_loop
    // Write your code for Ex 4.4 above this line.

    lds r16, 0x3400
    push r16



    // Ex 4.5
    // 
    // We have started writing below a procedure called "delay" which is
    // intended to implement a busy delay. Write code to complete this 
    // procedure by adding instructions that will take a total of 
    // 240 microseconds to execute.
    //
    // Tip: recall that the ATting1626 has a default system clock frequency
    // of 3.33 MHz.
    //
    // NOTE: If you have successfully completed Ex 4.2, 4.3 and 4.5,
    // the LED DS1-DP should flash 3 times.

    rjmp end_ex45 // Do not edit this line, it jumps over the procedure below.
                  // We will call this procedure later in the programme.

    // Write your code for Ex 4.5 below this line.
delay:
    ldi r17, 0xc4
    delay_2nd_loop:
        dec r17
        cpi r17, 0
        brne delay_2nd_loop
    ret
    // Write your code for Ex 4.5 above this line.
end_ex45:
    call flash_led  

    ldi r16, 0xFF
    push r16

// The code in main loop will execute indefinitely
main_loop:

    // Ex 4.6
    //
    // The code below reads the state of pushbutton S4. Complete this code
    // such LED DS1-DP is turned on whenever the pushbutton S4 is pressed, 
    // and turned off whenever pushbutton S4 is released. Note that we have
    // already enabled the pull-up resistor for the corresponding pin for you.
    //
    // Tip: You will need to use branch or skip instructions.

    in r16, VPORTA_IN
    andi r16, PIN7_bm

    // Write your code for Ex 4.6 below this line.
    ldi r19, PIN5_bm
    cpi r16, 0
    brne dp_off
        sts PORTB_OUTCLR, r19
    rjmp dp_button_end
    dp_off:
        sts PORTB_OUTSET, r19
    dp_button_end:
    // Write your code for Ex 4.6 above this line.



// END OF TUTORIAL04 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //
    pop r16
    cpi r16, 0xFF
    brne no_print

no_print:
    ldi r16, 0
    push r16
    rjmp main_loop

