#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *ptr;
    gets(ptr);
    printf("\n\n");
    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n\n");
    return 0;
}