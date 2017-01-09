#include <stdbool.h>

#include "benchmarquee.h"

long linearfibonacci(long n) {
    long prev = 0;
    long next = 1;
    for(long i=1; i<n; ++i) {
        long temp = prev+next;
        prev = next;
        next = temp;
    }
    return next;
}

//typedef long matrix[2][2];
typedef struct {
    long m[2][2];
} Matrix;

Matrix matrixmult(Matrix a, Matrix b) {
    Matrix ans;
    ans.m[0][0] = a.m[0][0]*b.m[0][0]+a.m[0][1]*b.m[1][0];
    ans.m[0][1] = a.m[0][0]*b.m[0][1]+a.m[0][1]*b.m[1][1];
    ans.m[1][0] = a.m[1][0]*b.m[0][0]+a.m[1][1]*b.m[1][0];
    ans.m[1][1] = a.m[1][0]*b.m[0][1]+a.m[1][1]*b.m[1][1];
    return ans;
}

Matrix matrixpow(Matrix m, long exp) {
    Matrix ans = m;
    while(--exp) {
        ans = matrixmult(ans,m);
    }
    return ans;
}

Matrix matrixfibonacci(long n) {
    Matrix I;
    I.m[0][0] = 1;
    I.m[0][1] = 1;
    I.m[1][0] = 1;
    I.m[1][1] = 0;
    if(n==1) return I;

    if(n%2)
        return matrixmult(matrixpow(matrixfibonacci(n/2),2),I);
    else
        return matrixpow(matrixfibonacci(n/2),2);
}

long logfibonacci(long n) {
    Matrix ans = matrixfibonacci(n-1);
    return ans.m[0][0];
}
