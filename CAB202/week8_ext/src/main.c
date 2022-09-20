#include <avr/io.h>
#include <stdio.h>

#include "qutyserial.h" 

// Prototype for the function you will implement in extension08.c
void init(void);    

int main(void) {

    serial_init();

    // Call init() and check code returns
    printf("Ex E8.0: Calling init()...");
    init();
    printf("DONE.\n");

    while(1); // Loop indefinitely
}