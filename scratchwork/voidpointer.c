#include <stdio.h>

struct MyArr {
	int *arr;
	int len;
};

// so long as you unpack everything properly
int voidargs(int *sizes, void *argv) {
	for(int i=0; i<sizes[0]; ++i)
		printf("%d\n", ((int *)((void **)argv)[0])[i]);
	for(int i=0; i<sizes[1]; ++i)
		printf("%f\n", ((double *)((void **)argv)[1])[i]);
	for(int i=0; i<sizes[2]; ++i)
		printf("0x%lx\n", ((long *)((void **)argv)[2])[i]);
	for(int i=0; i<sizes[3]; ++i) {
		for(int j=0; j<((struct MyArr *)((void **)argv)[3])[i].len; ++j)
			printf("%d ", ((struct MyArr *)((void **)argv)[3])[i].arr[j]);
		printf("\n");
	}
	return 0;
}

// you can pack 2D (actually any dimension) array into a void *
// unfortunately when you do this you lose size information
int main() {
	return voidargs((int []){3,5,4,2}, (void *)(void *[]){(int []){1,2,3},
															(double []){4.2, 5.5,6.7,7.0,8.0},
															(long []){9L,10L,11L,12L},
		(struct MyArr[]){(struct MyArr){(int[]){13,14},2},(struct MyArr){(int []){15,16,17},3}}});
}
