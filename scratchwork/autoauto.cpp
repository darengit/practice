#include <map>
#include <unordered_map>

using namespace std;

// g++ -Wall -g -std=c++20 autoauto.cpp
// i couldn't easily find out how this is compiled
// but most likely its compiled like a templated function
// this was available earlier, but didn't truly become part of the standard until c++20    
void autoadd(auto &m, auto k, auto v) {
    m[k]=v;
    return;
}

int main() {
    map<int,int> m;
    unordered_map<int,int> hm;

    autoadd(m,1,1);
    autoadd(hm,1,1);

    return 0;
}

