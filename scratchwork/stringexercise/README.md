I assume that only alphanumeric characters and characters that are passed in as
input are symbols that can make up words. I've created a custom function called
initializeIssym() which can be used to change the above assumption and map all
values of chars to be either a symbol or a delimiter.

There is also a Makefile which uses gcc and a functional testing bash script.

make # will make the executable as a.out
make test # will run bash script, with output for human examination
make clean # cleanup executable and test files
