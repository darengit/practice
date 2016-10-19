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
	pthread_t *p1, *p2;
	p1 = (pthread_t *)malloc(sizeof(pthread_t));
	p2 = (pthread_t *)malloc(sizeof(pthread_t));

	sem_t m;
	sem_init(&m, 0, 1);

	int ret;
	printf("main:\n");
	
	ret = pthread_create(p1, NULL, &thread1, (void *)&m);
	printf("p_create 0x%lx ret: %d\n", *p1, ret);
	ret = pthread_create(p2, NULL, &thread1, (void *)&m);
	printf("p_create 0x%lx ret: %d\n", *p2, ret);

	for(int i=0; i<EXAMPLE_CONST; ++i) {
		sem_wait(&m);
		++counter;
		sem_post(&m);
	}

	ret = pthread_join(*p1, NULL);
	printf("join 0x%lx ret: %d\n", *p1, ret);
	ret = pthread_join(*p2, NULL);
	printf("join 0x%lx ret: %d\n", *p2, ret);

	printf("actual counter %d but should be %d\n", counter, 3*EXAMPLE_CONST);

	printf("returning from main\n");
	return 0;
}
