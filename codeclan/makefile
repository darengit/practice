run: all
	bin/a.out

all: bin/a.out

bin/a.out: codeclan.cpp
	mkdir -p bin
	g++ -Wall -std=c++14 -g codeclan.cpp -o bin/a.out

clean:
	rm -rf bin
