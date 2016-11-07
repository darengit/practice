#include <stdlib.h>
#include <stdio.h>

int main() {
    char words[TEST_WORDS*8];
    for(int i=0; i<TEST_WORDS*8; ++i)
        words[i] = 'a' + rand()%26;

    for(int i=0; i<TEST_SIZE; ++i) {
        int r = rand()%TEST_WORDS;
        printf("%.8s", words + r*8);
    }
}
