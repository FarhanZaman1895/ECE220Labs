#ifndef LAB04_BUFFER_H
#define LAB04_BUFFER_H

#define Input_Local_BUFFER__SIZE 64
#define Output_BUFFER_SIZE 4


// this function fills input buffer using values
// obtained with the function get_value()
int reading();

// this function transfers data between two buffers
// it is used to transfer data from input buffer to local buffer
void transferringTOlocal(int[]);

// this function performs processing of data in local buffer
// and put results back into local buffer
void processing(int[]);

// this function transfers data between two buffers
// it is used to transfer data from local buffer to output buffer
void transferringFROMlocal(int[]);

// this function submit the results stored
// in output buffer for validation
void submitting(int*);

// Operation Functions
int max(int*);
int min(int*);
int odds(int*);
int evens(int*);

// Buffer Utility Functions
void printBuffer(int*);
void clearBuffer(int*);

#endif
