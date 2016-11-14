#include <stdio.h>
#include <vector>
#include <algorithm>


void recursivepermutate(std::vector<int> &v, int i, int size) {
    if(i+1 == size) {
        for(int elt: v) printf("%d ", elt);
        printf("\n");
        return;
    }    


    for(int j=i; j<size; ++j) {
        std::swap(v[i],v[j]);
        recursivepermutate(v, i+1, size);
        std::swap(v[i],v[j]);
    }    
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

void companionpermutate(std::vector<int> &v) {
    std::vector<int> companion(v.size());
    for(int i=0; i<(int)companion.size(); ++i) companion[i]=i;
    
    do {
        for(int i: v) printf("%d ", i);
        printf("\n");
    } while(orderedswap(v,companion));
}

int main() {
    
    std::vector<int> test(TEST_VECTOR_SIZE);
    for(int i=0; i<(int)test.size(); ++i) test[i]=i;
    std::sort(test.begin(), test.end());
    do {
        for(int i: test) printf("%d ", i);
        printf("\n");
        ;

    } while(std::next_permutation(test.begin(), test.end()));

    printf("*********\n");
    for(int i: test) printf("%d ", i);
    printf("\n");

    recursivepermutate(test,0,test.size());

    printf("*********\n");
    for(int i: test) printf("%d ", i);
    printf("\n");

    companionpermutate(test);

    return 0;
}
