#include <stdio.h>

int main() {
    int num;
    int sum = 0;
    do {
        printf("Sum so far: %d\n", sum);
        printf("Enter number: ");
        scanf("%d", &num);
        sum = sum + num;
    } while (num >= 0);
    printf("FINAL TOTAL: %d\n", sum);
    return 0;
} 
