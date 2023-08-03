#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printString(char *string);

int main(int argc, char *argv[]) {
    printf("Enter String: ");
    char *myString;
    gets(myString);
    printString(myString);
    return (0);
}

void printString(char *string) {
    printf("String Out: %s", string);
}