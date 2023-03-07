#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void uart_init(void);
uint8_t uart_getc(void);
void uart_putc(uint8_t c);
void uart_puts(char* string);