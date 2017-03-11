// g++ -Wall -std=c++14 -DTHREAD_COUNT=<number> <filename.c> -lpthread

#include <stdio.h>
#include <vector>
#include <thread>
#include <mutex>

#define EXAMPLE_CONST (1<<10)

void thread1(std::mutex &mu, volatile int &counter) {

    for(int i=0; i<EXAMPLE_CONST; ++i) {
	    mu.lock();
	    ++counter;
	    mu.unlock();
    }

    return;
}

int main(int argc, char *argv[]) {
    printf("main:\n");

    std::mutex mu;
    volatile int counter = 0;
    std::vector<std::thread> pts(THREAD_COUNT);


    for(int i=0; i<THREAD_COUNT; ++i) {
        pts[i] = std::thread(thread1,std::ref(mu),std::ref(counter));
        printf("created thread %d\n", i);
    }

    for(int i=0; i<THREAD_COUNT; ++i) {
	    pts[i].join();
	    printf("joined thread %d\n", i);
    }
	
    printf("actual counter %d but should be %d\n", counter, THREAD_COUNT*EXAMPLE_CONST);
    printf("returning from main\n");
    return 0;
}
