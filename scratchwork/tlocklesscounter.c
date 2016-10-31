-Wall -std=c11 -DTHREAD_COUNT=<number> <filename.c> -lpthread

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define EXAMPLE_CONST (1<<24)

volatile int counter = 0;

void *thread1(void *targ) {
    for(int i=0; i<EXAMPLE_CONST; ++i) {
        int curr = counter;
        while(!__sync_bool_compare_and_swap(&counter,curr,curr+1))
            curr = counter;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    printf("main:\n");
    pthread_t pts[THREAD_COUNT];

    int ret;
    for(int i=0; i<THREAD_COUNT; ++i) {	
        ret = pthread_create(pts+i, NULL, thread1, NULL);
        printf("p_create 0x%lx ret: %d\n", pts[i], ret);
    }

    for(int i=0; i<THREAD_COUNT; ++i) {
        ret = pthread_join(pts[i], NULL);
        printf("join 0x%lx ret: %d\n", pts[i], ret);
    }

    printf("actual counter %d but should be %d\n", counter, THREAD_COUNT*EXAMPLE_CONST);
    printf("returning from main\n");
    return 0;
}
