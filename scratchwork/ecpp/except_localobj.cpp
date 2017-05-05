#include <iostream>

using namespace std;

struct Cntr {
    static int cnt;
    int i;

    Cntr(): i(++cnt) {
        cout << "construct " << i << endl;
    }

    ~Cntr() {
        cout << "destruct " << i << endl;
    }
};

int Cntr::cnt = 0;

int main() {
    try {
        Cntr a,b;
        throw 42;
    } catch (int e) {
        cout << "cathing " << e << endl;
    }
}
