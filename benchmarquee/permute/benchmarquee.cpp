#include <vector>

#include "benchmarquee.h"

int benchmarkLength = 4;
std::vector<FUNC_TYPE *> benchmarquee {&sizefactorial, &stlpermutate, &recursivepermutate, &companionpermutate};

int inputSize;
std::vector<INPUT_TYPE> benchmarkInputs;

void initInputs() {
    inputSize = 3;
    std::vector<int> sizes = {5, 10, 11};
    benchmarkInputs = std::vector<INPUT_TYPE> {INPUT_TYPE(sizes[0]), INPUT_TYPE(sizes[1]), INPUT_TYPE(sizes[2])};

    for(int i=0; i<inputSize; ++i)
        for(int j=0; j<sizes[i]; ++j)
            benchmarkInputs[i][j] = sizes[i]-j;

    return;
}

