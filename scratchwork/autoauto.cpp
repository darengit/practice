#include <map>
#include <unordered_map>

using namespace std;
    
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

