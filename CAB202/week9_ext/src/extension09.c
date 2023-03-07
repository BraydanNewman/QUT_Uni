#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "spi.h"
#include "uart.h"

/***
 * Ex E9.0
 * 
 * Your task is to write a programme which:
 *   1) On initialisation, turns off the 7-segment display, AND
 *   2) On receipt of a character via the UART, displays the value
 *      of the character on the 7-segment display as two hexadecimal
 *      digits. The display should be updated every time a new
 *      character is received.
 * 
 * NOTE: The UART should be configured for 9600 baud, 8N1
 *       (8 data bits, no parity bit, 1 stop bit).
 * 
 * Examples:
 *   On receipt of  'a' the display should show "61"
 *   On receipt of  'A' the display should show "41"
 *   On receipt of '\n' the display should show "0A"     
 */

volatile uint8_t highNibble;
volatile uint8_t lowNibble;

uint8_t numToMask[16] = {
        0b00001000,
        0b01101011,
        0b01000100,
        0b01000001,
        0b00100011,
        0b00010001,
        0b00110000,
        0b01001011,
        0b00000000,
        0b00000011,
        0b00000010,
        0b00110000,
        0b00011100,
        0b01100000,
        0b00010100,
        0b00010110
};

int main(void) {
    spi_init();       // Initialise SPI
    uart_init();
    timer_init();

    spi_write(0xFF);  // Clear display

    while(1){
        // wait for char
        uint8_t c = uart_getc();

        highNibble = numToMask[(c & 0xF)];
        lowNibble = numToMask[(c >> 4)];
    }

} // end main()
