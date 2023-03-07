#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>


static const unsigned char base64_table[65] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


volatile uint32_t state = 0x11272031;


void next() {
    uint8_t lsb_bit = state & 0x1;
    state = state >> 1;
    if (lsb_bit) {
        state ^= 0xB4BCD35C;
    }
}

void descramble(volatile uint8_t* a) {
    *a ^= state;
    next();
}


uint8_t indexInTable(const char a) {
    for (uint8_t i = 0; i < sizeof(base64_table); i++) {
        if (base64_table[i] == a) {
            return i;
        }
    }
    return -1;
}

uint32_t decode(const char a, const char b, const char c, const char d) {
    uint8_t aIndex = indexInTable(a);
    uint8_t bIndex = indexInTable(b);
    uint8_t cIndex = indexInTable(c);
    uint8_t dIndex = indexInTable(d);

    uint32_t total = 0;
    total |= aIndex;
    total = (total << 6) | bIndex;
    total = (total << 6) | cIndex;
    return (total << 6) | dIndex;
}


