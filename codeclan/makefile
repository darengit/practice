
build/codeclan.o: src/codeclan.cpp
	mkdir -p build
	g++ -Wall -std=c++14 -Iinclude -c -g src/codeclan.cpp -o build/codeclan.o

build/clanmission.o: src/clanmission.cpp
	mkdir -p build
	g++ -Wall -std=c++14 -Iinclude -c -g src/clanmission.cpp -o build/clanmission.o


run: all
	bin/a.out

all: bin/a.out

bin/a.out: build/codeclan.o build/clanmission.o main.cpp
	mkdir -p bin
	g++ -Wall -std=c++14 -Iinclude -g main.cpp -o bin/a.out build/codeclan.o build/clanmission.o

clean:
	rm -rf bin build
