all: bin/a.out

bin/a.out: build/main.o build/write.o build/__boot.o build/__main.o build/__exit.o
	mkdir -p bin
	ld build/main.o build/write.o build/__boot.o build/__main.o build/__exit.o -o bin/a.out

build/main.o: src/main.c
	mkdir -p build
	gcc -Wall -std=c11 -g -c src/main.c -o build/main.o

build/write.o: src/write.s
	mkdir -p build
	as src/write.s -o build/write.o

build/__boot.o: src/__boot.s
	mkdir -p build
	as src/__boot.s -o build/__boot.o

build/__main.o: src/__main.c
	mkdir -p build
	gcc -Wall -std=c11 -g -c src/__main.c -o build/__main.o

build/__exit.o: src/__exit.s
	mkdir -p build
	as src/__exit.s -o build/__exit.o

run: all
	bin/a.out

clean:
	rm -rf bin build
