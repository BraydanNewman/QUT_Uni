#include <stdio.h>

// create struct with person1 variable
struct Person {
    char name[50];
    int citNo;
    float salary;
};

int main(int argc, char *argv[]) {
    struct Person person2, *ptr;
    ptr = &person2;

    printf("ENTER NAME: ");
    scanf("%s", person2.name);

    printf("ENTER citNo: ");
    scanf("%d", &ptr->citNo);

    printf("ENTER salary: ");
    scanf("%f", &ptr->salary);

    printf("\nName: %s", person2.name);
    printf("\nCitizenship No.: %d", person2.citNo);
    printf("\nSalary: %.2f", person2.salary);
    return 0;
}

