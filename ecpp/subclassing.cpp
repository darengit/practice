#include <stdio.h>

using namespace::std;

struct A {

	int i;
	void print() {
		printf("%d\n", i);
	}
};

struct B : A {
	int j;
	void print() {
		printf("%d\n", j);
	}
};

template <typename T>
void print(T &t) {
	t.print();
}

struct M {
/*
	static void print() {
		printf("Mmmmm\n");
	}
*/
	virtual void blah() {
		return;
	}
};

struct N : M {
/*
	static void print() {
		printf("Noooo\n");
	}
*/
	void blah() override {
		printf("blah");
	}
};

template <typename T>
struct S {
	T x;
	void staticprint() {
		x.blah();
	}
};

int main() {
	B *x = new B;
	x->i=1;
	x->j=2;
	A *y = x;

	x->print();
	y->print();

	print<B>(*x);
	print<A>(*y);
	print<A>(*x);
	print(*y);

	S<N> *n = new S<N>();
	S<M> *m = n;

	return 0;	
}
