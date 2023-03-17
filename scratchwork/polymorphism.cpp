// compile:
// g++ -Wall -g -std=c++17 polymorphism.cpp


#include <bits/stdc++.h>
typedef long long llong;

using namespace std;


class A {
public:
	virtual void output() const {
		cout << "A::output" << endl;
	}
};

class B : public A {
public:
	// experiment with adding const and override to this function declaration
	void output() {
		cout << "B::output" << endl;
	}
};




int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	A *obj1 = new A();
	A *obj2 = new B();
	B *obj3 = new B();

	obj1->output();
	obj2->output();
	obj3->output();

}
