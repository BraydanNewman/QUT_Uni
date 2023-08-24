#include <stdio.h>
#include <string.h>
struct books {
char title[60];
char author[40];
int pubYear;
};
int main(int argc, char *argv[]) {
    struct books myBookOne;
    strcpy(myBookOne.title, "CAB403"); //to assign a value to a string use
    strcpy()
    function
    strcpy(myBookOne.author, "Tommy Smith");
    myBookOne.pubYear = 2023;
    struct books myBookTwo = {"Learning to Program", "Jason Smith", 2019};
}