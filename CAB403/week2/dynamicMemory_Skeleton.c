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
    int *arrOnePtr; //There requirement for this program is a single array - there is no need to create a second array
    // ask user to determine the array size
    printf("Enter Number of elements in array:");
    scanf("%d", &numElements);

    //allocate sufficient memory and check memory allocation is successful
    arrOnePtr = malloc(numElements * sizeof(int));
    if(arrOnePtr == NULL) {
        free(arrOnePtr);
        return 1;
    }

    // Enter values into the array and then print out the array values
    enterValuesIntoArr(arrOnePtr, numElements);

    printOutArray(arrOnePtr, numElements);
    //Call function to prompt user to increase array size
    int newSize = askUserToIncreaseArraySize(arrOnePtr, numElements);
    //Populate the resized array with additional values
    enterValuesIntoExistingArray(arrOnePtr, newSize, numElements);
    numElements = newSize;
    //print out array - should contain values from initial creation and values entered after array is resized.
    printOutArray(arrOnePtr, numElements);
    return 0;
}

// Function to add additional elements to a pre-existing array - the inital values stored in the array are preserved
void enterValuesIntoExistingArray(int *ptr, int newLength, int oriLength) {
    int element;
    for (int i = 0; i < newLength - oriLength; ++i) {
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
        free(newPtr);
        free(ptr);
        return 1;
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

		
	
