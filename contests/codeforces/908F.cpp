
#include <iostream>
#include <vector>
#include <algorithm>


typedef long long llong;

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<llong> G,R,B;

    for(int i=0; i<n; ++i) {
        llong p;
        char c;
        cin >> p >> c;

        switch(c) {
        case 'G':
            G.push_back(p);
            break;
        case 'R':
            R.push_back(p);
            break;
        default:
            B.push_back(p);
        }
    }

    llong ans = 0;

    if(G.empty()) {
        if(R.size())
            ans += R.back()-R.front();
        if(B.size())
            ans += B.back()-B.front();
    } else {
//        ans += G.back()-G.front();


        vector<llong> gapsR(G.size());
        vector<llong> gapsB(G.size());


        if(R.size()) {

            if(R.front() < G.front()) ans += G.front()-R.front();
            if(R.back() > G.back()) ans += R.back() - G.back();

            if(G.size() > 1) {
                int idx=0;

                for(int i=1; i<G.size(); ++i) {
                    llong leftPost = G[i-1];
                    llong rightPost = G[i];
                    llong biggestGap = 0;

                    for(;idx<R.size() && R[idx]<leftPost;++idx);
                    if(idx<R.size() && R[idx]<rightPost) { // a red in between green posts exist
						biggestGap = R[idx]-leftPost;

                    	for(;idx+1<R.size() && R[idx+1]<rightPost; ++idx)
                        	biggestGap = max(biggestGap, R[idx+1]-R[idx]);

                    	biggestGap = max(biggestGap, rightPost-R[idx]);
					}
                    gapsR[i]=biggestGap;
//                    ans += G[i]-G[i-1]-biggestGap;
                }
            }
        }

        if(B.size()) {

            if(B.front() < G.front()) ans += G.front()-B.front();
            if(B.back() > G.back()) ans += B.back() - G.back();

            if(G.size() > 1) {
                int idx=0;

                for(int i=1; i<G.size(); ++i) {
                    llong leftPost = G[i-1];
                    llong rightPost = G[i];
                    llong biggestGap = 0;

                    for(;idx<B.size() && B[idx]<leftPost;++idx);
                    if(idx<B.size() && B[idx]<rightPost) { // a blue in between green posts exist
						biggestGap = B[idx]-leftPost;

                    	for(;idx+1<B.size() && B[idx+1]<rightPost;++idx)
                        	biggestGap = max(biggestGap, B[idx+1]-B[idx]);

                    	biggestGap = max(biggestGap, rightPost-B[idx]);
					}
					gapsB[i]=biggestGap;
//                    ans += G[i]-G[i-1]-biggestGap;
                }
            }
        }


        for(int i=1; i<G.size(); ++i) {
            llong width = G[i]-G[i-1];
            ans += width;

            if(!gapsR[i] && !gapsB[i]) {
                continue;
            }

            if(!gapsR[i]) {
                ans += width-gapsB[i];
                continue;
            }

            if(!gapsB[i]) {
                ans += width-gapsR[i];
                continue;
            }

            // both R and B are present
            if(gapsR[i]+gapsB[i]>width) {
                ans += width*2-gapsR[i]-gapsB[i];
            } else {
                ans += width;
            }

        }


    }


    cout << ans;

    return 0;
}
