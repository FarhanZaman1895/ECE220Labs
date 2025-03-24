#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "memory.h"

//#define _CRT_SECURE_NO_WARNINGS

int main(void) {

    int dataSize;
    int *localBuffer = NULL;

    dataSize = reading();

    while (dataSize !=-1) {

        localBuffer = (int *)my_malloc((dataSize + 2) * sizeof(int));

        transferringTOlocal(localBuffer);
        processing(localBuffer);
        transferringFROMlocal(localBuffer);

        my_free(localBuffer);

        submitting();

        dataSize = reading();
    }
    return 0;
}






