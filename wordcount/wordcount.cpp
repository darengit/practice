#include <stdio.h>
#include <thread>
#include <chrono>
#include "string8.h"
#include "wordreader.h"
#include "tester.h"

struct TestEntry {
    void (*testFunc)(WordReader *reader);
    const char *name;
};

TestEntry TestEntries[] = {
    { testLinearSearch, "linear search" },
    { testMap, "std::map" },
    { testUnorderedMap, "std::unordered_map" },
};

void tester(TestEntry *entry, char *filename) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    WordReader reader(filename);
    entry->testFunc(&reader);
    end = std::chrono::high_resolution_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    printf("%s : %ldms\n", entry->name, millis);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("usage: %s <input_file>\n", argv[0]);
        return 0;
    }

    std::thread ts[3];
    for(int i=0; i<3; ++i)
        ts[i] = std::thread(tester, &TestEntries[i], argv[1]);
    for(int i=0; i<3; ++i)
        ts[i].join();

    return 0;
}
