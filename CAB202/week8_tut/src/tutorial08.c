// n11272031

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "qutyserial.h" 

/***
 * Tutorial 08: Introduction
 *
 * In this week's tutorial you will be working with the TCA0 and
 * ADC0 peripherals. You will use these to control the brightness
 * of the 7-segment display, produce a tone from the buzzer and
 * read the position of the potentiometer.
 * 
 * Interfacing with these hardware devices on the QUTy is a core
 * requirement for Assessment 2. Specifically you should refer to
 * Assessment 2, Functional Specifications, Parts A1 & B2.3, and 
 * Appendix 1: Sequence steps.
 */



/***
 * Ex 8.0
 * 
 * Write a function named "pwm_init" below which will configure
 * TCA0 to produce a 112 Hz, 17 % duty cycle PWM
 * output on net DISP EN. Your function should take no arguments
 * and return no values.
 */

void pwm_init(void) {
    cli();

    PORTB.DIRSET = PIN1_bm;
    PORTB.OUTSET = PIN1_bm;

    PORTB_OUTSET = PIN0_bm;
    PORTB_DIRSET = PIN0_bm;

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc;

    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;

    TCA0.SINGLE.PER = 29732;

    TCA0.SINGLE.CMP1 = 5054;

    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

    sei();
}

// Write your code for Ex 8.0 above this line.



/***
 * Ex 8.1
 * 
 * Write a function named "adc_init" below which will configure
 * ADC0 in 8-bit single conversion mode. The ADC should be 
 * configured to sample the voltage on the POT net, be put
 * in free-running mode, and started.
 */

void adc_init(void) {
    ADC0.CTRLA = ADC_ENABLE_bm;

    ADC0.CTRLB = ADC_PRESC_DIV2_gc;

    ADC0.CTRLC = (4 << ADC_TIMEBASE_gp) | ADC_REFSEL_VDD_gc;

    ADC0.CTRLE = 64;

    ADC0.CTRLF = ADC_FREERUN_bm;

    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;

    ADC0.COMMAND = ADC_MODE_SINGLE_8BIT_gc | ADC_START_IMMEDIATE_gc;
}


// Write your code for Ex 8.1 above this line.



int main(void) {

    uint8_t result;

    serial_init();
    PORTA.DIRSET = PIN1_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
    _delay_ms(3000); // 3 second delay

    /***
     * Ex 8.2
     * 
     * Call the two initialiasation functions you have written above
     * such that the TCA0 and ADC0 are enabled and operational.
     * 
     * On completion of this exercise the 7-segment display should show
     * an 8 on the RHS that is initially bright, but dims after 3 seconds,
     * and you should be able to test your ADC configuration via the serial
     * terminal.
     */
    
    pwm_init();
    adc_init();

    // Write your code for Ex 8.1 above this line.

    printf("Turn the potentiometer R1 fully counter-clockwise, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT; printf("Ex 8.2.0: result = 0x%02X, expected = 0x00\n", result);
    _delay_ms(1000); printf("Turn the potentiometer R1 fully clockwise, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT; printf("Ex 8.2.1: result = 0x%02X, expected = 0xFF\n", result);
    _delay_ms(1000); printf("Turn the potentiometer R1 to the half-way position, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT; printf("Ex 8.2.2: result = 0x%02X, expected = ~0x80\n", result);



    // main loop    
    while(1) {

        /***
         * Ex 8.3
         * 
         * Write code below such that the position of the potentiometer controls
         * the brightness of the 7-segment display. The display should be at 
         * maximum brightness when the potentiometer is turned fully counter-
         * clockwise, and zero brightness (i.e. off) when the pot is turned fully
         * clockwise.
         */

        TCA0_SINGLE_CMP1BUF = 29733UL - ((29733UL * (ADC0.RESULT + 1)) >> 8);

        // Write your code for Ex 8.3 above this line.



        /***
         * Ex 8.4
         * 
         * Write code below such that the buzzer produces a 112 Hz tone
         * when the potentiometer position is between 87.5% and 100% (where
         * 100% is fully CW and 0% is fully CCW). When the pot position is
         * outside of this range the buzzer should be silent. The buzzer should
         * be driven with a 50% duty cycle square wave.
         * 
         * TIP: You will probably also want to modify the code you wrote in 
         *      pwm_init() to achieve this functionality.
         */
        
        


        // Write your code for Ex 8.4 above this line.
        

    } // end main loop

} // end main()

