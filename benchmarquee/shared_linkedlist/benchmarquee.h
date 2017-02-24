#ifndef BENCHMARQEE_H
#define BENCHMARQEE_H

typedef int INPUT_TYPE;
typedef int RETURN_TYPE;
typedef RETURN_TYPE FUNC_TYPE(INPUT_TYPE);

FUNC_TYPE shared_linkedlist;
FUNC_TYPE dynamic_linkedlist;

extern int benchmarkLength;
extern FUNC_TYPE *benchmarquee[];

extern int inputSize;
extern INPUT_TYPE *benchmarkInputs;

void initInputs();
void freeInputs();

inline void freeOutput(RETURN_TYPE) { return; }

inline bool checkOutput(RETURN_TYPE correct, RETURN_TYPE output) {
    return true;
}

#endif
