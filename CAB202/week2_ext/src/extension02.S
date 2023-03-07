; n11272031

.section .init0 // Places code at the top of programme memory

.include "include/individual.S" // Include individualised programme code 

entry:
    
    // Ex E2.1
    // 
    // The code included above pushes a number of unsigned 8-bit integers
    // onto the stack. Write assembly code to add the 8 values on top of the
    // stack together, and store the result in register pair r31:r30.
    //
    // NOTE: r8-r12 are reserved for use later in this programme; do not
    // use these registers in this exercise.
    ldi r30, 0x00
    ldi r31, 0x00

    ldi r19, 0x00

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    pop r16
    add r30, r16
    adc r31, r19

    // Write your code for Ex E2.1 above this line.
    push r30
    push r31



    // Ex E2.2
    // 
    // Write assembly code to add the following two unsigned 64-bit integers, 
    // and store the result in r7:r6:r5:r4:r3:r2:r1:r0 (lowest byte in r0):
    // 0x0F21592343B6D270
    // 0x04CDBF6BE30D2283
    //
    // NOTE: r8-r12 are reserved for use later in this programme; do not
    // use these registers in this exercise.

    clc

    ldi r16, 0x0F
    ldi r17, 0x21
    ldi r18, 0x59
    ldi r19, 0x23
    ldi r20, 0x43
    ldi r21, 0xB6
    ldi r22, 0xD2
    ldi r23, 0x70

    ldi r24, 0x04
    ldi r25, 0xCD
    ldi r26, 0xBF
    ldi r27, 0x6B
    ldi r28, 0xE3
    ldi r29, 0x0D
    ldi r30, 0x22
    ldi r31, 0x83

    add r23, r31
    adc r22, r30
    adc r21, r29
    adc r20, r28
    adc r19, r27
    adc r18, r26
    adc r17, r25
    adc r16, r24

    mov r7, r16
    mov r6, r17
    mov r5, r18
    mov r4, r19
    mov r3, r20
    mov r2, r21
    mov r1, r22
    mov r0, r23

    // Write your code for Ex E2.2 above this line.
    push r0
    push r1
    push r2
    push r3
    push r4
    push r5
    push r6
    push r7



    // Ex E2.3
    // 
    // Registers r11:r10:r9:r8 currently hold a 32-bit signed integer in
    // two's complement format (lowest byte in r8). Write assembly code to 
    // perform an arithmetic right shift by 3 positions on this integer. 
    // The result should be stored in the same four registers.
    //
    // NOTE: r12 is reserved for use later in this programme; do not
    // use this register in this exercise.

    asr r11
    ror r10
    ror r9
    ror r8

    asr r11
    ror r10
    ror r9
    ror r8

    asr r11
    ror r10
    ror r9
    ror r8

    // Write your code for Ex E2.3 above this line.
    push r8
    push r9
    push r10
    push r11



    // Ex E2.4
    // 
    // Register r12 currently holds an 8-bit unsigned integer. Write assembly
    // code to divide the value currently in r12 by 6.4 and store
    // the result in r13.

    ldi r16, 10

    asr r12
    asr r12
    asr r12
    asr r12
    asr r12
    asr r12

    mul r12, r16

    movw r12,r0

    mov r13, r12



    // Write your code for Ex E2.4 above this line.
    push r13


// END OF EXTENSION02 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //

    break   // Terminate here for autograder

    // Restore r1 before we call and C functions
    ldi r16, 0
    mov r1, r16

    // Lets set the display into a known state so we can easily
    // confirm that our programme successfully gets to this point
    call display_raw_init
    ldi r24, 0x77
    call display_raw

loop:
