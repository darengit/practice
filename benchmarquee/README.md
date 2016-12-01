Benchmarker and Benchmarquee
============================

Benchmark different versions of functions. They all require to have the same input and output
types. Both benchmark them as well as compare their output with each other.

To benchmark a new set of functions simply add a new directory with properly written
```
benchmarquee.h
benchmarquee.c(pp)
<functions>.c(pp)
```
To compile and run
compile:
```
g++ -Wall -std=c++14 -I<your dir> benchmarker.cpp <your dir>/benchmarquee.c(pp) <your dir>/<functions>.c(pp) <add optional args like -O0,1,2>
```
run:
```
./a.out
```

benchmarker.cpp is a cpp file to allow us to conveniently benchmark both c and cpp.

declarations and definitions can get tricky. Any global variable in benchmarquee.h should be
declared with 'extern'. And they should be defined in benchmarquee.c(pp). Functions in benchmarquee.h
are defined in benchmarquee.c(pp) and <functions>.c(pp).

