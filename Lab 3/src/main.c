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

        transferring(inputBuffer, localBuffer);

        processing(localBuffer);

        transferring(localBuffer, outputBuffer);

        submitting(outputBuffer);

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
    inputBuffer[0] = get_value();
    inputBuffer[1] = get_value();
    for (int i = 0; i < inputBuffer[1]; i++) {
        inputBuffer[i + 2] = get_value();
    }
}

void transferring(int sourceBuffer[], int destinationBuffer[]) {
    for (int i = 0; i < sourceBuffer[1] + 2; i++) {
        destinationBuffer[i] = sourceBuffer[i];
    }
}

void processing(int localBuffer[]) {
    int tempStorage = 0;
    switch (localBuffer[0]) {
        case 0:
            localBuffer[2] = min(localBuffer);
            break;
        case 1:
            localBuffer[2] = max(localBuffer);
            break;
        case 2:
            localBuffer[2] = odds(localBuffer);
            break;
        case 3:
            localBuffer[2] = evens(localBuffer);
            break;
        case 4:
            tempStorage = min(localBuffer);
            localBuffer[3] = max(localBuffer);
            localBuffer[2] = tempStorage;
            break;
        case 5:
            tempStorage = odds(localBuffer);
            localBuffer[3] = evens(localBuffer);
            localBuffer[2] = tempStorage;
            break;
    }

    localBuffer[1] = (localBuffer[0] >= 4) + 1;
}

void submitting(int outputBuffer[]) {
    if (submit_results(outputBuffer)) {
        printf("The results were not correct.\n");
    } else {
        printf("The results were correct.\n");
    }
}

int min(int localBuffer[]) {
    int min = localBuffer[2];

    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] < min) {
            min = localBuffer[i + 2];
        }
    }

    return min;
}

int max(int localBuffer[]) {
    int max = localBuffer[2];

    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] > max) {
            max = localBuffer[i + 2];
        }
    }

    return max;
}

int odds(int localBuffer[]) {
    int odds = 0;

    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] % 2 == 1) {
            odds++;
        }
    }

    return odds;
}

int evens(int localBuffer[]) {
    int evens = 0;

    for (int i = 0; i < localBuffer[1]; i++) {
        if (localBuffer[i + 2] % 2 == 0) {
            evens++;
        }
    }

    return evens;
}

void printBuffer(int localBuffer[]) {
    for (int i = 0; i < localBuffer[1] + 1; i++) {
        printf("%d, ", localBuffer[i]);
    }
    printf("%d\n", localBuffer[localBuffer[1] + 1]);
}
