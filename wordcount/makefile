GCC_N_ARGS=g++ -Wall -std=c++14 -Iinclude
LOAD_WHOLE_FILE=-DLOAD_WHOLE_FILE
PRINT_WORDCOUNT=
TEST_WORDS=1000
TEST_SIZE=1000000

all: bin/wordcount bin/testgen

bin/wordcount: src/wordcount.cpp build/tester.o build/wordreader.o
	mkdir -p bin
	$(GCC_N_ARGS) $(LOAD_WHOLE_FILE) $(PRINT_WORDCOUNT) -o bin/wordcount src/wordcount.cpp build/tester.o build/wordreader.o -lpthread

bin/testgen: src/testgen.cpp
	mkdir -p bin
	$(GCC_N_ARGS) -DTEST_WORDS=$(TEST_WORDS) -DTEST_SIZE=$(TEST_SIZE) -o bin/testgen src/testgen.cpp

build/tester.o: src/tester.cpp include/string8.h include/tester.h include/wordreader.h
	mkdir -p build
	$(GCC_N_ARGS) -c -o build/tester.o src/tester.cpp

build/wordreader.o: src/wordreader.cpp src/wordreaderfile.cpp src/wordreaderword.cpp include/string8.h include/wordreader.h
	mkdir -p build
	$(GCC_N_ARGS) -c -o build/wordreader.o src/wordreader.cpp

run: all
	bin/testgen > testfile
	bin/wordcount testfile

clean:
	rm -rf bin build testfile
