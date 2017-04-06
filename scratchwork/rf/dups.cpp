#include <iostream>
#include <vector>

#define MAX_ELT 64

void printDups(std::vector<int> A) {
    std::vector<char> cnts(MAX_ELT);
    for(int i:A)
        ++cnts[i];

    for(int i=0; i<MAX_ELT; ++i)
        if(cnts[i]>1)
            std::cout << i << " ";
}

int main() {
    printDups({3,1,1,3});
    printDups({1,3,2,2});
    return 0;
}
