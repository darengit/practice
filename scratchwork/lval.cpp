#include <stdio.h>


class Int {
public:
	int v;
	Int(int &&i): v(i) {
		printf("int double ref constructor\n");
	}

	Int(const int &i): v(i) {
		printf("const int ref constructor\n");
	}

	int &operator[](int i) {
		return v; // returns *(&v)
	}
};

int main() {
	int i = 0;
	int &r = i;
	r = 2;	

	printf("%lx %lx %d %d\n", (unsigned long)&i, (unsigned long)&r, i, r);

	//int &s = 1; // doesn't compile
	const int &t = 1; // compiles

//	int &&p = i; // doesn't compile
	int &&q = 1;

	//Int &&A = Int(1);	
	//const Int &B = Int(1);
	// const int &&p = i; // doesn't compile

	Int a(1);
//	Int b(i);
//	Int c(r);
//	Int d(t);
//	Int e(q);

	a[10] = 5;
	printf("%d\n", a.v);
}
