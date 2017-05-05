a.out: stringexercise.c
	gcc -Wall -g -std=c11 stringexercise.c

all: a.out

test: a.out
	bash functional_test

clean:
	rm -f test1.txt a.out
