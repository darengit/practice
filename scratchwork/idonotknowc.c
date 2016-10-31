#include <stdio.h>

int i;
int i=10;

void called() {
    printf("i was called\n");
}

void optimizeme(int *p) {
    int q=*p;
    if(!p)
        return;
    called();
    return;
}

int main() {
    printf("%d\n", i);
    optimizeme(NULL);

    int array[] = { 0, 1, 2 };
    printf("%d %d %d\n", 10, (5, array[1, 2]), 10);
}
