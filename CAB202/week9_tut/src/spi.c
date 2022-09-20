#include <avr/io.h>
#include <avr/interrupt.h>

void spi_init(void) {
    cli();
    SPI0.CTRLB = SPI_SSD_bm;
    SPI0.INTCTRL |= SPI_IE_bm;


    PORTB.DIRSET = PIN1;
    PORTB.OUTSET = PIN1;
    PORTA.DIRSET = PIN1;


    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;
    PORTC.DIR |= (PIN0_bm | PIN2_bm);

    SPI0.CTRLA = SPI_MASTER_bm;
    SPI0.CTRLA |= SPI_ENABLE_bm;

    sei();
}


void spi_write(uint8_t data) {
    SPI0.DATA = data;
}

ISR(SPI0_INT_vect) {
    PORTA.OUTCLR = PIN1;
    PORTA.OUTSET = PIN1;

}
