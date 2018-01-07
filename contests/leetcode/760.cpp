#include <bits/stdc++.h>

using namespace std;



  struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
  };



class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& avails) {
        vector<Interval> combine;
        for(int i=0; i<avails.size(); ++i)
            merge(combine, avails[i]);
        
        vector<Interval> res;
        for(int i=1; i<combine.size(); ++i)
            res.emplace_back(combine[i-1].end, combine[i].start);
        
        return res;
    }
    
    void merge(vector<Interval>& a, vector<Interval>& b) {
        vector<Interval> res;
        for(Interval& i: b) {
            bool merged=false;
            for(Interval& j: a)
            if(max(i.start,j.start)<=min(i.end,j.end)) {
                j.start=min(i.start,j.start),
                j.end=max(i.end,j.end);
                merged=true;
                break;
            }
            if(!merged) {
                res.push_back(i);
            }
        }
        
        for(Interval& i: a) {
            bool merged = false;
            for(Interval& j: res)
            if(max(i.start,j.start)<=min(i.end,j.end))
                j.start=min(i.start,j.start),
                j.end=max(i.end,j.end),
                merged=true;
            if(!merged)
                res.push_back(i);

        }
        
        sort(res.begin(), res.end(), [](Interval& a, Interval& b){ return a.start<b.start;});
        
        swap(a,res);
        return;
    }

};

int main() {
	Solution sol;
	vector<vector<Interval>> test{{Interval(1,2),Interval(5,6)},{Interval(1,3)},{Interval(4,10)}};
	auto ans = sol.employeeFreeTime(test);
	return 0;
}
