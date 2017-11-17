#include <iostream>

using namespace std;

struct ExampleA {
    int a;
    int b;
};

struct ExampleB {
    int a;
    int b;
    ExampleB(int n):a(n) {}
};

class ExampleC {
public:
    int a;
    int b;
    ExampleA c;
    
    ExampleC(int n):a(n){}
};

class ExampleD {
public:
    int a;
    int b;
    ExampleB c;

    ExampleD(int n):a(n), c(n){}
};

int main() {
    ExampleA a;
    ExampleB b(1);
    ExampleC c(1);
    ExampleD d(1);

    cout << a.a << endl;
    cout << a.b << endl;
    cout << b.a << endl;
    cout << b.b << endl;
    cout << c.a << endl;
    cout << c.b << endl;
    cout << c.c.a << endl;
    cout << c.c.b << endl;
    cout << d.a << endl;
    cout << d.b << endl;
    cout << d.c.a << endl;
    cout << d.c.b << endl;

    return 0;
};
