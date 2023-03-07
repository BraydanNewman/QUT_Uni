#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>


void tca0_init(){
    cli();

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;

    TCA0.SINGLE.PER = 29732;

    TCA0.SINGLE.CMP0 = 14866;
    TCA0.SINGLE.CMP1 = 20000;

    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm;

    sei();
}


void tcb0_init(void){
    cli();
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
    TCB0.CCMP = 10000;                   // Set interval for 1ms (10000 clocks @ 10 MHz)
    TCB0.INTCTRL = TCB_CAPT_bm;         // CAPT interrupt enable
    TCB0.CTRLA = TCB_ENABLE_bm;         // Enable
    sei();
}

void tcb1_init(void){
    cli();
    TCB1.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
    TCB1.CCMP = 65535;                   // Set interval for (100 ns * 2^17) (65535 clocks @ 10 MHz)
    TCB1.INTCTRL = TCB_CAPT_bm;         // CAPT interrupt enable
    TCB1.CTRLA = TCB_ENABLE_bm  | TCB_CLKSEL_DIV2_gc;         // Enable
    sei();
}


void spi_init(void){
    cli();
    SPI0.CTRLB = SPI_SSD_bm;
    SPI0.INTCTRL = SPI_IE_bm;
    PORTB.DIRSET = PIN1_bm;
    PORTB.OUTSET = PIN1_bm;
    PORTA.DIRSET = PIN1_bm;

    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc; // SPI pins on PC0-3
    PORTC.DIR |= (PIN0_bm | PIN2_bm); // Set SCK (PC0) and MOSI (PC2) as outputs
    SPI0.CTRLA = SPI_MASTER_bm; // Master, /4 prescaler, MSB first

    SPI0.CTRLA |= SPI_ENABLE_bm; // Enable

    sei();
}

void button_init(void) {
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
}

void adc_init(){
    ADC0.CTRLA = ADC_ENABLE_bm;
    ADC0.CTRLB = ADC_PRESC_DIV2_gc;
    ADC0.CTRLC = (4 << ADC_TIMEBASE_gp) | ADC_REFSEL_VDD_gc;
    ADC0.CTRLE = 64;
    ADC0.CTRLF = ADC_FREERUN_bm;
    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;
    ADC0.COMMAND = ADC_MODE_SINGLE_8BIT_gc | ADC_START_IMMEDIATE_gc;
}