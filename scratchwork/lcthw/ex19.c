#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void test_debug() {
    debug("this is a debug message");
    debug("this debug message has a number and its %d", 25);
}

void test_log_err() {
    log_err("logging this error with log_err()");
    log_err("there are %d numbers in this %s", 1, "sentence");
}

void test_log_warn() {
    log_warn("this is only a yellow");
    log_warn("additional params %s", "warning");
}

void test_log_info() {
    log_info("this is purely informational");
    log_info("pi is equal to %f", 3.1415f);
}

int test_check(char *file_name) {
    FILE *input = NULL;
    char *block = NULL;

    block = (char *)malloc(100);
    check_mem(block);

    input = fopen(file_name, "r");
    check(input, "Failed to open %s", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if(block) free(block);
    if(input) fclose(input);
    return -1;
}

int test_sentinel(int code) {
    char *temp = (char *)malloc(100);
    check_mem(temp);

    switch(code) {
        case 1:
            log_info("works");
            break;
        default:
            sentinel("shouldn't get here");
    }

    free(temp);
    return 0;

error:
    if(temp) free(temp);
    return -1;
}

int test_check_mem() {
    char *test = NULL;
    check_mem(test);

    free(test);
    return 1;

error:
    return 1;
}

int test_check_debug() {
    int i=0;
    check_debug(i!=0, "oopen i=0");

    return 0;

error:
    return -1;
}

int main(int argc, char *argv[]) {
    check(argc==2, "need an argument");

    test_debug();
    test_log_err();
    test_log_warn();
    test_log_info();

    check(test_check("ex20.c")==0, "failed with ex20.c");
    check(test_check(argv[1])==-1, "failed with argv");
    check(test_sentinel(1)==0, "test_sentinel failed");
    check(test_sentinel(100)==-1, "test_sentinel failed");
    check(test_check_mem()==-1, "test_check_mem failed");
    check(test_check_debug()==-1, "test_check_debug failed");

    return 0;

error:
    return -1;
}
