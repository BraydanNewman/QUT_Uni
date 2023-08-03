#include <stdio.h>
#include <stdlib.h>

//create object like Macros for Exit Values

//Add function prototypes based on your implementation
void enterValuesIntoArr(); //A function to permit the user to enter values which are stored in the array
void printOutArray();  //Simple function to print out the values in an array
int askUserToIncreaseArraySize(); //Function to prompt user to enter the new increased size of the array
void enterValuesIntoExistingArray(); //Function to add values into an existing array that is partially populated


int main(int argc, char *argv[]) {
    int numElements = 0;
    int *arrOnePtr;
    printf("Enter Number of elements in array:");
    scanf("%d", &numElements);
    arrOnePtr = malloc(numElements * sizeof(int));
    if(arrOnePtr == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    enterValuesIntoArr(arrOnePtr, numElements);
    printOutArray(arrOnePtr, numElements);
    int newSize = askUserToIncreaseArraySize(arrOnePtr, numElements);
    enterValuesIntoExistingArray(arrOnePtr, newSize, numElements);
    numElements = newSize;
    printOutArray(arrOnePtr, numElements);
    return 0;
}

// Function to add additional elements to a pre-existing array - the inital values stored in the array are preserved
void enterValuesIntoExistingArray(int *ptr, int newLength, int oriLength) {
    int element;
    for (int i = oriLength; i < newLength; ++i) {
        printf("Enter Value %d in array:", oriLength + i);
        scanf("%d", &element);
        ptr[i] = element;
    }
}

int askUserToIncreaseArraySize(int *ptr, int length) {
    int additionalElements = 0;
    printf("How many additional values will be required in the resized array:");
    scanf("%d", &additionalElements);
    int* newPtr = realloc(ptr, (length + additionalElements) * sizeof(int));
    if(newPtr == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    ptr = newPtr;
    return length + additionalElements;
}

//Function to add elements into an array	
void enterValuesIntoArr(int *ptr, int length) {
    int element;
    for (int i = 0; i < length; ++i) {
        printf("Enter Value %d in array:", i + 1);
        scanf("%d", &element);
        ptr[i] = element;
    }
}

//Function to print out the values in the array
void printOutArray(int *ptr, int length) {
    printf("\n");
    for (int i = 0; i < length; ++i) {
        printf("Element %d is %d\n", i, ptr[i]);
    }
}

		
	
