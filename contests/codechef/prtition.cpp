#include <bits/stdc++.h>
typedef long long llong;

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;

	for(int t=0; t<T; ++t) {
		llong x,n;
		cin >> x >> n;
		llong half = n*(n+1)/2-x;
		if(half%2) {
			cout << "impossible" << endl;
			continue;
		}

		half/=2;

		string res(n,'0');
		res[x-1]='2';

		for(llong i=n; i>0; --i) {
			if(i==x) continue;

			if(i<=half && !(x<3 && i+x==half)) {
				half-=i;
				res[i-1]='1';
			}

			if(half<i) i=half+1;
		}

		cout << (half ? "impossible" : res) << endl;
	}
	return 0;
}
