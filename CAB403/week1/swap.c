#include <stdio.h>

void swap(int *ptrA, int *ptrB);

int main(){
    int a = 10, b = 20;
    swap(&a, &b);
    printf("%d", a);
    return 0;
}

void swap(int *ptrA, int *ptrB) {
    int temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;
}