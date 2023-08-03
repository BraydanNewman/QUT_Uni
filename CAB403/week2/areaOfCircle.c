#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    float userInput = 0;
    for (int i = 0; i < 5; i++) {
        printf("\nEnter the radius of circle number %d- ", i + 1);
        scanf("%f", &userInput);
        float areaOfCircle = M_PI * userInput * userInput;
        printf("Area Of Circle is %.2f\n", areaOfCircle);
    }
    return 0;
}