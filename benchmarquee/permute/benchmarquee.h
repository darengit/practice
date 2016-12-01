#ifndef BENCHMARQEE_H
#define BENCHMARQEE_H

#include <vector>

typedef std::vector<int> INPUT_TYPE;
typedef int RETURN_TYPE;
typedef RETURN_TYPE FUNC_TYPE(INPUT_TYPE &);

FUNC_TYPE sizefactorial;
FUNC_TYPE recursivepermutate;
FUNC_TYPE companionpermutate;
FUNC_TYPE stlpermutate;

extern int benchmarkLength;
extern std::vector<FUNC_TYPE *> benchmarquee;

extern int inputSize;
extern std::vector<INPUT_TYPE> benchmarkInputs;

void initInputs();
inline void freeInputs() { return; }

inline void freeOutput(RETURN_TYPE) { return; }

inline bool checkOutput(RETURN_TYPE correct, RETURN_TYPE output) { return correct == output; }

#endif
