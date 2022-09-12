// n11272031

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "qutyserial.h"


/***
 * Ex E7.0
 * 
 * To synthesize sound using a buzzer, we need to produce a voltage across the
 * buzzer that changes over time. For a piezo buzzer connected between a digital 
 * ouput and ground (as is the case on the QUTy), we would typically do this by
 * synthesizing a 50% duty square wave i.e. apply a signal to the buzzer that 
 * is HIGH 50% of the time and LOW 50% of the time, and alternates between these
 * two states at a fixed rate.
 * 
 * For a square wave signal, we define one cycle as the interval of time over
 * which the signal repeats (e.g. the time from a LOW -> HIGH transition, to the 
 * next LOW -> HIGH transition). The frequency produced by the buzzer, in Hertz, 
 * will be equal to the number of cycles of the applied signal per second.
 * 
 * In this week's tutorial you saw an example of some code required to configure
 * TCB0 to produce interrupts at fixed intervals. If we can synthesize interrupts
 * with the correct timing, we can use an ISR to change the state of the PORT pin 
 * connected to the buzzer, such that we generate a square wave at an audible 
 * frequency, and consequently produce a sound from the buzzer.
 * 
 * Your task is to use TCB0 in periodic interrupt mode to drive the buzzer on the 
 * QUTy to produce a 4120 Hz tone.
 * 
 * These are the recommended steps:
 *   1) Configure TCB0 in periodic interrupt mode to produce interrupts at a fixed
 *      interval. You will want to read through the TCB operating principles,
 *      beginning p. 243 in the datasheet, and review the code that was provided
 *      in this week's tutorial.
 *      a) Disable interrupts globally by calling cli().
 *      b) Set the mode for TCB0 to periodic interrupt mode (TCB0.CTRLB).
 *      c) Set an appropriate interval using (TCB0.CCMP). The TCB counter will 
 *         increment by one for each CPU cycle (with the default clock selection),
 *         and an interrupt will be generated when the counter value reaches the 
 *         value in CCMP. The counter then resets and the process repeats.
 *      d) Enable interrupts by writing the appropriate bits to TCB0.INTCTRL.
 *      e) Enable TCB0 by writing to the appropriate bits in TCB0.CTRLA.
 *      f) Enable interrupts globally by calling the sei().
 *      
 *   2) Write an ISR to handle the TCB0 interrupts. In this ISR you can control
 *      the state of the PORT pin connected to the buzzer to synthesize a square
 *      wave of the appropriate frequency. Remember to acknowledge the interrupt
 *      by clearing the appropriate bits in TCB0.INTFLAGS at the end of your ISR.
 * 
 * TIP: A 50% duty cycle square wave can be synthesized by toggling a pin at a fixed
 *      interval; the interval will determine the frequency.
 * 
 * TIP: We've not included any header files at the top of this source file; you will 
 *      probably want to add you own #include directives. You may like to refer to 
 *      this weeks tutorial as a guide.
 * 
 * TIP: Because the buzzer will be interrupt driven, your main() function should be
 *      largely empty after any initialisation steps you need to do. However, because
 *      your code is running on an embedded system, main() should never return. Make 
 *      sure you trap your programme execution appropriately at the end of main().
 */ 

int main(void) {
    // Buzzer Set Up
    PORTB_OUTSET = PIN0_bm;
    PORTB_DIRSET = PIN0_bm;

    cli(); // Disable Interrupt Globally
    TCB0.CTRLB = TCB_CNTMODE_INT_gc; // Set Interrupt mode
    TCB0.CCMP = 404; // Set Interval
    TCB0.INTCTRL |= 0x1; // Enable Interrupts
    TCB0.CTRLA = TCB_CLKSEL_DIV1_gc | TCB_ENABLE_bm; // Enable TCB0
    sei(); // Enable Interrupts Globally

    while (1){} // End Loop
}

ISR(TCB0_INT_vect) {
    // Comment Line Below and Upload to Stop Buzzing
    PORTB_OUTTGL = PIN0_bm; // Toggle Buzzer

    TCB0.INTFLAGS |= 0x1; // Acknowledge Interrupt
}

// Write your code for Ex E7.0 above this line.
