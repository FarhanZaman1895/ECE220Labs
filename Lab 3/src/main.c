#include <stdio.h>
#include "io.h"

//#define _CRT_SECURE_NO_WARNINGS

#define BUFFER_SIZE 64

#define MIN     0
#define MAX     1
#define ODD     2
#define EVEN    3
#define MINMAX  4
#define ODDEVEN 5

// prototypes of your functions you need to write

// this function fills input buffer using values
// obtained with the function get_value()
void reading(int[]);

// this function performs processing of data in local buffer
// and put results back into local buffer
void processing(int[]);

// this function transfers data between two buffers
// it is used to transfer data from input buffer to local buffer
// and to transfer data from local buffer to output buffer
void transferring(int[], int[]);

// this function submit the results stored
// in output buffer for validation
void submitting(int[]);

// Functions for calculating max, min, # of odds, # of evens
int min(int localBuffer[]);
int max(int localBuffer[]);
int odds(int localBuffer[]);
int evens(int localBuffer[]);

void printBuffer(int localBuffer[]);

// two functions provided to you (defined in io.h and io.c) are:
// int get_value(void);
//       this function generates a single value
//       you use it to obtain this value and put it into an input buffer
// int submit_result(int[]);
//       you use this function to submit the data processing results
//       for validation (your results are checked inside this function)


int main(void) {
    
    int inputBuffer [BUFFER_SIZE]   = {0};
    int localBuffer [BUFFER_SIZE]   = {0};
    int outputBuffer [BUFFER_SIZE]  = {0};

    reading(inputBuffer);

    while (inputBuffer[0] != -1) {

        // Processes the input data
        transferring(inputBuffer, localBuffer);
        processing(localBuffer);
        transferring(localBuffer, outputBuffer);
        submitting(outputBuffer);

        // Prints the input, local and output buffers after the trial runs
        printf("Input Buffer: ");
        printBuffer(inputBuffer);
        printf("Local Buffer: ");
        printBuffer(localBuffer);
        printf("Output Buffer: ");
        printBuffer(outputBuffer);

        // set all buffers to 0
        for (int i = 0; i < BUFFER_SIZE; i++) {
            inputBuffer[i]  = 0;
            localBuffer[i]  = 0;
            outputBuffer[i] = 0;
        }

        reading(inputBuffer);
    }

    return 0;
}

void reading(int inputBuffer[]) {
    // First gets the first two values from get_value and puts them into the buffer
    // The second value is length of the data
    inputBuffer[0] = get_value();
    inputBuffer[1] = get_value();

    // Uses the length of the data to know how many data points to transfer to the input buffer
    for (int i = 0; i < inputBuffer[1]; i++) {
        inputBuffer[i + 2] = get_value();
    }
}

void transferring(int sourceBuffer[], int destinationBuffer[]) {
    // Copies over the contents of the source buffer to destination buffer
    // again uses the second value of the source buffer, which is the 
    // length of data to know how many data points to transfer
    for (int i = 0; i < sourceBuffer[1] + 2; i++) {
        destinationBuffer[i] = sourceBuffer[i];
    }
}

void processing(int localBuffer[]) {
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
}

void submitting(int outputBuffer[]) {
    // Since submit_results returns a 1 if the answers were incorrect,
    // if the result is true, it will print that the answer was incorrect
    // and otherwise print correct
    if (submit_results(outputBuffer)) {
        printf("The results were not correct.\n");
    } else {
        printf("The results were correct.\n");
    }
}

int min(int localBuffer[]) {
    // Sets the initial minimum to the first data element
    int min = localBuffer[2];

    // For all the data points, if that value is less than the current min,
    // it will replace the old min with new min
    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] < min) {
            min = localBuffer[i + 2];
        }
    }

    return min;
}

int max(int localBuffer[]) {
    // Sets the initial maximum to the first data element
    int max = localBuffer[2];

    // For all the data points, if that value is less than the current max,
    // it will replace the old max with new max
    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] > max) {
            max = localBuffer[i + 2];
        }
    }

    return max;
}

int odds(int localBuffer[]) {
    // Initialize a counter for the number of odds starting at 0
    int odds = 0;

    // Goes through all the data points, if the value / 2 leaves a remainder
    // of 1, it is odd (this is done by the modulus operator, %)
    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] % 2 == 1) {
            odds++;
        }
    }

    return odds;
}

int evens(int localBuffer[]) {
    // Initialize a counter for the number of evens starting at 0
    int evens = 0;

    // Goes through all the data points, if the value / 2 leaves a remainder
    // of 0, it is even (this is done by the modulus operator, %)
    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] % 2 == 0) {
            evens++;
        }
    }

    return evens;
}

void printBuffer(int localBuffer[]) {
    // Goes through the buffer and prints each element, using the second
    // element of the buffer to determine how many values to print
    for (int i = 0; i < localBuffer[1] + 1; i++) {
        printf("%d, ", localBuffer[i]);
    }
    printf("%d\n", localBuffer[localBuffer[1] + 1]);
}
