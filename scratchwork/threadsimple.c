// gcc -Wall -std=c11 -DTHREAD_COUNT=<number> <filename.c> -lpthread

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define EXAMPLE_CONST (1<<24)

volatile int counter = 0;

void *thread1(void *targ) {
    sem_t *mp = (sem_t *)targ;

    for(int i=0; i<EXAMPLE_CONST; ++i) {
	sem_wait(mp);
	++counter;
	sem_post(mp);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    printf("main:\n");

    pthread_t pts[THREAD_COUNT];

    sem_t m;
    sem_init(&m, 0, 1);

    int ret;
    for(int i=0; i<THREAD_COUNT; ++i) {	
        ret = pthread_create(pts+i, NULL, thread1, (void *)&m);
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
