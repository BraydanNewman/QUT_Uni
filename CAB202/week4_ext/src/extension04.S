; n11272031

#include <avr/io.h> // Include register definitions

.section .init0     // Places code at the top of programme memory

entry:
    
    // Ex E4.0
    // 
    // Included with this extension exercise is a precompiled object file
    // "lib/quty.o" in which is defined a number of procedures. You can call
    // these procedures from assembly code using a "call" instruction, followed
    // by the procedure name.
    // 
    // In this exercise you will need to use two procedures from this object file:
    //     display_raw_init
    //     display_raw
    // Both of these procedures provide utility functions to assist in driving the
    // 7-segment display on the QUTy. 
    //
    // "display_raw_init" must be called first, and configures both the required 
    // port pins, as well as the SPI peripheral which is used to drive the display. 
    // "display_raw_init" needs to be called only once, at the start of your programme. 
    //
    // "display_raw" sends a single byte of data to the shift register that controls 
    // the 7-segment display, and latches this data to the outputs Q0-7. This procedure
    // sends the byte in r24 at the time that the procedure is called. The LSB of the 
    // byte corresponds to Q0 and the MSB of the byte corresponds to Q7.
    //
    // You are required to write a programme to the following specification:
    //    1) On intialisation, the display will cleared (all segments off).
    //    2) When pushbutton S1 is depressed for the first time, the display
    //       will show the first digit of your student number for 1.0 seconds,
    //       and then return to the cleared state. You can assume that the pushbutton
    //       will be released some time during this interval in which the digit is
    //       being displayed. The digit should be shown on the RHS of the display.
    //    3) For each subsequent press of pushbutton S1, the display will show the
    //       next digit of your student number, in order (i.e. for the 2nd button
    //       press the 2nd digit should be displayed, for the 3rd button press the 3rd 
    //       digit should be displayed, etc.). For each button press, the corresponding
    //       digit should be displayed for 1.0 seconds, and then the display returned to
    //       the cleared state. The digit should be shown on the RHS of the display.
    //    4) Once all digits of your student number have been displayed exactly once,
    //       any additional presses of button S1 should result in "-" being displayed for
    //       1.0 seconds (on the RHS of the display), after which the display should 
    //       return to the cleared state.
    //
    // Note: r0 is assumed to always hold the value 0. If you change its value you must
    //       restore it to 0 prior to calling either of the "display_*" procedures.
    //
    // Note: The state of r18-r27, r30-31 and SREG are NOT guaranteed to be preserved
    //       following a call to either of the "display_*" procedures.

    // Initsalize Display and Button
    rcall display_raw_init
    ldi r16, PORT_PULLUPEN_bm
    sts PORTA_PIN5CTRL, r16

    // Student Number: 11272031
    ldi r16, 0b00111110 // 1
    push r16
    ldi r16, 0b01000001 // 3
    push r16
    ldi r16, 0b00001000 // 0
    push r16
    ldi r16, 0b01000100 // 2
    push r16
    ldi r16, 0b01001011 // 7
    push r16
    ldi r16, 0b01000100 // 2
    push r16
    ldi r16, 0b00111110 //1
    push r16
    ldi r16, 0b00111110 // 1
    push r16

    ldi r16, 8 // Number of Digits

    // Main Loop
    main:
        in r17, VPORTA_IN
        andi r17, PIN5_bm
        cpi r17, 0
        breq button_pressed
        rjmp button_exit
        button_pressed:
            cpi r16, 0
            brne student_digit
                ldi r24, 0b01110111
                rcall display_raw
                rcall delay_1s
                ldi r24, 0xff
                rcall display_raw
                rjmp button_exit
            student_digit:
                pop r24
                rcall display_raw
                rcall delay_1s
                ldi r24, 0xff
                rcall display_raw
                dec r16
        button_exit:
        rjmp main

// Delay Procedure
    delay_1s:
    rcall delay_500ms
    rcall delay_500ms
    ret
    delay_500ms:
        push r25
        push r24
        in r24, 0x3F
        push r24
        ldi r25, hi8(2082)
        ldi r24, lo8(2082)
    delay_500ms_loop:
        push r24
        push r25
        call delay
        pop r25
        pop r24
        sbiw r24, 1
        brne delay_500ms_loop
        pop r24
        out 0x3F, r24
        pop r24
        pop r25
        ret
    delay:
        ldi r18, 0xc4
        delay_loop:
            dec r18
            cpi r18, 0
            brne delay_loop
        ret

    // Write your code for Ex E4.0 above this line.

// END OF EXTENSION04 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //
