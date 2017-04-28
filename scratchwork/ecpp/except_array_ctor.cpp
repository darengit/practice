#include <iostream>

using namespace std;

struct Throw3rdCtor {
    static int cnt;
    int i;

    Throw3rdCtor(): i(++cnt) {
        cout << "construct " << i << endl;
        if(cnt == 3)
            throw i;
    }

    ~Throw3rdCtor() {
        cout << "destruct " << i << endl;
    }
};

int Throw3rdCtor::cnt = 0;

int main() {
    Throw3rdCtor *p;
    try {
        p = new Throw3rdCtor[5];
    } catch (int e) {
        cout << "cathing " << e << endl;
    }

    return (long)p;
}
