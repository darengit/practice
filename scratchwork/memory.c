// TASK: implement buffer overflow/underflow protection by changing
//       our_malloc() and our_free() functions only,
//       call alarm() in case of overflow/underflow happened during the life
//       time of the program
//
// TIP: go to http://www.compileonline.com/compile_c_online.php
//      for an online IDE
//
// Send code to jobs@daynix.com
//

#include <stdlib.h>
#include <stdio.h>

#define CANARY 0xaaaaaaaaaaaaaaaa

void alarm()
{
    printf("ALARM\n");
    exit(100);
}

void *our_malloc(size_t size)
{
    long *p=malloc(size+sizeof(long)*3);
    *p = (long)size;
    *(p+1) = (long)CANARY;
    *((long *)((void *)(p+2)+size)) = (long)CANARY;

    printf("ALLOC %d bytes\n", (int)size);
    return (void *)(p+2);
}

void our_free(void *ptr)
{
    size_t size = (size_t)*((long *)ptr-2);
    if(*((long *)ptr-1)!=CANARY ||
       *((long *)(ptr+size))!=CANARY)
        alarm();

    printf("FREE 0x%p\n", ptr);
    free((long *)ptr-2);
}

#define malloc our_malloc
#define free our_free

int main()
{
    char *x = malloc(64);

    if(!x)
    {
        printf("ALLOC FAILED\n");
        return -1;
    }

#ifdef TEST_BUFFER_UNDERFLOW
    //Buffer underflow
    x[-1] = 0;
#endif

#ifdef TEST_BUFFER_OVERFLOW
    //Buffer overflow
    x[64] = 0;
#endif

    free(x);
    return 0;
}
