#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "benchmarquee.h"

#define MILLIS_PER_SEC 1000

int main(int argc, char *argv[]) {
    int funcNum=-1;
    if(argc>1)
        funcNum = atoi(argv[1]);

    int inputNum=-1;
    if(argc>2)
        inputNum = atoi(argv[2]);

    clock_t start;
    clock_t end;

    initInputs();
    for(int j=0; j<inputSize; ++j) {

        if(j!=inputNum && inputNum!=-1)
            continue;

        RETURN_TYPE correct;
        if(funcNum<=0) {
            start = clock();
            correct = benchmarquee[0](benchmarkInputs[j]);
            end = clock();
            printf("benchmark %d input %d took %fms\n", 0, j, (double)(end-start)/CLOCKS_PER_SEC*MILLIS_PER_SEC);
        }

        for(int i=1; i<benchmarkLength; ++i) {
 
            if(i!=funcNum && funcNum!=-1)
                continue;

            start = clock();
            RETURN_TYPE output = benchmarquee[i](benchmarkInputs[j]);
            end = clock();
            printf("benchmark %d input %d took %fms\n", i, j, (double)(end-start)/CLOCKS_PER_SEC*MILLIS_PER_SEC);
 
            if(funcNum==-1)
                assert(checkOutput(correct, output));

            freeOutput(output);
        }

        printf("\n");

        if(funcNum<=0)
            freeOutput(correct);
    }
    freeInputs();
    return 0;
}
