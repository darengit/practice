i created a makefile with these two commands:
make clean
make test

my unit tests are more like functional tests than true unit tests. i also didn't fully answer some of the questions by functionally testing the memory usage of incr_dict and the timing of operations in my hash table implementation. i believe my implementation of incr_dict is memory efficient if python optimized for tail recursion(noticed too late that it does not), no matter how long the input tuple is, additional heap memory usage will be fairly constant due to not creating copies of the tuple argument.
