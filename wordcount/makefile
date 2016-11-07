TEST_WORDS=1000
TEST_SIZE=1000000

all: wordcount testgen

wordcount:
	g++ -Wall -std=c++14 -DLOAD_WHOLE_FILE -o wordcount wordcount.cpp tester.cpp wordreader.cpp -lpthread

testgen:
	g++ -Wall -std=c++14 -DTEST_WORDS=$(TEST_WORDS) -DTEST_SIZE=$(TEST_SIZE) -o testgen testgen.cpp

run: all
	./testgen > testfile
	./wordcount testfile

clean:
	rm testgen wordcount testfile
