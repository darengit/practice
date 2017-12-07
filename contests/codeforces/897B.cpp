#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long llong;

int main() {
	llong k,p;
	cin >> k >> p;

	llong ans = 0;
	for(llong i=1; i<=k; ++i) {
		string s1=to_string(i);
		string s2=s1;
		reverse(s2.begin(), s2.end());
		llong tmp = stoll(s1+s2);
		ans = (ans+tmp)%p;
	}

	cout << ans;
	return 0;

}
