GCC_N_ARGS=g++ -Wall -std=c++14 -Iinclude
LOAD_WHOLE_FILE=-DLOAD_WHOLE_FILE
PRINT_WORDCOUNT=
TEST_WORDS=1000
TEST_SIZE=1000000

all: wordcount testgen

wordcount: src/wordcount.cpp tester.o wordreader.o
	$(GCC_N_ARGS) $(LOAD_WHOLE_FILE) $(PRINT_WORDCOUNT) -o bin/wordcount src/wordcount.cpp build/tester.o build/wordreader.o -lpthread

testgen: src/testgen.cpp
	$(GCC_N_ARGS) -DTEST_WORDS=$(TEST_WORDS) -DTEST_SIZE=$(TEST_SIZE) -o bin/testgen src/testgen.cpp

tester.o: src/tester.cpp include/string8.h include/tester.h include/wordreader.h
	$(GCC_N_ARGS) -c -o build/tester.o src/tester.cpp

wordreader.o: src/wordreader.cpp src/wordreaderfile.cpp src/wordreaderword.cpp include/string8.h include/wordreader.h
	$(GCC_N_ARGS) -c -o build/wordreader.o src/wordreader.cpp

run: all
	bin/testgen > testfile
	bin/wordcount testfile

clean:
	rm bin/* build/* testfile
