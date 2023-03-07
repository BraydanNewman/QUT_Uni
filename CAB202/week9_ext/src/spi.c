#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>

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

void spi_write(uint8_t b){
    SPI0.DATA = b; 
}

ISR(SPI0_INT_vect){
    PORTA.OUTCLR = PIN1_bm;
    PORTA.OUTSET = PIN1_bm;

    SPI0.INTFLAGS = SPI_IE_bm;

    
}