#ifndef BENCHMARQEE_H
#define BENCHMARQEE_H

#include <stdbool.h>

typedef struct {int *a; int l;} INPUT_TYPE;
typedef int RETURN_TYPE;
typedef RETURN_TYPE FUNC_TYPE(INPUT_TYPE);

FUNC_TYPE holdwater2pass;
FUNC_TYPE holdwater1pass;

extern int benchmarkLength;
extern FUNC_TYPE *benchmarquee[];

extern int inputSize;
extern INPUT_TYPE *benchmarkInputs;

void initInputs();
void freeInputs();

inline void freeOutput(RETURN_TYPE) { return; }

inline bool checkOutput(RETURN_TYPE correct, RETURN_TYPE output) {
    return correct == output;
}

#endif
