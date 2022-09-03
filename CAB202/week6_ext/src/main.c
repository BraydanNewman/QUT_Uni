#include <stdint.h>
#include <stdio.h>

#include "qutyio.h"
#include "extension06.h"

// In this file you can write any test code you like to test
// your functions, however, this entire file will be replaced
// by our code when we test your functions. Your solutions
// to extension06 should be contained in "extension06.c" and
// prototype functions defined in "extension06.h".
// 
// We have provided below some helper code that might be of use
// in testing your functions. Feel free to modify anything
// in this file.

// set all elements in a matrix to 0
void matrix_zero(int16_t* matrix, uint8_t elements) {
    for (uint8_t i = 0; i < elements; i++) {
        *(matrix+i) = 0;
    }
}

// print a matrix via the serial interface
void matrix_print(int16_t* matrix, uint8_t* dim) {
    for (uint8_t i = 0; i < dim[0]; i++) {
        for (uint8_t j = 0; j < dim[1]; j++) {
            printf("% 6d ", matrix[i*dim[1]+j]);
        }
        printf("\n");
    }
}

// programme entry
int main(void) {

    serial_init(); // initialise serial interface

    // define a matrix A
    int16_t a[2][2] = {
        {1, 2},
        {3, 4}
    };

    // define a matrix B
    int16_t b[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // define a matrix I
    int16_t identity[2][2] = {
        {1, 0},
        {0, 1}
    };

    // define a result matrix
    int16_t result[6];
    
    // define some scalars
    int16_t multiplicand = 2;
    int16_t addend = 2;

    // define some dimensions
    uint8_t dim_2x2[2] = {2, 2};
    uint8_t dim_2x3[2] = {2, 3};

    // clear result matrix
    matrix_zero(result, 6);

    // wait for keypress
    while(!serial_bytes_available());

    // print matrix A
    printf("A =\n");
    matrix_print(a, dim_2x2);

    // print matrix B
    printf("B =\n");
    matrix_print(b, dim_2x3);

    printf("\n");
    matrix_zero(result, 6);
    matrix_add(a, dim_2x2, addend, result);
    matrix_print(result, dim_2x2);

    printf("\n");
    matrix_zero(result, 6);
    matrix_sum(a, dim_2x2, identity, result);
    matrix_print(result, dim_2x2);

    printf("\n");
    matrix_zero(result, 6);
    matrix_scale(a, dim_2x2, multiplicand, result);
    matrix_print(result, dim_2x2);

    printf("\n");
    matrix_zero(result, 6);
    matrix_mul(identity, dim_2x2, a, dim_2x2, result);
    matrix_print(result, dim_2x2);

    printf("\n");
    matrix_zero(result, 6);
    matrix_mul(identity, dim_2x2, b, dim_2x3, result);
    matrix_print(result, dim_2x3);

    while (1); // Trap programme execution here    
}