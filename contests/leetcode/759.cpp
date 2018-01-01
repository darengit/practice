#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int intersectionSizeTwo(const vector<vector<int>>& intervals) {
        int sz=intervals.size();
        vector<int> cnts(sz);
        
        vector<vector<int>> begs, ends;
        
        for(int i=0; i<sz; ++i)
            begs.push_back({intervals[i][0], i}),
            ends.push_back({intervals[i][1], i});
        
        sort(begs.begin(), begs.end());
        sort(ends.begin(), ends.end());
        
        int ans = 0;
        
        int begsIdx=0;
        for(auto& v: ends) {
            if(cnts[v[1]] < 2) {
                int select = 2-cnts[v[1]];
                ans += select;
                cnts[v[1]] = 2;
                
                for(int i=begsIdx; i<sz && begs[i][0]<=v[0]; ++i) {
                    if(cnts[begs[i][1]]<2) {
                        int thisSel = min(select, v[0]-begs[i][0]+1);
                        cnts[begs[i][1]] += thisSel;
                        cnts[begs[i][1]] = min(cnts[begs[i][1]], 2);

                    }
                    
                    if(cnts[begs[i][1]]==2) ++begsIdx;
                }
            } 
        }
        
        return ans;
    }
};

int main() {
	Solution sol;
	return sol.intersectionSizeTwo({{1,3},{1,4},{2,5},{3,5}});
}
