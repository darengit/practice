#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "benchmarquee.h"

#define MILLIS_PER_SEC 1000

int main(int argc, char *argv[]) {
    int inputNum = (argc>1?atoi(argv[1]):-1);
    int funcNum = (argc>2?atoi(argv[2]):-1);

    clock_t start;
    clock_t end;

    initInputs();
    for(int j=0; j<inputSize; ++j) {
        if(j!=inputNum && inputNum!=-1)
            continue;


        RETURN_TYPE correct;
        for(int i=0; i<benchmarkLength; ++i) {
            if(i!=funcNum && funcNum!=-1)
                continue;

            start = clock();
            RETURN_TYPE output = benchmarquee[i](benchmarkInputs[j]);
            end = clock();
            printf("input %d benchmark %d took %fms\n", j, i, (double)(end-start)/CLOCKS_PER_SEC*MILLIS_PER_SEC);

            if(inputNum==-1 && funcNum==-1) {
                if(i==0)
                    correct = output;
                else
                    checkOutput(correct, output);
            }
 
            freeOutput(output);
        }

        printf("\n");
        if(funcNum<=0)
            freeOutput(correct);
    }
    freeInputs();
    return 0;
}
