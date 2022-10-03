#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "qutyserial.h"
#include "sequence.h"

static const unsigned char base64_table[65] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

uint32_t state = 0x11272031;

void descramble(uint8_t* a) {
    *a ^= state;
    uint8_t lsb_bit = state & 0x1;
    state = state >> 1;
    if (lsb_bit) {
        state ^= 0xB4BCD35C;
    }
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

void test(uint8_t* a) {
    printf("%d\n", *a);
}


int main(void) {
    serial_init();

    printf("Start1\n");
    uint8_t B64_RESULT[12282];
    for (uint16_t k = 0; k < strlen(TEST_BASE64); k++) {
        char a = pgm_read_byte_near(TEST_BASE64 + (k*4));
        char b = pgm_read_byte_near(TEST_BASE64 + (k*4) + 1);
        char c = pgm_read_byte_near(TEST_BASE64 + (k*4) + 2);
        char d = pgm_read_byte_near(TEST_BASE64 + (k*4) + 3);

        uint32_t hex3 = decode(a, b, c, d);

        uint8_t B64byte1 = hex3 >> 16;
        uint8_t B64byte2 = hex3 >> 8;
        uint8_t B64byte3 = hex3;

        B64_RESULT[(k*3)] = B64byte1;
        B64_RESULT[(k*3) + 1] = B64byte2;
        B64_RESULT[(k*3) + 2] = B64byte3;
    }

    printf("Start2\n");
    for (uint16_t i = 0; i < 10; i++) test(&B64_RESULT[i]);

//    printf("Start3\n");
//    for (uint16_t i = 0; i < sizeof(B64_RESULT); i = i + 3) {
//        printf("%X\t", B64_RESULT[i]);
//        printf("%X\t", B64_RESULT[i + 1]);
//        printf("%X\t", B64_RESULT[i + 2]);
//        printf("\n");
//    }

//    printf("%X\n", B64_RESULT[0]);
//    printf("%X\n", B64_RESULT[1]);
//    printf("%X\n", B64_RESULT[2]);
//    printf("\n");
//    printf("%X\n", B64_RESULT[3]);
//    printf("%X\n", B64_RESULT[4]);
//    printf("%X\n", B64_RESULT[5]);
//    printf("\n");


    while (1) {}

//    for (uint16_t i = 0; i < sizeof(B64_RESULT); i = i + 3) {
//        printf("0x%X ", B64_RESULT[i]);
//        printf("0x%X ", B64_RESULT[i + 1]);
//        printf("0x%X ", B64_RESULT[i + 2]);
//        printf("\n");
//    }


}
