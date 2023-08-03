#include <stdio.h>

#define arrayLength(array) (sizeof((array))/sizeof((array)[0]))

int main(int argc, char *argv[]) {
    int arrayOne[] = {15, 22, 18, 34, 1, 10}; // 6 elements
    float arrayTwo[] = {12.45, 18.34, 20.55, 13.12, 88.62, 100.12, 64.23, 99.99,
                        121.23}; // 9 elements
    char arrayThree[] = {'m', 'a', 'c', 'r', 'o', 'd', 'e', 'f', 'i', 'n', 'i',
                         't', 'i', 'o', 'n'};// 15 elements
    int lengthArrayOne = arrayLength(arrayOne);
    int lengthArrayTwo = arrayLength(arrayTwo);
    int lengthArrayThree = arrayLength(arrayThree);
    printf("\n\nThe length of arrayOne = %d\n"
           "The length of arrayTwo = %d\n"
           "The length of arrayThree = %d\n\n",
           lengthArrayOne, lengthArrayTwo, lengthArrayThree);
    return 0;
}