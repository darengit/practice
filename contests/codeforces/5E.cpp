#include <bits/stdc++.h>
typedef long long llong;

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	vector<int> heights(n);
	for(int i=0; i<n; ++i)
		cin >> heights[i];


	int maxht = *max_element(heights.begin(), heights.end());
	int idx=0;
	for(;heights[idx]!=maxht;++idx);

	vector<int> newhts(n+1);
	for(int i=0; i<n; ++i)
		newhts[i]=heights[(i+idx)%n];
	newhts[n]=newhts[0];
	heights=newhts;


	vector<int> samehts(n+1,1);
	vector<int> previdx(n+1, -1);

	llong ans = 0;

	for(int i=1; i<=n; ++i) {
		int canSee=i-1;

		for(;;) {
			if(heights[canSee] < heights[i]) {
				if(i==n && previdx[canSee]==0) break;

			 	ans += samehts[canSee];
				canSee = previdx[canSee];
			} else if(heights[canSee] == heights[i]) {
				if(i==n) break;

				ans += samehts[canSee];
				samehts[i]=samehts[canSee]+1;

				if(heights[i]<heights[0]) {
					++ans;
					previdx[i]=previdx[canSee];
				}

				break;
			} else { // heights[canSee] > heights[i]
				++ans;
				previdx[i]=canSee;
				break;
			}
		}

	}

	cout << ans;
	return 0;
}
