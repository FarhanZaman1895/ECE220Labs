#define MIN     0
#define MAX     1
#define ODD     2
#define EVEN    3
#define MINMAX  4
#define ODDEVEN 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "memory.h"
#include "buffer.h"

int *inputBuffer = NULL;
int *outputBuffer = NULL;

int reading() {
    // Variables
    int op_ID;
    int no_data_points;

    // Check if the operation id is -1 to end program
    op_ID = get_value();
    if (op_ID == -1) {
        printf("-1 encountered, ending program\n");
        return -1;
    }

    // Get the number of data points
    printf("\nStart new test case:\n");
    no_data_points = get_value();

    // Allocate the input buffer to heap
    inputBuffer = (int*) my_malloc((no_data_points + 2) * sizeof(int));

    inputBuffer[0] = op_ID;
    inputBuffer[1] = no_data_points;

    // Uses the length of the data to know how many data points to transfer to the input buffer
    for (int i = 0; i < inputBuffer[1]; i++) {
        inputBuffer[i + 2] = get_value();
    }

    return inputBuffer[1];
}

void transferringTOlocal(int* localBuffer) {
    // Copy input buffer to local buffer
    for (int i = 0; i < inputBuffer[1] + 2; i++) {
        localBuffer[i] = inputBuffer[i];
    }

    printf("\nInput Buffer: ");
    printBuffer(inputBuffer);

    // Free input buffer
    my_free(inputBuffer);
}

void processing(int* localBuffer) {
    // A temporary storage variable for the cases MINMAX and ODDEVEN
    int tempStorage = 0;

    // Switch statement with the operation IDs to determine
    // which operation will be used
    switch (localBuffer[0]) {
        case MIN:
            localBuffer[2] = min(localBuffer);
            break;
        case MAX:
            localBuffer[2] = max(localBuffer);
            break;
        case ODD:
            localBuffer[2] = odds(localBuffer);
            break;
        case EVEN:
            localBuffer[2] = evens(localBuffer);
            break;
        case MINMAX:
            tempStorage = min(localBuffer);
            localBuffer[3] = max(localBuffer);
            localBuffer[2] = tempStorage;
            break;
        case ODDEVEN:
            tempStorage = odds(localBuffer);
            localBuffer[3] = evens(localBuffer);
            localBuffer[2] = tempStorage;
            break;
    }

    // This determines the length of the output, since the condition "true" 
    // in C evaluates to 1, we can say that if the operation ID is 4 or 5,
    // add 1 to the length of the output so it will be 2 instead of 1
    localBuffer[1] = (localBuffer[0] >= 4) + 1;

    printf("Local Buffer: ");
    printBuffer(localBuffer);
}

void transferringFROMlocal(int* localBuffer) {
    // Allocate output buffer to heap
    outputBuffer = (int*) my_malloc((localBuffer[1] + 2) * sizeof(int));

    // Copy over output buffer from local
    for (int i = 0; i < localBuffer[1] + 2; i++) {
        outputBuffer[i] = localBuffer[i];
    }

    printf("Output Buffer: ");
    printBuffer(outputBuffer);
}

void submitting() {
    // Since submit_results returns a 1 if the answers were incorrect,
    // if the result is true, it will print that the answer was incorrect
    // and otherwise print correct
    if (submit_results(outputBuffer)) {
        printf("The results were not correct.\n");
    } else {
        printf("The results were correct.\n");
    }

    // Free output buffer
    my_free(outputBuffer);
}

// Operation Functions
int min(int* buffer) {
    // Sets the initial minimum to the first data element
    int min = buffer[2];

    // For all the data points, if that value is less than the current min,
    // it will replace the old min with new min
    for (int i = 0; i < buffer[1]; i++) {
        if (buffer[i + 2] < min) {
            min = buffer[i + 2];
        }
    }

    return min;
}

int max(int* buffer) {
    // Sets the initial maximum to the first data element
    int max = buffer[2];

    // For all the data points, if that value is less than the current max,
    // it will replace the old max with new max
    for (int i = 0; i < buffer[1]; i++) {
        if (buffer[i + 2] > max) {
            max = buffer[i + 2];
        }
    }

    return max;
}

int odds(int* buffer) {
    // Initialize a counter for the number of odds starting at 0
    int odds = 0;

    // Goes through all the data points, if the value / 2 leaves a remainder
    // of 1, it is odd (this is done by the modulus operator, %)
    for (int i = 0; i < buffer[1]; i++) {
        if (buffer[i + 2] % 2 == 1) {
            odds++;
        }
    }

    return odds;
}

int evens(int* buffer) {
    // Initialize a counter for the number of evens starting at 0
    int evens = 0;

    // Goes through all the data points, if the value / 2 leaves a remainder
    // of 0, it is even (this is done by the modulus operator, %)
    for (int i = 0; i < buffer[1]; i++) {
        if (buffer[i + 2] % 2 == 0) {
            evens++;
        }
    }

    return evens;
}

// Print a given buffer
void printBuffer(int* buffer) {
    // Goes through the buffer and prints each element, using the second
    // element of the buffer to determine how many values to print
    for (int i = 0; i < buffer[1] + 1; i++) {
        printf("%d, ", buffer[i]);
    }
    printf("%d\n", buffer[buffer[1] + 1]);
}

// Clear a given buffer
void clearBuffer(int* buffer) {
    memset(buffer, 0, sizeof(int) * (buffer[1] + 2));
}
