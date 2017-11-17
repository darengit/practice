#include <iostream>

using namespace std;

struct A {

    void test();


};

    void A::test() {
        cout << "test" << endl;
    }

template <int N>
struct B : public A {
    void test();
};

template<int N>
void B<N>::test() {
        A::test();
        cout << N << endl;
    }

int main() {
    B<5> *x = new B<5>;
    x->test();
    return 0;
}
