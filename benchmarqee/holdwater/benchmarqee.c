#include <stdlib.h>

#include "benchmarqee.h"

int benchmarkLength = 2;
FUNC_TYPE *benchmarqee[2] = {&holdwater2pass, &holdwater1pass};

int inputSize;
INPUT_TYPE *benchmarkInputs;

void initInputs() {
    inputSize = 3;
    benchmarkInputs = (INPUT_TYPE *)malloc(inputSize*sizeof(INPUT_TYPE));

    int sizes[3] = {1000, 100000, 10000000};

    for(int i=0; i<inputSize; ++i) {
        benchmarkInputs[i].l = sizes[i];
        benchmarkInputs[i].a = (int *)malloc(sizes[i]*sizeof(int));
        for(int j=0; j<benchmarkInputs[0].l; ++j)
            benchmarkInputs[i].a[j] = rand()%1024;
    }
    return;
}

void freeInputs() {
    for(int i=0; i<inputSize; ++i)
        free(benchmarkInputs[i].a);
    free(benchmarkInputs);
}

void freeOutput(RETURN_TYPE output) {
    return;
}
