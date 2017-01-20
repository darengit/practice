#define V vector<vector<int>>
#define c(x) case x:r=V{
#define b }; break;

V r,magicSquare(int s, int t, int n) {

    switch (n) {
            /*
        case 1:
            r = V{{s}};
            break;
        case 2:
            r = V{};
            break;
        case 3:
            r = V{{1,6,5},{8,4,0},{3,2,7}};
            break;
        case 4:
            r = V{{0,1,14,15},{11,13,2,4},{12,6,9,3},{7,10,5,8}};
            */
            
        c(1) {s} b c(2) b c(3) {1,6,5},{8,4,0},{3,2,7} b c(4) {0,1,14,15},{11,13,2,4},{12,6,9,3},{7,10,5,8} b    
            
    }
    
    for(auto &v: r)
        for(int &i: v)
            i = s+i*t;
    return r;
}

