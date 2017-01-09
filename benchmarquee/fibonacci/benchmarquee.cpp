#include <stdlib.h>

#include "benchmarquee.h"

int benchmarkLength = 2;
FUNC_TYPE *benchmarquee[2] = {&linearfibonacci, &logfibonacci};

int inputSize;
INPUT_TYPE *benchmarkInputs;

void initInputs() {
    inputSize = 3;
    benchmarkInputs = (INPUT_TYPE *)malloc(inputSize*sizeof(INPUT_TYPE));

    benchmarkInputs[0] = 10;
    benchmarkInputs[1] = 1000;
    benchmarkInputs[2] = 1000000;

    return;
}

void freeInputs() {
    free(benchmarkInputs);
    return;
}
