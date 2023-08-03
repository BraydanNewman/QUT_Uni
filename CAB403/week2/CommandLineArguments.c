#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("\nThe number of command line arguments is %d\n", argc);
    printf("\nThe name of the program is %s\n", argv[0]);
    for(int i = 1; i <= argc; ++i) {
        printf("\nArgument %d is %s", i, argv[i - 1]);
    }
    return 0;
}