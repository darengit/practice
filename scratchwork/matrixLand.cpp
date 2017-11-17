#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int h,w;
    cin >> h >> w;
    vector<vector<int>> dp(h, vector<int>(w));

    vector<int> fromLeft1(w);
    vector<int> fromLeft2(w);
    vector<int> fromRight1(w);
    vector<int> fromRight2(w);
    
    for(int i=0; i<h; ++i)
    for(int j=0; j<w; ++j)
        cin >> dp[i][j];
    
    for(int i=0; i<h; ++i) {
        fromLeft1[0]=dp[i][0];
        for(int j=1; j<w; ++j) {
            fromLeft1[j]=dp[i][j];
            if(fromLeft1[j-1]>0)
                fromLeft1[j]+=fromLeft1[j-1];
        }
        
        fromRight1[w-1]=dp[i][w-1];
        for(int j=w-2; j>=0; --j) {
            fromRight1[j]=dp[i][j];
            if(fromRight1[j+1]>0)
                fromRight1[j]+=fromRight1[j+1];
        }
        
        if(!i) {
            for(int j=0; j<w; ++j) {
                int left = (j?max(fromLeft1[j-1],0):0);
                int right = (j<w-1 ? max(fromRight1[j+1],0):0);
                dp[i][j] += left+right;
            }
        } else {
            fromLeft2[0] = dp[i][0]+dp[i-1][0];
            for(int j=1; j<w; ++j)
                fromLeft2[j] = max(fromLeft2[j-1]+dp[i][j], dp[i-1][j]+dp[i][j]+max(fromLeft1[j-1],0));
            
            fromRight2[w-1] = dp[i][w-1]+dp[i-1][w-1];
            for(int j=w-2; j>=0; --j)
                fromRight2[j] = max(fromRight2[j+1]+dp[i][j], dp[i-1][j]+dp[i][j]+max(fromRight1[j+1],0));
            
            for(int j=0; j<w; ++j) {
                int left = (j?max(fromLeft1[j-1],0):0);
                int right = (j<w-1 ? max(fromRight1[j+1],0):0);
                
                dp[i][j] = max(fromRight2[j]+left, fromLeft2[j]+right);
                    
            }
        }
    }
    
        int ans = -100000000;
        for(int i=0; i<w; ++i)
            ans = max(dp.back()[i], ans);
        cout << ans;
   
    
    return 0;
}

