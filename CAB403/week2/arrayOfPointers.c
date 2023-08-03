#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define arrayLength(array) (sizeof((array))/sizeof((array)[0]))

void printStringList(char *list, int length);


int main(int argc, char *argv[]) {
    char *cityPtr[] = {"Toowong", "Chermside", "Taringa", "Indooroopilly"};
    printStringList(*cityPtr, arrayLength(cityPtr));
    return 0;
}

void printStringList(char *list, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%s\n", list);
        list = list + strlen(list) + 1;
    }
}