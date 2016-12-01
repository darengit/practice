#include <vector>
#include <algorithm>

#include "benchmarquee.h"

int recursivepermutate(std::vector<int> &v, int i, int size) {
    if(i+1 == size) {
        return 1;
    }    

    int count = 0;
    for(int j=i; j<size; ++j) {
        std::swap(v[i],v[j]);
        count += recursivepermutate(v, i+1, size);
        std::swap(v[i],v[j]);
    }

    return count;
}

int recursivepermutate(std::vector<int> &v) {
    return recursivepermutate(v, 0, v.size());
}

bool orderedswap(std::vector<int> &v, std::vector<int> &c) {
    int a,b;

    for(a=c.size()-2; a>=0; --a)
        if(c[a]<c[a+1]) break;
    if(a<0) return false;

    for(b=a+1; b<(int)c.size(); ++b)
        if(c[b]<c[a]) break;
    --b;

    std::swap(c[a],c[b]);
    for(int i=a+1,j=c.size()-1; i<j; ++i,--j)
        std::swap(c[i],c[j]);
    std::swap(v[a],v[b]);
    for(int i=a+1,j=v.size()-1; i<j; ++i,--j)
        std::swap(v[i],v[j]);

    return true;    
} 

int companionpermutate(std::vector<int> &v) {
    int count = 0;
    std::vector<int> companion(v.size());
    for(int i=0; i<(int)companion.size(); ++i) companion[i]=i;
    
    do {
        ++count;
    } while(orderedswap(v,companion));

    return count;
}
    
int stlpermutate(std::vector<int> &v) {
    int count = 0;
    std::sort(v.begin(), v.end());
    do {
        ++count;
    } while(std::next_permutation(v.begin(), v.end()));

    return count;
}

int sizefactorial(std::vector<int> &v) {
    int ret = 1;
    for(int i=1; i<=(int)v.size(); ++i) 
        ret *= i;
    return ret;
}
