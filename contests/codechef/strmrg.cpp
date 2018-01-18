#include <bits/stdc++.h>
typedef long long llong;

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for(int t=0; t<T; ++t) {
		int n,m;
		cin >> n >> m;
		string a,b;
		cin >> a >> b;

		int idx=1;
		for(int i=1; i<n; ++i)
		if(a[i]!=a[i-1])
			a[idx++]=a[i];
		n=idx;

		idx=1;
		for(int i=1; i<m; ++i)
		if(b[i]!=b[i-1])
			b[idx++]=b[i];
		m=idx;

		vector<vector<int>> dp(2, vector<int>(m+1));

		int prev=0, cur=1;

		for(int i=0; i<n; ++i) {
			prev = cur;
			cur = (cur+1)%2;

			for(int j=0; j<m; ++j)
				if(a[i]==b[j])
					dp[cur][j+1]=dp[prev][j]+1;
				else
					dp[cur][j+1]=max(dp[prev][j+1],dp[cur][j]);
		}
/*
for(auto& v: dp) {
for(int i: v)
	cout << i << " ";
cout << endl;

}
*/
		cout << n+m-dp[cur][m] << endl;

	}
	return 0;
}
