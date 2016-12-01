#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "benchmarquee.h"

#define MILLIS_PER_SEC 1000

int main() {
    clock_t start;
    clock_t end;

    initInputs();
    for(int j=0; j<inputSize; ++j) {

        start = clock();
        RETURN_TYPE correct = benchmarquee[0](benchmarkInputs[j]);
        end = clock();
        printf("benchmark %d input %d took %fms\n", 0, j, (double)(end-start)/CLOCKS_PER_SEC*MILLIS_PER_SEC);

        for(int i=1; i<benchmarkLength; ++i) {


            start = clock();
            RETURN_TYPE output = benchmarquee[i](benchmarkInputs[j]);
            end = clock();
            printf("benchmark %d input %d took %fms\n", i, j, (double)(end-start)/CLOCKS_PER_SEC*MILLIS_PER_SEC);

            assert(checkOutput(correct, output));

            freeOutput(output);



        }

        printf("\n");

        freeOutput(correct);
    }
    freeInputs();
    return 0;
}
