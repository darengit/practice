#include<bits/stdc++.h>
#include<x86intrin.h>

class clock_cycler {
	uint64_t start;
	uint64_t end;

public:
	static uint64_t rdtsc(){
    	unsigned int lo,hi;
    	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    	return ((uint64_t)hi << 32) | lo;
	}


	void warmup(){}
	void run(){}
	void cooldown() {
		std::cout << std::fixed << end-start << " clock cycles" << std::endl;
	}

	void count_cycle() {
		warmup();
		start = clock_cycler::rdtsc();
		run();
		end = clock_cycler::rdtsc();
		cooldown();
	}
};


