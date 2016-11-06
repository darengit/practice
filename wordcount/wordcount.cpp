#include <stdio.h>
#include <time.h>
#include <thread>
#include "string8.h"
#include "wordreader.h"
#include "tester.h"

struct TestEntry {
    void (*testFunc)(WordReader *reader);
    const char *name;
};

TestEntry testEntries[] = {
    { testLinearSearch, "linear search" },
    { testMap, "std::map" },
    { testUnorderedMap, "std::unordered_map" },
};

void tester(TestEntry *entry, char *filename) {
    clock_t start = clock();
    WordReader reader(filename);
    entry->testFunc(&reader);
    clock_t end = clock();
    double millis = (double)(end-start)/CLOCKS_PER_SEC*1000;
    printf("%s : %dms\n", entry->name, (int)millis);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("usage: %s <input_file>\n", argv[0]);
        return 0;
    }

    std::thread ts[3];
    for(int i=0; i<3; ++i)
        ts[i] = std::thread(tester, testEntries+i, argv[1]);
    for(int i=0; i<3; ++i)
        ts[i].join();

    return 0;
}
