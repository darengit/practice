#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string makeLargestSpecial(string S) {
        makeLargestSpecial(S,0,S.size()-1);
        return S;
    }
    
    void makeLargestSpecial(string& S, int beg, int end) {
        if(end==beg+1) return;
        int balance=1;
        vector<vector<int>> pairs;
        int start=beg;
        for(int i=beg+1; i<=end; ++i) {
            balance += (S[i]=='1' ? 1 : -1);
            if(!balance) {
                pairs.push_back({start, i});
                start=i+1;
            }
        }

		if(pairs.size()==1) {
			makeLargestSpecial(S, pairs[0][0]+1, pairs[0][1]-1);
			return;
		}

        for(auto& v: pairs)
            makeLargestSpecial(S,v[0],v[1]);
        
        for(int i=0; i<pairs.size(); ++i)
        for(int j=i+1; j<pairs.size(); ++j)
            if(S.substr(pairs[i][0], pairs[i][1]-pairs[i][0]+1) < S.substr(pairs[j][0], pairs[j][1]-pairs[j][0]+1))
                swap(pairs[i], pairs[j]);
        
        string tmp;
        for(auto& v: pairs)
        for(int i=v[0]; i<=v[1]; ++i)
            tmp.push_back(S[i]);
       
		for(int i=beg; i<=end; ++i)
			S[i]=tmp[i-beg];

        return;
    }
};

int main() {
	Solution sol;
	cout << sol.makeLargestSpecial("11011000") << endl;
	return 0;

}
