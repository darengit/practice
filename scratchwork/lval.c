#include <stdio.h>

struct T {
	unsigned long l;
};


struct T func() {
	return (struct T) {0x4242424242424242};
}


int main() {
	0xabababababababab;
	// illegal
	// (unsigned long) 0x0101010101010101 = (unsigned long) 0x1010101010101010;
	
	//{0xcdcdcdcdcdcdcdcd} = {0xefefefefefefefef};
	long a = 1;
	long b = 2;
	printf("%lx %lx\n", &a, &b);
	 (struct T){0xcdcdcdcdcdcdcdcd} = (struct T){0xefefefefefefefef};
	// print value above, show that its stored in memory
	// printf("%lx\n", ((struct T *)(&a-1))->l);
	//func() = (struct T){0x9090909090909090};

	return 0;
}
