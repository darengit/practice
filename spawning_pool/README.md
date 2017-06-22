This is an extremely simple threadpool implementation from my imagination using as many of the new c++11 features as possible. All parameters for 'Spawn(func, args...)' are copied by value for simplicity.

to compile test run on linux:

g++ -Wall -g -std=c++14 \<test script\>.cpp -lpthread
