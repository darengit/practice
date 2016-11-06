#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc<2) {
        printf("usage: %s <8 byte long string args>", argv[0]);
        return 0;
    }

    argc--;
    for(int i=0; i<TEST_SIZE; ++i) {
        int r = rand()%argc;
        printf("%s", argv[r+1]);
    }
}
